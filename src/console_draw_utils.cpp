#include "console_draw_utils.hpp"
#include <iostream>

#define _WIN32_WINNT 0x0500
#include <Windows.h>

#include "math/vec2.hpp"

//---------------------------------------



//#######################################################################################################################################


Painter::Painter(sf::RenderWindow* window) : window{window}{
	update_cons_par();
}

void Painter::clear() {
	window->clear();
}

void Painter::display() {
	window->display();
}

int Painter::get_sx() {
	return window->getSize().x;
}
int Painter::get_sy() {
	return window->getSize().y;
}
void Painter::update_cons_par(){
	sx = window->getSize().x, sy = window->getSize().y;
}
//---------------------------------------

PrimDrawer::PrimDrawer(sf::RenderWindow* window) : Painter(window)
{
	rects.setPrimitiveType(sf::Quads);
	triang.setPrimitiveType(sf::Triangles);
	lines.setPrimitiveType(sf::Lines);
}

void PrimDrawer::rectangle(float x0, float y0, float x1, float y1, const sf::Color& fill)
{
	x0 *= sx;
	x1 *= sx;
	y0 *= sy;
	y1 *= sy;
	 
	rects.append(sf::Vertex(sf::Vector2f(x0,y0), fill ));
	rects.append(sf::Vertex(sf::Vector2f(x1, y0), fill));
	rects.append(sf::Vertex(sf::Vector2f(x1, y1), fill));
	rects.append(sf::Vertex(sf::Vector2f(x0, y1), fill));
}
void PrimDrawer::triangle(float x0, float y0, float x1, float y1, float x2, float y2, const sf::Color& fill){

	triang.append(sf::Vertex(sf::Vector2f(x0 * sx + 0.5 * sx, y0 * sy + 0.5 * sy), fill));
	triang.append(sf::Vertex(sf::Vector2f(x1 * sx + 0.5 * sx, y1 * sy + 0.5 * sy), fill));
	triang.append(sf::Vertex(sf::Vector2f(x2 * sx + 0.5 * sx, y2 * sy + 0.5 * sy), fill));
}
void PrimDrawer::triangle(const vec2& p0, const vec2& p1, const vec2& p2, const sf::Color& fill)
{
	triang.append(sf::Vertex(sf::Vector2f((p0.x + 0.5) * sx, (p0.y + 0.5) * sy), fill));
	triang.append(sf::Vertex(sf::Vector2f((p1.x + 0.5) * sx, (p1.y + 0.5) * sy), fill));
	triang.append(sf::Vertex(sf::Vector2f((p2.x + 0.5) * sx, (p2.y + 0.5) * sy), fill));

	//lines.append(sf::Vertex(sf::Vector2f((p0.x + 0.5) * sx, (p0.y + 0.5) * sy), sf::Color::Black));
	//lines.append(sf::Vertex(sf::Vector2f((p1.x + 0.5) * sx, (p1.y + 0.5) * sy), sf::Color::Black));

	//lines.append(sf::Vertex(sf::Vector2f((p1.x + 0.5) * sx, (p1.y + 0.5) * sy), sf::Color::Black));
	//lines.append(sf::Vertex(sf::Vector2f((p2.x + 0.5) * sx, (p2.y + 0.5) * sy), sf::Color::Black));

	//lines.append(sf::Vertex(sf::Vector2f((p2.x + 0.5) * sx, (p2.y + 0.5) * sy), sf::Color::Black));
	//lines.append(sf::Vertex(sf::Vector2f((p0.x + 0.5) * sx, (p0.y + 0.5) * sy), sf::Color::Black));
}

void  PrimDrawer::draw() {

	window->draw(rects);
	window->draw(triang);
	window->draw(lines);
	rects.clear();
	triang.clear();
	lines.clear();
}

//---------------------------------------
