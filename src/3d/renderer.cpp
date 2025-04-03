#include "renderer.hpp"

#include "../console_draw_utils.hpp"

#include "mesh.hpp"
#include "../math/include_all.hpp"

#include <algorithm>

#include<SFML/Graphics.hpp>



MeshRanderer::MeshRanderer(PrimDrawer* drawer) : drawer{drawer} {

	render_mesh = new Mesh(900, 1000);
	temp_model_convert_mesh = new Mesh(900, 1000);

	order_of_faces = new unsigned short[MAX_VERTICES_COUNT];
	dists_faces = new float[MAX_VERTICES_COUNT];

	project_vertices = new vec2[ MAX_VERTICES_COUNT ] ;

	clearProjectedVertices();


}

void MeshRanderer::clearProjectedVertices() {
	for (int i = 0; i < MAX_VERTICES_COUNT; i++) {
		project_vertices[i].x = 0;
		project_vertices[i].y = 0;
	}
}
void MeshRanderer::clearRenderMesh() {
	render_mesh->clear();
}

void MeshRanderer::addMesh(const Mesh& mesh){
	render_mesh->addMesh(mesh);
}
void MeshRanderer::addModel(const Model& m)
{
	temp_model_convert_mesh->clear();
	temp_model_convert_mesh->addMesh(m.original_mesh);
	temp_model_convert_mesh->transform(m.transform);
	temp_model_convert_mesh->move(m.position);

	addMesh(*temp_model_convert_mesh);
}
void MeshRanderer::clear(){
	clearRenderMesh();
}

void MeshRanderer::transformAll(const mtrx4& m){
	render_mesh->transform(m);
}

void MeshRanderer::prepare_order_of_faces(){
	for (int i = 0; i < render_mesh->faces.size(); i++) {
		order_of_faces[i] = i;

		dists_faces[i] = render_mesh->vertices[render_mesh->faces[i].v1].nosMod() 
			+ render_mesh->vertices[render_mesh->faces[i].v2].nosMod() 
			+ render_mesh->vertices[render_mesh->faces[i].v3].nosMod();
	}
		
}
void MeshRanderer::sort_faces(){
	for (int j = 0; j < render_mesh->faces.size(); j++) {

		for (int i = render_mesh->faces.size() - 1; i > 0; i--) {
			if (dists_faces[i] > dists_faces[i - 1]) {

				std::swap(dists_faces[i], dists_faces[i - 1]);
				std::swap(order_of_faces[i], order_of_faces[i - 1]);

			}
		}

	}
}

void MeshRanderer::projectVertices()
{
	for (int i = 0; i < render_mesh->vertices.size(); i++) {

		project_vertices[i].x = render_mesh->vertices[i].x / render_mesh->vertices[i].z;
		project_vertices[i].y = render_mesh->vertices[i].y / render_mesh->vertices[i].z;

	}
}

void MeshRanderer::drawFacesOnScreen() {

	for (int i = 0; i < render_mesh->faces.size(); i++) {

		drawer->triangle(
			project_vertices[render_mesh->faces[order_of_faces[i]].v1],
			project_vertices[render_mesh->faces[order_of_faces[i]].v2],
			project_vertices[render_mesh->faces[order_of_faces[i]].v3],
			render_mesh->faces[order_of_faces[i]].color
			);

	}
}

void MeshRanderer::render() {

	prepare_order_of_faces();
	sort_faces();

	projectVertices();
	drawFacesOnScreen();
}