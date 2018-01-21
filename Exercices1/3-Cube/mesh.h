#ifndef MESH_H
#define MESH_H

#include <gl.h>

struct Triangle;

struct Vertex {
    GLdouble pos [3]; // Les coordonées géomértique du vertex
    Triangle* t; // Un des triangles qui contient ce vertex
};

struct Triangle {
    // Les 3 vertex de ce triangle, dans le sens trigo
    Vertex v0;
    Vertex v1;
    Vertex v2;

    // Les 3 triangles adjacent à ce triangle tel que t0 est opposé à v0, etc.
    Triangle* t0;
    Triangle* t1;
    Triangle* t2;
};

struct Face {
    Vertex v [4];
};

struct Color {
    double x, y, z;
};

class Mesh
{
public:
    Mesh();
    void draw();
    void draw_triangle(Triangle triangle);
    void draw_tetra();
    void set_color(Color color);
};

#endif // MESH_H
