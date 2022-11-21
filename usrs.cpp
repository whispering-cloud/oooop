#include <iostream>
#include "usrs.h"

unsigned int rectIndices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};
usrs* usrlib = new usrs();

void usrs::usrlib_init(void)
{
	tickrate = 10;
	windowh = new window();
	keyputh = new keyput();
	keyputh->initKey();
	tick_counter = 0;
	

	return;
}

void logPrint(std::string logText) {
	std::cout << "Log whispering19: " << logText << std::endl;
}

void logError(int errid) {
	std::cout << "ERROR whispering19: " << errid << std::endl;
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
	soundEngine->drop();
}
