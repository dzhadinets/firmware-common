#include <sfc/periphery/gpio.h>

extern sfc_gpio_port_t* esp32_gpio_open();
sfc_gpio_pin_t led_pin = {0};
sfc_gpio_pin_t btn_pin = {0};

void sfc_board_init()
{
    sfc_gpio_port_t *gpioChip = esp32_gpio_open();
    sfc_gpio_assign_port(SFC_GPIO_CORE_1, gpioChip);
    sfc_gpio_pin_config_t pinCfg = {SFC_GPIO_PIN_DIR_OUT, SFC_GPIO_PIN_PULL_NONE};
    sfc_gpio_init_pin(gpioChip, 1, &pinCfg, &led_pin);

    pinCfg.dir = SFC_GPIO_PIN_DIR_IN;
    sfc_gpio_init_pin(gpioChip, 2, &pinCfg, &btn_pin);
}
