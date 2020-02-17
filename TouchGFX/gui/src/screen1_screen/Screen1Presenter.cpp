#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

#ifndef SIMULATOR

extern "C" {
#include <stm32f4xx_hal.h>

}
#endif

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{
}

void Screen1Presenter::activate()
{

#ifndef SIMULATOR

	model->uartInit();
	model->gpioInit(GPIOG,GPIO_PIN_6,GPIO_MODE_OUTPUT_OD);
	model->gpioInit(GPIOK,GPIO_PIN_3,GPIO_MODE_OUTPUT_OD);
	model->gpioInit(GPIOD,GPIO_PIN_4 | GPIO_PIN_5,GPIO_MODE_OUTPUT_OD);


#endif

}

void Screen1Presenter::deactivate()
{

}

#ifndef SIMULATOR

void Screen1Presenter::sendData(uint16_t * input_data, uint16_t length)
{

	model->sendDataViaUart(input_data, length);

	model->gpioSet(GPIOK, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_Delay(50);
	model->gpioSet(GPIOK, GPIO_PIN_3, GPIO_PIN_SET);
}


uint16_t Screen1Presenter::getData(uint8_t source)
{
	/*
	 * choose data source from model
	 * */
	return model->getSeconds();
}

#endif
