#ifndef __WINDOW__
#define __WINDOW__
#include "widget.h"
#define SLEEPDELAY 10
class window {
public:
	int genWindow();
	void loopRender();
	void setSize(int x, int y);
	widget* rootRender;
	spirit* frameCanvas;
	std::vector<unsigned int> delvao;
	std::vector<unsigned int> delvbo;
private:
	int height;
	int width;
	void renderRecursion(widget* x);

};


#endif