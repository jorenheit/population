#ifndef COORDINATE_H
#define COORDINATE_H

// coordinate on a unit sphere

class Coordinate
{
    double d_th;
    double d_phi;

public:
    Coordinate(double th = 0, double phi = 0):
        d_th(th),
        d_phi(phi)
    {}

    double theta() const { return d_th; }
    double phi() const { return d_phi; }
};

double distance(Coordinate const &c1, Coordinate const &c2);

#endif
