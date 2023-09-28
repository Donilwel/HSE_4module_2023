#define sc static_cast<double>
#include "polygon.h"

#include "line.h"
#include "segment.h"
namespace geometry {
Polygon::Polygon() = default;
Polygon::Polygon(std::vector<Point> points) : points_(points), num_points_(points_.size()) {
}
Polygon& Polygon::Move(const Vector& vector) {
    for (auto i = 0; i < num_points_; ++i) {
        points_[i].Move(vector);
    }
    return *this;
}
bool Polygon::ContainsPoint(const Point& point) const {
    auto l = Line(point, Point(point.GetX() + 1, point.GetY() + 4));
    size_t inc = 0;

    const auto min_double = 10e-9;

    for (auto i = 0; i < num_points_; ++i) {
        auto current_segment = Segment(points_[i], points_[(i + 1) % num_points_]);

        if (current_segment.ContainsPoint(point)) {
            return true;
        }

        if (l.ContainsPoint(current_segment.GetStart()) && l.ContainsPoint(current_segment.GetEnd())) {
            if (std::max(current_segment.GetStart().GetX(), current_segment.GetEnd().GetX()) < point.GetX()) {
                continue;
            }
            ++inc;
            continue;
        }
        if (l.CrossesSegment(current_segment) && (!l.ContainsPoint(current_segment.GetStart()))) {
            auto il = sc(current_segment.GetStart().GetX());
            auto bi = sc(current_segment.GetStart().GetY());
            auto c = sc(current_segment.GetEnd().GetX());
            auto d = sc(current_segment.GetEnd().GetY());
            auto x = sc(point.GetX());
            auto y = sc(point.GetY());
            auto m = y - x * 4;
            if (std::abs(il - c) < min_double) {
                if (il - x > min_double) {
                    ++inc;
                }
                continue;
            }
            auto x_i = (il * (d - m) - (bi + m) * c) / (4 * il - 4 * c - bi + d);
            auto y_i = 4 * x_i + m;
            if (x_i - x > min_double && y_i - y > min_double) {
                ++inc;
            }
        }
    }

    return inc % 2 == 1;
}
bool Polygon::CrossesSegment(const Segment& segment) const {
    for (auto i = 0; i < num_points_; ++i) {
        auto poi = points_[(i + 1) % num_points_];
        if (((segment.GetEnd().GetY() - segment.GetStart().GetY()) * (points_[i].GetX() - segment.GetEnd().GetX()) -
             (segment.GetEnd().GetX() - segment.GetStart().GetX()) * (points_[i].GetY() - segment.GetEnd().GetY())) *
                    ((segment.GetEnd().GetY() - segment.GetStart().GetY()) * (poi.GetX() - segment.GetEnd().GetX()) -
                     (segment.GetEnd().GetX() - segment.GetStart().GetX()) * (poi.GetY() - segment.GetEnd().GetY())) <
                0 &&
            ((poi.GetY() - points_[i].GetY()) * (segment.GetStart().GetX() - poi.GetX()) -
             (poi.GetX() - points_[i].GetX()) * (segment.GetStart().GetY() - poi.GetY())) *
                    ((poi.GetY() - points_[i].GetY()) * (segment.GetEnd().GetX() - poi.GetX()) -
                     (poi.GetX() - points_[i].GetX()) * (segment.GetEnd().GetY() - poi.GetY())) <
                0) {
            return true;
        }
        if ((segment.GetEnd().GetY() - segment.GetStart().GetY()) * (points_[i].GetX() - segment.GetEnd().GetX()) -
                    (segment.GetEnd().GetX() - segment.GetStart().GetX()) *
                        (points_[i].GetY() - segment.GetEnd().GetY()) ==
                0 &&
            points_[i].CrossesSegment(segment)) {
            return true;
        }
        if ((segment.GetEnd().GetY() - segment.GetStart().GetY()) * (poi.GetX() - segment.GetEnd().GetX()) -
                    (segment.GetEnd().GetX() - segment.GetStart().GetX()) * (poi.GetY() - segment.GetEnd().GetY()) ==
                0 &&
            poi.CrossesSegment(segment)) {
            return true;
        }
        if ((poi.GetY() - points_[i].GetY()) * (segment.GetStart().GetX() - poi.GetX()) -
                    (poi.GetX() - points_[i].GetX()) * (segment.GetStart().GetY() - poi.GetY()) ==
                0 &&
            segment.GetStart().CrossesSegment({points_[i], poi})) {
            return true;
        }
        if ((poi.GetY() - points_[i].GetY()) * (segment.GetEnd().GetX() - poi.GetX()) -
                    (poi.GetX() - points_[i].GetX()) * (segment.GetEnd().GetY() - poi.GetY()) ==
                0 &&
            segment.GetEnd().CrossesSegment({points_[i], poi})) {
            return true;
        }
    }
    return false;
}
Polygon* Polygon::Clone() const {
    auto cp = new Polygon(points_);
    return cp;
}
}  // namespace geometry