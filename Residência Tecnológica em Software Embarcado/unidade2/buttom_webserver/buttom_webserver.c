#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "pico/cyw43_arch.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "lwip/netif.h"

// Configurações de Wi-Fi
#define WIFI_SSID "MEGALINK+_0923"
#define WIFI_PASSWORD "sarris2005"

// Definição dos pinos dos botões
#define BUTTON_A_PIN 5
#define BUTTON_B_PIN 6

// Variáveis globais
volatile bool button_a_status = false;
volatile bool button_b_status = false;
float temperature = 0.0f;

// Função para ler botões e sensor
void read_inputs() {
    button_a_status = !gpio_get(BUTTON_A_PIN); // Invertido devido ao pull-up
    button_b_status = !gpio_get(BUTTON_B_PIN);
    
    // Leitura da temperatura
    adc_select_input(4);
    uint16_t raw_value = adc_read();
    const float conversion_factor = 3.3f / (1 << 12);
    temperature = 27.0f - ((raw_value * conversion_factor) - 0.706f) / 0.001721f;
}

// Função de callback para requisições HTTP
static err_t tcp_server_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    if (!p) {
        tcp_close(tpcb);
        tcp_recv(tpcb, NULL);
        return ERR_OK;
    }

    read_inputs(); // Atualiza os dados

    char response[1024];
    snprintf(response, sizeof(response),
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<!DOCTYPE html>"
        "<html lang='pt-BR'>"
        "<head>"
        "<meta charset='UTF-8'>"
        "<title>Status do Pico</title>"
        "<style>"
        "body { background-color: #d0e8f2; font-family: Arial; text-align: center; padding: 40px; }"
        ".container { border: 2px solid #333; padding: 20px; border-radius: 10px; display: inline-block; background: #fff; }"
        "h1 { color: #003366; }"
        "p { font-size: 20px; }"
        ".status { font-weight: bold; color: green; }"
        "</style>"
        "</head>"
        "<body>"
        "<div class='container'>"
        "<h1>Status do Raspberry Pi Pico</h1>"
        "<p>Botão A: <span class='status'>%s</span></p>"
        "<p>Botão B: <span class='status'>%s</span></p>"
        "<p>Temperatura: <span class='status'>%.2f °C</span></p>"
        "</div>"
        "</body></html>",
        button_a_status ? "Pressionado" : "Solto",
        button_b_status ? "Pressionado" : "Solto",
        temperature
    );

    tcp_write(tpcb, response, strlen(response), TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);

    pbuf_free(p);
    return ERR_OK;
}


// Callback para aceitar conexões
static err_t tcp_server_accept(void *arg, struct tcp_pcb *newpcb, err_t err) {
    tcp_recv(newpcb, tcp_server_recv);
    return ERR_OK;
}

int main() {
    stdio_init_all();

    // Configura botões como entrada com pull-up
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);

    // Inicializa ADC para temperatura
    adc_init();
    adc_set_temp_sensor_enabled(true);

    // Conexão Wi-Fi
    if (cyw43_arch_init()) {
        printf("Falha ao inicializar Wi-Fi\n");
        return -1;
    }
    
    cyw43_arch_enable_sta_mode();
    printf("Conectando ao Wi-Fi...\n");
    
    while (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 20000)) {
        printf("Falha ao conectar. Tentando novamente...\n");
        sleep_ms(1000);
    }
    printf("Conectado!\n");

    // Mostra IP atribuído
    if (netif_default) {
        printf("IP: %s\n", ipaddr_ntoa(&netif_default->ip_addr));
    }

    // Configura servidor TCP na porta 80
    struct tcp_pcb *server = tcp_new();
    if (!server) {
        printf("Erro ao criar servidor\n");
        return -1;
    }

    if (tcp_bind(server, IP_ADDR_ANY, 80) != ERR_OK) {
        printf("Erro ao vincular porta 80\n");
        return -1;
    }

    server = tcp_listen(server);
    tcp_accept(server, tcp_server_accept);
    printf("Servidor pronto!\n");

    while (true) {
        cyw43_arch_poll();
        sleep_ms(100);
    }

    cyw43_arch_deinit();
    return 0;
}