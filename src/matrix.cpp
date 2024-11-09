#include <matrix.hpp>

namespace cnn_practice {
    #define MATRIX_CNSRT(x) template <typename T> __Matrix<T>::x    
    #define MATRIX_BASE_RET(x,y) template<typename T> x __Matrix<T>::y
    
    MATRIX_CNSRT(__Matrix(int dimensionality)){

    }

    MATRIX_CNSRT(~__Matrix()){

    }

    MATRIX_BASE_RET(int, get_dimension_size_count(int dimension)){

    }

    #define INTERIM_MATRIX_CNSRT(x) template <typename T> __InterimMatrix<T>::x
    #define INTERIM_MATRIX_BASE_RET(x,y) template <typename T> x __InterimMatrix<T>::y

    INTERIM_MATRIX_CNSRT(__InterimMatrix(__Matrix<T>& rvalue)){

    }

    INTERIM_MATRIX_CNSRT(~__InterimMatrix()){

    }

    INTERIM_MATRIX_BASE_RET(__InterimMatrix<T>, operator[](int index)){

    }

    INTERIM_MATRIX_BASE_RET(T, operator[](int index)){

    }

    INTERIM_MATRIX_BASE_RET(Matrix<T>, operator[](int index)){

    }
};