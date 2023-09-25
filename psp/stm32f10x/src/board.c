#include <sfc/board.h>
#include <stm32f1xx_hal.h>

__weak void sfc_board_init(void)
{
    HAL_Init();
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
