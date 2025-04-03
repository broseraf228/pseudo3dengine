#include<SFML/Graphics.hpp>

struct vec2;

class Painter {
protected:

	int sx, sy;
	float res;

	sf::RenderWindow* window;

public:

	Painter(sf::RenderWindow* window);

	void clear();

	void display();

	virtual int get_sx();
	virtual int get_sy();
	void update_cons_par();
};

class PrimDrawer : public Painter {
protected:
	sf::VertexArray rects{};
	sf::VertexArray triang{};
	sf::VertexArray lines{};
public:
	PrimDrawer(sf::RenderWindow* window);

	void rectangle(float x0, float y0, float sx, float sy, const sf::Color&);

	void triangle(float x0, float y0, float x1, float y1, float x2, float y2, const sf::Color&);
	void triangle(const vec2& p0, const vec2& p1, const vec2& p2, const sf::Color&);

	void draw();
};