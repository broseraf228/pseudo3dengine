#pragma once

#include "../math/mtrx4.hpp"

#include <vector>

#include "SFML/Graphics/Color.hpp"

struct mtrx4;

struct face {
	// create a empty face
	face();
	// use x,y and z pars of vertices vector. copy normla
	face(const vec4& vertices, const sf::Color& color = sf::Color::Magenta);
	// dnic
	face(unsigned short v1, unsigned short v2, unsigned short v3, const sf::Color& color = sf::Color::Magenta);

	unsigned short v1, v2, v3;
	sf::Color color;

};

struct Mesh {

	// create a enpty mesh with setted size
	Mesh(int vertices_cap = 900, int feces_cap = 1000);
	// copy input args. caps is equal array sizes
	Mesh(const std::vector<vec4>&  vertices, const std::vector<face>& faces, const std::vector <vec4>& normals = {});

	~Mesh();
	
	std::vector<vec4> vertices;

	std::vector<face> faces;

	std::vector <vec4> normals;

	void transform(const mtrx4&);
	void move(const vec4&);

	void addMesh(const Mesh&);
	void clear();
};

struct Model {
	Model(const Mesh& mesh, const vec4& position, const mtrx4& transform);

	const Mesh& original_mesh;

	vec4 position;
	mtrx4 transform;
};