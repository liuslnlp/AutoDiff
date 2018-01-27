//
// Created by Administrator on 2018/1/15.
//

#ifndef AUTODIFF_TENSOR_H
#define AUTODIFF_TENSOR_H

#include "storage.h"

#include <vector>
typedef float TDtype

class Tensor
{
public:
    Tensor(const Tensor &t):ndim_(t.ndim_), storage(t.storage){
        memcpy(size_, t.size_, sizeof(size_t) * ndim_);
    }
//    Tensor(const std::vector<TDtype> &v, const std::vector<size_t> &size){
//        len_ = v.size();
//        ndim_ = size.size();
//        data_ = new TDtype[len_];
//        size_t i;
//        for(i = 0; i < len_; ++i)
//            data_[i] = v[i];
//        for(i = 0; i < ndim_; ++i)
//            size_[i] = size[i];
//    }
//    Tensor(TDtype *arr, size_t len);
//    Tensor(TDtype *arr, size_t len, size_t *size, size_t ndim);
    Tensor();
    ~Tensor(){
        delete [] data_;
        delete [] size_;
    }
    void from_array(TDtype *arr, size_t len, size_t *size, size_t ndim);
    bool resize(size_t *size, size_t ndim){
        size_t i, new_size_len = 0;
        for(i = 0; i < ndim; ++ i)
            new_size_len += size[i];
        if (new_size_len != len_)
            return 0;
        if(ndim != ndim_){
            delete size_;
            size_ = new size_t[ndim];
        }
        memcpy(size_, size, sizeof(size_t) * ndim);
    }
    bool squeeze();
    Storage& storage(){
        return storage;
    }
    float *data(){
        return this->storage.get_data();
    }

private:
    Storage storage;
    int ndim_;
    size_t *size_;// 每个维度的长度
    size_t *stride_;
};

#endif //AUTODIFF_TENSOR_H
