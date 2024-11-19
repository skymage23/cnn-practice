#include <cstdio>
#include <memory>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <vector>

//Project includes:
#include <common.hpp>
#include <exceptions.hpp>
#include <internal/tensor/IndexCache.hpp>


#ifndef CNN_PRACTICE_TENSOR_BASE
#define CNN_PRACTICE_TENSOR_BASE
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
    template <numeric T> class __Tensor {
        private:
        template<numeric A>
        class __IndexCachingTemporaryFetcher {
            private:
            int  cache_len;
            int  curr_index;
            std::shared_ptr<std::vector<int>> index_cache; 
            __Tensor<A>& tensor_ref;

            public:
            __IndexCachingTemporaryFetcher(__Tensor<A>& parent){
                this -> tensor_ref = parent;
                this -> index_cache = std::unique_ptr<std::vector<int>>(
                    new std::vector<int>()
                );
            }
            

            //bool is_cache_full(); //Set each element in the cache to some bogus value
            //int  num_free_elements();
            //void reset_cache();
            //bool add(int index);
            //int get_cache_length();
            __IndexCachingTemporaryFetcher& operator[](int index){
                if (this -> is_cache_full()){
                    throw new exceptions::TensorFetchException();
                }
                this -> add(index);
                return this;
            }
            A operator[](int index){
                if (this -> num_free_elements() != 1){
                    throw new exceptions::TensorFetchException();
                }
                this -> add(index);
                return tensor_ref.get_element(this -> index_cache);
            }
        }

        protected:
        std::unique_ptr<std::vector<unsigned int>> shape;
        int rank;

        //row-major order:
        std::unique_ptr<std::vector<unsigned char>> data;

        //Hacky stuff to make operator[] work properly:
        private:
        bool is_being_moved; //Keep the memory from being freed in the destructor.
        std::unordered_map<std::thread::id, IndexCache> index_caches;

        //Constructors:
        public:
        __Tensor(std::vector<unsigned int> shape){
            int dim_err_str_size = 56; 
            this -> rank = shape.size()
            if (this -> rank == 0){
                throw exceptions::ArgumentException("rank cannot be 0");
            }

            this -> shape = shape;
            
            //Check for sizes of 0
            for (int i : shape) {
                if (shape[i] < 1){
                    dim_err_str_size += get_num_chars_in_int(i);
                    char* buff = (char*)malloc(sizeof(char) * dim_err_str_size);
                    vsnprintf(
                        buff,
                        dim_err_str_size,
                        "Dimensions may not have a size 0: Offending dimension: %d",
                        i
                    );
                    throw exceptions::ArgumentException(std::string(buff))
                }
            }
        
        }

        __Tensor(__Tensor<T>&& input){
            this -> rank = input.rank;
            this -> shape = input.shape.swap();
            this -> data = input.data.swap();
            this -> index_caches = input.index_caches;
        }

        //Destructors:

        //Internal API:
        protected:
        __IndexCache& get_cache(){
            std::thread::id t_id = std::this_thread::get_id();
            if (! (this -> index_caches).contains(t_id)){
                return nullptr;
            }

            return (this -> index_caches)[t_id];
        }

        //API:
        public:
        int get_shape(int dimension){ return this -> shape; }
        T get_element(std::shared_ptr<std::vector<int>> indicies) {

        }   

        __Tensor<T> operator[](int index){
            //Get index cache:
            IndexCache cache = this -> get_cache(); 
            //Is the cache full?:
            if (cache.is_cache_full()){
                //Programming error:
            }

            return this;
        }

        T operator[](int index){
            IndexCache cache =
        }

        const __Tensor<T> operator[](int index) const;
        void operator=(T&& rvalue);
        void operator=(T rvalue);    
    };
    
};
#endif