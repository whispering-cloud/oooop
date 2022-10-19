#ifndef __KEYPUT__
#define __KEYPUT__

#include <vector>
#include "../render/widget.h"


class eventListener {
public:
	point zonex;
	point zoney;
	keyListen buttonListener;
	eventListener(point zx, point zy, keyListen bl)
	:zonex(zx), zoney(zy), buttonListener(bl)
	{}
};

class keyput {
public:
	void detectKey(GLFWwindow* argwindow);
	void buttonHandler(GLFWwindow* argwindow, point clickPosition);
	int addListener(eventListener evl);
	std::vector<keyListen> keyputCall;
	int keytable[127];
	std::vector<eventListener> listenerList;
};

#endif // !__KEYPUT__
