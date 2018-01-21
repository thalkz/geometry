#include "mesh.h"
#include <gl.h>
#include <cstdlib>
#include <time.h>
#include <QtGlobal>
#include <QByteArray>

Tetra tetra;

Color red = {1.0, 0.0, 0.0};
Color green = {0.0, 1.0, 0.0};
Color blue = {0.0, 0.0, 1.0};
Color yellow = {1.0, 1.0, 0.0};

Vertex create_vertex(double x, double y, double z, Triangle* t) {
    Vertex *result = new Vertex;
    result->pos[0] = x;
    result->pos[1] = y;
    result->pos[2] = z;
    result->t = t;
    return *result;
}

void create_tetra() {

    Triangle* ta = new Triangle;
    Triangle* tb = new Triangle;
    Triangle* tc = new Triangle;
    Triangle* td = new Triangle;

    Vertex va = create_vertex(0.0, 0.0, 0.0, ta);
    Vertex vb = create_vertex(0.0, 0.0, 0.5, td);
    Vertex vc = create_vertex(0.5, 0.0, 0.0, tb);
    Vertex vd = create_vertex(0.0, 0.5, 0.0, tc);

//    t0->v = {va, vc, vb};
//    t0->t = {td, tc, tb};

    ta->v0 = va;
    ta->v1 = vc;
    ta->v2 = vb;

    ta->t0 = td;
    ta->t1 = tc;
    ta->t2 = tb;

//    tb->v = {va, vd, vc};
//    tb->t = {td, ta, tc};

    tb->v0 = va;
    tb->v1 = vd;
    tb->v2 = vc;

    tb->t0 = td;
    tb->t1 = ta;
    tb->t2 = tc;

//    tc->v = {va, vb, vd};
//    tc->t = {td, tb, ta};

    tc->v0 = va;
    tc->v1 = vb;
    tc->v2 = vd;

    tc->t0 = td;
    tc->t1 = tb;
    tc->t2 = ta;

//    td->v = {vb, vc, vd};
//    td->t = {tb, tc, ta};

    td->v0 = vb;
    td->v1 = vc;
    td->v2 = vd;

    td->t0 = tb;
    td->t1 = tc;
    td->t2 = ta;

    tetra.triangles[0] = ta;
    tetra.triangles[1] = tb;
    tetra.triangles[2] = tc;
    tetra.triangles[3] = td;

    tetra.vertices[0] = va;
    tetra.vertices[1] = vb;
    tetra.vertices[2] = vc;
    tetra.vertices[3] = vd;
}

Mesh::Mesh()
{
    create_tetra();
}

void Mesh::draw()
{
    glBegin(GL_TRIANGLES);
    draw_tetra();
    glEnd();
}

void Mesh::set_color(Color color)
{
    glColor3dv(&color.x);
}

void Mesh::draw_triangle(Triangle triangle)
{
    triangle;
    glVertex3dv(triangle.v0.pos);
    glVertex3dv(triangle.v1.pos);
    glVertex3dv(triangle.v2.pos);
}

void Mesh::draw_tetra()
{
    set_color(green);
    draw_triangle(*tetra.triangles[0]);

    set_color(red);
    draw_triangle(*tetra.triangles[1]);

    set_color(yellow);
    draw_triangle(*tetra.triangles[2]);

    set_color(blue);
    draw_triangle(*tetra.triangles[3]);
}
