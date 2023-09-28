#define sc static_cast<double>
#include "circle.h"

#include "iostream"
#include "segment.h"

namespace geometry {
Circle::Circle() : centre_(Point()), radius_(0) {
}

Circle::Circle(Point centre, int64_t radius) : centre_(centre), radius_(radius) {
}
Circle& Circle::Move(const Vector& vector) {
    centre_.Move(vector);
    return *this;
}
bool Circle::ContainsPoint(const Point& point) const {
    int64_t f = (point.GetX() - centre_.GetX()) * (point.GetX() - centre_.GetX());
    return (f + (point.GetY() - centre_.GetY()) * (point.GetY() - centre_.GetY()) <= radius_ * radius_);
}

bool Circle::CrossesSegment(const Segment& segment) const {
    double start = sqrt(sc(pow(sc(segment.GetStart().GetX() - centre_.GetX()), 2)) +
                        sc(pow(sc(segment.GetStart().GetY() - centre_.GetY()), 2)));
    double end = sqrt(sc(pow(sc(segment.GetEnd().GetX() - centre_.GetX()), 2)) +
                      sc(pow(sc(segment.GetEnd().GetY() - centre_.GetY()), 2)));
    if ((start <= sc(radius_) && end >= sc(radius_)) || (start >= sc(radius_) && end <= sc(radius_))) {
        return true;
    }
    return start > sc(radius_) && end > sc(radius_) && segment.Distance(centre_) <= sc(radius_);
}

Circle* Circle::Clone() const {
    return new Circle(*this);
}

int64_t Circle::GetRadius() const {
    return radius_;
}

Point Circle::GetCenter() const {
    return centre_;
}

}  // namespace geometry