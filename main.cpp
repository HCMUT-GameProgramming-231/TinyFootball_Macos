#include "../header/CollisionDetector.h"
#include <iostream>

using namespace std;
int main() {
    Vector v1(0,0);
    Vector v2(2,2);
    Circle c(v1, 2);
    Rectangle r(v2, 2, 4);
    CollisionDectector d;
    cout << d.CircleAndRect(c,r);
}