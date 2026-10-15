#pragma once

#include "LinkedList.hpp"
#include "Sequence.hpp"

template <class T> class ListSequence : public Sequence<T>{

    protected:

        LinkedList<T> list;

        void append_internal(T item){

            this->list.append(item);

        }

        void prepend_internal(T item){

            this->list.prepend(item);

        }

        void insert_at_internal(T item, int index){

            this->list.insert_at(item, index);

        }

    public:

        ListSequence(){}

        ListSequence(T *items, size_t count) : list(items, count){}
        
        ListSequence(const LinkedList<T> &another_list) : list(another_list){}

        ListSequence(const ListSequence<T> &another) : list(another.list){}

        ListSequence(std::initializer_list<T> elements){

            for (const T& elem : elements){

                list.append(elem);

            }

        }

        ~ListSequence() override{}

        T get_first() const override{

            return list.get_first();

        }

        T get_last() const override{

            return list.get_last();

        }

        void set(int index, T item){

            list.set(index, item);

        }

        T& get(int index) override{

            return list.get(index);

        }

        const T& get(int index) const override{

            return list.get(index);

        }

        size_t get_length() const override{

            return list.get_length();

        }

        Sequence<T> *append(T item) override{

            append_internal(item);

            return this;

        }

        Sequence<T> *prepend(T item) override{

            prepend_internal(item);

            return this;

        }

        Sequence<T> *insert_at(T item, int index) override{

            insert_at_internal(item, index);

            return this;

        }
        
        void remove_at(int index) override{

            list.remove_at(index);

        }

        Sequence<T> *get_sub_sequence(int start_index, int end_index) const override{

            LinkedList<T> *res_list = list.get_sub_list(start_index, end_index);
            Sequence<T> *res_sequence = new ListSequence<T>(*res_list);

            delete res_list;

            return res_sequence;

        }

        Sequence<T> *concat(Sequence<T> *sequence) const override{

            if (sequence == nullptr){

                Sequence<T> *res_sequence = new ListSequence<T>(list);

                return res_sequence;

            }

            LinkedList<T> l_list;
            size_t size = sequence->get_length();

            for (size_t i = 0; i < size ; ++i){

                l_list.append(sequence->get(i));

            }

            LinkedList<T> *concatenated_list = list.concat(&l_list);
            Sequence<T> *res_sequence = new ListSequence<T>(*concatenated_list);
            
            delete concatenated_list;
            return res_sequence;

        }

        ListSequence<T> &operator=(const ListSequence<T> &other){

            if (this == &other){

                return *this;

            }

            list = other.list;

            return *this;

        }

        ListSequence<T> operator+(const ListSequence<T> &other) const{

            ListSequence<T> new_seq(list + other.list);

            return new_seq;

        }

        bool operator==(const ListSequence<T> &other) const{

            size_t other_len = other.get_length();
            size_t len = list.get_length();

            if (other_len != len){

                return false;

            }

            for (size_t i = 0; i < len; ++i){

                if (list[i] != other[i]){

                    return false;

                }

            }

            return true;

        }

        T& operator[](int index){

            return get(index);

        }

        const T& operator[](int index) const{

            return get(index);

        }

};