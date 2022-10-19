#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../usrs.h"


const int KEYMAP[127] = {
	GLFW_KEY_ESCAPE,
	GLFW_KEY_ENTER,
	GLFW_MOUSE_BUTTON_1
};


void keyput::detectKey(GLFWwindow* argwindow) {

	for (re i = 0; i < 3; i++) {
		if (glfwGetKey(argwindow, KEYMAP[i]) == GLFW_PRESS) {
			keytable[i] = 100;
		}
		else if (glfwGetKey(argwindow, KEYMAP[i]) == GLFW_RELEASE){
			if (keytable[i] > 0) {
				keytable[i] = 0;
				if (keyputCall[i] != nullptr) {
					double nx, ny;
					glfwGetCursorPos(usrlib->wds, &nx, &ny);
					keyputCall[i](point(nx, ny, false));
				}
			}
		}
		else {
			if (keytable[i] > 0) {
				keytable[i]--;
			}
		}
	}

	return;
}

void keyput::buttonHandler(GLFWwindow* argwindow, point clickPosition) {
	for (re i = (int)(listenerList.size()) - 1; i >= 0; i--) {
		if (listenerList[i].buttonListener != nullptr)
		{
			if (clickPosition.x < listenerList[i].zoney.x
				&& clickPosition.x > listenerList[i].zonex.x
				&& clickPosition.y < listenerList[i].zoney.y
				&& clickPosition.y > listenerList[i].zonex.x) {
				listenerList[i].buttonListener(clickPosition);
				break;
			}
		}
	}
}

int keyput::addListener(eventListener evl) {
	listenerList.push_back(evl);
	return (int)(listenerList.size()) - 1;
}
