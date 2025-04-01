#include "camera.hpp"

#include "../console_draw_utils.hpp"

#include "../mesh.hpp"
#include "../math/include_all.hpp"

#include<SFML/Graphics.hpp>



Camera::Camera(PrimDrawer* drawer) : drawer{drawer} {

	render_mesh = new Mesh(900, 1000);

	project_vertices = new vec2[ MAX_VERTICES_COUNT ] ;

	clearProjectedVertices();


}

void Camera::clearProjectedVertices() {
	for (int i = 0; i < MAX_VERTICES_COUNT; i++) {
		project_vertices[i].x = 0;
		project_vertices[i].y = 0;
	}
}
void Camera::clearRenderMesh() {
	render_mesh->clear();
}

void Camera::addMesh(const Mesh& mesh){
	render_mesh->addMesh(mesh);
}
void Camera::clear(){
	clearRenderMesh();
}

void Camera::projectVertices()
{
	for (int i = 0; i < render_mesh->vertices_array_size; i++) {

		project_vertices[i].x = render_mesh->vertices[i].x / render_mesh->vertices[i].z;
		project_vertices[i].y = render_mesh->vertices[i].y / render_mesh->vertices[i].z;

	}
}

void Camera::drawFacesOnScreen() {

	for (int i = 0; i < render_mesh->faces_array_size; i++) {

		drawer->triangle(
			project_vertices[render_mesh->faces[i].v1].x,
			project_vertices[render_mesh->faces[i].v1].y,
			project_vertices[render_mesh->faces[i].v2].x,
			project_vertices[render_mesh->faces[i].v2].y,
			project_vertices[render_mesh->faces[i].v3].x,
			project_vertices[render_mesh->faces[i].v3].y,
			sf::Color::White
			);

	}
}

void Camera::render() {
	projectVertices();
	drawFacesOnScreen();
}