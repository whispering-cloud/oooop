#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../usrs.h"


const int KEYMAP[127] = {
	GLFW_KEY_ESCAPE,
	GLFW_KEY_ENTER,
	GLFW_MOUSE_BUTTON_LEFT + 114514,
	GLFW_MOUSE_BUTTON_RIGHT + 114514
};

void closeWindow(point clickPosition) {
	glfwSetWindowShouldClose(usrlib->wds, true);
	logPrint("CLOSED");
}


void buttonHelper(point clickPosition) {
	usrlib->keyputh->buttonHandler(usrlib->wds, clickPosition);
}


void keyput::initKey() {
	keyputCall = std::vector<keyListen>(128, nullptr);
	keyputCall[0] = closeWindow;
	//keyputCall[1] = closeWindow;
	keyputCall[2] = buttonHelper;
}

void keyput::detectKey(GLFWwindow* argwindow) {
	for (re i = 0; i < 120; i++) {
		if ((KEYMAP[i] >= 114514 ? glfwGetMouseButton(argwindow, KEYMAP[i] - 114514) : glfwGetKey(argwindow, KEYMAP[i])) == GLFW_PRESS) {
			//logPrint("Press");
			keytable[i]++;
		}
		else if ((KEYMAP[i] >= 114514 ? glfwGetMouseButton(argwindow, KEYMAP[i] - 114514) : glfwGetKey(argwindow, KEYMAP[i])) == GLFW_RELEASE){
			if (keytable[i] > 0) {
				keytable[i] = 0;
				if (keyputCall[i] != nullptr) {
					double x, y;
					glfwGetCursorPos(usrlib->wds, &x, &y);
					keyputCall[i](point(floor(x), floor(y)));
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
	std::cout << clickPosition.x << "," << clickPosition.y << std::endl;
	for (re i = (int)(listenerList.size()) - 1; i >= 0; i--) {
		if (listenerList[i].buttonListener != nullptr && listenerList[i].enabled)
		{
			if (clickPosition.x <= listenerList[i].zoney.x
				&& clickPosition.x >= listenerList[i].zonex.x
				&& clickPosition.y <= listenerList[i].zoney.y
				&& clickPosition.y >= listenerList[i].zonex.y) {
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
