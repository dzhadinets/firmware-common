#include <sfc/periphery/gpio.h>
#include <sfc/board.h>

extern sfc_gpio_pin_t led_pin;
extern sfc_gpio_pin_t btn_pin;

int main(void)
{
    sfc_board_init();
    while (1)
    {
        sfc_gpio_pin_state_t state = sfc_gpio_get(&btn_pin);
        sfc_gpio_set(&led_pin, state);
    }
}
