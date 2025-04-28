// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <memory>
#include <utility>

struct SYM {
    char ch;
    int prior;
};

template<typename T>
struct Node {
    T val;
    std::unique_ptr<Node<T>> next;
};


template<typename T>
class TPQueue {
 public:
    TPQueue() noexcept = default;

    void push(const T& value) {
        auto new_node = std::unique_ptr<Node<T>>(new Node<T>{value});
        new_node->val = value;

        if (!head_ || value.prior > head_->val.prior) {
            new_node->next = std::move(head_);
            head_ = std::move(new_node);
        } else {
            Node<T>* prev = head_.get();
            while (prev->next && prev->next->val.prior >= value.prior) {
                prev = prev->next.get();
            }
            new_node->next = std::move(prev->next);
            prev->next = std::move(new_node);
        }
    }
    T pop() {
        if (!head_) {
            throw std::out_of_range("Очередь пуста");
        }
        T front_val = head_->val;
        head_ = std::move(head_->next);
        return front_val;
    }
    bool empty() const noexcept {
        return !head_;
    }

 private:
    std::unique_ptr<Node<T>> head_{nullptr};
};

#endif  // INCLUDE_TPQUEUE_H_
