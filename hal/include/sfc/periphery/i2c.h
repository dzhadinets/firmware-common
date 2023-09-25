#if !defined SOFTEQ_FW_COMMON_PERIPHERY_I2C_H_
#define SOFTEQ_FW_COMMON_PERIPHERY_I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

struct i2c_bus_vtable_t
{
    int (*open)(i2c_bus *);
    int (*close)(i2c_bus *);
};

// particular port
struct i2c_bus {
    struct module *owner;
    struct i2c_bus_vtable_t vtable;
    void *iface_data;
};

// PSP particular drver implementation
struct i2c_driver_iface {
  unsigned int class;
  int (* attach_driver) (struct i2c_driver *);

  int (* remove) (struct i2c_client *);
  int (* probe_new) (struct i2c_client *);
  void (* shutdown) (struct i2c_client *);
  void (* alert) (struct i2c_client *, enum i2c_alert_protocol protocol, unsigned int data);
  int (* command) (struct i2c_client *client, unsigned int cmd, void *arg);
  struct device_driver driver;

  int (* detect) (struct i2c_client *, struct i2c_board_info *);
  const unsigned short * address_list;
  struct list_head clients;
  bool disable_i2c_core_irq_mapping;
};


/**
 * @brief I2C initialization parameters
 */
typedef struct{
    i2c_mode_t mode;     /*!< I2C mode */
    gpio_conf_t sda;
    gpio_conf_t scl;

    union {
        struct {
            uint32_t clk_speed;      /*!< I2C clock frequency for master mode, (no higher than 1MHz for now) */
        } master;                    /*!< I2C master config */
        struct {
            uint8_t addr_10bit_en;   /*!< I2C 10bit address mode enable for slave mode */
            uint16_t slave_addr;     /*!< I2C address for slave mode */
            uint32_t maximum_speed;  /*!< I2C expected clock speed from SCL. */
        } slave;                     /*!< I2C slave config */
    };
    uint32_t clk_flags;              /*!< Bitwise of ``I2C_SCLK_SRC_FLAG_**FOR_DFS**`` for clk source choice*/
} i2c_config_t;


// i2c device on wire or this slave device
struct i2c_client {
  unsigned short flags;
  unsigned short addr;
//  char name;
  struct i2c_driver * driver;
//  struct device dev;
//  int irq;
//  struct list_head detected;
#if IS_ENABLED(CONFIG_I2C_SLAVE
  i2c_slave_cb_t slave_cb;
#endif
};

void i2c_lock_bus(struct i2c_adapter * adapter, unsigned int flags)
int i2c_trylock_bus(struct i2c_adapter * adapter, unsigned int flags)
void i2c_unlock_bus(struct i2c_adapter * adapter, unsigned int flags)

struct i2c_client * i2c_new_device(struct i2c_adapter * adap, struct i2c_board_info const * info)
void i2c_unregister_device(struct i2c_client * client)
struct i2c_client * i2c_new_dummy(struct i2c_adapter * adapter, u16 address)

int i2c_add_adapter(struct i2c_adapter * adapter)
void i2c_del_adapter(struct i2c_adapter * adap)

int i2c_transfer(struct i2c_adapter * adap, struct i2c_msg * msgs, int num)
int i2c_master_send(const struct i2c_client * client, const char * buf, int count)
int i2c_master_recv(const struct i2c_client * client, char * buf, int count)

#ifdef __cplusplus
}
#endif

#endif //!defined SOFTEQ_FW_COMMON_PERIPHERY_I2C_H_
