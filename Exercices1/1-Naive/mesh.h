#ifndef MESH_H
#define MESH_H

struct Vertex {
    double x, y, z;
};

struct Triangle {
    Vertex va, vb, vc;
};

struct Tetra {
    Vertex vertices [4];
    Triangle triangles [4];
};

struct Cube {
    Vertex vertices [8];
    Triangle triangles [12];
};

struct Pyramid {
    Vertex vertices [5];
    Triangle triangles [6];
};

struct Plane {
    Vertex vertices [4];
    Triangle triangles [2];
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
    void draw_cube();
    void draw_tetra();
    void draw_pyramid();
    void draw_plane();
    void set_color(Color color);
    void show_figure(int mode);
};

#endif // MESH_H
