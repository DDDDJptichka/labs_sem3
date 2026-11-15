#pragma once

#include "HashTable.hpp"

template <typename T, typename E> class Graph{

    private:

        struct Edge{

            size_t id_to;
            E value;

        };

        HashTable<size_t, T> vertices;
        HashTable<size_t, ListSequence<Edge>> adjacency;
        size_t next_id = 0;
        size_t adjacency_count = 0;

};