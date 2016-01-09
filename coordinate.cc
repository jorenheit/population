#include "coordinate.h"
#include <cmath>

double distance(Coordinate const &c1, Coordinate const &c2)
{
    using namespace std;

    long double const PI = atan(1) * 4;

    double lat1 = PI / 2 - c1.phi();
    double lat2 = PI / 2 - c2.phi();
    double lon1 = c1.theta();
    double lon2 = c2.theta();

    return acos(cos(lat1) * cos(lat2) * cos(lon1 - lon2) + sin(lat1) * sin(lat2));
}
