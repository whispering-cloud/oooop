#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../include/ctrl/keyput.h"

void keyput::detectKey(GLFWwindow* argwindow) {
	if (glfwGetKey(argwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		usrlib->keytable[0] = 100;
	}
	
	else {
		if (usrlib->keytable[0] > 0) {
			usrlib->keytable[0]--;
		}
	}
}