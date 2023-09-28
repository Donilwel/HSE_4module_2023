#include "point.h"

#include "segment.h"
#include "vector.h"

namespace geometry {

constexpr double EPSILON = 1e-9;

Point::Point(int64_t x, int64_t y) : x_coord_(x), y_coord_(y) {
}

void Point::SetX(int64_t x) {
    x_coord_ = x;
}

int64_t Point::GetX() const {
    return x_coord_;
}

int64_t Point::GetY() const {
    return y_coord_;
}

Point& Point::Move(const Vector& vector) {
    x_coord_ += vector.GetX();
    y_coord_ += vector.GetY();
    return *this;
}
void Point::SetY(int64_t y) {
    y_coord_ = y;
}

bool Point::ContainsPoint(const Point& point) const {
    return (point.GetX() == x_coord_ && point.GetY() == y_coord_);
}
Vector Point::operator-(const Point other) const {
    return Vector(x_coord_ - other.GetX(), y_coord_ - other.GetY());
}
Point* Point::Clone() const {
    return new Point(*this);
}
bool Point::CrossesSegment(const Segment& segment) const {

    Point v1(segment.GetEnd().GetX() - segment.GetStart().GetX(), segment.GetEnd().GetY() - segment.GetStart().GetY());
    Point v2(x_coord_ - segment.GetStart().GetX(), y_coord_ - segment.GetStart().GetY());

    double cross_product = static_cast<double>(v1.GetX() * v2.GetY() - v1.GetY() * v2.GetX());
    double minim_x =
        std::min(static_cast<double>(segment.GetStart().GetX()), static_cast<double>(segment.GetEnd().GetX()));
    double maxim_x =
        std::max(static_cast<double>(segment.GetStart().GetX()), static_cast<double>(segment.GetEnd().GetX()));
    double maxim_y =
        std::max(static_cast<double>(segment.GetStart().GetY()), static_cast<double>(segment.GetEnd().GetY()));
    double minim_y =
        std::min(static_cast<double>(segment.GetStart().GetY()), static_cast<double>(segment.GetEnd().GetY()));
    if (!(cross_product <= EPSILON)) {
        return false;
    }
    if (static_cast<double>(x_coord_) > maxim_x || static_cast<double>(x_coord_) < minim_x) {
        return false;
    }
    if (static_cast<double>(y_coord_) < minim_y || static_cast<double>(y_coord_) > maxim_y) {
        return false;
    }

    return true;
}
}  // namespace geometry