#include <sfc/periphery/gpio.h>
#include <stm32f1xx_hal.h>

extern sfc_gpio_port_t* stm32_gpio_port_open(GPIO_TypeDef *);
sfc_gpio_pin_t led_pin = {0};
sfc_gpio_pin_t btn_pin = {0};

void sfc_board_init()
{
    HAL_Init();

    sfc_gpio_port_t *gpioChip = stm32_gpio_port_open(GPIOC);
    sfc_gpio_assign_port(SFC_GPIO_CORE_3, gpioChip);
    sfc_gpio_pin_config_t pinCfg = {SFC_GPIO_PIN_DIR_OUT, SFC_GPIO_PIN_PULL_NONE};
    sfc_gpio_init_pin(gpioChip, 13, &pinCfg, &led_pin);

    gpioChip = stm32_gpio_port_open(GPIOB);
    sfc_gpio_assign_port(SFC_GPIO_CORE_2, gpioChip);
    pinCfg.dir = SFC_GPIO_PIN_DIR_IN;
    pinCfg.pull = SFC_GPIO_PIN_PULL_UP;
    sfc_gpio_init_pin(gpioChip, 0, &pinCfg, &btn_pin);
}
