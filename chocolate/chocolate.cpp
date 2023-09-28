#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    if (slices_amount < height * width && (slices_amount % height == 0 || slices_amount % width == 0)) {
        return true;
    }
    return false;
};