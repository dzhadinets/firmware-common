#include  <sfc/periphery/spi.h>

typedef struct uppper_spi_t
{
    sfc_spi_master_t* iface;
    //lock object must be added
} uppper_spi_t;

static uppper_spi_t masters[SFC_SPI_CORE_LAST] = {0};

int sfc_spi_assign_master(sfc_spi_core_t id, sfc_spi_master_t* master)
{
    if ((!master) || (id >= SFC_SPI_CORE_LAST))
    {
        return -1;
    }

    if (masters[id].iface)
    {
        //assert . means that the port is already used by other periphery
        return -2;
    }

    masters[id].iface = master;
    masters[id].iface->priv = &masters[id];

    return 0;
}

sfc_spi_master_t* sfc_spi_get_master(sfc_spi_core_t id)
{
    if (id >= SFC_SPI_CORE_LAST)
    {
        return NULL;
    }

    return masters[id].iface;
}

void sfc_spi_xmit_raw(const sfc_spi_device_t* dev, const void *tx, void *rx, size_t size)
{
    const auto master = dev->master;

    // master->ops->setup(master, dev->mode, dev->max_speed);
    master->ops->xmit(master, tx, rx, size);
}

void spi_transfer(const spi_transfer_t *t)
{
    const auto dev = t->dev;
    const auto master = dev->master;

    master->ops->setup(master, dev->mode, dev->max_speed);

    gpio_set(&dev->_cs, GPIO_PIN_STATE_LOW);

    master->ops->xmit(master, t->txbuf, t->rxbuf, t->size);

    gpio_set(&dev->_cs, GPIO_PIN_STATE_HIGH);
}

void spi_bus_lock(spi_master_t* m)
{

}

void spi_bus_unlock(spi_master_t* m)
{

}
