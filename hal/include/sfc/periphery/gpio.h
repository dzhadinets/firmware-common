#if !defined SOFTEQ_FW_COMMON_PERIPHERY_GPIO_H_
#define SOFTEQ_FW_COMMON_PERIPHERY_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

typedef enum
{
    SFC_GPIO_CORE_1 = 0,
    SFC_GPIO_CORE_2,
    SFC_GPIO_CORE_3,
    SFC_GPIO_CORE_4,
    SFC_GPIO_CORE_5,
    SFC_GPIO_CORE_6,
    SFC_GPIO_CORE_7,
    SFC_GPIO_CORE_8,
    SFC_GPIO_CORE_LAST,
} sfc_gpio_core_t;

typedef enum
{
    SFC_GPIO_PIN_STATE_LOW = 0,
    SFC_GPIO_PIN_STATE_HIGH,
    SFC_GPIO_PIN_STATE_LAST
} sfc_gpio_pin_state_t;

typedef enum
{
    SFC_GPIO_PIN_DIR_IN = 0,
    SFC_GPIO_PIN_DIR_OUT,
    SFC_GPIO_PIN_DIR_ANALOG
} sfc_gpio_pin_dir_t;

typedef enum
{
    SFC_GPIO_PIN_PULL_NONE = 0,
    SFC_GPIO_PIN_PULL_UP,
    SFC_GPIO_PIN_PULL_DOWN,
} sfc_gpio_pin_pull_t;

typedef enum
{
    SFC_GPIO_SPEED_LOW = 0,
    SFC_GPIO_SPEED_MEDIUM,
    SFC_GPIO_SPEED_HIGH,
} sfc_gpio_pin_speed_t;

typedef struct
{
    sfc_gpio_pin_dir_t dir;
    sfc_gpio_pin_pull_t pull;
    sfc_gpio_pin_speed_t speed;
} sfc_gpio_pin_config_t;

///////////////////////////////////////////////////////////////////////////////////
struct sfc_gpio_ops_t;

typedef struct
{
    void *priv;
    struct sfc_gpio_ops_t *ops;
} sfc_gpio_port_t;

typedef struct sfc_gpio_ops_t
{
    void (*set)(const sfc_gpio_port_t*, uint32_t, sfc_gpio_pin_state_t);
    sfc_gpio_pin_state_t (*get)(const sfc_gpio_port_t*, uint32_t);
    void (*cfg)(const sfc_gpio_port_t*, const sfc_gpio_pin_config_t*, uint32_t);
} sfc_gpio_ops_t;

typedef struct
{
    sfc_gpio_port_t* port;
    uint32_t pin;
} sfc_gpio_pin_t;

typedef void (*sfc_gpio_interrupt_fn)(const sfc_gpio_pin_t*);

int sfc_gpio_assign_port(sfc_gpio_core_t core, sfc_gpio_port_t* port);
//disable??
int sfc_gpio_init_pin(sfc_gpio_port_t* port, uint32_t pin_index, const sfc_gpio_pin_config_t* cfg, sfc_gpio_pin_t* pin);
void sfc_gpio_set(const sfc_gpio_pin_t* pin, sfc_gpio_pin_state_t val);
sfc_gpio_pin_state_t sfc_gpio_get(sfc_gpio_pin_t* pin);
void sfc_gpio_setup(sfc_gpio_pin_t* pin, const sfc_gpio_pin_config_t* cfg);
void sfc_gpio_set_irq_handler(sfc_gpio_pin_t* pin, const sfc_gpio_interrupt_fn fn);

#ifdef __cplusplus
}
#endif

#endif //!defined SOFTEQ_FW_COMMON_PERIPHERY_GPIO_H_
