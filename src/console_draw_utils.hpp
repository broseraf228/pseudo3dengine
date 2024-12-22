
class ConsolePainter {
protected:

	int sx, sy;
	int screen_lenght;

	char* screen; char* clear_screen;

public:

	ConsolePainter(int sx, int sy);

	inline void edit_symbol(int px, int py, char symbol);

	void clear();

	void display();

	virtual int get_sx();
	virtual int get_sy();

	void update_cons_par();
};

class ConsolePrimDrawer : public ConsolePainter {
public:
	ConsolePrimDrawer(int sx, int sy);

	void line(int x0, int y0, int x1, int y1, char symbol);
	void rectangle(int x0, int y0, int sx, int sy, char fill);

	int get_sx();
};