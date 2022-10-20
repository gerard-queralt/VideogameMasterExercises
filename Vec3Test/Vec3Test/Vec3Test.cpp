#include <iostream>
#include "Vec3.h"
#include "Vec3f.h"

int main()
{
    Vec3<int> a(0, 0, 0);
    Vec3<int> b(1, 2, 3);
    a.print();
    a = a + b;
    a.print();
    a = a + a;
    a.print();
    b.Normalize().print();
    std::cout << a.distance_to(b) << "\n";
    std::cout << a.dot_product(b) << "\n";
    a.cross_product(b).print();
    std::cout << a.angle_between(b) << "\n";
    std::cout << Vec3<int>(0, 1, 0).angle_between(Vec3<int>(0, -1, 0)) << "\n";

    Vec3f c(0.f, 0.f, 0.f);
}

