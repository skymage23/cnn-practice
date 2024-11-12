#include <cstdlib>
#include <exceptions.hpp>
#include <tensor.hpp>

namespace cnn_practice {
    #define TENSOR_CNSRT(x) template <typename T> __Tensor<T>::x    
    #define TENSOR_BASE_RET(x,y) template<typename T> x __Tensor<T>::y

    TENSOR_CNSTR(__Tensor<T>(int rank, const int const* shape)){
        int temp = 1;
        void *ptr_temp = nullptr;

        if (rank == 0){
            throw exceptions::ArgumentError("rank cannot be 0");
        }

        if (shape == nullptr) {
            throw exceptions::ArgumentError("shape cannot be NULL");
        }
        this -> rank = rank
        this -> shape = shape; //Do I need a cast?

        //Calculate the total amount of memory we need to allocate
        //so we that we only need to call malloc once.
        for (int i = 0; i < rank; i++){
            temp *= shape[i];
        }

        ptr_temp = malloc(sizeof(T)*temp);
        if (ptr_temp == nullptr) {
            throw exceptions::OutOfMemoryException();
        }
        
        this -> data = ptr_temp;
    }
};