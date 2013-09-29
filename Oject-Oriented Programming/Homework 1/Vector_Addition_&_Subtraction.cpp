#include <iostream>
using namespace std;

class point {

    double x_;
    double y_;

public:

    point (double x, double y) {
        x_ = x;
        y_ = y;
    }

    double get_x() {
        return x_;
    }

    double get_y() {
        return y_;
    }

    void set_y(double y) {
        y_ = y;
    }

    void set_x(double x) {
        x_ = x;
    }

    void add (point p) {
        x_ += p.x_;
        y_ += p.y_;
    }

    void sub (point p) {
        if (x_ >= p.x_) {
            x_ -= p.x_;
        }
        else {
            x_ = p.x_ - x_;
        }

        if (y_ >= p.y_) {
            y_ -= p.y_;
        }
        else {
            y_ = p.y_ - y_;
        }
    }

};

int main () {

    point p1(4,6);
    point p2(2,4);

    cout << "p1(" << p1.get_x() << "," << p1.get_y() << ");" <<endl;
    cout << "p2(" << p2.get_x() << "," << p2.get_y() << ");\n" <<endl;

    p1.add(p2);
    cout << "Add p1(" << p1.get_x() << "," << p1.get_y() << ");" <<endl;

    p1.set_x(4);
    p1.set_y(6);

    p1.sub(p2);
    cout << "Sub p1(" << p1.get_x() << "," << p1.get_y() << ");" <<endl;

    return 0;
}
