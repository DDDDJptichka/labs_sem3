#pragma once

template <class T> class SharedPtr{

    private:

        T* ptr ;
        size_t* ref_count;

    public:

        explicit SharedPtr(T* p = nullptr){

            if (p == nullptr){

                ref_count = nullptr;

            }
            else{
                
                ref_count = new size_t(1);

            }

            ptr = p;

        }

        SharedPtr(const SharedPtr& another) noexcept{

            ptr = another.ptr;
            ref_count = another.ref_count;

            if (ref_count != nullptr){
            
                ++(*ref_count);

            }

        }

        SharedPtr(SharedPtr&& another) noexcept{

            ptr = another.ptr;
            ref_count = another.ref_count;

            another.ptr = nullptr;
            another.ref_count = nullptr;

        }

        ~SharedPtr(){

            if (ref_count != nullptr){

                if (--(*ref_count) == 0){

                    delete ptr;
                    delete ref_count;

                }    
            
            }

        }

        SharedPtr& operator=(const SharedPtr& another) noexcept{

            if (this != &another){

                if ((ref_count != nullptr) && (--(*ref_count) == 0)){

                    delete ptr;
                    delete ref_count;

                }

                ptr = another.ptr;
                ref_count = another.ref_count;

                if (ref_count != nullptr){
                
                    ++(*ref_count);

                }

            }

            return *this;
    
        }

        SharedPtr& operator=(SharedPtr&& another) noexcept{

            if (this != &another){

                if ((ref_count != nullptr) && (--(*ref_count) == 0)){

                    delete ptr;
                    delete ref_count;

                }

                ptr = another.ptr;
                ref_count = another.ref_count;

                another.ptr = nullptr;
                another.ref_count = nullptr;

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

        void reset(T* p = nullptr){

            if (ptr == p){

                return;

            }

            if ((ref_count != nullptr) && (--(*ref_count) == 0)){

                delete ptr;                
                delete ref_count;

            }

            ptr = p;
            
            if (ptr == nullptr){

                ref_count = nullptr;

            }
            else{

                ref_count = new size_t(1);

            }

        }

        size_t r_count() const noexcept{

            if (ref_count == nullptr){

                return 0;

            }

            return *ref_count;

        }

};

template <typename T> SharedPtr<T> makeShared(T value){

    return SharedPtr<T>(new T(value));
    
}

template <class T> class SharedPtr<T[]>{

    private:

        T* ptr;
        size_t* ref_count;

    public:

        explicit SharedPtr(T* p = nullptr){

            if (p == nullptr){

                ref_count = nullptr;

            }
            else{
                
                ref_count = new size_t(1);

            }

            ptr = p;

        }

        SharedPtr(const SharedPtr& another) noexcept{

            ptr = another.ptr;
            ref_count = another.ref_count;

            if (ref_count != nullptr){
            
                ++(*ref_count);

            }

        }

        SharedPtr(SharedPtr&& another) noexcept{

            ptr = another.ptr;
            ref_count = another.ref_count;

            another.ptr = nullptr;
            another.ref_count = nullptr;

        }

        ~SharedPtr(){

            if (ref_count != nullptr){

                if (--(*ref_count) == 0){

                    delete[] ptr;
                    delete ref_count;

                }    
            
            }

        }

        SharedPtr& operator=(const SharedPtr& another) noexcept{

            if (this != &another){

                if ((ref_count != nullptr) && (--(*ref_count) == 0)){

                    delete[] ptr;
                    delete ref_count;

                }

                ptr = another.ptr;
                ref_count = another.ref_count;

                if (ref_count != nullptr){
                
                    ++(*ref_count);

                }

            }

            return *this;
    
        }

        SharedPtr& operator=(SharedPtr&& another) noexcept{

            if (this != &another){

                if ((ref_count != nullptr) && (--(*ref_count) == 0)){

                    delete[] ptr;
                    delete ref_count;

                }

                ptr = another.ptr;
                ref_count = another.ref_count;

                another.ptr = nullptr;
                another.ref_count = nullptr;

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

        void reset(T* p = nullptr){

            if (ptr == p){

                return;

            }

            if ((ref_count != nullptr) && (--(*ref_count) == 0)){

                delete[] ptr;                
                delete ref_count;

            }

            ptr = p;
            
            if (ptr == nullptr){

                ref_count = nullptr;

            }
            else{

                ref_count = new size_t(1);

            }

        }

        size_t r_count() const noexcept{

            if (ref_count == nullptr){

                return 0;

            }

            return *ref_count;

        }

};

template <typename T> SharedPtr<T[]> makeSharedArray(size_t size){

    return SharedPtr<T[]>(new T[size]);
    
}