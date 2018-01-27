//
// Created by Administrator on 2018/1/26.
//

#ifndef AUTODIFF_STORAGE_H
#define AUTODIFF_STORAGE_H

#include <assert.h>

class Storage{
public:
    Storage();
    Storage(float *data, size_t size):size_(size){
        data_ = new float[size];
        memcpy(data_, data, size);
    }
    ~Storage(){
        delete []data_;
    }
    void set(size_t idx, float value){
        assert(idx < size_);
        data_[idx] = value;
    }
    float get(size_t idx){
        assert(idx < size_);
        return data_[i];
    }
    float* get_data(){
        return data_;
    }

    size_t size(){ return size_;}
    void fill(float value){
        for(size_t i = 0; i < size_; ++i)
            data_[i] = value;
    }
private:
    float *data_;
    size_t size_;
};

#endif //AUTODIFF_STORAGE_H
