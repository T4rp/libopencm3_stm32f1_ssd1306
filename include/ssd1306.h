#ifndef SSD1306_I2C_H
#define SSD1306_I2C_H

#include <stdbool.h>
#include <stdint.h>

#define SSD1306_DEFAULT_ADDRESS 0x3C

void ssd1306_send_address(uint32_t i2c, uint8_t address);
void ssd1306_send_data(uint32_t i2c, uint8_t data);
void ssd1306_send_control(uint32_t i2c);
void ssd1306_init(uint32_t i2c);

// fundemental commands
#define SSD1306_SET_CONTRAST_CONTROL 0x81
#define SSD1306_ENTIRE_DISPLAY_ON 0xA5
#define SSD1306_ENTIRE_DISPLAY_ON_RAM 0xA4
#define SSD1306_SET_DISPLAY_NORMAL 0xA6
#define SSD1306_SET_DISPLAY_INVERTED 0xA7
#define SSD1306_DISPLAY_ON 0xAF
#define SSD1306_DISPLAY_OFF 0xAE

void ssd1306_set_contrast_control(uint32_t i2c, uint8_t contrast);
void ssd1306_entire_display_on(uint32_t i2c);
void ssd1306_entire_display_on_ram(uint32_t i2c);
void ssd1306_set_display_normal(uint32_t i2c);
void ssd1306_set_display_inverted(uint32_t i2c);
void ssd1306_set_display_on(uint32_t i2c);
void ssd1306_set_display_off(uint32_t i2c);

// scrolling commands
#define SSD1306_SETUP_CONTINUOUS_HORIZONTAL_SCROLL 0x26
#define SSD1306_SETUP_CONTINUOUS_HORIZONTAL_SCROLL_LEFT 0x27
#define SSD1306_SETUP_CONTINUOUS_VERTICAL_HORIZONTAL_SCROLL 0x29
#define SSD1306_SETUP_CONTINUOUS_VERTICAL_HORIZONTAL_SCROLL_LEFT 0x2A
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3

void ssd1306_setup_continuous_horizontal_scroll(uint32_t i2c, bool scroll_left,
                                                uint8_t start_page,
                                                uint8_t scroll_interval,
                                                uint8_t end_page);

void ssd1306_setup_continuous_vertical_and_horizontal_scroll(
    uint32_t i2c, bool scroll_left, uint8_t start_page, uint8_t scroll_interval,
    uint8_t end_page, uint8_t vertical_scroll_offset);

void ssd1306_deactivate_scroll(uint32_t i2c);
void ssd1306_activate_scroll(uint32_t i2c);
void ssd1306_set_vertical_scroll_area(uint32_t i2c, uint8_t top_rows,
                                      uint8_t rows);

// address setting commands
#define SSD1306_SET_ADDRESSING_MODE 0x20
#define SSD1306_SET_COLUMN_MODE 0x21
#define SSD1306_SET_PAGE_ADDRESS 0x22
#define SSD1306_SET_HIGHER_COLUMN_START_ADDRESS 0x10
#define SSD1306_SET_PAGE_START_ADDRESS 0xB0

typedef enum {
  SSD1306_ADDRESSING_MODE_HORIZONTAL = 0,
  SSD1306_ADDRESSING_MODE_VERTICAL = 1,
  SSD1306_ADDRESSING_MODE_PAGE = 2,
} ssd1306_addressing_mode_t;

void ssd1306_set_lower_column_start_address(uint32_t i2c, uint8_t nibble);
void ssd1306_set_higher_column_start_address(uint32_t i2c, uint8_t nibble);
void ssd1306_set_memory_addressing_mode(
    uint32_t i2c, ssd1306_addressing_mode_t addressing_mode);
void ssd1306_set_column_address(uint32_t i2c, uint8_t column_start,
                                uint8_t column_end);
void ssd1306_set_page_address(uint32_t i2c, uint8_t page_start,
                              uint8_t page_end);
void ssd1306_set_page_start_address(uint32_t i2c, uint8_t page_start);

// hardware configuration commands
#define SSD1306_SET_DISPLAY_START_LINE 0x40
#define SSD1306_SET_SEGMENT_REMAP 0xA0
#define SSD1306_SET_MULTIPLEX_RATIO 0xA8
#define SSD1306_SET_COM_OUTPUT_SCAN_DIRECTION 0xC0
#define SSD1306_SET_DISPLAY_OFFSET 0xD3
#define SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION 0xDA

void ssd1306_set_display_start_line(uint32_t i2c, uint8_t value);
void ssd1306_set_segment_remap(uint32_t i2c, bool remap);
void ssd1306_set_multiplex_ratio(uint32_t i2c, uint8_t ratio);
void ssd1306_set_com_output_scan_direction(uint32_t i2c, bool remapped);
void ssd1306_set_display_offset(uint32_t i2c, uint8_t offset);
void ssd1306_set_com_pins_hardware_configuration(uint32_t i2c, bool alternative,
                                                 bool remap_enabled);

// timing and driving scheme setting commands
#define SSD1306_SET_DISPLAY_CLOCK_AND_OSCILLATOR_FREQ 0xD5
#define SSD1306_SET_PRECHARGE_PERIOD 0xD9
#define SSD1306_SET_V_COMH_DESELECT_LEVEL 0xDB
#define SSD1306_NOP 0xE3

typedef enum {
  SSD1306_VCOMH_DESELECT_LEVEL_065_VCC = 0b0001000,
  SSD1306_VCOMH_DESELECT_LEVEL_077_VCC = 0b0010000,
  SSD1306_VCOMH_DESELECT_LEVEL_083_VCC = 0b0011000,
} ssd1306_vcomh_deselect_level_t;

void ssd1306_set_display_clock_and_oscillator_freq(uint32_t i2c,
                                                   uint8_t divide_ratio,
                                                   uint8_t oscillator_freq);
void ssd1306_set_precharge_period(uint32_t i2c, uint8_t phase_1,
                                  uint8_t phase_2);
void ssd1306_set_v_comh_deselect_level(
    uint32_t i2c, ssd1306_vcomh_deselect_level_t level);
void ssd1306_send_nop(uint32_t i2c);
void ssd1306_status_register_read(uint32_t i2c);

// charge pump commands
#define SSD1306_SET_CHARGE_PUMP 0x8D

void ssd1306_enable_charge_pump(uint32_t i2c);
void ssd1306_disable_charge_pump(uint32_t i2c);

#endif
