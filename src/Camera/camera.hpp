#pragma once

#define MAX_VERTICES_COUNT 10000

struct PrimDrawer;
struct Mesh;
struct vec2;

class Camera {
private:

    PrimDrawer* drawer;

    // итоговый меш из которого берется всё для рендера
    Mesh* render_mesh;
    void clearRenderMesh();

    // массив спроецированных на экран вершин
    // создается один раз что бы кучу раз не выделять память
    vec2* project_vertices;
    void clearProjectedVertices();

    void projectVertices();
    void drawFacesOnScreen();

public:

    Camera(PrimDrawer* drawer);

    void addMesh(const Mesh&);
    void clear();

    void render();
};