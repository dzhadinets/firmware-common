#include <sfc/periphery/gpio.h>

#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_rcc.h>
#include <stm32f1xx_hal_gpio.h>

typedef struct
{
    sfc_gpio_port_t dev;
    GPIO_TypeDef* core;
} stm32_gpio_t;

static void set(const sfc_gpio_port_t *port, uint32_t pin, sfc_gpio_pin_state_t state);
static sfc_gpio_pin_state_t get(const sfc_gpio_port_t *port, uint32_t pin);
static void cfg(const sfc_gpio_port_t *port, const sfc_gpio_pin_config_t* cfg, uint32_t pin);

static sfc_gpio_ops_t ops =
{
    .set = set,
    .get = get,
    .cfg = cfg,
};

static stm32_gpio_t gpios[] =
{
    {
        .dev = {.ops = &ops,},
        .core = GPIOA,
    },
    {
        .dev = {.ops = &ops,},
        .core = GPIOB,
    },
    {
        .dev = {.ops = &ops,},
        .core = GPIOC,
    },
    {
        .dev = {.ops = &ops,},
        .core = GPIOD,
    },
};

sfc_gpio_port_t* stm32_gpio_port_open(GPIO_TypeDef* core)
{
    int id = 0;
    for ( ;id < sizeof(gpios)/sizeof(gpios[0]);id ++)
    {
        if (gpios[id].core == core)
        {
            if (core == GPIOA)
            {
                __HAL_RCC_GPIOA_CLK_ENABLE();
            }
            else if (core == GPIOB)
            {
                __HAL_RCC_GPIOB_CLK_ENABLE();
            }
            else if (core == GPIOC)
            {
                __HAL_RCC_GPIOC_CLK_ENABLE();
            }
            else if (core == GPIOD)
            {
                __HAL_RCC_GPIOD_CLK_ENABLE();
            }

//            gpios[id].dev.id = id;
//            gpios[id].dev.priv = gpios[id];

            return (sfc_gpio_port_t *)&gpios[id];
        }
    }

    return NULL;
}

void set(const sfc_gpio_port_t *port, uint32_t pin, sfc_gpio_pin_state_t state)
{
    const stm32_gpio_t *gpio = (stm32_gpio_t*)port;

    HAL_GPIO_WritePin(gpio->core, (1 << pin), state == SFC_GPIO_PIN_STATE_LOW  ? GPIO_PIN_RESET : GPIO_PIN_SET);
}

sfc_gpio_pin_state_t get(const sfc_gpio_port_t *port, uint32_t pin)
{
    const stm32_gpio_t *gpio = (stm32_gpio_t*)port;

    GPIO_PinState state = HAL_GPIO_ReadPin(gpio->core, (1 << pin));

    return state == GPIO_PIN_SET ? SFC_GPIO_PIN_STATE_HIGH : SFC_GPIO_PIN_STATE_LOW;
}

void cfg(const sfc_gpio_port_t *port, const sfc_gpio_pin_config_t *cfg, uint32_t pin)
{
    const stm32_gpio_t *gpio = (stm32_gpio_t*)port;
    GPIO_InitTypeDef initStruct = {0};

    if (cfg->dir == SFC_GPIO_PIN_DIR_OUT)
    {
        HAL_GPIO_WritePin(gpio->core, (1 << pin), GPIO_PIN_RESET);
        initStruct.Mode = GPIO_MODE_OUTPUT_PP; //open drain????
        if (cfg->speed == SFC_GPIO_SPEED_LOW)
        {
            initStruct.Speed = GPIO_SPEED_FREQ_LOW;
        }
        else if (cfg->speed == SFC_GPIO_SPEED_MEDIUM)
        {
            initStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
        }
        else if (cfg->speed == SFC_GPIO_SPEED_HIGH)
        {
            initStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        }
    }
    else if (cfg->dir == SFC_GPIO_PIN_DIR_IN)
    {
        initStruct.Mode = GPIO_MODE_INPUT;
    }
    else
    {
        initStruct.Mode = GPIO_MODE_ANALOG;
    }

    if (cfg->pull == SFC_GPIO_PIN_PULL_UP)
    {
        initStruct.Pull = GPIO_PULLUP;
    }
    else if (cfg->pull == SFC_GPIO_PIN_PULL_DOWN)
    {
        initStruct.Pull = GPIO_PULLDOWN;
    }
    else if (cfg->pull == SFC_GPIO_PIN_PULL_NONE)
    {
        initStruct.Pull = GPIO_NOPULL;
    }

    initStruct.Pin = (1 << pin);

    HAL_GPIO_Init(gpio->core, &initStruct);
}
