#include "segment.h"

namespace geometry {
Segment::Segment() = default;
Segment::Segment(Point point1, Point point2) : start_(point1), end_(point2) {
}
Point Segment::GetStart() const {
    return start_;
}
Point Segment::GetEnd() const {
    return end_;
}
double Segment::Distance(Point point) const {
    double dx = static_cast<double>(end_.GetX() - start_.GetX());
    double dy = static_cast<double>(end_.GetY() - start_.GetY());
    return std::abs(dy * static_cast<double>(point.GetX()) - dx * static_cast<double>(point.GetY()) +
                    static_cast<double>(end_.GetX() * start_.GetY() - end_.GetY() * start_.GetX())) /
           std::sqrt(dx * dx + dy * dy);
}
bool Segment::Degenerate() const {
    return start_.GetX() == end_.GetX() && start_.GetY() == end_.GetY();
}
Segment& Segment::Move(const geometry::Vector& vector) {
    start_.Move(vector);
    end_.Move(vector);
    return *this;
}
bool Segment::ContainsPoint(const Point& point) const {
    return std::min(start_.GetX(), end_.GetX()) <= point.GetX() &&
           point.GetX() <= std::max(start_.GetX(), end_.GetX()) &&
           std::min(start_.GetY(), end_.GetY()) <= point.GetY() &&
           point.GetY() <= std::max(start_.GetY(), end_.GetY()) &&
           (point.GetX() - start_.GetX()) * (end_.GetY() - start_.GetY()) ==
               (end_.GetX() - start_.GetX()) * (point.GetY() - start_.GetY());
}
bool Segment::CrossesSegment(const Segment& segment) const {
    return std::max(std::min(start_.GetX(), end_.GetX()),
                    std::min(segment.GetStart().GetX(), segment.GetEnd().GetX())) <=
               std::min(std::max(start_.GetX(), end_.GetX()),
                        std::max(segment.GetStart().GetX(), segment.GetEnd().GetX())) &&
           std::max(std::min(start_.GetY(), end_.GetY()),
                    std::min(segment.GetStart().GetY(), segment.GetEnd().GetY())) <=
               std::min(std::max(start_.GetY(), end_.GetY()),
                        std::max(segment.GetStart().GetY(), segment.GetEnd().GetY())) &&
           ((end_ - start_).GetX() * (segment.GetStart() - start_).GetY() -
            (end_ - start_).GetY() * (segment.GetStart() - start_).GetX()) *
                   ((end_ - start_).GetX() * (segment.GetEnd() - start_).GetY() -
                    (end_ - start_).GetY() * (segment.GetEnd() - start_).GetX()) <=
               0 &&
           ((segment.GetEnd() - segment.GetStart()).GetX() * (start_ - segment.GetStart()).GetY() -
            (segment.GetEnd() - segment.GetStart()).GetY() * (start_ - segment.GetStart()).GetX()) *
                   ((segment.GetEnd() - segment.GetStart()).GetX() * (end_ - segment.GetStart()).GetY() -
                    (segment.GetEnd() - segment.GetStart()).GetY() * (end_ - segment.GetStart()).GetX()) <=
               0;
}
Segment* Segment::Clone() const {
    auto copy = new Segment(start_, end_);
    return copy;
}
}  // namespace geometry