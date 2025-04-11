#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#define BUTTON_PIN 5
#define LED_PIN_AZ 12
#define LED_PIN_VD 11

QueueHandle_t botaoQueue;

void gpio_callback(uint gpio, uint32_t events) {
    static uint32_t ultimaTroca = 0;
    uint32_t agora = to_ms_since_boot(get_absolute_time());

    if (agora - ultimaTroca > 50) {
        bool estado = gpio_get(BUTTON_PIN);
        xQueueSendFromISR(botaoQueue, &estado, NULL);
        ultimaTroca = agora;
    }
}

void controlarLED(void *pvParameters) {
    bool botaoEstado;
    for (;;) {
        if (xQueueReceive(botaoQueue, &botaoEstado, portMAX_DELAY)) {
            gpio_put(LED_PIN_AZ, !botaoEstado);
            gpio_put(LED_PIN_VD, !botaoEstado);
        }
    }
}

void init_setup() {
    stdio_init_all();

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    gpio_init(LED_PIN_AZ);
    gpio_set_dir(LED_PIN_AZ, GPIO_OUT);
    gpio_put(LED_PIN_AZ, 0);

    gpio_init(LED_PIN_VD);
    gpio_set_dir(LED_PIN_VD, GPIO_OUT);
    gpio_put(LED_PIN_VD, 0);

    // Configura interrupção no botão para detectar mudanças
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &gpio_callback);
}

int main() {
    init_setup();

    botaoQueue = xQueueCreate(5, sizeof(bool));

    xTaskCreate(controlarLED, "controlarLED", 256, NULL, 2, NULL);

    vTaskStartScheduler();
    for (;;);
}
