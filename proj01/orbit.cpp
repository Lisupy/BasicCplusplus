#include <iostream>
using std::scientific; using std::fixed;

#include <iomanip>
using std::setprecision;

#include <cmath>
using std::cos; using std::sin;
using std::tan; using std::atan;
using std::pow; using std::sqrt;


inline double compute_e(const double &a, const double &b){
    double a2 = a * a;
    double b2 = b * b;
    double e = sqrt(1 - b2/a2);
    return e;
}

inline double compute_E(const double &e, const double &theta){
    double tmp = sqrt((1-e)/(1+e));
    double E = 2.0 * atan(tmp * tan(theta / 2.0));
    return E;
}

inline double deg2rad(double &deg){
    return deg * M_PI / 180.0;
}

inline double rad2deg(double &rad){
    return rad * 180.0 / M_PI;
}

int main(int argc, char *argv[]){
    double a;
    double b;
    double theta_deg;

    std::cout << "Enter the semi-major axis (a):" << std::ends;
    std::cin >> a;
    std::cout << "Enter the semi-minor axis (b):" << std::ends;
    std::cin >> b;
    std::cout << "Enter the true anomaly in degree (θ):" << std::ends;
    std::cin >>theta_deg;

    double theta_rad = deg2rad(theta_deg);
    
    double e = compute_e(a, b);
    double E_rad = compute_E(e, theta_rad);
    double E_deg = rad2deg(E_rad);
    double x = a * (cos(E_rad) - e);
    double y = b * sin(E_rad);
    double r = sqrt( x*x + y*y );

    std::cout << scientific << setprecision(2) << e << std::endl;
    std::cout << fixed << setprecision(1) << E_deg << "°" << std::endl;
    std::cout << scientific << setprecision(2) << r << std::endl;
    std::cout << scientific << setprecision(2) 
              << x << " " << y << std::endl;
    return 0;
}

