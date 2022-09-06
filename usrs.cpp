#include "usrs.h"
const int tickrate = 10;

usrs* usrlib;

void usrs::usrlib_init(void)
{
	windowh = new window();
	keyputh = new keyput();
	tick_counter = 0;
	return;
}

void usrs::ticking(void) {
	// down fps
	tick_counter++;
	if (tick_counter >= tickrate) {
		tick_counter = 0;
		// tick
		if (keytable[0]) {
			glfwSetWindowShouldClose(wds, true);
			keytable[0] = 0;
		}
	}
	return;
}

usrs::~usrs() {
	delete this->windowh;
	this->windowh = nullptr;
	delete this->keyputh;
	this->keyputh = nullptr;
}