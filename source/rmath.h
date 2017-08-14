//
//  rmath.h
//  render
//
//  Created by chao on 2017/8/7.
//  Copyright © 2017年 chao. All rights reserved.
//

#ifndef rmath_h
#define rmath_h

#include <cmath>

const float floatEqualValue = 0.001f;
const float PI = 3.1415926535f;

static inline bool floatEqual(float f1, float f2)
{
    return fabsf(f1 - f2) <= floatEqualValue;
}

static inline bool radiansFromDegrees(float degrees)
{
    return PI * degrees / 180.0f;
}

static inline bool degreesFromRadians(float radians)
{
    return 180 * radians /PI;
}

#endif /* rmath_h */
