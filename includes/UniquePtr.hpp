#pragma once

template <class T> class UniquePtr{

    private:

        T* ptr;

    public:

        explicit UniquePtr(T* p = nullptr) noexcept : ptr(p){}

        UniquePtr(const UniquePtr&) = delete;
        UniquePtr& operator=(const UniquePtr&) = delete;

        UniquePtr(UniquePtr&& another) noexcept{

            ptr = another.ptr;
            another.ptr = nullptr;

        }

        ~UniquePtr(){

            delete ptr;

        }

        UniquePtr& operator=(UniquePtr&& another) noexcept{

            if (this != &another){

                delete ptr;

                ptr = another.ptr;
                another.ptr = nullptr;

            }

            return *this;

        }


        T& operator*() const noexcept{

            return *ptr;

        }

        T* operator->() const noexcept{

            return ptr;

        }

        T* get() const noexcept{

            return ptr;

        }

        T* release() noexcept{

            T* tmp = ptr;
            ptr = nullptr;
            return tmp;

        }

        void reset(T* p = nullptr) noexcept{

            if (ptr != p){

                delete ptr;
                ptr = p;

            }

        }

};

template <typename T> UniquePtr<T> makeUnique(T value){

    return UniquePtr<T>(new T(value));
    
}

template <class T> class UniquePtr<T[]>{

    private:

        T* ptr;

    public:

        explicit UniquePtr(T* p = nullptr) noexcept : ptr(p){}

        ~UniquePtr(){

            delete[] ptr;

        }

        UniquePtr(const UniquePtr&) = delete;
        UniquePtr& operator=(const UniquePtr&) = delete;

        UniquePtr(UniquePtr&& another) noexcept{

            ptr = another.ptr;
            another.ptr = nullptr;

        }

        UniquePtr& operator=(UniquePtr&& another) noexcept{

            if (this != &another){

                delete[] ptr;

                ptr = another.ptr;
                another.ptr = nullptr;

            }

            return *this;

        }

        T& operator[](size_t index) noexcept{

            return ptr[index];

        }

        const T& operator[](size_t index) const noexcept{

            return ptr[index];

        }

        T* get() const noexcept{

            return ptr;

        }

        T* release() noexcept{

            T* tmp = ptr;
            ptr = nullptr;
            return tmp;

        }

        void reset(T* p = nullptr) noexcept{

            if (ptr != p){

                delete[] ptr;
                ptr = p;

            }

        }

};

template <typename T> UniquePtr<T[]> makeUniqueArray(size_t size){

    return UniquePtr<T[]>(new T[size]);
    
}


//noexcept
//explicit
//тесты разделить
//в ридми бенчмарки+валгринд закинуть