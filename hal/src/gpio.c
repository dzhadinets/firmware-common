#include <sfc/periphery/gpio.h>

typedef struct
{
    sfc_gpio_port_t* iface;
    sfc_gpio_interrupt_fn irq;
} upper_gpio_t;

static upper_gpio_t ports[SFC_GPIO_CORE_LAST] = {0};

int sfc_gpio_assign_port(sfc_gpio_core_t id, sfc_gpio_port_t* port)
{
    if ((!port) || (id >= SFC_GPIO_CORE_LAST))
    {
        return -1;
    }

    if (ports[id].iface)
    {
        //assert . means that the port is already used by other periphery
        return -2;
    }

    ports[id].iface = port;
    port->priv = &ports[id];

    return 0;
}

int sfc_gpio_init_pin(sfc_gpio_port_t* port, uint32_t pin_index, const sfc_gpio_pin_config_t* cfg, sfc_gpio_pin_t* pin)
{
    pin->port = port;
    pin->pin = pin_index;

    sfc_gpio_setup(pin, cfg);

    return 0;
}

void sfc_gpio_set(const sfc_gpio_pin_t* pin, sfc_gpio_pin_state_t val)
{
    pin->port->ops->set(pin->port, pin->pin, val);
}

sfc_gpio_pin_state_t sfc_gpio_get(sfc_gpio_pin_t* pin)
{
    return pin->port->ops->get(pin->port, pin->pin);
}

void sfc_gpio_setup(sfc_gpio_pin_t* pin, const sfc_gpio_pin_config_t* cfg)
{
    pin->port->ops->cfg(pin->port, cfg, pin->pin);
}
