#include <iostream>
#include "usrs.h"


usrs* usrlib = new usrs();

void closeWindow(point clickPosition) {
	glfwSetWindowShouldClose(usrlib->wds, true);
	usrlib->logPrint("CLOSED");
}

void buttonHelper(point clickPosition) {
	usrlib->keyputh->buttonHandler(usrlib->wds, clickPosition);
}

void usrs::usrlib_init(void)
{
	tickrate = 10;
	windowh = new window();
	keyputh = new keyput();
	keyputh->keyputCall = std::vector<keyListen>(128, nullptr);
	tick_counter = 0;

	keyputh->keyputCall[0] = closeWindow;
	keyputh->keyputCall[2] = buttonHelper;

	return;
}
void usrs::logPrint(std::string logText) {
	std::cout << "Log whispering19: " << logText << std::endl;
}
void usrs::ticking(void) {
	

	// down fps
	tick_counter++;
	if (tick_counter >= tickrate) {
		tick_counter = 0;
		// tick -> /10fps
	}
	return;
}

usrs::~usrs() {
	delete this->windowh;
	this->windowh = nullptr;
	delete this->keyputh;
	this->keyputh = nullptr;
}
