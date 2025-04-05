#pragma once

#define MAX_VERTICES_COUNT 10000
#define MAX_MODEL_COUNT 100

#include "../math/mtrx4.hpp"

struct PrimDrawer;
struct Mesh;
struct vec2;
struct Model;

/*
*                   RENDERING PIPELINE
* 
*   1 добавление модели на отрисовываемуе сцену
*       1 копирование меша модели во временный меш преобразований |temp_model_convert_mesh|
*       2 применение марицы преобразования модели на временный меш преобразования  ( вращение, масштабирование, собственное перемещение )
*       3 преобразование локальных координат модели в глобальные координаты ( сдвиг всех вертексов на вектор, сохраненный в модели )
*       4 перенос модели из временного меша в меш рендера и очистка первого
*   2 преобразование координат вершин из меша рендера в координаты камеры
*       1 сдвиг камеры ( сдвиг свех вершин меша на отрицательный вектор позиции камеры )
*       2 вращение камеры ( умножение всех вершин меша рендера на отрицательную матрицу вращения камеры)
*   2 ...
*/
class MeshRanderer {
protected:

    PrimDrawer* drawer;

    Mesh* render_mesh;
    void clearRenderMesh();

    // temp mesh needed to convert model vertexes to global coordinate system
    Mesh* temp_model_convert_mesh;

    // параметры поворота и позиции камеры
    vec4 camera_position;
    float camera_rotation_x, camera_rotation_y, camera_rotation_z;
    mtrx4 camera_rotation;
    mtrx4 camera_rotation_inv;

    // converting  from world coordinates system to camera coordinates system
    void covertToCameraCord();

    // faces sotring
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


    // set absolute camera position
    void setCameraPosition(const vec4&);
    // *all angles in radians
    void setCameraRotation(float camera_rotation_x, float camera_rotation_y, float camera_rotation_z);

    // moves the camera relative to its rotation
    void changeCameraPosition(const vec4&);
    // *all angles in radians
    void changeCameraRotation(float camera_rotation_x, float camera_rotation_y, float camera_rotation_z);

    void render();
};