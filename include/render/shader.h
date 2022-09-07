#ifndef __SHADER__
#define __SHADER__
#include <string>
class shader {
public:
	unsigned int index;
	// constructor
	shader(const char* vertex_path, const char* fragment_path);
	// enable program
	void enable();
	// uniforms
	void setUniform(const std::string& name, bool value) const;
	void setUniform(const std::string& name, int value) const;
	void setUniform(const std::string& name, float value) const;

};

#endif // !__SHADER__