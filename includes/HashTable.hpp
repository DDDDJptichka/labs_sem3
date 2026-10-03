#pragma once

#include <cstddef>

#include "ListSequence.hpp"
#include "IDictionary.hpp"

template <class TKey, class TElement> class HashTable : public IDictionary<TKey, TElement>{

    private:

        std::unique_ptr<ListSequence<std::pair<TKey, TElement>>[]> bucket;
        size_t count;
        size_t capacity;

    public:

        

};