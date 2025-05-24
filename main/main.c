#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led_strip.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "driver/spi_master.h"
#include "esp_log.h"

#define LED_STRIP_GPIO    8
#define LED_STRIP_LENGTH  1
#define TAG               "MORSE"

#define LCD_HOST          SPI2_HOST
#define LCD_PIXEL_CLOCK_HZ (20 * 1000 * 1000)
#define PIN_NUM_MOSI      6
#define PIN_NUM_CLK       7
#define PIN_NUM_CS        14
#define PIN_NUM_DC        15
#define PIN_NUM_RST       21
#define LCD_H_RES         172
#define LCD_V_RES         320

led_strip_handle_t led_strip;
esp_lcd_panel_handle_t panel_handle = NULL;

void init_led_strip() {
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_STRIP_GPIO,
        .max_leds = LED_STRIP_LENGTH,
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = 10 * 1000 * 1000,
    };

    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    ESP_ERROR_CHECK(led_strip_clear(led_strip));
}



void init_lcd() {
    spi_bus_config_t buscfg = {
        .sclk_io_num = PIN_NUM_CLK,
        .mosi_io_num = PIN_NUM_MOSI,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_H_RES * 40 * 2 + 8,
    };
    ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));

    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = PIN_NUM_DC,
        .cs_gpio_num = PIN_NUM_CS,
        .pclk_hz = LCD_PIXEL_CLOCK_HZ,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .spi_mode = 0,
        .trans_queue_depth = 10,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_config, &io_handle));

    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = PIN_NUM_RST,
        .color_space = ESP_LCD_COLOR_SPACE_RGB,
        .bits_per_pixel = 16,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));
}

void blink_dot() {
    ESP_LOGI(TAG, "DOT");
    led_strip_set_pixel(led_strip, 0, 255, 255, 255);
    led_strip_refresh(led_strip);
    vTaskDelay(pdMS_TO_TICKS(200));
    led_strip_clear(led_strip);
    vTaskDelay(pdMS_TO_TICKS(200));
}

void blink_dash() {
    ESP_LOGI(TAG, "DASH");
    led_strip_set_pixel(led_strip, 0, 255, 255, 255);
    led_strip_refresh(led_strip);
    vTaskDelay(pdMS_TO_TICKS(600));
    led_strip_clear(led_strip);
    vTaskDelay(pdMS_TO_TICKS(200));
}

void blink_morse(const char *morse_code) {
    for (int i = 0; morse_code[i] != '\0'; i++) {
        if (morse_code[i] == '.') {
            blink_dot();
        } else if (morse_code[i] == '-') {
            blink_dash();
        } else if (morse_code[i] == ' ') {
            vTaskDelay(pdMS_TO_TICKS(600)); // Space between letters
        } else if (morse_code[i] == '/') {
            vTaskDelay(pdMS_TO_TICKS(1400)); // Space between words
        }
    }
}

void app_main(void) {
    init_led_strip();
    init_lcd();
    const char *morse_hello = ".... . .-.. .-.. ---";
    while (1) {
        blink_morse(morse_hello);
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}
