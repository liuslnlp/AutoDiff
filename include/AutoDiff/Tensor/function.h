//
// Created by Administrator on 2018/1/22.
//

#ifndef AUTODIFF_FUNCTION_H
#define AUTODIFF_FUNCTION_H

#include <cmath>
#include "tensor.h"

void fill(const Tensor &t, float value);

float mean(const Tensor &t){
    return sum(t) / t.storage().size();
}
Tensor mean(const Tensor &t, int axis);

Tensor add(const Tensor &t, float val);
void add_(Tensor &t, float val);

Tensor exp(const Tensor &t){
    Tensor r(t);
    auto storage = r.storage();
    for(size_t i = 0; i < r.storage().size(); ++i){
        storage.set(i, std::exp(storage.get(i)));
    }
    return r;
}
Tensor pow(const Tensor &t, float val);
Tensor sum(const Tensor &t, int axis);
float sum(const Tensor &t){
    auto storage = t.storage();
    float count = 0;
    for(size_t i = 0; i < r.storage().size(); ++i){
        count += storage.get(i);
    }
    return count;
}

#endif //AUTODIFF_FUNCTION_H
