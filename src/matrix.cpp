#include <matrix.hpp>

namespace cnn_practice {
    #define MATRIX_BASE(x) template <typename T> __Matrix<T>::x    
    #define MATRIX_BASE_RET(t,x) template<typename T> t __Matrix<T>::x
    
    MATRIX_BASE(__Matrix(int dimensionality)){}
    MATRIX_BASE(~__Matrix()){}
    MATRIX_BASE_RET(int, get_dimension_size_count(int dimension)){}

    #define INTERIM_MATRIX_BASE(x) template <typename T> __InterimMatrix<T>::x
    #define INTERIM_MATRIX_BASE_RET(t,x) template <typename T> t __InterimMatrix<T>::x

    INTERIM_MATRIX_BASE(__InterimMatrix(__Matrix<T>&& rvalue)){}
    INTERIM_MATRIX_BASE(~__InterimMatrix()){}
    INTERIM_MATRIX_BASE_RET(__InterimMatrix<T>, operator[](int index)){}
    INTERIM_MATRIX_BASE_RET(T, operator[](int index)){}
};