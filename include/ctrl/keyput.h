#ifndef __KEYPUT__
#define __KEYPUT__

#include <vector>
#include "../render/widget.h"

typedef void (*keyListen)(point clickPosition);

class eventListener {
public:
	point zonex;
	point zoney;
	keyListen buttonListener;
};

class keyput {
public:
	void detectKey(GLFWwindow* argwindow);
	void buttonHandler(GLFWwindow* argwindow, point clickPosition);
	std::vector<keyListen> keyputCall;
	int keytable[127];
private:
	std::vector<eventListener> listenerList;
};

#endif // !__KEYPUT__
