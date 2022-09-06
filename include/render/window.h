#ifndef __WINDOW__
#define __WINDOW__


class window {
public:
	int genWindow();
	void loopRender();
	void setSize(int x, int y);

private:
	int height;
	int width;
};


#endif