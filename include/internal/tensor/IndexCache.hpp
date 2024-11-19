#include <memory>
#ifndef CNN_PRACTICE_INDEX_CACHE
namespace cnn_practice {
/*
    If we ever need to be aggressive about cleaning up index
    caches, we can update the __IndexCache class to capture
    a timestamp whenever a read/write operation is initiated
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
            out-of-process access.  You would essentially be asking for anti-cheat protection,
            and that is not feasible to implement unless you have a major incentive (like cheaters
            plaguing your game, leaving the majority of players disatisfied).
*/
    class IndexCache {
        private:
        int  cache_len;
        int  curr_index;
        std::vector<int> index_cache;
        

        public:
        IndexCache(int cache_len);
        ~IndexCache();
        bool is_cache_full(); //Set each element in the cache to some bogus value
        int  num_free_elements();
        void reset_cache();
        bool add(int index);
        int get_cache_length();
        int operator[](int index);
    };
};
#endif