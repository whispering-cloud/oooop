#ifndef __WIDGET__
#define __WIDGET__

#include <vector>
#include <string>
#include "shader.h"

class point {
public:
	point();
	point(int x, int y);
	point(double nx, double ny, bool polar);

	point operator+ (point from) const;
	point operator- (point from) const;
	operator glm::vec2();
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
	widget(int index, int posx, int posy, int sizex, int sizey, widget* fth = nullptr, bool relation = false);
	widget(int index, int posx, int posy, widget* fth = nullptr, bool relation = false);
	~widget();
	widget(const widget& from);
	

	widget* getFather(void) const;
	widget* getChildren(int ind) const;
	point getPosition(void) const;
	point getSize(void) const;
	unsigned int getTexture(void) const;
	operator int();

	virtual void relocate(int x, int y, int w, int h);
	virtual void relocate(point x, point y);
	virtual void revlocate(point revec);
	virtual void resize(point resec);
	widget& setColor(int cornor, glm::vec4 color);
	widget& setTexture(unsigned int tr);
	void lockedRelation(bool status);

	void deleteRecursion();
	widget& enable(bool status);

	virtual void update();
	widget* findIndex(int ind);


protected:
	int localx;
	int localy;
	int revx;
	int revy;
	bool relationmode = true;
	int height;
	int width;
	widget* father;
	int nth_child = 0;
	bool enabled = false;
	vabo renderer;
	void updateRelation();
	unsigned int chartlet = 0;
	glm::vec4 cornorColor[4];
};


class spirit : public widget {
public:
	spirit(int index, int posx, int posy, int sizex, int sizey, widget* fth = nullptr, bool relation = false, unsigned int textureID = 0);

};

class button : public widget {
public:
	button(int index, int posx, int posy, int sizex, int sizey, widget* fth = nullptr, bool relation = false, keyListen reCall = nullptr);
	~button();
	
	void relocate(int x, int y, int w, int h) override;
	void relocate(point x, point y) override;
	virtual void update() override;
	int listenerIndex;
};

class text : public widget {
public:
	text(int index, int posx, int posy, float size = 1, widget* fth = nullptr, bool relation = false, std::string message = "");
	std::string text_content;
	text& setColor(glm::vec3 color);
	text& setText(std::string);
	text& setScale(float scale);
	void update();
private:
	glm::vec3 color;
	float scale;
};


#endif // !__WIDGET__
