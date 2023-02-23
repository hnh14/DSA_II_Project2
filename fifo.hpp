#ifndef FIFO_H
#define FIFO_H
#include "customer.hpp"

class FIFO {
    private:
        Customer* head;
        Customer* tail;
    public:
        FIFO();
        void Push(Customer*);
        Customer* Pop();
        bool isEmpty();
};

#endif