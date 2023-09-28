#ifndef GEOMETRYCLASSES__POINT_H_
#define GEOMETRYCLASSES__POINT_H_
#include <cmath>

#include "i_shape.h"

namespace geometry {
class Point : public IShape {
public:
    double DistanceTo(const Point& other) const {
        double dx = static_cast<double>(x_coord_ - other.x_coord_);
        double dy = static_cast<double>(y_coord_ - other.y_coord_);
        return std::sqrt(dx * dx + dy * dy);
    }
    int64_t GetX() const;

    int64_t GetY() const;

    void SetX(int64_t);

    void SetY(int64_t);

    Point& Move(const Vector&) override;

    bool ContainsPoint(const Point&) const override;

    bool CrossesSegment(const Segment&) const override;

    Point* Clone() const override;

    Point() = default;

    Point(int64_t, int64_t);

    Vector operator-(Point other) const;
    double Distance(const Point& other) const {
        double dx = static_cast<double>(x_coord_ - other.x_coord_);
        double dy = static_cast<double>(y_coord_ - other.y_coord_);
        return std::sqrt(dx * dx + dy * dy);
    }

private:
    int64_t x_coord_;
    int64_t y_coord_;
};
}  // namespace geometry

#endif  // GEOMETRYCLASSES__POINT_H_
