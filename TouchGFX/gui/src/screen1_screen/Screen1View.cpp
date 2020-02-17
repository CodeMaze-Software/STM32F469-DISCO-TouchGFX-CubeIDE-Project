#include <gui/screen1_screen/Screen1View.hpp>

#ifndef SIMULATOR

extern "C"{
#include "string.h"

}
#endif

Screen1View::Screen1View() {

}

void Screen1View::setupScreen() {
	Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen() {
	Screen1ViewBase::tearDownScreen();
}

void Screen1View::button1_clicked() {

	counter++;
	if (counter >= 10)
		counter = 10;

	Unicode::UnicodeChar str1[40];
	Unicode::strncpy(str1, "Up  ", Unicode::strlen(str1));

	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", counter);
	Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%s", str1);

	textArea2.invalidate();

	textArea3.invalidate();

#ifndef SIMULATOR

	presenter->sendData(str1,Unicode::strlen(str1));

#endif
}

void Screen1View::button2_clicked() {

	counter--;
	if (counter <= 0)
		counter = 0;

	Unicode::UnicodeChar str2[40];
	Unicode::strncpy(str2, "Down", Unicode::strlen(str2));

	Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%d", counter);
	Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%s", str2);

	textArea2.invalidate();

	textArea3.invalidate();

#ifndef SIMULATOR

	presenter->sendData(str2,Unicode::strlen(str2));

#endif

}

void Screen1View::handleTickEvent(){

#ifndef SIMULATOR

	ui_timer++;

	if(ui_timer > 100)
	{
		uint16_t time = presenter->getData(0);

		Unicode::snprintf(textArea4Buffer, TEXTAREA4_SIZE, "%d", time);
		textArea4.invalidate();

		ui_timer = 0;

	}
#endif
}
