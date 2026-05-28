#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/i2c.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/usart.h>
#include <ssd1306.h>
#include <stdio.h>

extern void initialise_monitor_handles(void);

void setup_i2c() {
  rcc_periph_clock_enable(RCC_I2C1);
  gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_10_MHZ, GPIO_CNF_OUTPUT_ALTFN_OPENDRAIN,
                GPIO_I2C1_SCL | GPIO_I2C1_SDA);

  i2c_peripheral_disable(I2C1);

  i2c_set_clock_frequency(I2C1, 36); // APB1 = 36 MHz

  i2c_set_standard_mode(I2C1);
  i2c_set_ccr(I2C1, 180);
  i2c_set_trise(I2C1, 37);

  i2c_peripheral_enable(I2C1);
}

void setup_gpio() {
  rcc_periph_clock_enable(RCC_GPIOB);
  rcc_periph_clock_enable(RCC_GPIOC);
  gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL,
                GPIO13);
}

void entire_display_on() {
  i2c_send_start(I2C1);

  while (!((I2C_SR1(I2C1) & I2C_SR1_SB) &
           (I2C_SR2(I2C1) & (I2C_SR2_MSL | I2C_SR2_BUSY))))
    ;

  ssd1306_send_address(I2C1, SSD1306_DEFAULT_ADDRESS);
  ssd1306_send_control_command(I2C1, false);
  ssd1306_entire_display_on(I2C1);

  while (!(I2C_SR1(I2C1) & I2C_SR1_BTF))
    ;

  i2c_send_stop(I2C1);
}

int main() {
  initialise_monitor_handles();
  rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE16_72MHZ]);

  setup_gpio();
  setup_i2c();

  gpio_set(GPIOC, GPIO13);

  ssd1306_init(I2C1);
  entire_display_on();

  while (1) {
    for (int i = 0; i < 200000; i++) {
      __asm__("nop");
    }
    printf("test\n");
  }

  return 0;
}
