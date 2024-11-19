#include <memory>
#include <exceptions.hpp>
#include <internal/tensor/IndexCache.hpp>

namespace cnn_practice {
    IndexCache::IndexCache(int cache_len) : cache_len(cache_len){
        this -> index_cache = std::move(std::unique_ptr<int[]> (new int[cache_len]));
        this -> curr_index = 0;
    }

    /*
    IndexCache::~IndexCache(){
        delete (this -> index_cache);
    }
    */

    bool IndexCache::is_cache_full(){
        return (this -> curr_index) == (this -> cache_len);
    }
    
    int IndexCache::num_free_elements(){
        return ((this -> cache_len) - (this -> curr_index) - 1);
    }

    void IndexCache::reset_cache(){
        this -> curr_index = 0;
    }

    bool IndexCache::add(int index){
        if (this -> is_cache_full()){
            return false;
        }

        (this -> index_cache)[this -> curr_index] = index;
        this -> curr_index += 1;
    }

    int  IndexCache::get_cache_length(){
        return (this -> cache_len);
    }
    int  IndexCache::operator[](int index){
        if(index < 0){
            throw new exceptions::ArgumentException("index cannot be less than 0.");
        }

        if (index > (this -> cache_len)){
            throw new exceptions::ArgumentException("index cannot be greater than the cache length.");
        }

        return ((this -> index_cache)[index]);
    } 
};
