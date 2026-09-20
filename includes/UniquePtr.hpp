#pragma once

template <class T> class UniquePtr{

    private:

        T* ptr;

    public:

        UniquePtr(T* p = nullptr) : ptr(p){}

        ~UniquePtr(){

            delete ptr;

        }

        UniquePtr(const UniquePtr&) = delete;
        UniquePtr& operator=(const UniquePtr&) = delete;

        UniquePtr(UniquePtr&& another){

            ptr = another.ptr;
            another.ptr = nullptr;

        }

        UniquePtr& operator=(UniquePtr&& another){

            if (this != &another){

                delete ptr;

                ptr = another.ptr;
                another.ptr = nullptr;

            }

            return *this;

        }


        T& operator*() const{

            return *ptr;

        }

        T* operator->() const{

            return ptr;

        }

        T* get() const{

            return ptr;

        }

        T* release(){

            T* tmp = ptr;
            ptr = nullptr;
            return tmp;

        }

        void reset(T* p = nullptr){

            if (ptr != p){

                delete ptr;
                ptr = p;

            }

        }

};

template <class T> UniquePtr<T> makeUnique(T value){

    return UniquePtr<T>(new T(value));
    
}

template <class T> class UniquePtr<T[]>{

    private:

        T* ptr;

    public:

        UniquePtr(T* p = nullptr) : ptr(p){}

        ~UniquePtr(){

            delete[] ptr;

        }

        UniquePtr(const UniquePtr&) = delete;
        UniquePtr& operator=(const UniquePtr&) = delete;

        UniquePtr(UniquePtr&& another){

            ptr = another.ptr;
            another.ptr = nullptr;

        }

        UniquePtr& operator=(UniquePtr&& another){

            if (this != &another){

                delete[] ptr;

                ptr = another.ptr;
                another.ptr = nullptr;

            }

            return *this;

        }

        T& operator[](size_t index){

            return ptr[index];

        }

        T* get() const{

            return ptr;

        }

        T* release(){

            T* tmp = ptr;
            ptr = nullptr;
            return tmp;

        }

        void reset(T* p = nullptr){

            if (ptr != p){

                delete[] ptr;
                ptr = p;

            }

        }

};

template <class T> UniquePtr<T[]> makeUniqueArray(size_t size){

    return UniquePtr<T[]>(new T[size]);
    
}