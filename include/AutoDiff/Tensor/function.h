//
// Created by Administrator on 2018/1/22.
//

#ifndef AUTODIFF_FUNCTION_H
#define AUTODIFF_FUNCTION_H

#include "tensor.h"
void fill(const Tensor &t, float value);

Tensor add(const Tensor &t, float val);
void add_(Tensor &t, float val);

#endif //AUTODIFF_FUNCTION_H
