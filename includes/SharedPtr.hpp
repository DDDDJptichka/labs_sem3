#pragma once

template <class T> class SharedPtr{

    private:

        T* ptr;
        size_t* ref_count;

    public:

        SharedPtr(T* p = nullptr) : ptr(p), ref_count(new size_t(1)){}

        SharedPtr(const SharedPtr& another){

            ptr = another.ptr;
            

        }
        SharedPtr& operator=(const SharedPtr&) = delete;

};

template <class T> class SharedPtr<T[]>{

    private:

        T* ptr;
        size_t* ref_count;

    public:

        

};