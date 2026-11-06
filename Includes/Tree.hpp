#pragma once

#include <memory>

#include "Exception.hpp"

template <typename T> class Tree{

    private:

        struct Node{

            T data;
            size_t count = 1;
            Node* parent = nullptr;
            std::unique_ptr<Node> left = nullptr;
            std::unique_ptr<Node> right = nullptr;

            explicit Node(const T& value) : data(value){}

        };

        std::unique_ptr<Node> root = nullptr;

        Node* find_internal(const T& value) const{

            Node* curr = root.get();

            while (curr != nullptr){

                if (value == curr->data){

                    return curr;

                }
                else if (value < curr->data){

                    curr = curr->left.get();

                }
                else{

                    curr = curr->right.get();

                }

            }

            return nullptr;

        }

    public:

        Tree(){}

        Tree(const T& value) : root(std::make_unique<Node>(value)){}

        void add(const T& value){

            if (root == nullptr){

                root = std::make_unique<Node>(value);
                return;

            }

            Node* curr = root.get();

            while (true){

                if (value <= curr->data){

                    if (curr->left == nullptr){

                        curr->left = std::make_unique<Node>(value);
                        curr->left.get()->parent = curr;
                        return;

                    }

                    curr = curr->left.get();

                }
                else{

                    if (curr->right == nullptr){

                        curr->right = std::make_unique<Node>(value);
                        curr->right.get()->parent = curr;
                        return;

                    }

                    curr = curr->right.get();

                }

            }

        }

        bool find(const T& value) const{

            return (find_internal(value) != nullptr);

        }

        bool remove(const T& value){

            Node* curr = find_internal(value);

            if (curr == nullptr){

                return false;

            }

            std::unique_ptr<Node>* owner = nullptr;
            
            if (curr->parent == nullptr){

                owner = &root;

            }
            else if (curr->parent->left.get() == curr){

                owner = &curr->parent->left;

            }
            else{

                owner = &curr->parent->right;

            }

            if ((curr->left != nullptr) && (curr->right != nullptr)){

                Node* max_left = curr->left.get();

                while (max_left->right != nullptr){

                    max_left = max_left->right.get();

                }

                max_left->right = std::move(curr->right);
                max_left->right.get()->parent = max_left;

            }

            std::unique_ptr<Node> child;

            if (curr->left != nullptr){

                child = std::move(curr->left);

            }
            else{

                child = std::move(curr->right);

            }

            if (child != nullptr){

                child.get()->parent = curr->parent;

            }

            *owner = std::move(child);

            return true;

        }
        
        T get_root() const{

            if (root == nullptr){

                throw root_is_empty("Root is empty");

            }

            return root->data;

        }

        template <typename Func> void travel(Node* start, Func& f) const{

            if (start == nullptr){

                return;

            }

            f(start->data);

            travel(start->left.get(), f);
            travel(start->right.get(), f);

        }

        template <typename Func> Tree<T> map(Func f) const{

            Tree<T> res;

            auto action = [&](const T& value){

                res.add(f(value));

            };

            travel(root.get(), action);

            return res;

        }

        template <typename Func> Tree<T> where(Func f) const{

            Tree<T> res;

            auto filter = [&](const T& value){

                if (f(value)){

                    res.add(value);

                }

            };

            travel(root.get(), filter);

            return res;

        }

        template <typename A, typename Func> A reduce(const A& start_value, Func f) const{

            A res = start_value;

            auto action = [&](const T& value){res = f(res, value);};
            travel(root.get(), action);

            return res;

        }

        Tree<T> get_subtree(const T& root_value){

            Tree<T> subtree;

            auto action = [&](const T& value){subtree.add(value);};

            travel(find_internal(root_value), action);

            return subtree;

        }

};