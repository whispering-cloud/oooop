#ifndef __WIDGET__
#define __WIDGET__

class widget {
public:
	widget(int posx, int posy, int sizex, int sizey);
	~widget();
	void relocate(int x, int y);

protected:
	int localx;
	int localy;
	int height;
	int width;

};

#endif // !__WIDGET__
