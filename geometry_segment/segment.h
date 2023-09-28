#ifndef GEOMETRYCLASSES__SEGMENT_H_
#define GEOMETRYCLASSES__SEGMENT_H_

#include "i_shape.h"
#include "point.h"
#include "vector.h"

namespace geometry {
class Segment : public IShape {
private:
    Point start_;
    Point end_;

public:
    const double EPSILON = 1e-10;

    Segment();

    Segment(Point, Point);

    Point GetStart() const;

    Point GetEnd() const;

    double Distance(Point) const;

    bool Degenerate() const;

    Segment& Move(const Vector& vector) override;

    bool ContainsPoint(const Point& point) const override {
        Vector v1(end_ - start_);
        Vector v2(point - start_);
        Vector v3(point - end_);

        if (std::abs(CrossProduct(v1, v2)) > EPSILON) {
            return false;
        }

        return v2.Length() <= v1.Length() && v3.Length() <= v1.Length();
    }

    static bool Between(const Point& a, const Point& b, const Point& c) {
        return (c.GetX() - a.GetX()) * (b.GetX() - c.GetX()) >= 0 && (c.GetY() - a.GetY()) * (b.GetY() - c.GetY()) >= 0;
    }

    static double CrossProduct(const Vector& a, const Vector& b) {
        return static_cast<double>(a.GetX() * b.GetY() - a.GetY() * b.GetX());
    }

    bool CrossesSegment(const Segment& other) const override {
        double v1 = CrossProduct(other.end_ - other.start_, start_ - other.start_);
        double v2 = CrossProduct(other.end_ - other.start_, end_ - other.start_);
        double v3 = CrossProduct(end_ - start_, other.start_ - start_);
        double v4 = CrossProduct(end_ - start_, other.end_ - start_);

        if ((v1 * v2 < 0) && (v3 * v4 < 0)) {
            return true;
        }

        if (v1 == 0 && Between(other.start_, other.end_, start_)) {
            return true;
        }

        if (v2 == 0 && Between(other.start_, other.end_, end_)) {
            return true;
        }

        if (v3 == 0 && Between(start_, end_, other.start_)) {
            return true;
        }

        if (v4 == 0 && Between(start_, end_, other.end_)) {
            return true;
        }

        return false;
    }

    Segment* Clone() const override {
        return new Segment(*this);
    }
};
}  // namespace geometry

#endif  // GEOMETRYCLASSES__SEGMENT_H_
