
// Created by Elad Aharon & Shahar Palmor on 29/10/17.
// ID: 311200786 307929927
//

#ifndef EX02_POINT_H
#define EX02_POINT_H

#include <vector>
#include <string>

using namespace std;

class Point {
public:
    Point(int x, int y);
    Point(const Point &p);
    ~Point();

    Point& operator =(const Point &point);
    bool operator ==(const Point &point);

    int getX() const;
    int getY() const;
    const vector<Point*> &getDirVector() const;

    void setX(int x);
    void setY(int y);

    void insertFlowPoint(Point *p);
    bool isEqual(const Point &p) const;
    string toString() const;

private:
    int x;
    int y;
    vector<Point*> flowDirection;
};


#endif //EX02_POINT_H
