#include "resource_manager.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include "3d/mesh.hpp"

std::vector<std::string> split(const std::string& str, char splitter) {
	std::string t("");
	std::vector<std::string> r{};

	for (char i : str) {
		if (i == splitter) {
			r.push_back(t);
			t = "";
		}
		t += i;
	}


	return r;
}

std::string ResourceManager::path = "";

void ResourceManager::setPath(const std::string& p) {
	path = p;
}

std::string ResourceManager::loadTextFromFile(const std::string& n) {

	std::ifstream in(n);
	if (!in.is_open())
	{
		return "";
	}

	std::string text("");

	std::string line("");

	while (std::getline(in, line))
	{
		text += line;
	}

	in.close();

	return text;
}

Mesh* ResourceManager::loadOBJFile(const std::string& n)
{
	std::ifstream in(n);
	if (!in.is_open())
	{
		return nullptr;
	}


	std::vector<vec4> vrtices;
	std::vector<vec4> normals;


	std::string line("");
	while (std::getline(in, line))
	{
		
	}
	in.close();

	return nullptr;
}