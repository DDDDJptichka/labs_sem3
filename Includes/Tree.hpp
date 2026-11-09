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

        bool is_same_tree(const Node* a, const Node* b) const{

            if ((a == nullptr) || (b == nullptr)){

                return a == b;

            }

            if ((a->data != b->data) || (a->count != b->count)){

                return false;

            }

            return is_same_tree(a->left.get(), b->left.get()) && is_same_tree(a->right.get(), b->right.get());

        }

        bool is_subtree_internal(const Node* start, const Node* node) const{

            if (start == nullptr){

                return false;

            }

            if (is_same_tree(start, node)){

                return true;
            
            }

            return is_subtree_internal(start->left.get(), node) || is_subtree_internal(start->right.get(), node);

        }

        void left_rotate(std::unique_ptr<Node>& curr){

            if ((curr == nullptr) || curr->right == nullptr){

                return;

            }
   
            Node* parent = curr->parent;
            auto new_root = std::move(curr->right);

            if (new_root->left != nullptr){

                curr->right = std::move(new_root->left);
                curr->right->parent = curr.get();

            }

            new_root->parent = parent;
            new_root->left = std::move(curr);
            new_root->left->parent = new_root.get();

            curr = std::move(new_root);

        }

        void right_rotate(std::unique_ptr<Node>& curr){

            if ((curr == nullptr) || curr->left == nullptr){

                return;

            }
   
            Node* parent = curr->parent;
            auto new_root = std::move(curr->left);

            if (new_root->right != nullptr){

                curr->left = std::move(new_root->right);
                curr->left->parent = curr.get();

            }

            new_root->parent = parent;
            new_root->right = std::move(curr);
            new_root->right->parent = new_root.get();

            curr = std::move(new_root);

        }

        size_t make_chain(){

            size_t node_count = 0;
            std::unique_ptr<Node>* curr = &root;

            while (*curr != nullptr){

                if ((*curr)->left != nullptr){

                    right_rotate(*curr);

                }
                else{

                    curr = &(*curr)->right;
                    ++node_count;

                }

            }

            return node_count;

        }

        void compress(size_t count){

            std::unique_ptr<Node>* curr = &root;

            for (size_t i = 0; i < count; ++i){

                left_rotate(*curr);
                curr = &(*curr)->right;

            }

        }

    public:

        Tree(){}

        Tree(const T& root_value) : root(std::make_unique<Node>(root_value)){}

        void add(const T& value){

            if (root == nullptr){

                root = std::make_unique<Node>(value);
                return;

            }

            Node* curr = root.get();

            while (true){

                if (value == curr->data){

                    ++curr->count;
                    
                    return;

                }
                else if (value < curr->data){

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

            if (curr->count > 1){

                --curr->count;

                return true;

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

            for (size_t i = 0; i < start->count; ++i){

                f(start->data);

            }

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

        Tree<T> get_subtree(const T& root_value) const{

            Tree<T> subtree;

            auto action = [&](const T& value){subtree.add(value);};
            travel(find_internal(root_value), action);

            return subtree;

        }

        std::string to_string() const{

            std::ostringstream str;

            auto action = [&](const T& value){str << value << " ";};
            travel(root.get(), action);

            return str.str();

        }

        static Tree<T> from_string(const std::string& str){

            Tree<T> res;
            std::istringstream stream(str);
            T value;

            while (stream >> value){

                res.add(value);

            }

            if (stream.eof() == false){

                throw invalid_str("Invalid tree string");

            }

            return res;

        }

        bool is_subtree(const Tree<T>& subtree) const{

            if (subtree.root == nullptr){

                return true;

            }

            Node* start = root.get();
            T sub_data = subtree.get_root();

            while (start != nullptr){

                if (sub_data == start->data){

                    break;

                }
                else if (sub_data < start->data){

                    start = start->left.get();

                }
                else{

                    start = start->right.get();

                }

            }

            return is_subtree_internal(start, subtree.root.get());

        }

        void balance(){

            size_t count = make_chain();
            size_t m = 1;

            while (m <= (count + 1) / 2){

                m *= 2;

            }

            --m;
            compress(count - m);

            while (m > 1){

                m /= 2;
                compress(m);

            }

        }

};