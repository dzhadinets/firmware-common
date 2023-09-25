#if !defined SOFTEQ_FW_COMMON_PERIPHERY_SPI_H_
#define SOFTEQ_FW_COMMON_PERIPHERY_SPI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sfc/periphery/spi_definitions.h>

int sfc_spi_add_master(sfc_spi_core_t id, sfc_spi_master_t* m);

sfc_spi_master_t* sfc_spi_get_master(sfc_spi_core_t id);
void sfc_spi_bus_lock(sfc_spi_master_t* m);
void sfc_spi_bus_unlock(sfc_spi_master_t* m);
void sfc_spi_xmit_raw(const sfc_spi_device_t* dev, const void *tx, void *rx, size_t size);
void sfc_spi_transfer(const sfc_spi_transfer_t *t);

#ifdef __cplusplus
}
#endif

#endif //!defined SOFTEQ_FW_COMMON_PERIPHERY_SPI_H_
