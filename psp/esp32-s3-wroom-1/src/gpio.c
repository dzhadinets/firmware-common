#include <sfc/periphery/gpio.h>

#include "driver/gpio.h"
#include "sdkconfig.h"

typedef struct
{
    sfc_gpio_port_t dev;
} esp_gpio_t;

static void set(const sfc_gpio_port_t *port, uint32_t pin, sfc_gpio_pin_state_t state);
static sfc_gpio_pin_state_t get(const sfc_gpio_port_t *port, uint32_t pin);
static void cfg(const sfc_gpio_port_t *port, const sfc_gpio_pin_config_t* cfg, uint32_t pin);

static sfc_gpio_ops_t ops =
{
    .set = set,
    .get = get,
    .cfg = cfg,
};

static esp_gpio_t gpios[] =
{
    {
        .dev = {.ops = &ops,},
    },
};

sfc_gpio_port_t* esp32_gpio_open()
{
    return (sfc_gpio_port_t *)&gpios[0];
}

void set(const sfc_gpio_port_t *port, uint32_t pin, sfc_gpio_pin_state_t state)
{
    gpio_set_level(pin, state == SFC_GPIO_PIN_STATE_LOW  ? 0 : 1);
}

sfc_gpio_pin_state_t get(const sfc_gpio_port_t *port, uint32_t pin)
{
    int level = gpio_get_level(pin);

    return level == 1 ? SFC_GPIO_PIN_STATE_HIGH : SFC_GPIO_PIN_STATE_LOW;
}

void cfg(const sfc_gpio_port_t *port, const sfc_gpio_pin_config_t *cfg, uint32_t pin)
{
    if (cfg->dir == SFC_GPIO_PIN_DIR_OUT)
    {
        gpio_set_direction(pin, GPIO_MODE_OUTPUT);
    }
    else
    {
       gpio_set_direction(pin, GPIO_MODE_INPUT);
    }
    if (cfg->pull == SFC_GPIO_PIN_PULL_UP)
    {
        gpio_set_pull_mode(pin, GPIO_PULLUP_ONLY);
    }
    else if (cfg->pull == SFC_GPIO_PIN_PULL_DOWN)
    {
        gpio_set_pull_mode(pin, GPIO_PULLDOWN_ONLY);
    }
    else
    {
        gpio_set_pull_mode(pin, GPIO_FLOATING);
    }
}
