#include "complex.h"

complex complex::operator+(complex rhs) {
    complex ans(a_ + rhs.a_, b_ + rhs.b_);
    return ans;
}

complex complex::operator-(complex rhs) {
    complex ans(a_ - rhs.a_, b_ - rhs.b_);
    return ans;
}

complex complex::operator*(complex rhs) {
    complex ans(a_ * rhs.a_ - b_ * rhs.b_, a_ * rhs.b_ + b_ * rhs.a_);
    return ans;
}

complex complex::operator/(complex rhs) {
    double d = rhs.a_ * rhs.a_ + rhs.b_ * rhs.b_;
    complex ans((a_ * rhs.a_ + b_ * rhs.b_) / d, (rhs.a_ * b_ - a_ * rhs.b_) / d);
    return ans;
}

double complex::module() {
    return std::sqrt(a_ * a_ + b_ * b_);
}

double complex::get_a() {
    return a_;
}
double complex::get_b() {
    return b_;
}
