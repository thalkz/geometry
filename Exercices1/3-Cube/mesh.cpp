#include "mesh.h"
#include <gl.h>
#include <cstdlib>
#include <time.h>
#include <QtGlobal>
#include <iostream>
#include <fstream>
#include <string>
#include <QDebug>
using namespace std;

Vertex *vertices;
Face *faces;

int nv, nf;

void read_dataset()
{
    // Container holding last line read
    string readLine;

    // Containers for delimiter positions
    int delimiterPos_1, delimiterPos_2, delimiterPos_3, delimiterPos_4, delimiterPos_5;

    // Open file for reading
    ifstream in("/Users/roland/Code/Geometry/Exercices1/cube.off");

    // Check if file is in OFF format
    getline(in, readLine);
    if (readLine != "OFF")
    {
        cout << "The file to read is not in OFF format." << endl;
        return;
    }

    // Read values for Nv and Nf
    getline(in, readLine);

    delimiterPos_1 = readLine.find(" ", 0);
    nv = atoi(readLine.substr(0,delimiterPos_1+1).c_str());
    delimiterPos_2 = readLine.find(" ", delimiterPos_1);
    nf = atoi(readLine.substr(delimiterPos_1,delimiterPos_2 +1).c_str());

    // Read the vertices
    vertices = new Vertex[nv];

    for (int n = 0; n < nv; n++)
    {
        getline(in, readLine);
        delimiterPos_1 = readLine.find(" ", 0);
        vertices[n].pos[0] = atof(readLine.substr(0,delimiterPos_1).c_str());
        delimiterPos_2 = readLine.find(" ", delimiterPos_1+1);
        vertices[n].pos[1] = atof(readLine.substr(delimiterPos_1,delimiterPos_2 ).c_str());
        delimiterPos_3 = readLine.find(" ", delimiterPos_2+1);
        vertices[n].pos[2] = atof(readLine.substr(delimiterPos_2,delimiterPos_3 ).c_str());

        qDebug() << "Vertex #" << n << " : " << vertices[n].pos[0] << vertices[n].pos[1] << vertices[n].pos[2];
    }

    faces = new Face[nf];

    for (int n = 0; n < nf; n++)
    {
        int v1, v2, v3, v4, v5;

        getline(in, readLine);
        delimiterPos_1 = readLine.find(" ", 0);
        v1 = atoi(readLine.substr(0,delimiterPos_1).c_str());
        delimiterPos_2 = readLine.find(" ", delimiterPos_1+1);
        v2 = atoi(readLine.substr(delimiterPos_1, delimiterPos_2 ).c_str());
        delimiterPos_3 = readLine.find(" ", delimiterPos_2+1);
        v3 = atoi(readLine.substr(delimiterPos_2, delimiterPos_3 ).c_str());
        delimiterPos_4 = readLine.find(" ", delimiterPos_3+1);
        v4 = atoi(readLine.substr(delimiterPos_3, delimiterPos_4 ).c_str());
        delimiterPos_5 = readLine.find(" ", delimiterPos_4 + 1);
        v5 = atoi(readLine.substr(delimiterPos_4, delimiterPos_5 ).c_str());

        qDebug() << "Face #" << n << " : " << v2 << v3 << v4 << v5;

        faces[n].v[0] = vertices[v2];
        faces[n].v[1] = vertices[v3];
        faces[n].v[2] = vertices[v4];
        faces[n].v[3] = vertices[v5];
    }
}

Vertex create_vertex(double x, double y, double z, Triangle* t) {
    Vertex *result = new Vertex;
    result->pos[0] = x;
    result->pos[1] = y;
    result->pos[2] = z;
    result->t = t;
    return *result;
}

Mesh::Mesh()
{
    read_dataset();
}

void Mesh::draw()
{
    glBegin(GL_QUADS);
    draw_tetra();
    glEnd();
}

void Mesh::set_color(Color color)
{
    glColor3dv(&color.x);
}

void Mesh::draw_triangle(Triangle triangle)
{
    glVertex3dv(triangle.v0.pos);
    glVertex3dv(triangle.v1.pos);
    glVertex3dv(triangle.v2.pos);
}

void Mesh::draw_tetra()
{
    for (int i = 0; i < nf; i++) {

        Color c = { (double) (i+ 1)/nf, 0.0, 0.0};

        set_color(c);

        glVertex3dv(faces[i].v[0].pos);
        glVertex3dv(faces[i].v[1].pos);
        glVertex3dv(faces[i].v[2].pos);
        glVertex3dv(faces[i].v[3].pos);
    }
}
