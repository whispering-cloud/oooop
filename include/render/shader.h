#ifndef __SHADER__
#define __SHADER__
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class shader {
public:
	unsigned int index;
	// constructor
	shader() {};
	shader(const char* vertex_path, const char* fragment_path);
	//shader(const shader& from);
	// enable program
	void enable();
	// uniforms
	void setUniform(const std::string& name, bool value) const;
	void setUniform(const std::string& name, int value) const;
	void setUniform(const std::string& name, float value) const;
	void setUniform(const std::string& name, float value1, float value2, float value3) const;
	void setUniform(const std::string& name, float value1, float value2, float value3, float value4) const;
	void setUniform(const std::string& name, GLfloat* ptr) const;
	operator GLuint();
};

class vabo {
public:
	unsigned int vaoid;
	unsigned int vboid;
	unsigned int eboid;
	unsigned int graphUnit;
	int vtx;
	shader* renderShader;
	vabo() { vtx = -1; };
	vabo(float vertices[], int vtcsize, int vtxnum, shader* shad, unsigned int vboMode = GL_STATIC_DRAW, unsigned int gut = GL_TRIANGLES, int propernum = 3);
	vabo(float vertices[], int vtcsize, unsigned int indices[], int indsize, int vtxnum, shader* shad, unsigned int vboMode = GL_STATIC_DRAW, unsigned int gut = GL_TRIANGLES, int propernum = 2);
	vabo(vabo& from);
	void render(unsigned int textureID);
	void updateBuffer(float vertices[], int vtcsize, unsigned int vboMode);
private:
	int rtx;
};



#endif // !__SHADER__
