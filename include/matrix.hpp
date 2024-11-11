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
*  In order that the Tensor class can be treated like any other multidimensional C array,
*  we use a special, temporary, interim class coupled with a few of "operator[]"
*  overloads.
*
*  We are relying a LOT on the compiler choosing the correct overloads.
*
*  To keep things simple, the size and shape of the Tensor, set upon
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

    //Even if we don't know the values at construction, we will
    //always know the rank and shape of the tensor. Hence,
    //we can allocate the precise amount of memory we need
    //at construction.
    template <typename T> class __Tensor {
    
        protected:
        int* shape;
        int rank;
        void* data;  //This is because we can 

        //Constructors:
        public:
        __Tensor(int rank, int* shape);
    
        //Destructors:
        public:
        ~__Tensor();

        //API:
        public:
           int get_shape(int dimension);
           T operator[](int index);
           const __Tensor<T>& operator[](int index) const;
    };

/*
    template <typename T,
        typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr
    > class Tensor : __Tensor<T> {
        //Constructors:        
        public:
        Tensor(int* dimension_sizes, int num_dimensions) : __Tensor<T> (dimension_sizes, num_dimensions);
        Tensor(__Tensor<T> &lvalue);
    
        public:
        ~Tensor();

        public:
        __InterimTensor<T> operator[](int index);
    };


    //The next two classes are hacks to allow us to iterate
    //over Tensor objects like C arrays.
    template <typename T> class __FinalTensor : __InterimTensor<T> {
        private:
        int* index_stores;

        public:
        __FinalTensor(__Tensor<T>&& rvalue) : __InterimTensor<T>(std::move(rvalue));
        
        T operator[](int index);
    };

    template <typename T> class __InterimTensor : __Tensor<T>{
        //Hello.
        private:
        int** dim_indices;  //Allocated when created, size = dimensionality of source Tensor.

        //MoveConstructors:
        public:
        __InterimTensor(__Tensor<T>&& rvalue);

        //Destructors:
        ~__InterimTensor();

        //API
  
        //Cannot have multiple operator[] overloads with different return types.
        __FinalTensor<T> operator[](int index);
        //Tensor<T> operator[](int index);  //When you are trying to isolate a slice.
        //S__InterimTensor<T> operator[](int index);
    };
*/
};