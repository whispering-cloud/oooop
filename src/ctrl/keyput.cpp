#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../usrs.h"

/*
0	Esc
1	Enter

*/

void keyput::detectKey(GLFWwindow* argwindow) {
	if (glfwGetKey(argwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		usrlib->keytable[0] = 100;
	}
	else {
		if (usrlib->keytable[0] > 0) {
			usrlib->keytable[0]--;
		}
	}
	if (glfwGetKey(argwindow, GLFW_KEY_ENTER) == GLFW_PRESS) {
		usrlib->keytable[1] = 100;
	}
	else {
		if (usrlib->keytable[1] > 0) {
			usrlib->keytable[1]--;
		}
	}
	return;
}