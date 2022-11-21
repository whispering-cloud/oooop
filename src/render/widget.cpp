#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../usrs.h"




double normalization(int x, bool isY) {
	if (isY) {
		return -((double(x) / MAX_HEIGHT)*2-1);
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
		theta = 3.1415926535897932 / 2;
	}
}

point::point(double nx, double ny, bool polar) {
	if (!polar) {
		nx /= 2;
		nx += 1;
		ny /= 2;
		ny += 1;
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

point point::operator+ (point from) const {
	return point(this->x + from.x, this->y + from.y);
}

point point::operator- (point from) const {
	return point(this->x - from.x, this->y - from.y);
}

point::operator glm::vec2() {
	return glm::vec2(x, y);
}

//widget:: widget() {}

// with renderer
widget::widget(int index, int posx, int posy, int sizex, int sizey, widget* fth, bool relation)
:id(index),width(sizex),height(sizey),father(fth)
{
	if (relation && father != nullptr) {
		localx = posx + father->getPosition().x;
		localy = posy + father->getPosition().y;
	} else {
		localx = posx;
		localy = posy;
	}
	if (father != nullptr) {
		nth_child = father->children.size();
		father->children.push_back(this);
		revx = localx - father->getPosition().x;
		revy = localy - father->getPosition().y;
	}
	point tmp(localx, localy);
	point tpp(localx + sizex, localy + sizey);
	float vertices[] = {
		// positions          // colors           // texture coords
		 tmp.nx, tmp.ny, 0.0f,   cornorColor[0].x, cornorColor[0].y, cornorColor[0].z,   0.0f, 0.0f, cornorColor[0].w, // top left
		 tmp.nx, tpp.ny, 0.0f,   cornorColor[2].x, cornorColor[2].y, cornorColor[2].z,   0.0f, 1.0f, cornorColor[2].w, // bottom left
		 tpp.nx, tpp.ny, 0.0f,   cornorColor[3].x, cornorColor[3].y, cornorColor[3].z,   1.0f, 1.0f, cornorColor[3].w, // bottom right
		 tpp.nx, tmp.ny, 0.0f,   cornorColor[1].x, cornorColor[1].y, cornorColor[1].z,   1.0f, 0.0f, cornorColor[1].w  // top right
	};
	renderer = vabo(vertices, sizeof(vertices), rectIndices, sizeof(rectIndices), 4, &usrlib->glslPrograms[0], GL_DYNAMIC_DRAW, GL_TRIANGLES, 3);
}

// no renderer
widget::widget(int index, int posx, int posy, widget* fth, bool relation)
	:id(index), width(0), height(0), father(fth)
{
	if (relation && father != nullptr) {
		localx = posx + father->getPosition().x;
		localy = posy + father->getPosition().y;
	}
	else {
		localx = posx;
		localy = posy;
	}
	if (father != nullptr) {
		nth_child = father->children.size();
		father->children.push_back(this);
		revx = localx - father->getPosition().x;
		revy = localy - father->getPosition().y;
	}
}
// relocate and update vabo
void widget::relocate(int x, int y, int w, int h) {
	localx = x;
	localy = y;
	point fatpp = (father == nullptr) ? (point(0, 0)) : (father->getPosition());
	revx = localx - fatpp.x;
	revy = localy - fatpp.y;
	width = w;
	height = h;
	for (re i = 0; i < children.size(); i++) {
		children[i]->updateRelation();
	}
	point tmp(localx, localy);
	point tpp(localx + width, localy + height);
	/*
	float vertices[] = {
		// positions          // colors           // texture coords & alpha
		 tmp.nx, tmp.ny, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f, // top right
		 tmp.nx, tpp.ny, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 1.0f, // bottom right
		 tpp.nx, tpp.ny, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f, // bottom left
		 tpp.nx, tmp.ny, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f, 1.0f  // top left 
	};
	*/
	float vertices[] = {
		// positions          // colors           // texture coords
		 tmp.nx, tmp.ny, 0.0f,   cornorColor[0].x, cornorColor[0].y, cornorColor[0].z,   0.0f, 0.0f, cornorColor[0].w, // top left
		 tmp.nx, tpp.ny, 0.0f,   cornorColor[2].x, cornorColor[2].y, cornorColor[2].z,   0.0f, 1.0f, cornorColor[2].w, // bottom left
		 tpp.nx, tpp.ny, 0.0f,   cornorColor[3].x, cornorColor[3].y, cornorColor[3].z,   1.0f, 1.0f, cornorColor[3].w, // bottom right
		 tpp.nx, tmp.ny, 0.0f,   cornorColor[1].x, cornorColor[1].y, cornorColor[1].z,   1.0f, 0.0f, cornorColor[1].w  // top right
	};
	renderer.updateBuffer(vertices, sizeof(vertices), GL_DYNAMIC_DRAW);
	return;
};

// update location by relation
void widget::updateRelation() {
	if (!relationmode) {
		relocate(getPosition(), getPosition() + getSize());
	}
	else {
		point fatpp = point(revx, revy) + ((father == nullptr) ? (point(0, 0)) : (father->getPosition()));
		relocate(fatpp, fatpp + getSize());
	}
}

void widget::relocate(point x, point y) {
	widget::relocate(x.x, x.y, y.x - x.x, y.y - x.y);
	return;
}

void widget::resize(point resec) {
	this->relocate(this->getPosition(), this->getPosition() + resec);
}

void widget::revlocate(point revec) {
	if (this->father == nullptr) {
		return;
	}
	point p1 = this->father->getPosition() + revec;
	this->relocate(p1, p1 + this->getSize());
}

widget& widget::setColor(int cornor, glm::vec4 color) {
	cornorColor[cornor] = color;
	updateRelation();
	return *this;
}

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
	enabled = from.enabled;
	revx = from.revx;
	revy = from.revy;
	renderer = from.renderer;
	if (father != nullptr) {
		nth_child = father->children.size();
		father->children.push_back(this);
	}
}

widget* widget::getFather() const {
	return father;
}

widget* widget::getChildren(int ind) const {
	if (ind >= this->children.size()) {
		logError(5);
		return (widget*)(this);
	}
	return this->children[ind];
}

point widget::getPosition(void) const {
	return point(localx, localy);
}

point widget::getSize(void) const {
	return point(width, height);
}

unsigned int widget::getTexture(void) const {
	return chartlet;
}

widget& widget::setTexture(unsigned int tr) {
	this->chartlet = tr;
	return *this;
}

widget::operator int()
{
	return this->id;
}

widget& widget::enable(bool status) {
	enabled = status;
	return *this;
}

void widget::lockedRelation(bool status) {
	relationmode = status;
}

void widget::update() {
	if (enabled) {
		renderer.render(this->chartlet);
	}
}

widget* widget::findIndex(int ind) {
	if (this->id == ind) return this;
	for (re i = 0; i < children.size(); i++) {
		widget* res = children[i]->findIndex(ind);
		if (res != nullptr) {
			return res;
		}
	}
	return nullptr;
}

spirit::spirit(int index, int posx, int posy, int sizex, int sizey, widget* fth, bool relation, unsigned int textureID)
:widget(index, posx, posy, sizex, sizey, fth, relation)
{
	glm::vec4 full = glm::vec4(1, 1, 1, 1);
	this->setColor(0, full).setColor(1, full).setColor(2, full).setColor(3, full);
	this->chartlet = textureID;
}

button::button(int index, int posx, int posy, int sizex, int sizey, widget* fth, bool relation, keyListen reCall)
:widget(index, posx, posy, sizex, sizey, fth, relation)
{
	listenerIndex = usrlib->keyputh->addListener(eventListener(point(posx, posy), point(posx + sizex, posy + sizey), reCall));
	
}

void button::update() {
	usrlib->keyputh->listenerList[this->listenerIndex].enabled = this->enabled;
	widget::update();
}

void button::relocate(int x, int y, int w, int h) {
	widget::relocate(x, y, w, h);
	usrlib->keyputh->listenerList[listenerIndex].zonex = point(x, y);
	usrlib->keyputh->listenerList[listenerIndex].zoney = point(x + w, y + h);

}

void button::relocate(point x, point y) {
	button::relocate(x.x, x.y, y.x - x.x, y.y - x.y);
}

button::~button() {
	usrlib->keyputh->listenerList[listenerIndex].buttonListener = nullptr;
}

text::text(int index, int posx, int posy, float size, widget* fth, bool relation, std::string message)
:widget(index, posx, posy, fth, relation), scale(size), text_content(message), color(0,0,0)
{
	renderer = vabo();
	glGenVertexArrays(1, &renderer.vaoid);
	glGenBuffers(1, &renderer.vboid);
	glBindVertexArray(renderer.vaoid);
	glBindBuffer(GL_ARRAY_BUFFER, renderer.vboid);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	
}


text& text::setColor(glm::vec3 color) {
	this->color = color;
	return *this;
}

text& text::setText(std::string txt) {
	text_content = txt;
	// todo
	return *this;
}

text& text::setScale(float scale) {
	this->scale = scale;
	return *this;
}

void text::update() {
	if (!enabled) return;
	usrlib->glslPrograms[1].enable();
	usrlib->glslPrograms[1].setUniform("textColor", color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(renderer.vaoid);
	std::string::const_iterator c;
	int lc = localx;
	for (c = text_content.begin(); c != text_content.end(); c++) {
		chr ch = chrlist[*c];
		float xp = (lc + ch.ux * scale);
		float yp = MAX_HEIGHT-(localy + (ch.y - ch.uy) * scale);
		float w = (ch.x * scale);
		float h = (ch.y * scale);
		float vertices[6][4] = {
			{ xp,     yp + h,   0.0, 0.0 },
			{ xp,     yp,       0.0, 1.0 },
			{ xp + w, yp,       1.0, 1.0 },
			{ xp,     yp + h,   0.0, 0.0 },
			{ xp + w, yp,       1.0, 1.0 },
			{ xp + w, yp + h,   1.0, 0.0 }
		};
		glBindTexture(GL_TEXTURE_2D, ch.cht->index);
		glBindBuffer(GL_ARRAY_BUFFER, renderer.vboid);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		lc += (ch.advance >> 6) * scale;
		if (c == text_content.end() - 1) {
			width = xp + w - localx;
			height = yp + h - localy;
		}
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	return;
}