#include <execinfo.h>
#include <string>

namespace cnn_practice {
    namespace exceptions {
        class BaseException {
            private:
            std::string message;
            void** stacktrace;

            public:
            BaseException() = delete;
            //BaseException(std::string message);
            //BaseException(std::string message);
            BaseException(std::string&& message);
            ~BaseException();
            char* to_string();
            void print_to_stderr();
        };

        class ArgumentException : BaseException {
            public:
            ArgumentException() = delete;
            ArgumentException(std::string message) : 
               BaseException(std::move(message)){}
        };

        class OutOfBoundsException : BaseException {
            public:
            OutOfBoundsException() : BaseException("Attempted out of bounds access"){}

        };

        class OutOfMemoryException : BaseException {
            public:
            OutOfMemoryException() : BaseException("Out of available memory"){}
        };

    };
};