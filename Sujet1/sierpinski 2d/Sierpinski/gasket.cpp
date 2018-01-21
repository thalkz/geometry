#include "gasket.h"
#include <gl.h>
#include <cstdlib>
#include <time.h>

#define POINTS 6000

Gasket::Gasket()
{
    point vertices[3] = {
        {-1.0f, -1.0f},
        {0.0f,  1.0f},
        {1.0f, -1.0f}
    };

    points = new point[POINTS];

    point p = {0.0, 0.0};

    srand(time(NULL));

    for( int i = 0; i < POINTS; i++ ) {
        int index = rand() % 3;

        point newPoint = { (vertices[index].x + p.x) / 2.0,
                           (vertices[index].y + p.y) / 2.0 };

        p = newPoint;
        points[i] = newPoint;
    }
}

void Gasket::draw()
{
    glBegin(GL_POINTS);

    for( int i = 0; i < POINTS; i++ ) {
        glVertex2f(points[i].x, points[i].y);
    }

    glEnd();
}
