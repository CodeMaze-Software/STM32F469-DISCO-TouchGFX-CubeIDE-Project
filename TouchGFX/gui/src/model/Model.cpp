#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR

extern "C" {
#include <stm32f4xx_hal.h>
#include <stm32f4xx_hal_uart.h>

UART_HandleTypeDef huart6;
GPIO_InitTypeDef GPIO_InitStruct = { 0 };

}

#endif

Model::Model() :
		modelListener(0) {
}

void Model::tick() {


#ifndef SIMULATOR

	app_seconds++;

	static int led_tick;
	led_tick++;


	if(led_tick > 20)
	{
		led_tick = 0;
		HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
	}


#endif
}

#ifndef SIMULATOR

void Model::uartInit() {

	huart6.Instance = USART6;
	huart6.Init.BaudRate = 115200;
	huart6.Init.WordLength = UART_WORDLENGTH_8B;
	huart6.Init.StopBits = UART_STOPBITS_1;
	huart6.Init.Parity = UART_PARITY_NONE;
	huart6.Init.Mode = UART_MODE_TX_RX;
	huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart6.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart6) != HAL_OK) {

		/* do something */
	}


}

void Model::gpioInit(GPIO_TypeDef * gpio_port, uint16_t gpio_pin, uint16_t dir) {

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOK_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOJ_CLK_ENABLE();



	GPIO_InitStruct.Pin = gpio_pin;
	GPIO_InitStruct.Mode = dir;

	if(dir == GPIO_MODE_OUTPUT_OD)
		GPIO_InitStruct.Pull = GPIO_NOPULL;
	else if(dir == GPIO_MODE_INPUT)
		GPIO_InitStruct.Pull = GPIO_PULLUP;

	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(gpio_port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(gpio_port, gpio_pin, GPIO_PIN_SET);

}

void Model::gpioSet(GPIO_TypeDef * gpio_port, uint16_t gpio_pin, GPIO_PinState state)
{
	HAL_GPIO_WritePin(gpio_port, gpio_pin, state);
}

void Model::sendDataViaUart(uint16_t *input_data, uint16_t length) {

	HAL_UART_Transmit(&huart6, (uint8_t*) input_data, length, 10);

}

uint16_t Model::getSeconds()
{
	return app_seconds;
}

#endif
