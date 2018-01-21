#include "gldisplay.h"

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent)
{
}

void GLDisplay::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0, 1.0, 0.0);
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gasket.draw();
}

void GLDisplay::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}
