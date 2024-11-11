#include <matrix.hpp>

namespace cnn_practice {
    #define MATRIX_CNSRT(x) template <typename T> __Tensor<T>::x    
    #define MATRIX_BASE_RET(x,y) template<typename T> x __Tensor<T>::y
/*
    MATRIX_CNSRT(__Tensor(int dimensionality)){

    }

    MATRIX_CNSRT(~__Tensor()){

    }

    MATRIX_BASE_RET(int, get_dimension_size_count(int dimension)){

    }

    #define INTERIM_MATRIX_CNSRT(x) template <typename T> __InterimTensor<T>::x
    #define INTERIM_MATRIX_BASE_RET(x,y) template <typename T> x __InterimTensor<T>::y

    INTERIM_MATRIX_CNSRT(__InterimTensor(__Tensor<T>& rvalue)){

    }

    INTERIM_MATRIX_CNSRT(~__InterimTensor()){

    }

    INTERIM_MATRIX_BASE_RET(__InterimTensor<T>, operator[](int index)){

    }

    INTERIM_MATRIX_BASE_RET(T, operator[](int index)){

    }

    INTERIM_MATRIX_BASE_RET(Tensor<T>, operator[](int index)){

    }
*/
};