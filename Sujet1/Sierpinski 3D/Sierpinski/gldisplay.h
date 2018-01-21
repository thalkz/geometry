#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>
#include <gasket.h>
#include <QMouseEvent>

class GLDisplay : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDisplay(QWidget *parent = 0);

    virtual void initializeGL();

    virtual void paintGL(); // Fonction provoquant l'affichage du gasket

    virtual void resizeGL(int w, int h); // Fonction dans laquelle est également spécifiée la boite délimitant la scène à afficher

protected:
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );

private:
    void drawSierpinski();
    Gasket gasket;

    float _angle;
    QPoint _position;
    
signals:
    
public slots:
    
};

#endif // GLDISPLAY_H
