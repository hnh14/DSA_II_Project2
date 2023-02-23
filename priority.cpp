#include "priority.hpp"
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

    if(getSize() > 200) {
        fifo.Push(toPush);
    }

    if(head == nullptr) {
        head = toPush;
        head->setNext(nullptr);
        incrementSize();
        return;
    }

    if(currentNode == nullptr) {
        if(toPush->getPriority() <= head->getPriority()) {
            toPush->setNext(head);
            head = toPush;
            incrementSize();
            return;
        }
        else
            currentNode = head;
    }
    
    if(currentNode->getNext() == nullptr) {
        toPush->setNext(nullptr);
        currentNode->setNext(toPush);
        incrementSize();
        return;
    }

    if(toPush->getPriority() <= currentNode->getNext()->getPriority()) {
        toPush->setNext(currentNode->getNext());
        currentNode->setNext(toPush);
        incrementSize();
        return;
    }

    Push(toPush, currentNode->getNext());    
    
}

Customer* PriorityQueue::Pop() {
    if(head == nullptr)
        return nullptr;

    Customer* toPop = head;
    head = head->getNext();
    decrementSize();

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
    if(serverAvailableCnt == M) {
    float time = 0;
    time += (cust->getDepartureTime() - lastWait);
    setIdleTime(time);
    std::cout << lastWait << std::endl;
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

int PriorityQueue::incrementSize(){
    return size++;
}

int PriorityQueue::decrementSize(){
    return size--;
}

void PriorityQueue::setIdleTime(float time){
    idleTime = time;
}
float PriorityQueue::getIdleTime(){
    return idleTime;
}

void PriorityQueue::Print(int n) {
    std::cout << "\nSimulation Statistics:\n"
              << "Po: " << idleTime
              << "\nAvg Time in System: " << totalWaitTime / n 
              << "\nAvg Service Time: " << serviceTime / n
              << "\nRho: " << serviceTime / (M * totalWaitTime) << std::endl;
}