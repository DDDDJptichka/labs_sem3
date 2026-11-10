#pragma once

template <typename T> class ICollection{

    public:

        virtual void add(const T& value) = 0;
        virtual bool remove(const T& value) = 0;
        virtual bool find(const T& value) const = 0;
        virtual size_t get_count() const = 0;
        virtual bool is_empty() const = 0;
        virtual void clear() = 0;

};