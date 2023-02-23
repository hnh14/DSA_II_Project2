#include "fifo.hpp"

FIFO::FIFO() {
    head = nullptr;
    tail = nullptr;
}

void FIFO::Push(Customer* toPush) {
    if(head == nullptr) {
        head = toPush;
        tail = toPush;
        head->setNext(nullptr);
    }
    else {
        tail->setNext(toPush);
        tail = toPush;
    }

}

Customer* FIFO::Pop() {
    if(head == nullptr)
        return nullptr;

    else {
        Customer* temp = head;
        head = head->getNext();
        if(head != nullptr)
            head->setNext(nullptr);

        temp->setNext(nullptr);
        return temp;
    }
}

bool FIFO::isEmpty() {
    if(head == nullptr)
        return true;
    else   
        return false;
}