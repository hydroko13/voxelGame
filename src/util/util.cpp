#include "util.h"


bool rectOverlaps(float x1, float y1, float w1, float h1,
    float x2, float y2, float w2, float h2)
{

    // WRITTEN BY CHATGPT
    return (x1 < x2 + w2 && x1 + w1 > x2 &&
        y1 < y2 + h2 && y1 + h1 > y2);
}


bool rectOverlapsStrict(float x1, float y1, float w1, float h1,
    float x2, float y2, float w2, float h2)
{

    // WRITTEN BY CHATGPT
    return (x1 < x2 + w2 && x1 + w1 > x2 &&
        y1 < y2 + h2 && y1 + h1 > y2 &&
        x1 + w1 != x2 && x2 + w2 != x1 &&
        y1 + h1 != y2 && y2 + h2 != y1);
}
