#include "segment.h"
namespace geometry {
Segment::Segment() {
}

Segment::Segment(Point start, Point end) : start_(start), end_(end) {
}

Point Segment::GetStart() const {
    return start_;
}

Point Segment::GetEnd() const {
    return end_;
}
double Segment::Distance(Point point) const {
    double length = std::sqrt(static_cast<double>((end_.GetX() - start_.GetX()) * (end_.GetX() - start_.GetX()) +
                                                  (end_.GetY() - start_.GetY()) * (end_.GetY() - start_.GetY())));

    if (length < EPSILON) {
        double dstart = start_.Distance(point);
        double dend = end_.Distance(point);
        auto minimal = std::min(dstart, dend);
        return minimal;
    }

    double tat = static_cast<double>(std::pow((point.GetX() - start_.GetX()), 2)) +
                 std::pow((point.GetY() - start_.GetY()), 2) / std::pow(length, 2);

    if (tat < 0) {
        return start_.Distance(point);
    }

    if (tat > 1) {
        return end_.Distance(point);
    }

    double proj_x = static_cast<double>(start_.GetX()) +
                    tat * (static_cast<double>(end_.GetX()) - static_cast<double>(start_.GetX()));
    double proj_y = static_cast<double>(start_.GetY()) +
                    tat * (static_cast<double>(end_.GetY()) - static_cast<double>(start_.GetY()));

    return std::sqrt(static_cast<double>(std::pow((static_cast<double>(point.GetX()) - proj_x), 2) +
                                         std::pow((static_cast<double>(point.GetY()) - proj_y), 2)));
}

bool Segment::Degenerate() const {
    return start_.GetX() == end_.GetX() && start_.GetY() == end_.GetY();
}
Segment& Segment::Move(const Vector& vector) {
    start_ = start_.Move(vector);
    end_ = end_.Move(vector);
    return *this;
}

}  // namespace geometry