#include "mesh.hpp"

#include "../math/include_all.hpp"

face::face() : face(0, 0, 0) {}
face::face(const vec4& vertices, const sf::Color& color) : face(vertices.x, vertices.y, vertices.z, color) {}
face::face(unsigned short v1, unsigned short v2, unsigned short v3, const sf::Color& color) : v1{ v1 }, v2{ v2 }, v3{ v3 }, color{color} {}


Mesh::Mesh(int vertices_cap, int feces_cap) {
	vertices.resize(vertices_cap);
	faces.resize(feces_cap);
	normals.resize(feces_cap);

	clear();
}
Mesh::Mesh(const std::vector<vec4>& vertices, const std::vector<face>& faces, const std::vector<vec4>& Inormals) :
	 vertices{ vertices }, faces{ faces }, normals{Inormals}
{
	normals.resize(faces.size() - normals.size());
}

Mesh::~Mesh(){
}

void Mesh::transform(const mtrx4& t){
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i] = t * vertices[i];
		normals[i] = t * normals[i];
	}
}
void Mesh::move(const vec4& v){
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices[i] += v;
	}
}

void Mesh::addMesh(const Mesh& m) {
	if (vertices.size() + m.vertices.size() >= vertices.capacity())
		throw "tyr to attach an array with too many vertices";
	if (faces.size() + m.faces.size() >= faces.capacity())
		throw "tyr to attach an array with too many faces";

	for (int i = 0; i < m.vertices.size(); i++)
		vertices.push_back(m.vertices[i]);

	for (int i = 0; i < m.faces.size(); i++) {
		faces.push_back(m.faces[i]);
		normals.push_back(m.normals[i]);
	}
}
void Mesh::clear() {
	vertices.clear();
	normals.clear();
	faces.clear();
}

Model::Model(const Mesh& mesh, const vec4& position, const mtrx4& transform) 
	: original_mesh{ mesh }, position{ position }, transform{ transform } {}