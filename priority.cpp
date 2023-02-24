#include "priority.hpp"
#include "stats.hpp"
#include <iostream>
#include <math.h>
#include <cstdlib>

PriorityQueue::PriorityQueue(float avg, float m) {
    head = nullptr;
    fifo = FIFO();
    this->avg = avg;
    this->serverAvailableCnt = m;
    this->M = m;
}

void PriorityQueue::Push(Customer* toPush, Customer* currentNode) {
    if(toPush == nullptr)
        return;

    if(size > 200) {
        fifo.Push(toPush);
    }

    if(head == nullptr) {
        head = toPush;
        head->setNext(nullptr);
        size++;
        return;
    }

    if(currentNode == nullptr) {
        if(toPush->getPriority() <= head->getPriority()) {
            toPush->setNext(head);
            head = toPush;
            size++;
            return;
        }
        else
            currentNode = head;
    }
    
    if(currentNode->getNext() == nullptr) {
        toPush->setNext(nullptr);
        currentNode->setNext(toPush);
        size++;
        return;
    }

    if(toPush->getPriority() <= currentNode->getNext()->getPriority()) {
        toPush->setNext(currentNode->getNext());
        currentNode->setNext(toPush);
        size++;
        return;
    }

    Push(toPush, currentNode->getNext());    
    
}

Customer* PriorityQueue::Pop() {
    if(head == nullptr)
        return nullptr;

    Customer* toPop = head;
    head = head->getNext();
    size--;

    return toPop;
}

void PriorityQueue::processNextEvent() {
    Customer* event = Pop();
    if(event == nullptr)
        return;

    if(!event->isDeparture()) {
        if(serverAvailableCnt > 0) {
            serverAvailableCnt--;
            event->setStartOfServiceTime(event->getArrivalTime());
            float interval = getNextRandomfloaterval(avg);
            event->setDepartureTime(event->getArrivalTime() + interval);
            Push(event);
        }
        else 
            fifo.Push(event);

        currentTime = event->getArrivalTime();
    }
    else {
        if(serverAvailableCnt < M)
            serverAvailableCnt++;
        processStatistics(event);
        currentTime = event->getDepartureTime();
        if(!fifo.isEmpty()) {
            Customer* newEvent = fifo.Pop();        
            newEvent->setStartOfServiceTime(event->getDepartureTime());
            float interval = getNextRandomfloaterval(avg);
            newEvent->setDepartureTime(newEvent->getStartOfServiceTime() + interval);
            Push(newEvent);
            serverAvailableCnt--;
        }
        // delete event;
    }
}

void PriorityQueue::processStatistics(Customer* cust) {
    //
    if(currentWaitTime < 0) 
        customerWaitCount++;
    
    //For average total time
    totalWaitTime += cust->getDepartureTime();

    //For average service
    serviceTime += cust->getDepartureTime() - cust->getStartOfServiceTime(); 

    //Po
    if(serverAvailableCnt >= M-1) {
        idleTime += cust->getDepartureTime() - lastWait;
    }
    lastWait = cust->getDepartureTime();
}

void PriorityQueue::Add() {
    Customer* newCust = new Customer(currentTime);
    Push(newCust);
}

float PriorityQueue::getNextRandomfloaterval(float mu) {
    float f = (rand() % 99 + 1) / 100.0;

    float interval = -1 * (1.0/mu) * log(f);
    interval = abs(interval);

    return interval;
}

int PriorityQueue::getSize() {
    return size;
}

void PriorityQueue::Print(int n) {
    Stats stats(((n/totalWaitTime) / (n)) * M / n, (n / serviceTime) / (n*currentTime), M);
    std::cout << "\nSimulation Statistics:\n"
              << "Po: " << idleTime
              << "\nAvg Time in System: " << stats.calcW()
              << "\nAvg Service Time: " << (serviceTime*totalWaitTime) / M
              << "\nRho: " << round(serviceTime / (M * totalWaitTime) * 100) / 100 << std::endl;
}