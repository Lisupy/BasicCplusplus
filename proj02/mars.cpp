#include <iostream>
using std::scientific; using std::fixed;

#include <iomanip>
using std::setprecision;

#include <cmath>
using std::cos; using std::sin;
using std::sqrt;


inline double deg2rad(const double &deg){
    return deg * M_PI / 180.0;
}

inline double rad2deg(const double &rad){
    return rad * 180.0 / M_PI;
}

double Eccentricity(double semi_major, double semi_minor){
    double a2 = semi_major * semi_major;
    double b2 = semi_minor * semi_minor;
    double e = sqrt(1 - b2/a2);
    return e;
}

double EccentricAnomaly(double eccentricity, double true_anomaly){
    double tmp = sqrt((1-eccentricity)/(1+eccentricity));
    double theta = deg2rad(true_anomaly);
    double E = 2.0 * atan(tmp * tan(theta / 2.0));
    return rad2deg(E);
}


double XPos(double semi_major, double semi_minor, double true_anomaly){
    double eccentricity = Eccentricity(semi_major, semi_minor);
    double eccentricAnomaly = EccentricAnomaly(eccentricity, true_anomaly);
    double eccentricAnomaly_rad = deg2rad(eccentricAnomaly);

    return semi_major * (cos(eccentricAnomaly_rad) - eccentricity);
}

double YPos(double semi_major, double semi_minor, double true_anomaly){
    double eccentricity = Eccentricity(semi_major, semi_minor);
    double eccentricAnomaly = EccentricAnomaly(eccentricity, true_anomaly);
    double eccentricAnomaly_rad = deg2rad(eccentricAnomaly);

    return semi_minor * sin(eccentricAnomaly_rad);
}

double Distance(double x1, double y1, double x2, double y2, double phi){
    double phi_rad = deg2rad(phi);
    double _x1 = x1 * cos(phi_rad) - y1 * sin(phi_rad);
    double _y1 = x1 * sin(phi_rad) + y1 * cos(phi_rad);

    double x_diff = x2 - _x1;
    double y_diff = y2 - _y1;

    return sqrt(x_diff * x_diff + y_diff * y_diff);
}

double Distance(double semi_major1, double semi_minor1, double true_anomaly1,
                double semi_major2, double semi_minor2, double true_anomaly2,
                double phi)
{
    double x1 = XPos(semi_major1, semi_minor1, true_anomaly1);
    double x2 = XPos(semi_major2, semi_minor2, true_anomaly2);
    
    double y1 = YPos(semi_major1, semi_minor1, true_anomaly1);
    double y2 = YPos(semi_major2, semi_minor2, true_anomaly2);

    return Distance(x1, y1, x2, y2, phi);
}


