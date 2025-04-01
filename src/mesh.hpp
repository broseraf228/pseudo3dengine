#pragma once

#include "math/mtrx4.hpp"

struct face {
	// create a empty face
	face();
	// use x,y and z pars of vertices vector. copy normla
	face(vec4 vertices, vec4 normal);
	// dnic
	face(unsigned short v1, unsigned short v2, unsigned short v3, vec4 normal);

	unsigned short v1, v2, v3;
	vec4 normal;
};

struct Mesh {

	// create a enpty mesh with setted size
	Mesh(int vertices_cap = 900, int feces_cap = 1000);
	// copy input args. caps is equal array sizes
	Mesh(	int vertices_array_size, vec4* vertices, int face_array_size, face* faces );
	
	int vertices_array_cap = 0;
	int vertices_array_size;
	vec4* vertices;

	int faces_array_cap = 0;
	int faces_array_size;
	face* faces;

	void transform(const mtrx4&);
	void move(const vec4&);

	void addMesh(const Mesh&);
	void clear();
};