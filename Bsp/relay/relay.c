#include "relay.h"
#include "gpio.h"
void relay_on(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
			
}
void relay_off(void)
{
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);

}

