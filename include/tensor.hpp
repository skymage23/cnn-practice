#include <vector>

#include <internal/tensor/__tensor.hpp>

#ifndef CNN_PRACTICE_TENSOR
#define CNN_PRACTICE_TENSOR
namespace cnn_practice {
       template <typename T> class Tensor : __Tensor<T> {
        public:
        Tensor(std::vector<int> shape) : __Tensor<T>(shape){}
       // Tensor(Tensor<T>&& input) : __Tensor<T>(std::dynamic_cast<__Tensor<T>>(input)){}
    }; 
};
#endif