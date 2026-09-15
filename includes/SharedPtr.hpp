#pragma once

template <class T> class SharedPtr{

    private:

        T* ptr;
        size_t* ref_count;

    public:



};

template <class T> class SharedPtr<T[]>{

    private:

        T* ptr;
        size_t* ref_count;

    public:

        

};