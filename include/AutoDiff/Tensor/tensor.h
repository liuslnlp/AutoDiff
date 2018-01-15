//
// Created by Administrator on 2018/1/15.
//

#ifndef AUTODIFF_TENSOR_H
#define AUTODIFF_TENSOR_H

#include <vector>
typedef float tendata_t;

class Tensor
{
public:
    Tensor(tendata_t *arr, size_t len);
    Tensor();
    Tensor resize(size_t *size, size_t len);
    bool resize_(size_t *size, size_t len);
    Tensor* dot();

private:
    tendata_t *data_;
    int ndim_;
    size_t *size_;// 每个维度的长度
};

#endif //AUTODIFF_TENSOR_H
