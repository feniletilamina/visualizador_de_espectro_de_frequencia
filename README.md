# Link do video
- https://www.youtube.com/shorts/CBJmNtGZdpM

# Visualizador de Espectro de Frequência

Este projeto utiliza a biblioteca: [pico_fft](https://github.com/Googool/pico_fft)

## Instalação

Para a instalação da biblioteca `pico_fft`, siga os seguintes passos:

1. Clone o repositório `pico_fft`:
bash
git clone https://github.com/Googool/pico_fft.git


2. Mova o repositório clonado para dentro da pasta visualizador_de_espectro_de_frequência:
mv pico_fft /caminho/para/visualizador_de_espectro_de_frequencia


3. Altere o arquivo CMakeLists.txt dentro da pasta pico_fft para:

```CMAKE
# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.13)

# Pull in the Pico SDK
include(pico_sdk_import.cmake)

# Set the name of the project
project(pico_fft)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Create the library target (alterado para STATIC)
add_library(${PROJECT_NAME} STATIC)

# Specify the source files for the library
target_sources(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/fft.c
    ${CMAKE_CURRENT_LIST_DIR}/src/kiss_fft.c
    ${CMAKE_CURRENT_LIST_DIR}/src/kiss_fftr.c
)

# Specify the include directories for the library
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src/include
)

# Link the necessary libraries
target_link_libraries(${PROJECT_NAME} PUBLIC
    pico_stdlib
    hardware_adc
    hardware_dma
)```
