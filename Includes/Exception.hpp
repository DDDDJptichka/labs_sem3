#pragma once

#include <string>
#include <exception>

class exception : public std::exception{

    protected:

        std::string message;

    public:

        explicit exception(const std::string &msg) : message(msg){}

        const char *what() const noexcept override{

            return message.c_str();

        }

};