#include "line.h"

#include <cmath>

#include "segment.h"
#include "vector.h"
namespace geometry {
double CrossProduct(const Vector& v1, const Vector& v2) {
    return static_cast<double>(v1.GetX() * v2.GetY() - v1.GetY() * v2.GetX());
}
constexpr double EPSILON = 1e-9;
int64_t Line::GetC() const {
    return -GetA() * start_.GetX() - GetB() * start_.GetY();
}

Line::Line() : start_(0, 0), end_(0, 0) {
}

Line::Line(Point start, Point end) : start_(start), end_(end) {
}

int64_t Line::GetA() const {
    return end_.GetY() - start_.GetY();
}

int64_t Line::GetB() const {
    return start_.GetX() - end_.GetX();
}

double Line::Distance(Point point) const {
    return std::abs(static_cast<double>(GetA() * point.GetX() + GetB() * point.GetY() + GetC())) /
           std::sqrt(std::pow(GetA(), 2) + std::pow(GetB(), 2));
}

Line& Line::Move(const Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}

bool Line::ContainsPoint(const Point& point) const {
    if (std::abs(static_cast<double>(start_.GetX() - end_.GetX())) < EPSILON) {
        return std::abs(static_cast<double>(point.GetX() - start_.GetX())) < EPSILON;
    }
    return std::abs(static_cast<double>(point.GetY()) - static_cast<double>(start_.GetY()) -
                    static_cast<double>(end_.GetY() - start_.GetY()) /
                        static_cast<double>(end_.GetX() - start_.GetX()) *
                        static_cast<double>(point.GetX() - start_.GetX())) < EPSILON;
}

bool Line::CrossesSegment(const Segment& segment) const {
    Vector start(segment.GetStart().GetX() - start_.GetX(), segment.GetStart().GetY() - start_.GetY());
    Vector end(segment.GetEnd().GetX() - start_.GetX(), segment.GetEnd().GetY() - start_.GetY());

    Vector livec(end_.GetX() - start_.GetX(), end_.GetY() - start_.GetY());
    if (CrossProduct(livec, start) * CrossProduct(livec, end) <= 0) {
        return true;
    }
    return false;
}

Line* Line::Clone() const {
    return new Line(*this);
}

}  // namespace geometry