#include <sfc/periphery/gpio.h>
#include <stm32f1xx_hal.h>

extern sfc_gpio_port_t* stm32_gpio_port_open(GPIO_TypeDef *);
sfc_gpio_pin_t led_pin = {0};
sfc_gpio_pin_t btn_pin = {0};

// TODO: need right place for this method
void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

//TODO: need a frequencies tree builder
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

void sfc_board_init()
{
    HAL_Init();

    sfc_gpio_port_t *gpioPort = stm32_gpio_port_open(GPIOA);
    sfc_gpio_assign_port(SFC_GPIO_CORE_1, gpioPort);
    sfc_gpio_pin_config_t pinCfg = {SFC_GPIO_PIN_DIR_OUT, SFC_GPIO_PIN_PULL_NONE};
    sfc_gpio_init_pin(gpioPort, 5, &pinCfg, &led_pin);

    gpioPort = stm32_gpio_port_open(GPIOC);
    sfc_gpio_assign_port(SFC_GPIO_CORE_3, gpioPort);
    pinCfg.dir = SFC_GPIO_PIN_DIR_IN;
    pinCfg.pull = SFC_GPIO_PIN_PULL_NONE;
    sfc_gpio_init_pin(gpioPort, 13, &pinCfg, &btn_pin);
}

// TODO: need right place for this method
void HAL_MspInit(void)
{
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG();
}

