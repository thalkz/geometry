#ifndef GASKET_H
#define GASKET_H

struct point {
    double x, y;
};

class Gasket
{
public:
    Gasket();

    void draw(); // Fonction contenant l'affichage des points et des lignes composant la scène

private:
    point * points;
};

#endif // GASKET_H
