#include "segment.h"
namespace geometry {
Segment::Segment() {
}

Segment::Segment(Point start, Point end) : start_(start), end_(end) {
}
Point Segment::GetEnd() const {
    return end_;
}
Point Segment::GetStart() const {
    return start_;
}
}  // namespace geometry