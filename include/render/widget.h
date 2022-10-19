#ifndef __WIDGET__
#define __WIDGET__

#include <vector>
#include <string>
#include "shader.h"

class point {
public:
	point();
	point(int x, int y);
	point(double nx, double ny, bool polar = false);

	point operator+ (point& from) const;
	point operator- (point& from) const;

	int x, y;
	double nx, ny;
	double r, theta;

};

typedef void (*keyListen)(point clickPosition);


class widget {
friend double normalization(int x, bool isY);
friend point normalization(point* xp);
public:
	int id;
	std::vector<widget*> children;

	//widget();
	widget(int index, int posx, int posy, int sizex, int sizey, widget* fth = nullptr);
	~widget();
	widget(const widget& from);
	

	widget* getFather() const;
	point getPosition(void);

	operator int();

	void relocate(int x, int y);
	void deleteRecursion();
	void enable(bool status);

	virtual void update();

protected:
	int localx;
	int localy;
	int height;
	int width;
	widget* father;
	int nth_child = 0;
	bool enabled;
	vabo renderer;
};


class spirit : public widget {
public:
	spirit(int index, int posx, int posy, int sizex, int sizey, widget* fth = nullptr, int textureID = 0);
};

class button : public widget {
public:
	button(int index, int posx, int posy, int sizex, int sizey, widget* fth = nullptr, keyListen reCall = nullptr);
	~button();
	
	int listenerIndex;
};

class text : public widget {
public:
	text(int index, int posx, int posy, int sizex, int sizey, widget* fth = nullptr, std::string message = "");
	std::string text_content;
};


#endif // !__WIDGET__
