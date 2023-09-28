#include "ray.h"

#include "point.h"
#include "segment.h"
#include "vector.h"

namespace geometry {
Ray::Ray() {
}
Ray::Ray(Point first, Point second) : start_(first), end_(second) {
}
Ray& Ray::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}
const double EPSILON = 1e-9;
bool Ray::ContainsPoint(const Point& point) const {
    Vector v1(end_ - start_);
    Vector v2(point - start_);
    double lenght_m = v1.Length() * v2.Length();
    return std::abs(v1.DotProduct(v2) - lenght_m) < EPSILON && v1.DotProduct(v2) >= 0;
}
static double CrossProduct(const Vector& a, const Vector& b) {
    return static_cast<double>(a.GetX() * b.GetY() - a.GetY() * b.GetX());
}
bool Ray::CrossesSegment(const Segment& segment) const {

    double cross_1 = CrossProduct(segment.GetEnd() - segment.GetStart(), start_ - segment.GetStart());
    double cross_2 = CrossProduct(segment.GetEnd() - segment.GetStart(), end_ - start_);
    if (cross_1 * cross_2 <= EPSILON) {
        double cross_3 = CrossProduct(end_ - start_, segment.GetStart() - start_);
        double cross_4 = CrossProduct(end_ - start_, segment.GetEnd() - start_);
        return cross_3 * cross_4 <= EPSILON;
    }
    return false;
}

Ray* Ray::Clone() const {
    return new Ray(*this);
}

Point Ray::GetStart() const {
    return start_;
}

Point Ray::GetEnd() const {
    return end_;
}
}  // namespace geometry
