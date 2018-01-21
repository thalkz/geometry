#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>
#include <gasket.h>

class GLDisplay : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDisplay(QWidget *parent = 0);

    virtual void initializeGL();

    virtual void paintGL();   // Fonction provoquant l'affichage du gasket

    virtual void resizeGL(int w, int h);

private:
    void drawSierpinski();
    Gasket gasket;
    
signals:
    
public slots:
    
};

#endif // GLDISPLAY_H
