#include<SFML/Graphics.hpp>

class Painter {
protected:

	int sx, sy;

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
public:
	PrimDrawer(sf::RenderWindow* window);

	void rectangle(float x0, float y0, float sx, float sy, const sf::Color&);

	void draw();
};