
// Created by Elad Aharon & Shahar Palmor on 29/10/17.
// ID: 311200786 307929927
//

#include <sstream>
#include "Point.h"
using namespace std;

Point::Point(int x, int y) : x(x), y(y) {}

Point::Point(const Point &p) {
    x = p.getX();
    y = p.getY();

    // Copy all the directions vector with new allocations.
    for (unsigned int i = 0; i < p.flowDirection.size(); ++i) {
        Point *pointToInsert = new Point(*p.flowDirection.at(i));
        flowDirection.push_back(pointToInsert);
    }
}


int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

void Point::setX(int x) {
    Point::x = x;
}

void Point::setY(int y) {
    Point::y = y;
}

bool Point::isEqual(const Point &p) const {
    return (this->x == p.getX() && this->y == p.getY());
}


void Point::insertFlowPoint(Point *p) {
    for (unsigned int i = 0; i < flowDirection.size(); ++i)
        if (flowDirection.at(i)->isEqual(*p))
            return;

    this->flowDirection.push_back(p);
}

Point::~Point() {
    for (unsigned int i = 0; i < flowDirection.size(); i++) {
        delete(flowDirection.at(i));
    }
    flowDirection.clear();
}

const vector<Point *> &Point::getDirVector() const {
    return flowDirection;
}

string Point::toString() const{
    ostringstream xConvert;
    ostringstream yConvert;

    xConvert << (x + 1);
    yConvert << (y + 1);

    return '(' + xConvert.str() + ',' + yConvert.str() + ')';
}

Point &Point::operator=(const Point &point) {
    if (this != & point) {
        delete(this);

        x = point.x;
        y = point.y;
        for (unsigned int i = 0; i < point.flowDirection.size(); ++i) {
            Point *newFlowDirection = new Point(*point.flowDirection.at(i));
            flowDirection.push_back(newFlowDirection) ;
        }
    }
    return *this;
}

bool Point::operator==(const Point &point) {
    return (x == point.x && y == point.y);
}


