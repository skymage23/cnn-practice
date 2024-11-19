#include <concepts>
#include <type_traits>
#ifndef CNN_PRACTICE_COMMON
#define CNN_PRACTICE_COMMON
namespace cnn_practice {

    //Generic template concepts:
    template<typename T>
    concept numeric = std::integral<T> or std::floating_point<T>;

    //Utility functions:
    int get_num_chars_in_int(unsigned int input){
        int temp = input;
        int counter = 0;
        while(temp != 0){
            counter++;
            temp /= 10;
        }
        return counter;
    }
}
#endif