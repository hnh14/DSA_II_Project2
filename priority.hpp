#ifndef PRIORITY_H
#define PRIORITY_H
#include "customer.hpp"
#include "fifo.hpp"

class PriorityQueue {
    private:
        Customer* head;
        FIFO fifo;
        float avg;
        float serverAvailableCnt, customerCount, currentTime;
        int size=0;
        int M;
        float totalWaitTime = 0;
        int customerWaitCount=0;
        float currentWaitTime;
        float serviceTime=0;
        int idleTime;
        float lastWait=0;
    public:
        PriorityQueue(float, float);
        void Push(Customer*, Customer* currentNode = nullptr);
        Customer* Pop();
        void processNextEvent();
        void processStatistics(Customer*);
        float getNextRandomfloaterval(float);
        void Add();
        int getSize();
        void Print(int);
};

#endif 