#ifndef __RESOURCES__
#define __RESOURCES__
#include <vector>
#include <string>
#include <map>

class texture {
public:
	int index;
	texture(int id);
	texture(texture& from) { this->index = from.index; };
	texture(std::string path);
	operator int();
	static int loadResource(std::string path);
	static void loadFont();
};

struct chr {
	texture* cht;
	int x;
	int y;
	int ux;
	int uy;
	int advance;
};

extern std::vector <texture> textureList;
extern std::map<char, chr> chrlist;
#endif // !__RESOURCES__
