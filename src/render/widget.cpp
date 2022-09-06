#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../usrs.h"


widget::widget(int posx, int posy, int sizex, int sizey) {
	localx = posx;
	localy = posy;
	width = sizex;
	height = sizey;
}
void widget::relocate(int x, int y) {
	localx = x;
	localy = y;
	return;
};

widget::~widget() {
	return;
}