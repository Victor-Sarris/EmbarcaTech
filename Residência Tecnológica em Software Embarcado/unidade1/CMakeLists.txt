# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Configuração do FreeRTOS
SET(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS-Kernel)
include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

project(freertos_button C CXX ASM)
pico_sdk_init()

# Adicionar os arquivos do projeto
file(GLOB SRC_FILES *.c)
add_executable(freertos_button ${SRC_FILES})

# Configuração do programa
pico_set_program_name(freertos_button "freertos_button")
pico_set_program_version(freertos_button "0.1")

# Habilitar saída USB
pico_enable_stdio_uart(freertos_button 0)
pico_enable_stdio_usb(freertos_button 1)

# Adicionar bibliotecas necessárias
target_link_libraries(freertos_button 
    pico_stdlib 
    FreeRTOS-Kernel 
    FreeRTOS-Kernel-Heap4
    hardware_gpio  # Adicionado suporte ao GPIO
)

# Gerar arquivos finais (.uf2, .bin, etc.)
pico_add_extra_outputs(freertos_button)
