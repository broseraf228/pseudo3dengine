#pragma once

#define MAX_VERTICES_COUNT 10000
#define MAX_MODEL_COUNT 100

struct PrimDrawer;
struct Mesh;
struct vec2;
struct mtrx4;
struct Model;

class MeshRanderer {
protected:

    PrimDrawer* drawer;

    // меш из которого берется всё для рендера
    Mesh* render_mesh;
    void clearRenderMesh();

    unsigned short* order_of_faces;
    int rendering_faces_count;
    float* dists_faces;

    void prepare_order_of_faces();
    void sort_faces();

    // массив спроецированных на экран вершин
    // создается один раз что бы кучу раз не выделять память
    vec2* project_vertices;
    void clearProjectedVertices();

    void projectVertices();
    void drawFacesOnScreen();

    // temp mesh needed to convert model to mesh
    Mesh* temp_model_convert_mesh;

public:

    MeshRanderer(PrimDrawer* drawer);

    // attach mesh(A) to render mesh (mesh(A) need a ready to be rendered)
    void addMesh(const Mesh&);
    // convert model to mesh
    // use model position and transforms
    void addModel(const Model&);
    // clear render mesh
    // recomended to use after ever frame
    void clear();

    // transform all render vertex
    // use this to move the camera
    void transformAll(const mtrx4&);

    void render();
};