#pragma once

template <class T> class SharedPtr{

    private:

        T* ptr ;
        size_t* ref_count;

    public:

        SharedPtr(T* p = nullptr){

            if (p == nullptr){

                ref_count = nullptr;

            }
            else{
                
                ref_count = new size_t(1);

            }

            ptr = p;

        }

        SharedPtr(const SharedPtr& another){

            ptr = another.ptr;
            ref_count = another.ref_count;

            if (ref_count != nullptr){
            
                ++(*ref_count);

            }

        }

        SharedPtr(SharedPtr&& another){

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

        SharedPtr& operator=(const SharedPtr& another){

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

        SharedPtr& operator=(SharedPtr&& another){

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

        T& operator*() const{

            return *ptr;

        }

        T* operator->() const{

            return ptr;

        }

        T* get() const{

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

        size_t r_count() const{

            if (ref_count == nullptr){

                return 0;

            }

            return *ref_count;

        }

};

template <class T> class SharedPtr<T[]>{

    private:

        T* ptr;
        size_t* ref_count;

    public:

        SharedPtr(T* p = nullptr){

            if (p == nullptr){

                ref_count = nullptr;

            }
            else{
                
                ref_count = new size_t(1);

            }

            ptr = p;

        }

        SharedPtr(const SharedPtr& another){

            ptr = another.ptr;
            ref_count = another.ref_count;

            if (ref_count != nullptr){
            
                ++(*ref_count);

            }

        }

        SharedPtr(SharedPtr&& another){

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

        SharedPtr& operator=(const SharedPtr& another){

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

        SharedPtr& operator=(SharedPtr&& another){

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

        T& operator[](size_t index){

            return ptr[index];

        }

        const T& operator[](size_t index) const{

            return ptr[index];

        }

        T* get() const{

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

        size_t r_count() const{

            if (ref_count == nullptr){

                return 0;

            }

            return *ref_count;

        }

};