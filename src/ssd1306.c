#include <libopencm3/stm32/i2c.h>
#include <ssd1306.h>
#include <stdbool.h>
#include <stdint.h>

void ssd1306_send_address(uint32_t i2c, uint8_t address) {
  uint32_t reg32 __attribute__((unused));

  i2c_send_7bit_address(i2c, address, I2C_WRITE);
  while (!(I2C_SR1(i2c) & I2C_SR1_ADDR))
    ;

  reg32 = I2C_SR2(i2c);
}

void ssd1306_send_data(uint32_t i2c, uint8_t data) {
  i2c_send_data(i2c, data);
  while (!(I2C_SR1(i2c) & I2C_SR1_TxE))
    ;
}

void ssd1306_send_control_command(uint32_t i2c, bool last) {
  ssd1306_send_data(i2c, 0x00 | (last ? 0x00 : 0x80));
}

void ssd1306_send_control_data(uint32_t i2c, bool last) {
  ssd1306_send_data(i2c, 0x40 | (last ? 0x00 : 0x80));
}

void ssd1306_set_contrast_control(uint32_t i2c, uint8_t contrast) {
  ssd1306_send_data(i2c, SSD1306_SET_CONTRAST_CONTROL);
  ssd1306_send_data(i2c, contrast);
}

void ssd1306_entire_display_on(uint32_t i2c) {
  ssd1306_send_data(i2c, SSD1306_ENTIRE_DISPLAY_ON);
}

void ssd1306_entire_display_on_ram(uint32_t i2c) {
  ssd1306_send_data(i2c, SSD1306_ENTIRE_DISPLAY_ON_RAM);
}

void ssd1306_set_display_normal(uint32_t i2c) {
  ssd1306_send_data(i2c, SSD1306_SET_DISPLAY_NORMAL);
}

void ssd1306_set_display_inverted(uint32_t i2c) {
  ssd1306_send_data(i2c, SSD1306_SET_DISPLAY_INVERTED);
}

void ssd1306_set_display_on(uint32_t i2c) {
  ssd1306_send_data(i2c, SSD1306_DISPLAY_ON);
}

void ssd1306_set_display_off(uint32_t i2c) {
  ssd1306_send_data(i2c, SSD1306_DISPLAY_OFF);
}

void ssd1306_setup_continuous_horizontal_scroll(uint32_t i2c, bool scroll_left,
                                                uint8_t start_page,
                                                uint8_t scroll_interval,
                                                uint8_t end_page) {
  ssd1306_send_data(i2c, scroll_left
                             ? SSD1306_SETUP_CONTINUOUS_HORIZONTAL_SCROLL_LEFT
                             : SSD1306_SETUP_CONTINUOUS_HORIZONTAL_SCROLL);
  ssd1306_send_data(i2c, 0);
  ssd1306_send_data(i2c, start_page);
  ssd1306_send_data(i2c, scroll_interval);
  ssd1306_send_data(i2c, end_page);
  ssd1306_send_data(i2c, 0x00);
  ssd1306_send_data(i2c, 0xFF);
}

void ssd1306_setup_continuous_vertical_and_horizontal_scroll(
    uint32_t i2c, bool scroll_left, uint8_t start_page, uint8_t scroll_interval,
    uint8_t end_page, uint8_t vertical_scroll_offset) {
  ssd1306_send_data(
      i2c, scroll_left
               ? SSD1306_SETUP_CONTINUOUS_VERTICAL_HORIZONTAL_SCROLL_LEFT
               : SSD1306_SETUP_CONTINUOUS_VERTICAL_HORIZONTAL_SCROLL);
  ssd1306_send_data(i2c, 0);
  ssd1306_send_data(i2c, start_page);
  ssd1306_send_data(i2c, scroll_interval);
  ssd1306_send_data(i2c, end_page);
  ssd1306_send_data(i2c, vertical_scroll_offset);
}

void ssd1306_deactivate_scroll(uint32_t i2c) {
  ssd1306_send_data(i2c, SSD1306_DEACTIVATE_SCROLL);
}

void ssd1306_activate_scroll(uint32_t i2c) {
  ssd1306_send_data(i2c, SSD1306_ACTIVATE_SCROLL);
}

void ssd1306_set_vertical_scroll_area(uint32_t i2c, uint8_t top_rows,
                                      uint8_t rows) {
  ssd1306_send_data(i2c, SSD1306_SET_VERTICAL_SCROLL_AREA);
  ssd1306_send_data(i2c, top_rows);
  ssd1306_send_data(i2c, rows);
}

void ssd1306_set_lower_column_start_address(uint32_t i2c, uint8_t nibble) {
  ssd1306_send_data(i2c, SSD1306_SET_LOWER_COLUMN_START_ADDRESS | nibble);
}

void ssd1306_set_higher_column_start_address(uint32_t i2c, uint8_t nibble) {
  ssd1306_send_data(i2c, SSD1306_SET_HIGHER_COLUMN_START_ADDRESS | nibble);
}

void ssd1306_set_memory_addressing_mode(
    uint32_t i2c, ssd1306_addressing_mode_t addressing_mode) {
  ssd1306_send_data(i2c, SSD1306_SET_ADDRESSING_MODE);
  ssd1306_send_data(i2c, (uint8_t)addressing_mode);
}

void ssd1306_set_column_address(uint32_t i2c, uint8_t column_start,
                                uint8_t column_end) {
  ssd1306_send_data(i2c, SSD1306_SET_COLUMN_MODE);
  ssd1306_send_data(i2c, column_start);
  ssd1306_send_data(i2c, column_end);
}

