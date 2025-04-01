#include "mesh.hpp"

face::face() : face(0, 0, 0, 0) {}
face::face(vec4 vertices, vec4 normal) : face(vertices.x, vertices.y, vertices.z, normal) {}
face::face(unsigned short v1, unsigned short v2, unsigned short v3, vec4 normal) : v1{ v1 }, v2{ v2 }, v3{ v3 }, normal{normal} {}

Mesh::Mesh(int vertices_cap, int feces_cap) :
	vertices_array_cap{ vertices_cap  }, faces_array_cap{ feces_cap  },
	vertices_array_size { 0 }, vertices{ new vec4[vertices_array_cap] }, 
	faces_array_size{ 0 }, faces{ new face[faces_array_cap] } {}

Mesh::Mesh( int vertices_array_size, vec4* vertices, int face_array_size, face* faces ) : 
	vertices_array_cap{ vertices_array_size }, faces_array_cap{ face_array_size },
	vertices_array_size{ vertices_array_size }, vertices{ vertices }, 
	faces_array_size{ face_array_size }, faces{ faces }
{}

void Mesh::transform(const mtrx4& t){
	for (unsigned int i = 0; i < vertices_array_size; i++) {
		vertices[i] = t * vertices[i];
	}
}
void Mesh::move(const vec4& v){
	for (unsigned int i = 0; i < vertices_array_size; i++) {
		vertices[i] += v;
	}
}

void Mesh::addMesh(const Mesh& m) {
	if (vertices_array_size + m.vertices_array_size >= vertices_array_cap)
		throw "tyr to attach an array with too many vertices";
	if (faces_array_size + m.faces_array_size >= faces_array_cap)
		throw "tyr to attach an array with too many faces";

	for (int i = 0; i < m.vertices_array_size; i++)
		vertices[vertices_array_size + i] = m.vertices[i];
	vertices_array_size += m.vertices_array_size;

	for (int i = 0; i < m.faces_array_size; i++)
		faces[faces_array_size + i] = m.faces[i];
	faces_array_size += m.faces_array_size;
}
void Mesh::clear() {
	for (int i = 0; i < vertices_array_size; i++)
		vertices[i] = 0;
	vertices_array_size = 0;

	for (int i = 0; i < faces_array_size; i++) {
		faces[i].v1 = 0;
		faces[i].v2 = 0;
		faces[i].v3 = 0;
		faces[i].normal = 0;
	}
	faces_array_size = 0;
}