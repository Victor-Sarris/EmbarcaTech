# -*- coding: utf-8 -*-

import time
import datetime
import os
import gpiod
import gpiod_dht

# --- CONFIGURAÇÕES ---
INTERVALO_LEITURA = 60  # Em segundos
LOG_FILE_PATH = "/mnt/sdcard/datalogger.txt"

# --- CONFIGURAÇÃO DO PINO GPIO (Método Direto) ---
# Com base na documentação, usamos o chip e a linha do pino.
# GPIOA25 -> Grupo A é o chip 0. A linha é 25.
GPIO_CHIP = '/dev/gpiochip0'
GPIO_LINE = 25
SENSOR_TYPE = "DHT22"

# --- DATALOGGER ---
def main():
    print("Iniciando Datalogger com método direto (gpiod).")
    print(f"Dados serão salvos em: {LOG_FILE_PATH}")
    print("Pressione Ctrl+C para parar.")

    if not os.path.exists(GPIO_CHIP):
        print(f"Erro: Chip GPIO '{GPIO_CHIP}' não encontrado.")
        return

    while True:
        try:
            humidity, temperature_c = gpiod_dht.read(GPIO_CHIP, GPIO_LINE, SENSOR_TYPE)
            timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

            if humidity is not None and temperature_c is not None:
                log_data = f"{timestamp} - Temperatura: {temperature_c:.1f}°C, Umidade: {humidity:.1f}%"
                print(log_data)

                os.makedirs(os.path.dirname(LOG_FILE_PATH), exist_ok=True)
                
                with open(LOG_FILE_PATH, "a") as log_file:
                    log_file.write(log_data + "\n")
            else:
                print(f"{timestamp} - Falha ao ler o sensor. Verifique a conexão.")

            time.sleep(INTERVALO_LEITURA)

        except RuntimeError as error:
            print(f"{datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')} - Erro de leitura: {error}")
            time.sleep(5)
        except KeyboardInterrupt:
            print("\nPrograma interrompido.")
            break
        except Exception as e:
            print(f"Um erro inesperado ocorreu: {e}")
            break

if __name__ == "__main__":
    main()