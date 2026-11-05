#pragma once

#include <memory>

#include "Exception.hpp"

template <typename T> class Tree{

    private:

        struct Node{

            T data;
            Node* parent = nullptr;
            std::unique_ptr<Node> left = nullptr;
            std::unique_ptr<Node> right = nullptr;

            explicit Node(const T& value, Node* p = nullptr) : data(value), parent(p){}

        };

        std::unique_ptr<Node> root = nullptr;

    public:

        Tree(){}

        Tree(const T& value) : root(std::make_unique<Node>(value)){}

        void add(T value){

            if (root == nullptr){

                root = std::make_unique<Node>(value);
                return;

            }

            Node* curr = root.get();

            while (true){

                if (value <= curr->data){

                    if (curr->left == nullptr){

                        curr->left = std::make_unique<Node>(value, curr);
                        return;

                    }

                    curr = curr->left.get();

                }
                else{

                    if (curr->right == nullptr){

                        curr->right = std::make_unique<Node>(value, curr);
                        return;

                    }

                    curr = curr->right.get();

                }

            }

        }

};