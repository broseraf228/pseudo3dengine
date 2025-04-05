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

void MeshRanderer::covertToCameraCord() {
	render_mesh->move(-camera_position);
	render_mesh->transform(camera_rotation_inv);
}

void MeshRanderer::prepare_order_of_faces(){
	int ind = 0;
	for (int i = 0; i < render_mesh->faces.size(); i++) {
		if (render_mesh->vertices[render_mesh->faces[i].v1].z < 0 ||
			render_mesh->vertices[render_mesh->faces[i].v2].z < 0 ||
			render_mesh->vertices[render_mesh->faces[i].v3].z < 0) 
		{
			continue;
		}

		order_of_faces[ind] = i;

		dists_faces[ind] = render_mesh->vertices[render_mesh->faces[i].v1].nosMod() 
			+ render_mesh->vertices[render_mesh->faces[i].v2].nosMod() 
			+ render_mesh->vertices[render_mesh->faces[i].v3].nosMod();

		ind++;
	}

	rendering_faces_count = ind;
}
void MeshRanderer::sort_faces(){
	for (int j = 0; j < rendering_faces_count; j++) {

		for (int i = rendering_faces_count - 1; i > 0; i--) {
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

	float fow = 1 / PI * 2;

	for (int i = 0; i < rendering_faces_count; i++) {

		drawer->triangle(
			project_vertices[render_mesh->faces[order_of_faces[i]].v1] * fow,
			project_vertices[render_mesh->faces[order_of_faces[i]].v2] * fow,
			project_vertices[render_mesh->faces[order_of_faces[i]].v3] * fow,
			render_mesh->faces[order_of_faces[i]].color
			);

	}
}

void MeshRanderer::render() {

	covertToCameraCord();

	prepare_order_of_faces();
	sort_faces();

	projectVertices();
	drawFacesOnScreen();
}

void MeshRanderer::setCameraPosition(const vec4& v){
	camera_position = v;
}
void MeshRanderer::setCameraRotation(float camera_rotation_x, float camera_rotation_y, float camera_rotation_z){
	camera_rotation = mtrx4::mtrx_rotation_x(camera_rotation_x) * mtrx4::mtrx_rotation_y(camera_rotation_y) * mtrx4::mtrx_rotation_y(camera_rotation_z);
	camera_rotation_inv = mtrx4::mtrx_rotation_x(-camera_rotation_x) * mtrx4::mtrx_rotation_y(-camera_rotation_y) * mtrx4::mtrx_rotation_y(-camera_rotation_z);
}

// moves the camera relative to its rotation
void MeshRanderer::changeCameraPosition(const vec4& v){
	camera_position += camera_rotation * v;
}
// recomended for use
// *all angles in radians
void MeshRanderer::changeCameraRotation(float camera_rotation_x, float camera_rotation_y, float camera_rotation_z) {
	camera_rotation = camera_rotation * mtrx4::mtrx_rotation_x(camera_rotation_x) * mtrx4::mtrx_rotation_y(camera_rotation_y) * mtrx4::mtrx_rotation_y(camera_rotation_z);;
	camera_rotation_inv = camera_rotation_inv * mtrx4::mtrx_rotation_x(-camera_rotation_x) * mtrx4::mtrx_rotation_y(-camera_rotation_y) * mtrx4::mtrx_rotation_y(-camera_rotation_z);
}