void ssd1306_set_page_address(uint32_t i2c, uint8_t page_start,
                              uint8_t page_end) {
  ssd1306_send_data(i2c, SSD1306_SET_PAGE_ADDRESS);
  ssd1306_send_data(i2c, page_start);
  ssd1306_send_data(i2c, page_end);
}

void ssd1306_set_page_start_address(uint32_t i2c, uint8_t page_start) {
  ssd1306_send_data(i2c, SSD1306_SET_PAGE_START_ADDRESS | page_start);
}

void ssd1306_set_display_start_line(uint32_t i2c, uint8_t value) {
  ssd1306_send_data(i2c, SSD1306_SET_DISPLAY_START_LINE | value);
}

void ssd1306_set_segment_remap(uint32_t i2c, bool remap) {
  ssd1306_send_data(i2c, SSD1306_SET_SEGMENT_REMAP | (remap ? 1 : 0));
}

void ssd1306_set_multiplex_ratio(uint32_t i2c, uint8_t ratio) {
  ssd1306_send_data(i2c, SSD1306_SET_MULTIPLEX_RATIO);
  ssd1306_send_data(i2c, ratio);
}

void ssd1306_set_com_output_scan_direction(uint32_t i2c, bool remapped) {
  ssd1306_send_data(i2c, SSD1306_SET_COM_OUTPUT_SCAN_DIRECTION |
                             (remapped ? 0b0001000 : 0));
}

void ssd1306_set_display_offset(uint32_t i2c, uint8_t offset) {
  ssd1306_send_data(i2c, SSD1306_SET_DISPLAY_OFFSET);
  ssd1306_send_data(i2c, offset);
}

void ssd1306_set_com_pins_hardware_configuration(uint32_t i2c, bool alternative,
                                                 bool remap_enabled) {
  uint8_t pin_config_bit = alternative ? 0b00010000 : 0;
  uint8_t remap_bit = remap_enabled ? 0b00100000 : 0;

  ssd1306_send_data(i2c, SSD1306_SET_COM_PINS_HARDWARE_CONFIGURATION);
  ssd1306_send_data(i2c, 0b00000010 | pin_config_bit | remap_bit);
}

void ssd1306_set_display_clock_and_oscillator_freq(uint32_t i2c,
                                                   uint8_t divide_ratio,
                                                   uint8_t oscillator_freq) {
  ssd1306_send_data(i2c, SSD1306_SET_DISPLAY_CLOCK_AND_OSCILLATOR_FREQ);
  ssd1306_send_data(i2c, divide_ratio | (oscillator_freq << 4));
}

void ssd1306_set_precharge_period(uint32_t i2c, uint8_t phase_1,
                                  uint8_t phase_2) {
  ssd1306_send_data(i2c, SSD1306_SET_PRECHARGE_PERIOD);
  ssd1306_send_data(i2c, phase_1 | (phase_2 << 4));
}

void ssd1306_set_v_comh_deselect_level(uint32_t i2c,
                                       ssd1306_vcomh_deselect_level_t level) {
  ssd1306_send_data(i2c, SSD1306_SET_V_COMH_DESELECT_LEVEL);
  ssd1306_send_data(i2c, (uint8_t)level);
}

void ssd1306_enable_charge_pump(uint32_t i2c) {
  ssd1306_send_data(i2c, SSD1306_SET_CHARGE_PUMP);
  ssd1306_send_data(i2c, 0b00010100);
}

void ssd1306_disable_charge_pump(uint32_t i2c) {
  ssd1306_send_data(i2c, SSD1306_SET_CHARGE_PUMP);
  ssd1306_send_data(i2c, 0b00010000);
}

void ssd1306_init(uint32_t i2c) {
  i2c_send_start(i2c);

  while (!((I2C_SR1(i2c) & I2C_SR1_SB) &
           (I2C_SR2(i2c) & (I2C_SR2_MSL | I2C_SR2_BUSY))))
    ;

  ssd1306_send_address(i2c, SSD1306_DEFAULT_ADDRESS);

  ssd1306_send_control_command(i2c, true);

  ssd1306_set_display_off(i2c);
  ssd1306_set_multiplex_ratio(i2c, 63); // device takes ratio - 1
  ssd1306_set_display_offset(i2c, 0);
  ssd1306_set_display_start_line(i2c, 0);
  ssd1306_set_segment_remap(i2c, true);
  ssd1306_set_com_output_scan_direction(i2c, true);
  ssd1306_set_com_pins_hardware_configuration(i2c, true, false);
  ssd1306_set_contrast_control(i2c, 0xc4);
  ssd1306_entire_display_on_ram(i2c);
  ssd1306_set_display_normal(i2c);
  ssd1306_set_display_clock_and_oscillator_freq(i2c, 0, 8);
  ssd1306_set_memory_addressing_mode(i2c, SSD1306_ADDRESSING_MODE_HORIZONTAL);
  ssd1306_enable_charge_pump(i2c);
  ssd1306_set_display_on(i2c);

  // ssd1306_set_precharge_period(i2c, 1, 15);
  // ssd1306_set_v_comh_deselect_level(i2c,
  // SSD1306_VCOMH_DESELECT_LEVEL_077_VCC);

  while (!(I2C_SR1(i2c) & I2C_SR1_BTF))
    ;

  i2c_send_stop(i2c);
}
