#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

// UART GPS
#define GPS_UART     uart1
#define GPS_BAUD     9600
#define GPS_RX_PIN   0   // Pico recebe no GPIO0 ← TX do GPS
#define GPS_TX_PIN   1   // não precisa ligar, mas configuramos

// ---- Função para converter NMEA em graus decimais ----
static double parse_latlon(const char *field, char hemi) {
    if (!field || !*field) return 0.0;
    double val = atof(field);
    int deg = (int)(val / 100);
    double min = val - deg * 100;
    double dec = deg + min / 60.0;
    if (hemi == 'S' || hemi == 'W') dec = -dec;
    return dec;
}

int main() {
    stdio_init_all();

    // Inicializa UART para GPS
    uart_init(GPS_UART, GPS_BAUD);
    gpio_set_function(GPS_RX_PIN, GPIO_FUNC_UART);
    gpio_set_function(GPS_TX_PIN, GPIO_FUNC_UART);

    char line[128];
    int idx = 0;

    while (1) {
        if (uart_is_readable(GPS_UART)) {
            char c = uart_getc(GPS_UART);

            if (c == '\n') {  // fim da frase NMEA
                line[idx] = 0;
                idx = 0;

                if (strncmp(line, "$GPRMC", 6) == 0) {
                    // Quebra a frase em campos separados por vírgula
                    char *tok;
                    char *arr[20] = {0};
                    int n = 0;
                    tok = strtok(line, ",");
                    while (tok && n < 20) {
                        arr[n++] = tok;
                        tok = strtok(NULL, ",");
                    }

                    // arr[3] = latitude, arr[4] = N/S
                    // arr[5] = longitude, arr[6] = E/W
                    if (n > 6 && arr[3] && arr[5]) {
                        double lat = parse_latlon(arr[3], arr[4][0]);
                        double lon = parse_latlon(arr[5], arr[6][0]);
                        printf("Latitude: %.6f | Longitude: %.6f\n", lat, lon);
                    }
                }
            } else {
                if (idx < 127) line[idx++] = c;
            }
        }
    }
}
