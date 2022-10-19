#ifndef __WINDOW__
#define __WINDOW__
#include "widget.h"

class window {
public:
	int genWindow();
	void loopRender();
	void setSize(int x, int y);
	widget* rootRender;
	std::vector<unsigned int> delvao;
	std::vector<unsigned int> delvbo;
private:
	int height;
	int width;

};


#endif