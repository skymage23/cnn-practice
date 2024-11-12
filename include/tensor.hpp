#include <mutex>
#include <thread>
#include <unordered_map>

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
        private:
/*
    If we ever need to be aggressive about cleaning up index
    caches, we can update the __IndexCache class to capture
    a timestamp whenever a read/write operation is initianted
    on the tensor.  Then, elsewhere we periodically check
    this timestamp, subtract it from a current timestamp,
    and compare the value to some predefined record age
    parameter set either at compile time or passed in
    from somewhere. If the age of the index is equal to
    or older than this value, the cache object is deleted.

    How do I prevent one thread from writing to the index of another thread erroneously.
    Other threads should only have authority to destroy index caches that have not
    been accessed by their associated threads recently.
    
    Answer: Since the threads do not have direct access to the cache map, there is very little
            risk of them accessing caches they do not own, and if they do, that is a situation
            that cannot be reasonably accounted for as it implies a programming error or unknown
            out-of-process access.
*/
        class __IndexCache {
            private:
            int* index_cache; //Should always be of size rank - 1;
            int  rank;
            int  curr_index;

            public:
            __IndexCache(int rank);
            ~__IndexCache();
            bool is_cache_full(); //Set each element in the cache to some bogus value
            void reset_cache();
            bool add(int index);
            int get_cache_length();
            int operator[](int index);
        };

        protected:
        int* shape;
        int rank;
        void* data;

        //Hacky stuff to make operator[] work properly:
        private:
        std::unordered_map<std::thread::id, __IndexCache&> index_caches;
        std::mutex index_cache_mutex;

        //Constructors:
        public:
        __Tensor(int rank, int* shape);
        __Tensor(__Tensor<T>&& rvalue);
    
        //Destructors:
        public:
        ~__Tensor();

        //API:
        public:
           int get_shape(int dimension);
           T operator[](int index);
           const __Tensor<T>& operator[](int index) const;
           void operator=(T&& rvalue);
           void operator=(T rvalue);
    };
};