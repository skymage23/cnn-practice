#include <execinfo.h>
#include <string>

namespace cnn_practice {
    namespace exceptions {
        class BaseException {
            private:
            std::string message;
            void** stacktrace;

            public:
            //BaseException(std::string message);
            BaseException(std::string&& message);
            ~BaseException();
            char* to_string();
            void print_to_stderr();
        };

        class OutOfBoundsException : BaseException {
            public:
            OutOfBoundsException() : BaseException("Attempted out of bounds access"){};

        };
    };
};