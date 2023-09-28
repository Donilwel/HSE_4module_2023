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
    const double EPSILON = 1e-9;

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

        if (v1.DotProduct(v2) < 0) {
            return false;
        }

        return v2.Length() <= v1.Length();
    }

    bool CrossesSegment(const Segment& other) const override {
        int64_t v1 = (other.start_.GetX() - start_.GetX()) * (end_.GetY() - start_.GetY()) -
                     (other.start_.GetY() - start_.GetY()) * (end_.GetX() - start_.GetX());
        int64_t v2 = (other.end_.GetX() - start_.GetX()) * (end_.GetY() - start_.GetY()) -
                     (other.end_.GetY() - start_.GetY()) * (end_.GetX() - start_.GetX());
        int64_t v3 = (start_.GetX() - other.start_.GetX()) * (other.end_.GetY() - other.start_.GetY()) -
                     (start_.GetY() - other.start_.GetY()) * (other.end_.GetX() - other.start_.GetX());
        int64_t v4 = (end_.GetX() - other.start_.GetX()) * (other.end_.GetY() - other.start_.GetY()) -
                     (end_.GetY() - other.start_.GetY()) * (other.end_.GetX() - other.start_.GetX());

        return (v1 * v2 <= 0) && (v3 * v4 <= 0);
    }

    Segment* Clone() const override {
        return new Segment(*this);
    }
};
}  // namespace geometry

#endif  // GEOMETRYCLASSES__SEGMENT_H_
