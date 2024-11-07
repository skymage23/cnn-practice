#include <cstdarg>
#include <vector>

/*
*
*  In order that the Matrix class can be treated like any other multidimensional C array,
*  we use a special, temporary, interim class coupled with a few of "operator[]"
*  overloads.
*
*  We are relying a LOT on the compiler choosing the correct overrides.
*/
namespace cnn_practice {
    template <typename T> class __Matrix {
    
        protected:
        int dimensionality;
        void* data;

        //Constructors:
        public:
        __Matrix(int dimensionality);
    
        //Destructors:
        public:
        ~__Matrix();
    
        //API:
        public:
           int get_dimension_size_count(int dimension);
    };

    template <typename T> class __InterimMatrix:__Matrix<T>{
        //Hello.
        private:
        int** dim_indices;  //Allocated when created, size = dimensionality of source Matrix.

        //MoveConstructors:
        public:
        __InterimMatrix(__Matrix<T>&& rvalue);

        //Destructors:
        ~__InterimMatrix();

        //API
        __InterimMatrix<T> operator[](int index);
        T operator[](int index);
        Matrix operator[](int index);  //When you are trying to isolate a slice.
    };

    template <typename T> class Matrix:__Matrix<T> {
        //Constructors:        
        public:
        Matrix();
        Matrix(__Matrix&);
        Matrix(__InterimMatrix&)
    
        public:
        ~Matrix();

        public:
        __InterimMatrix operator[](int index);
    };
};