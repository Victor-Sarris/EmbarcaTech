#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include <string.h>
#include "lwip/tcp.h"
#include <math.h>

// Configurações Wi-Fi
#define WIFI_SSID "MEGALINK+_0923"
#define WIFI_PASSWORD "sarris2005"

// Pinos do Joystick (BitDogLab)
#define JOYSTICK_X_PIN 26  // ADC0
#define JOYSTICK_Y_PIN 27  // ADC1
#define JOYSTICK_BUTTON_PIN 22

// Estrutura para dados do joystick
typedef struct {
    float x;
    float y;
    bool button;
    const char* direction;
} JoystickData;

JoystickData joystick;

// Função para ler joystick
void read_joystick() {
    // Leitura dos eixos X e Y (0-1.0)
    adc_select_input(0);
    joystick.x = adc_read() / 4095.0f;
    adc_select_input(1);
    joystick.y = adc_read() / 4095.0f;
    
    // Leitura do botão (ativo em LOW)
    joystick.button = !gpio_get(JOYSTICK_BUTTON_PIN);
    
    // Determina direção cardinal
    float angle = atan2f(joystick.y - 0.5f, joystick.x - 0.5f) * 180 / M_PI;
    if (angle < 0) angle += 360;
    
    if (joystick.x < 0.3 && joystick.y < 0.3) {
        joystick.direction = "Centro";
    } else if (angle >= 337.5 || angle < 22.5) {
        joystick.direction = "Leste";
    } else if (angle >= 22.5 && angle < 67.5) {
        joystick.direction = "Nordeste";
    } else if (angle >= 67.5 && angle < 112.5) {
        joystick.direction = "Norte";
    } else if (angle >= 112.5 && angle < 157.5) {
        joystick.direction = "Noroeste";
    } else if (angle >= 157.5 && angle < 202.5) {
        joystick.direction = "Oeste";
    } else if (angle >= 202.5 && angle < 247.5) {
        joystick.direction = "Sudoeste";
    } else if (angle >= 247.5 && angle < 292.5) {
        joystick.direction = "Sul";
    } else {
        joystick.direction = "Sudeste";
    }
}

// Callback para requisições HTTP
static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    if (!p) {
        tcp_close(tpcb);
        return ERR_OK;
    }

    read_joystick();
    
    char response[512];
    snprintf(response, sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "\r\n"
        "{\"joystick\":{\"x\":%.2f,\"y\":%.2f,\"button\":%d,\"direction\":\"%s\"}}",
        joystick.x, joystick.y, joystick.button, joystick.direction
    );

    tcp_write(tpcb, response, strlen(response), TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);
    pbuf_free(p);
    return ERR_OK;
}

static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err) {
    tcp_recv(newpcb, tcp_server_recv);
    return ERR_OK;
}

int main() {
    stdio_init_all();
    
    // Configuração do Joystick
    adc_init();
    adc_gpio_init(JOYSTICK_X_PIN);
    adc_gpio_init(JOYSTICK_Y_PIN);
    
    gpio_init(JOYSTICK_BUTTON_PIN);
    gpio_set_dir(JOYSTICK_BUTTON_PIN, GPIO_IN);
    gpio_pull_up(JOYSTICK_BUTTON_PIN);

    // Conexão Wi-Fi
    if (cyw43_arch_init()) {
        printf("Erro ao iniciar Wi-Fi\n");
        return -1;
    }
    
    cyw43_arch_enable_sta_mode();
    printf("Conectando a %s...\n", WIFI_SSID);
    
    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Falha na conexão. Tentando novamente...\n");
        sleep_ms(2000);
    }
    printf("Conectado!\n");

    // Mostra IP
    if (netif_default) {
        printf("Servidor acessível em: http://%s\n", ipaddr_ntoa(&netif_default->ip_addr));
    }

    // Configura servidor web
    struct tcp_pcb *server = tcp_new();
    tcp_bind(server, IP_ADDR_ANY, 80);
    server = tcp_listen(server);
    tcp_accept(server, tcp_server_accept);
    printf("Servidor pronto!\n");

    while (true) {
        cyw43_arch_poll();
        sleep_ms(10);
    }

    cyw43_arch_deinit();
    return 0;
}