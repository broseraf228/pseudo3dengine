#pragma once

#include <string>

class Mesh;

class ResourceManager {
private:
	static std::string path;
	
	static std::string loadTextFromFile(const std::string&);

public:
	static void setPath(const std::string&);
	
	static Mesh* loadOBJFile(const std::string&);
};