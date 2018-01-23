#ifndef MESH_H
#define MESH_H


#include "vertex.h"
#include "triangle.h"
#include <vector>

using namespace std;

class Mesh
{
public:
    Mesh();
    Mesh(vector<Vertex>* _v, vector<Triangle>* _t){vertices = *_v; triangles = *_t;}

    vector<Vertex> vertices;
    vector<Triangle> triangles;

    void draw();

    void build_mesh();
    void insert_point(double x, double y, double z);
    bool is_inside(Triangle triangle, Vertex vertex);
    void insert_outside_point(double x, double y, double z);
    void insert_inside_point(int i, double x, double y, double z);
};

#endif // MESH_H
