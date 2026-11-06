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

class root_is_empty : public exception{

    public:

        explicit root_is_empty(const std::string &msg) : exception(msg){}

};

class invalid_str : public exception{

    public:

        explicit invalid_str(const std::string &msg) : exception(msg){}

};