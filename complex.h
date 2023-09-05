#ifndef COMPLEX_H
#define COMPLEX_H
#include <cmath>

class complex {
 public:
    complex(): a_(0), b_(0) {};
    ~complex() = default;
    complex(double a, double b): a_(a), b_(b) {};
    double get_a();
    double get_b();
    complex operator+(complex rhs);
    complex operator-(complex rhs);
    complex operator*(complex rhs);
    complex operator/(complex rhs);

    double module();
 private:
     double a_, b_;
};

#endif // COMPLEX_H
