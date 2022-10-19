#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "resources.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

void loadResource()
{
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("./wall.jpg", &width, &height, &nrChannels, 0);
	unsigned int trt;
	glGenTextures(1, &trt);
	glBindTexture(GL_TEXTURE_2D, trt);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);


}
