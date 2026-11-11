#pragma once

#include <memory>

#include "Exception.hpp"
#include "ICollection.hpp"

template <typename T> class Tree : public ICollection<T>{

    private:

        struct Node{

            T data;
            size_t count = 1;
            int height = 0;
            Node* parent = nullptr;
            std::unique_ptr<Node> left = nullptr;
            std::unique_ptr<Node> right = nullptr;

            explicit Node(const T& value) : data(value){}

        };

        std::unique_ptr<Node> root = nullptr;
        size_t members_count = 0;

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

        int node_height(const Node* node) const{

            if (node == nullptr){

                return -1;

            }

            return node->height;

        }

        void update_height(Node* node){

            node->height = 1 + std::max(node_height(node->left.get()), node_height(node->right.get()));

        }

        int balance_factor(const Node* node) const{

            return node_height(node->left.get()) - node_height(node->right.get());

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

            update_height(new_root->left.get());
            update_height(new_root.get());
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

            update_height(new_root->right.get());
            update_height(new_root.get());
            curr = std::move(new_root);

        }

        void rebalance(std::unique_ptr<Node>& curr){

            if (curr == nullptr){

                return;

            }

            update_height(curr.get());

            if (balance_factor(curr.get()) > 1){

                if (balance_factor(curr->left.get()) < 0){

                    left_rotate(curr->left);

                }

                right_rotate(curr);

            }
            else if (balance_factor(curr.get()) < -1){

                if (balance_factor(curr->right.get()) > 0){

                    right_rotate(curr->right);

                }

                left_rotate(curr);

            }

        }

        std::unique_ptr<Node>& owner(Node* node){

            if (node->parent == nullptr){

                return root;

            }

            if (node->parent->left.get() == node){

                return node->parent->left;

            }

            return node->parent->right;

        }

        void rebalance_up(Node* node){

            while (node != nullptr){

                Node* parent = node->parent;

                rebalance(owner(node));
                node = parent;

            }

        }

        std::unique_ptr<Node> clone(const Node* node, Node* parent = nullptr){

            if (node == nullptr){

                return nullptr;

            }

            auto copy = std::make_unique<Node>(node->data);

            copy->count = node->count;
            copy->height = node->height;
            copy->parent = parent;

            copy->left = clone(node->left.get(), copy.get());
            copy->right = clone(node->right.get(), copy.get());
            
            return copy;

        }

    public:

        Tree(){}

        Tree(const T& root_value) : root(std::make_unique<Node>(root_value)), members_count(1){}

        Tree(const Tree<T>& another) : root(clone(another.root.get())), members_count(another.members_count){}

        Tree(Tree&& another) noexcept : root(std::move(another.root)), members_count(another.members_count){another.members_count = 0;}

        Tree& operator=(const Tree& another){

            if (this != &another){

                Tree copy(another);
                root = std::move(copy.root);
                members_count = another.members_count;

            }

            return *this;

        }

        Tree& operator=(Tree&& another) noexcept{

            if (this != &another){

                root = std::move(another.root);
                members_count = another.members_count;

                another.members_count = 0;

            }

            return *this;

        }

        void add(const T& value) override{

            ++members_count;

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

                        rebalance_up(curr);

                        return;

                    }

                    curr = curr->left.get();

                }
                else{

                    if (curr->right == nullptr){

                        curr->right = std::make_unique<Node>(value);
                        curr->right.get()->parent = curr;

                        rebalance_up(curr);

                        return;

                    }

                    curr = curr->right.get();

                }

            }

        }

        bool find(const T& value) const override{

            return (find_internal(value) != nullptr);

        }

        bool remove(const T& value) override{

            Node* curr = find_internal(value);

            if (curr == nullptr){

                return false;

            }

            if (curr->count > 1){

                --curr->count;

                return true;

            }

            if ((curr->left != nullptr) && (curr->right != nullptr)){

                Node* max_left = curr->left.get();

                while (max_left->right != nullptr){

                    max_left = max_left->right.get();

                }

                curr->data = max_left->data;
                curr->count = max_left->count;

                curr = max_left;

            }

            Node* parent = curr->parent;
            std::unique_ptr<Node>& curr_owner = owner(curr);
            std::unique_ptr<Node> child;

            if (curr->left != nullptr){

                child = std::move(curr->left);

            }
            else{

                child = std::move(curr->right);

            }

            if (child != nullptr){

                child.get()->parent = parent;

            }

            curr_owner = std::move(child);
            rebalance_up(parent);

            return true;

        }

        size_t get_count() const override{

            return members_count;

        }

        bool is_empty() const override{

            if (members_count == 0){

                return true;

            }

            return false;

        }

        void clear() override{

            root.reset();
            members_count = 0;

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

};