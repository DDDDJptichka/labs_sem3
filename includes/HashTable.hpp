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

        TElement get(TKey key) const override{

            size_t bucket_index = hash_function(key) % capacity;
            size_t bucket_size = buckets[bucket_index].get_length();

            for (size_t i = 0; i < bucket_size; ++i){

                if (buckets[bucket_index][i].first == key){

                    return buckets[bucket_index][i].second;

                }

            }

            throw key_not_found("Key Not Found");

        }
        
        bool contains_key(TKey key) const override{

            size_t bucket_index = hash_function(key) % capacity;
            size_t bucked_size = buckets[bucket_index].get_length();

            for (size_t i = 0; i < bucked_size; ++i){

                if (buckets[bucket_index][i].first == key){

                    return 1;

                }

            }

            return 0;

        }

        void add(TKey key, TElement element) override{

            size_t bucket_index = hash_function(key) % capacity;
            buckets[bucket_index].append(std::pair(key, element));
            ++count;

        }
        
        void remove(TKey key) override{}

};