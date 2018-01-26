//
// Created by Administrator on 2018/1/26.
//

#include "blas.h"

float dot(size_t n, float *x, size_t incx, float *y, size_t incy)
{
    float sum=0;
    size_t i;
    for(i = 0; i < n; ++i)
        sum += x[i * inx] * y[i * incy];
    return sum;
}

