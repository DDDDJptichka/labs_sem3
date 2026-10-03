#pragma once

template <class TKey, class TElement> class IDictionary{

    public:

        virtual size_t get_count() const = 0;
        virtual size_t get_capacity() const = 0;
        virtual TElement get(TKey key) const = 0;
        virtual bool contains_key(TKey key) const = 0;
        virtual void add(TKey key, TElement element) = 0;
        virtual void remove(TKey key) = 0;

        ~IDictionary(){}

};