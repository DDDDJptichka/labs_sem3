#pragma once

#include <cstddef>

#include "ListSequence.hpp"
#include "IDictionary.hpp"

template <class TKey, class TElement> class HashTable : public IDictionary<TKey, TElement>{

    private:

        std::unique_ptr<ListSequence<std::pair<TKey, TElement>>[]> buckets;
        size_t count;
        size_t capacity;
        size_t (*hash_function)(TKey);

    public:

        HashTable(size_t (*hash_function)(TKey), size_t capacity){

            this->capacity = capacity;
            this->hash_function = hash_function;
            this->count = 0;

            buckets = std::make_unique<ListSequence<std::pair<TKey, TElement>>[]>(capacity);

        }

        size_t get_count() const override{

            return count;

        }

        size_t get_capacity() const override{

            return capacity;

        }

        TElement get(TKey key) const override{return buckets[0][0].second;}
        bool contains_key(TKey key) const override{return 1;}
        void add(TKey key, TElement element) override{}
        void remove(TKey key) override{}

};