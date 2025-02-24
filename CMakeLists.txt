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
set(PICO_BOARD pico CACHE STRING "Board type")

# Microphone_DMA/CMakeLists.txt

cmake_minimum_required(VERSION 3.13)

# Configurações padrão do projeto
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Inicializar o SDK do Raspberry Pi Pico
include(pico_sdk_import.cmake)

project(Microphone_DMA C CXX ASM)

# Inicializar o SDK
pico_sdk_init()

# Adicionar a biblioteca pico_fft como um subdiretório
add_subdirectory(pico_fft)

# Criar o executável principal
add_executable(Microphone_DMA Microphone_DMA.c inc/ssd1306_i2c.c)

# Linkar a biblioteca pico_fft ao executável
target_link_libraries(Microphone_DMA
    pico_stdlib
    pico_fft  # Linkar a biblioteca pico_fft
    hardware_i2c
)

# Configurar diretórios de inclusão
target_include_directories(Microphone_DMA PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/inc
    ${CMAKE_CURRENT_LIST_DIR}/pico_fft/src/include
)

# Configurações adicionais do Pico
pico_set_program_name(Microphone_DMA "Microphone_DMA")
pico_set_program_version(Microphone_DMA "0.1")
pico_enable_stdio_uart(Microphone_DMA 0)
pico_enable_stdio_usb(Microphone_DMA 1)
pico_add_extra_outputs(Microphone_DMA)