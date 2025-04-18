# FreeRTOS_Basic

## Configurando o FreeRTOS para Raspberry Pi Pico

### 1. Download e Extração do FreeRTOS
O primeiro passo é fazer o download da versão mais recente do FreeRTOS no site oficial:

[FreeRTOS Oficial](https://www.freertos.org/)

Após baixar o arquivo compactado, extraia a pasta e procure pela seguinte pasta dentro do pacote:

```
FreeRTOS-Kernel
```

### 2. Criando e Organizando o Projeto
Agora, crie um novo projeto em C para a Raspberry Pi Pico. Depois que o projeto for criado, organize a estrutura corretamente:

1. Dentro do seu projeto, crie uma pasta chamada `lib` ou `libraries` para melhor organização.
2. Mova a pasta `FreeRTOS-Kernel` para dentro da pasta `lib`.

### 3. Adicionando FreeRTOSConfig.h
Antes de configurar o restante do projeto, adicione o arquivo `FreeRTOSConfig.h` dentro do diretório do seu projeto. Esse arquivo contém as definições necessárias para a configuração do FreeRTOS.

### 4. Configurando o CMake
Agora, ajuste seu `CMakeLists.txt` com as configurações necessárias para importar o FreeRTOS. Aqui está um exemplo das partes importantes que você deve incluir:

```cmake
# Definir variável para o caminho do FreeRTOS-Kernel
SET(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS-Kernel)

# Importar o SDK da Raspberry Pi Pico (deve ser antes do projeto)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Adicionar as bibliotecas necessárias ao projeto

target_link_libraries(blinkfreertos
        pico_stdlib
        FreeRTOS-Kernel
        FreeRTOS-Kernel-Heap4
        hardware_adc
        )
```

Essas configurações permitem que o FreeRTOS funcione corretamente, garantindo que as bibliotecas sejam carregadas corretamente.

### 5. Incluindo as Bibliotecas no Projeto
No início do seu arquivo principal em C, inclua as bibliotecas necessárias:

```c
#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
```

Se precisar adicionar outras bibliotecas, faça isso após essas inclusões, sem alterar a ordem original.

Agora seu ambiente está pronto para rodar o FreeRTOS na Raspberry Pi Pico! 🚀

