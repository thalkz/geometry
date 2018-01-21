#include "mesh.h"
#include <gl.h>
#include <cstdlib>
#include <time.h>
#include <QtGlobal>
#include <QByteArray>

Tetra tetra;
Cube cube;
Pyramid pyramid;
Plane plane;

Color red = {1.0, 0.0, 0.0};
Color green = {0.0, 1.0, 0.0};
Color blue = {0.0, 0.0, 1.0};
Color yellow = {1.0, 1.0, 0.0};

int current_mode = 0;

void Mesh::show_figure(int mode)
{
    current_mode = mode;

}

void create_tetra() {
    Vertex v0 = {0.0, -0.5, 0.0};
    Vertex v1 = {0.5, 0.0, 0.0};
    Vertex v2 = {0.0, 0.5, 0.0};
    Vertex v3 = {0.0, 0.0, 0.5};

    Triangle t0 = {v1, v2, v3};
    Triangle t1 = {v1, v3, v0};
    Triangle t2 = {v0, v3, v2};
    Triangle t3 = {v0, v2, v1};

    tetra.triangles[0] = t0;
    tetra.triangles[1] = t1;
    tetra.triangles[2] = t2;
    tetra.triangles[3] = t3;

    tetra.vertices[0] = v0;
    tetra.vertices[1] = v1;
    tetra.vertices[2] = v2;
    tetra.vertices[3] = v3;
}

void create_plane() {
    Vertex v0 = {-100.0, -100.0, 0.0};
    Vertex v1 = {100.0, -100.0, 0.0};
    Vertex v2 = {100.0, 100.0, 0.0};
    Vertex v3 = {-100.0, 100.0, 0.0};

    Triangle t0 = {v0, v2, v3};
    Triangle t1 = {v0, v1, v2};

    plane.triangles[0] = t0;
    plane.triangles[1] = t1;

    plane.vertices[0] = v0;
    plane.vertices[1] = v1;
    plane.vertices[2] = v2;
    plane.vertices[3] = v3;
}

void create_cube() {
    Vertex v0 = {-0.5, -0.5, -0.5};
    Vertex v1 = {0.5, -0.5, -0.5};
    Vertex v2 = {0.5, -0.5, 0.5};
    Vertex v3 = {-0.5, -0.5, 0.5};
    Vertex v4 = {-0.5, 0.5, -0.5};
    Vertex v5 = {0.5, 0.5, -0.5};
    Vertex v6 = {0.5, 0.5, 0.5};
    Vertex v7 = {-0.5, 0.5, 0.5};

    Triangle t0 = {v0, v2, v3};
    Triangle t1 = {v0, v1, v2};

    Triangle t2 = {v3, v6, v7};
    Triangle t3 = {v3, v2, v6};

    Triangle t4 = {v5, v6, v2};
    Triangle t5 = {v1, v5, v2};

    Triangle t6 = {v7, v5, v4};
    Triangle t7 = {v7, v6, v5};

    Triangle t8 = {v3, v7, v4};
    Triangle t9 = {v3, v4, v0};

    Triangle t10 = {v0, v4, v5};
    Triangle t11 = {v0, v5, v1};

    cube.triangles[0] = t0;
    cube.triangles[1] = t1;
    cube.triangles[2] = t2;
    cube.triangles[3] = t3;
    cube.triangles[4] = t4;
    cube.triangles[5] = t5;
    cube.triangles[6] = t6;
    cube.triangles[7] = t7;
    cube.triangles[8] = t8;
    cube.triangles[9] = t9;
    cube.triangles[10] = t10;
    cube.triangles[11] = t11;

    cube.vertices[0] = v0;
    cube.vertices[1] = v1;
    cube.vertices[2] = v2;
    cube.vertices[3] = v3;
    cube.vertices[4] = v4;
    cube.vertices[5] = v5;
    cube.vertices[6] = v6;
    cube.vertices[7] = v7;
}

void create_pyramid() {
    Vertex v0 = {-0.5, 0.0, -0.5};
    Vertex v1 = {0.5, 0.0, -0.5};
    Vertex v2 = {0.5, 0.0, 0.5};
    Vertex v3 = {-0.5, 0.0, 0.5};
    Vertex v4 = {0.0, 0.5, 0.0};

    Triangle t0 = {v0, v2, v3};
    Triangle t1 = {v0, v1, v2};
    Triangle t2 = {v0, v3, v4};
    Triangle t3 = {v3, v2, v4};
    Triangle t4 = {v2, v1, v4};
    Triangle t5 = {v0, v4, v1};

    pyramid.triangles[0] = t0;
    pyramid.triangles[1] = t1;
    pyramid.triangles[2] = t2;
    pyramid.triangles[3] = t3;
    pyramid.triangles[4] = t4;
    pyramid.triangles[5] = t5;

    pyramid.vertices[0] = v0;
    pyramid.vertices[1] = v1;
    pyramid.vertices[2] = v2;
    pyramid.vertices[3] = v3;
    pyramid.vertices[4] = v4;
}

Mesh::Mesh()
{
    create_tetra();
    create_cube();
    create_pyramid();
    create_plane();
}

void Mesh::draw()
{
    glBegin(GL_TRIANGLES);

    switch (current_mode) {
    case 0:
        draw_tetra();
        break;

    case 1:
        draw_cube();
        break;

    case 2:
        draw_pyramid();
        break;

    case 3:
        draw_plane();
        break;

    default:
        draw_tetra();
        break;
    }

    glEnd();
}

void Mesh::set_color(Color color)
{
    glColor3dv(&color.x);
}

void Mesh::draw_triangle(Triangle triangle)
{
    glVertex3dv(&triangle.va.x);
    glVertex3dv(&triangle.vb.x);
    glVertex3dv(&triangle.vc.x);
}

void Mesh::draw_tetra()
{
    set_color(green);
    draw_triangle(tetra.triangles[0]);

    set_color(red);
    draw_triangle(tetra.triangles[1]);

    set_color(yellow);
    draw_triangle(tetra.triangles[2]);

    set_color(blue);
    draw_triangle(tetra.triangles[3]);
}

void Mesh::draw_cube()
{
    set_color(green);
    draw_triangle(cube.triangles[0]);

    set_color(red);
    draw_triangle(cube.triangles[1]);

    set_color(yellow);
    draw_triangle(cube.triangles[2]);

    set_color(blue);
    draw_triangle(cube.triangles[3]);

    set_color(green);
    draw_triangle(cube.triangles[4]);

    set_color(red);
    draw_triangle(cube.triangles[5]);

    set_color(yellow);
    draw_triangle(cube.triangles[6]);

    set_color(blue);
    draw_triangle(cube.triangles[7]);

    set_color(green);
    draw_triangle(cube.triangles[8]);

    set_color(red);
    draw_triangle(cube.triangles[9]);

    set_color(yellow);
    draw_triangle(cube.triangles[10]);

    set_color(blue);
    draw_triangle(cube.triangles[11]);
}

void Mesh::draw_pyramid()
{
    set_color(green);
    draw_triangle(pyramid.triangles[0]);

    set_color(red);
    draw_triangle(pyramid.triangles[1]);

    set_color(yellow);
    draw_triangle(pyramid.triangles[2]);

    set_color(blue);
    draw_triangle(pyramid.triangles[3]);

    set_color(green);
    draw_triangle(pyramid.triangles[4]);

    set_color(red);
    draw_triangle(pyramid.triangles[5]);
}

void Mesh::draw_plane()
{
    set_color(green);
    draw_triangle(plane.triangles[0]);

    set_color(red);
    draw_triangle(plane.triangles[1]);
}
