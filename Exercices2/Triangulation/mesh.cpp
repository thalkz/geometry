#include "mesh.h"
#include <gl.h>
#include <cstdlib>
#include <time.h>


struct point {
    double x, y, z;
};


point colors[] = {
                  {0.5,0.1,0.2},
                  {0.1,0.5,0.3},
                  {0.2,0.9,0.4},
                  {0.3,0.7,0.2},
                  {0.6,0.6,0.1},
                  {0.2,0.8,0.2},
                  {1.0,0.0,0.0},
                  {0.0,1.0,0.0},
                  {0.0,0.0,1.0},
                  {1.0,1.0,0.0},
                  {0.0,1.0,1.0},
                  {1.0,0.0,1.0}
                 };

Mesh::Mesh()
{
    build_mesh();
    insert_point(0.5, 0.0, 0.2);
    insert_point(-0.6, 0.2, -0.1);
    insert_point(0.0, 1.0, -0.1);
    insert_point(0.0, -1.0, -0.1);
    insert_point(0.4, 0.9, -0.3);
    insert_point(0.0, -0.6, 0.0);
}

void Mesh::build_mesh()
{
    vertices.clear();
    triangles.clear();

    double mesh_size = 0.7;

    vertices.push_back(Vertex(-1.0 * mesh_size, -1.0 * mesh_size, 0.0, 0)); // s0
    vertices.push_back(Vertex(1.0 * mesh_size, -1.0 * mesh_size, 0.0, 0)); // s1
    vertices.push_back(Vertex(1.0 * mesh_size, 1.0 * mesh_size, 0.0, 0)); // s2
    vertices.push_back(Vertex(-1.0 * mesh_size, 1.0 * mesh_size, 0.0, 1)); // s3
    vertices.push_back(Vertex(0.0, 0.0, -2.0 * mesh_size, 2)); // s_inf

    triangles.push_back(Triangle(0, 1, 2, 3, 1, 4)); // t0
    triangles.push_back(Triangle(0, 2, 3, 2, 5, 0)); // t1

    triangles.push_back(Triangle(3, 2, 4, 3, 5, 1)); // t2
    triangles.push_back(Triangle(2, 1, 4, 4, 2, 0)); // t3
    triangles.push_back(Triangle(0, 4, 1, 3, 1, 5)); // t4
    triangles.push_back(Triangle(0, 3, 4, 2, 4, 1)); // t5

    triangles[2].is_box = true;
    triangles[3].is_box = true;
    triangles[4].is_box = true;
    triangles[5].is_box = true;
}

bool positive_vectoriel(Vertex a, Vertex b, Vertex c)
{
    double ab [2];
    ab[0] = b.x - a.x;
    ab[1] = b.y - a.y;

    double ac [2];
    ac[0] = c.x - a.x;
    ac[1] = c.y - a.y;

    return (ab[0] * ac[1] - ab[1] * ac[0] > 0.0);
}

bool Mesh::is_inside(Triangle triangle, Vertex vertex)
{
    Vertex a = vertices[triangle.vertices_indexes[0]];
    Vertex b = vertices[triangle.vertices_indexes[1]];
    Vertex c = vertices[triangle.vertices_indexes[2]];

    return positive_vectoriel(a, b, vertex)
            && positive_vectoriel(b, c, vertex)
            && positive_vectoriel(c, a, vertex);
}

void Mesh::insert_inside_point(int i, double x, double y, double z)
{
    Triangle old = triangles[i];

    int new_vertex_index = vertices.size();

    int t1_index = i;
    int t2_index = triangles.size();
    int t3_index = triangles.size() + 1;

    Triangle t1 = Triangle(
                old.vertices_indexes[0],
                old.vertices_indexes[1],
                new_vertex_index,
                t2_index,
                t3_index,
                old.triangles_indexes[2]);

    if (t1.vertices_indexes[0] == 4 || t1.vertices_indexes[1] == 4 || t1.vertices_indexes[2] == 4)
    {
        t1.is_box = true;
    }

    Triangle t2 = Triangle(
                new_vertex_index,
                old.vertices_indexes[1],
                old.vertices_indexes[2],
                old.triangles_indexes[0],
                t3_index,
                t1_index);

    if (t2.vertices_indexes[0] == 4 || t2.vertices_indexes[1] == 4 || t2.vertices_indexes[2] == 4)
    {
        t2.is_box = true;
    }

    Triangle t3 = Triangle(
                old.vertices_indexes[0],
                new_vertex_index,
                old.vertices_indexes[2],
                t2_index,
                old.triangles_indexes[1],
                t1_index);

    if (t3.vertices_indexes[0] == 4 || t3.vertices_indexes[1] == 4 || t3.vertices_indexes[2] == 4)
    {
        t3.is_box = true;
    }

    vertices.push_back(Vertex(x, y, z, t1_index));

    triangles[i] = t1;
    triangles.push_back(t2);
    triangles.push_back(t3);
}

void Mesh::insert_outside_point(double x, double y, double z)
{
    int max = (int) triangles.size();

    for (int i = 0; i < max; i++)
    {
        if (triangles[i].is_box)
        {
            continue;
        }

        Vertex a = vertices[triangles[i].vertices_indexes[0]];
        Vertex b = vertices[triangles[i].vertices_indexes[1]];
        Vertex c = vertices[triangles[i].vertices_indexes[2]];

        Vertex new_vertex = Vertex(x, y, z, 0);

        if (triangles[triangles[i].triangles_indexes[2]].is_box &&
                !positive_vectoriel(a, b, new_vertex))
        {
            insert_inside_point(triangles[i].triangles_indexes[2], x, y, z);
        }

        if (triangles[triangles[i].triangles_indexes[0]].is_box &&
                !positive_vectoriel(b, c, new_vertex))
        {
            insert_inside_point(triangles[i].triangles_indexes[0], x, y, z);
        }

        if (triangles[triangles[i].triangles_indexes[1]].is_box &&
                !positive_vectoriel(c, a, new_vertex))
        {
            insert_inside_point(triangles[i].triangles_indexes[1], x, y, z);
        }
    }
}

void Mesh::insert_point(double x, double y, double z)
{
    bool found = false;
    for (int i = 0; i < (int) triangles.size(); i++)
    {
        if (is_inside(triangles[i], Vertex(x, y, z, 0)))
        {
            insert_inside_point(i, x, y, z);
            found = true;
            break;
        }
    }

    if (found == false)
    {
        insert_outside_point(x, y, z);
    }
}

void Mesh::draw()
{
    glBegin(GL_TRIANGLES);

    for (int i = 0; i < (int)triangles.size(); i++)
    {
        if (triangles[i].is_box)
        {
           point grey = {0.1 + 0.4 / (1 + (i%5)), 0.1 + 0.4 / (1 + (i%5)), 0.1 + 0.4 / (1 + (i%5))};
           glColor3dv(&grey.x);
        } else
        {
           glColor3dv(&colors[i%12].x);
        }

        Triangle* triangle = &(triangles[i]);

        for (int j = 0; j < 3; j++)
        {
            Vertex* vertex = &vertices[triangle->vertices_indexes[j]];

            // specify vertex
            glVertex3d(vertex->x, vertex->y, vertex->z);
        }

    }
    glEnd();
}
