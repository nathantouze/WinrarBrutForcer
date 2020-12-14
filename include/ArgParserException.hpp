#ifndef ARGPARSEREXCEPTION_HPP_
#define ARGPARSEREXCEPTION_HPP_

#include <exception>
#include <string>

class ArgParserException : public std::exception {
    public:
        ArgParserException(const std::string &msg) : _msg(msg) {};
        ~ArgParserException() {};
        const char *what() const noexcept {
            return _msg.c_str();
        }

    protected:
    private:
        std::string _msg;
};

#endif /* !ARGPARSEREXCEPTION_HPP_ */
