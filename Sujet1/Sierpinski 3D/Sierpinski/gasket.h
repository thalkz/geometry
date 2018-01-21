#ifndef GASKET_H
#define GASKET_H

struct point {
    double x, y, z;
};

class Gasket
{
public:
    Gasket();

    void draw(); // Fonction contenant l'affichage des primitives composant la scène

private:
    point * points;
};

#endif // GASKET_H
