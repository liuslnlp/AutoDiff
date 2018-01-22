//
// Created by Administrator on 2018/1/15.
//

#ifndef AUTODIFF_TENSOR_H
#define AUTODIFF_TENSOR_H

#include <vector>
typedef float TDtype

class Tensor
{
public:
    Tensor(const Tensor & t){
        len_ = t.len_;
        data_ = new TDtype[len_];
        ndim_ = t.ndim_;
        size_ = new size_t[ndim_];
        memcpy(data_, t.data_, sizeof(TDtype) * len_);
        memcpy(size_, t.size_, sizeof(size_t) * ndim_);
    }
    Tensor(const std::vector<TDtype> &v, const std::vector<size_t> &size){
        len_ = v.size();
        ndim_ = size.size();
        data_ = new TDtype[len_];
        size_t i;
        for(i = 0; i < len_; ++i)
            data_[i] = v[i];
        for(i = 0; i < ndim_; ++i)
            size_[i] = size[i];
    }
    Tensor(TDtype *arr, size_t len);
    Tensor(TDtype *arr, size_t len, size_t *size, size_t ndim);
    Tensor();
    ~Tensor(){
        delete [] data_;
        delete [] size_;
    }
    void from_array(TDtype *arr, size_t len, size_t *size, size_t ndim);
    Tensor resize(size_t *size, size_t len);
    Tensor mean(int axis);
    Tensor pow(int p);

private:
    TDtype *data_;
    size_t len_;
    int ndim_;
    size_t *size_;// 每个维度的长度
};

#endif //AUTODIFF_TENSOR_H
