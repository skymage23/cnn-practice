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
            int  curr_shape_index;
            std::shared_ptr<std::vector<int>> index_cache; 
            __Tensor<A>& tensor_ref;

            public:
            __IndexCachingTemporaryFetcher(__Tensor<A>& parent){
                this -> tensor_ref = parent;
                this -> index_cache = std::unique_ptr<std::vector<int>>(
                    new std::vector<int>()
                );
                this -> curr_shape_index = 0;
            }
            

            //bool is_cache_full(); //Set each element in the cache to some bogus value
            //int  num_free_elements();
            //void reset_cache();
            //bool add(int index);
            //int get_cache_length();
            __IndexCachingTemporaryFetcher& operator[](int index){
                if (index < 1){
                    throw new exceptions::ArgumentException("index cannot be 0.")
                }

                if (index > 0)

                if (this -> is_cache_full()){
                    throw new exceptions::TensorFetchException();
                }
                this -> add(index);
                return this;
            }
            A operator[](int index){
                if (index < 1){
                    throw new exceptions::ArgumentException("index cannot be 0.")
                }
                if (this -> num_free_elements() != 1){
                    throw new exceptions::TensorFetchException();
                }
                this -> add(index);
                return tensor_ref.get_element(this -> index_cache);
            }
        }
        friend __IndexCachingTemporaryFetcher;

        private:
        unsigned int data_byte_limit;
        protected:
        std::unique_ptr<std::vector<unsigned int>> shape;
        int rank;
        size_t datatype_size;
        //row-major order:
        std::unique_ptr<std::vector<unsigned char>> data; //Greate. Little endian or big endian.


        //Constructors:
        public:
        __Tensor() = delete;
        __Tensor(__Tensor<T>) = delete;

        __Tensor(std::vector<int>& shape) : __Tensor(std::move(shape)){}
        __Tensor(std::unique_ptr<std::vector<unsigned int>> shape) : 
            shape(std::move(shape)),
            datatype_size(sizeof(T))
        
        {
            static int dim_err_str_size = 56;
            unsigned int temp = 1;
            this -> rank = shape.size()
            if (this -> rank == 0){
                throw exceptions::ArgumentException("rank cannot be 0");
            }
 
            //Check for sizes of 0
            for (int i : shape) {
                if (i < 1){
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
                temp *= i;
            }
            this -> data_byte_limit = temp * this -> datatype_size;
            this -> data = std::vector<char>();
        }

        __Tensor(__Tensor<T>&& input){
            this -> rank = input.rank;
            this -> shape = std::move(input.shape);
            this -> data = std::move(input.data);
        }

        //Destructors:

        //Internal API:
        protected:
        /*
        __IndexCache& get_cache(){
            std::thread::id t_id = std::this_thread::get_id();
            if (! (this -> index_caches).contains(t_id)){
                return nullptr;
            }

            return (this -> index_caches)[t_id];
        }
        */
        //API:
        public:
        int get_rank(){ return this -> rank;}
        std::vector<int> get_shape(){ return std::vector<int>((this -> shape).get()); }
        T get_element(std::shared_ptr<std::vector<int>> indicies) {
            T retval;
            int skip = 1;

            for(int i = 0; i < this -> rank; i++){
                skip *= indices[i];
            }

            retval = std::static_cast<T>(
                ((this -> data).data() + skip)*
            )
            return retval; 
        }   

        __IndexCachingTemporaryFetcher<T> operator[](int index){

            if (index < 1){
                throw new exceptions::ArgumentException("index cannot be 0.");
            }

            if (index > (this -> shape)[0]){
                throw new exceptions::OutOfBoundsException();
            }

            __IndexCachingTemporaryFetcher<T> retval(this);
            retval.add(index);
            return retval;
        }
    };    
};
#endif