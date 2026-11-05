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

        bool find(const T& value) const{

            if (root == nullptr){

                return false;

            }

            Node* curr = root.get();

            while (curr != nullptr){

                if (value == curr->data){

                    return true;

                }
                else if (value < curr->data){

                    curr = curr->left.get();

                }
                else{

                    curr = curr->right.get();

                }

            }

            return false;

        }

        T get_root() const{

            if (root == nullptr){

                throw root_is_empty("Root is empty");

            }

            return root->data;

        }

};