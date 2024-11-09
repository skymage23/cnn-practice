#include <cstdarg>
#include <vector>
/*
* TO-DO:
* 1.) get and value and slice fetch working.
* 2.) Implement the dot product.
*
*/

/*
*
*  In order that the Matrix class can be treated like any other multidimensional C array,
*  we use a special, temporary, interim class coupled with a few of "operator[]"
*  overloads.
*
*  We are relying a LOT on the compiler choosing the correct overloads.
*
*  To keep things simple, the size and shape of the Matrix, set upon
*  object construction, should thereafter be immutable.
*
*  What happens if multiple threads want to read or write to the matrix?
*  Because of how operator overloading works here, we need to keep track
*  of where each thread is in resolving nested calls to "operator[]".
*  
*  A hashtable keyed to the thread ID could work. 
*/

namespace cnn_practice {

    //Keep the base class as generic as possible so we can overload with
    //developer-defined numeric types later.
    template <typename T> class __Matrix {
    
        protected:
        int dimensionality;
        void* data;

        private:
        int* dimension_index_array;


        //Constructors:
        public:
        __Matrix(int dimensionality);
    
        //Destructors:
        public:
        ~__Matrix();
    
        //Operator overloads:
        __Matrix<T> operator[](int index)

        //API:
        public:
           int get_dimension_size_count(int dimension);
    };


    template <typename T,
        typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr
    > class Matrix : __Matrix<T> {
        //Constructors:        
        public:
        Matrix();
        Matrix(__Matrix<T> &rvalue);
    
        public:
        ~Matrix();

        public:
        __Matrix<T> operator[](int index);
    };

/*
    template <typename T> class __InterimMatrix : __Matrix<T>{
        //Hello.
        private:
        int** dim_indices;  //Allocated when created, size = dimensionality of source Matrix.

        //MoveConstructors:
        public:
        __InterimMatrix(__Matrix<T>& rvalue);

        //Destructors:
        ~__InterimMatrix();

        //API
  
        //Cannot have multiple operator[] overloads with different return types.
        T operator[](int index);
        //Matrix<T> operator[](int index);  //When you are trying to isolate a slice.
        //S__InterimMatrix<T> operator[](int index);
    };
*/
};