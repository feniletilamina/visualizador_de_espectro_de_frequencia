#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/fft.h"
#include "inc/ssd1306.h"
#include "hardware/i2c.h"

#define BIN_COUNT 5

// Definição dos pinos I2C
const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

int main() {
    stdio_init_all();
    fft_setup();

    // Inicialização do I2C
    i2c_init(i2c1, ssd1306_i2c_clock * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicialização do display OLED
    ssd1306_init();

    // Configuração da área de renderização
    struct render_area frame_area = {
        .start_column = 0,
        .end_column = ssd1306_width - 1,
        .start_page = 0,
        .end_page = ssd1306_n_pages - 1
    };
    calculate_render_area_buffer_length(&frame_area);

    // Criação do buffer para o display
    uint8_t ssd[ssd1306_buffer_length];

    // Limpeza do display
    memset(ssd, 0, ssd1306_buffer_length);
    render_on_display(ssd, &frame_area);

    

    uint8_t capture_buf[SAMPLES];
    frequency_bin_t bins[BIN_COUNT] = {
        {"Subgraves", 20, 250, 0},
        {"Graves", 251, 500, 0},
        {"Médios", 501, 1500, 0},
        {"Agudos", 1501, 4000, 0},
        {"Superagudos", 4001, 22050, 0}
    };

    // Largura de cada coluna no display
    int column_width = ssd1306_width / BIN_COUNT;

    while (true) {
        // Captura e processa os dados do FFT
        fft_sample(capture_buf);
        fft_process(capture_buf, bins, BIN_COUNT);
    
        // Limpa o display
        memset(ssd, 0, ssd1306_buffer_length);
    
        // Desenha as colunas no display
        for (int i = 0; i < BIN_COUNT; i++) {
            // Ajusta a altura máxima para deixar espaço para o texto 
            int max_column_height = ssd1306_height - 8; // Reserva 8 pixels no topo
          float amplitude = sqrtf(bins[i].amplitude);
          int height = (int)((amplitude / 3.16f) * max_column_height);
            
            // Limita a altura ao novo máximo
            if (height > max_column_height) {
                height = max_column_height;
            }
    
            // Desenho da coluna 
            int x_start = i * column_width;
            int x_end = x_start + column_width - 1;
            int y_start = ssd1306_height - height; // Começa acima do texto
            int y_end = ssd1306_height - 1;
    
            for (int x = x_start; x <= x_end; x++) {
                for (int y = y_start; y <= y_end; y++) {
                    ssd1306_set_pixel(ssd, x, y, true);
                }
            }
    
            //  Adiciona o texto "F1" a "F5" no topo 
            char label[4]; // Buffer para "F1" a "F5"
            snprintf(label, sizeof(label), "F%d", i + 1);
            
            // Centraliza horizontalmente abaixo da coluna
            int text_width = strlen(label) * 8; // Cada caractere tem 8 pixels de largura
            int text_x = x_start + (column_width - text_width) / 2;
            
            // Posiciona no topo (y = 0)
            ssd1306_draw_string(ssd, text_x, 0, label); // Texto fixo no topo
        }
    
        // Renderiza o frame no display
        render_on_display(ssd, &frame_area);

        // Exibe as amplitudes no console 
        for (int i = 0; i < BIN_COUNT; i++) {
            printf("%f", bins[i].amplitude);
            if (i < BIN_COUNT - 1) {
                printf(",");
            }
        }
        printf("\n");

        // Aguarda um pouco antes de atualizar o display novamente
        sleep_ms(100);
    }

    return 0;
}