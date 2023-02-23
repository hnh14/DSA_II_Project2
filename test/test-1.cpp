#include "catch/catch.hpp"
#include "../priority.hpp"
#include "../fifo.hpp"
#include "../customer.hpp"
#include <iostream>

TEST_CASE(("Push Test")) {
    PriorityQueue priority(5, 5);

    priority.Push(new Customer(3));
    priority.Push(new Customer(5));
    priority.Push(new Customer(4));
    priority.Push(new Customer(1));
    priority.Push(new Customer(2));
    CHECK((priority.getSize() == 5));
    std::cout << priority.getSize() << std::endl;

    
    CHECK((priority.Pop()->getArrivalTime() == 1));
    CHECK((priority.Pop()->getArrivalTime() == 2));
    CHECK((priority.Pop()->getArrivalTime() == 3));
    CHECK((priority.Pop()->getArrivalTime() == 4));
    CHECK((priority.Pop()->getArrivalTime() == 5));
    CHECK((priority.Pop() == nullptr));
    CHECK((priority.getSize() == 0));
}

TEST_CASE(("Test rand interval")) {
    PriorityQueue priority(5,5);
    float test = priority.getNextRandomfloaterval(5.0);
}