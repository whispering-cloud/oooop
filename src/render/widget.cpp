#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../usrs.h"



double normalization(int x, bool isY) {
	if (isY) {
		return (double(x) / MAX_HEIGHT)*2-1;
	}
	else {
		return (double(x) / MAX_WIDTH)*2-1;
	}
}

point normalization(point xp) {
	return point((xp.x / MAX_WIDTH)*2-1, (xp.y / MAX_HEIGHT)*2-1);
}

point::point(int x, int y)
{
	this->x = x;
	this->y = y;
	nx = normalization(x, false);
	ny = normalization(y, true);
	r = sqrt(x * x + y * y);
	if (x != 0) {
		theta = atan2(y, x);
	}
	else {
		theta = 3.1415926 / 2;
	}
}

point::point(double nx, double ny, bool polar) {
	if (!polar) {
		nx *= MAX_WIDTH;
		ny *= MAX_HEIGHT;
		r = sqrt(nx * nx + ny * ny);
		if (x != 0) {
			theta = atan2(ny, nx);
		}
		else {
			theta = 3.1415926 / 2;
		}
	}
	else {
		r = nx;
		theta = ny;
	}
	x = int(r * cos(theta));
	y = int(r * sin(theta));
	this->nx = normalization(x, false);
	this->ny = normalization(y, true);
}

point point::operator+ (point& from) const {
	return point(this->x + from.x, this->y + from.y);
}

point point::operator- (point& from) const {
	return point(this->x - from.x, this->y - from.y);
}

point::point() {}
widget:: widget() {}

widget::widget(int index,int posx, int posy, int sizex, int sizey, widget* fth) 
:id(index),localx(posx),localy(posy),width(sizex),height(sizey),father(fth)
{
	if (father != nullptr) {
		nth_child = father->children.size();
		father->children.push_back(this);
	}
}
void widget::relocate(int x, int y) {
	localx = x;
	localy = y;
	return;
};

widget::~widget() {
	if (father != nullptr) {
		father->children[nth_child] = nullptr;
	}
	for (re i = 0; i < children.size(); i++) {
		if (children[i] != nullptr) {
			children[i]->father = nullptr;
		}
		
	}
}

void widget::deleteRecursion() {
	for (re i = 0; i < children.size(); i++) {
		if (children[i] != nullptr) {
			children[i]->deleteRecursion();
		}
	}
	std::cout << "Deleted: " << this->id << std::endl;
	delete this;
}

widget::widget(const widget& from) {
	id = from.id;
	localx = from.localx;
	localy = from.localy;
	width = from.width;
	height = from.height;
	father = from.father;
	if (father != nullptr) {
		nth_child = father->children.size();
		father->children.push_back(this);
	}
}

widget* widget::getFather() const {
	return father;
}

point widget::getPosition(void){
	return point(localx, localy);
}

widget::operator int()
{
	return this->id;
}

spirit::spirit(int index, int posx, int posy, int sizex, int sizey, widget* fth, int textureID)
{
	id = index;
	localx = posx;
	localy = posy;
	width = sizex;
	height = sizey;
	father = fth;
	if (father != nullptr) {
		nth_child = father->children.size();
		father->children.push_back(this);
	}
	
}


