#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer {
    private:
        float arrivalTime;
        float startOfServiceTime;
        float departureTime;
        float priority;
        bool IsDeparture;
        Customer* nextCust;
    public:
        Customer(float);
        void setNext(Customer*);
        bool isDeparture();
        Customer* getNext(){return nextCust;};
        void setPriority(float);
        void setStartOfServiceTime(float);
        void setDepartureTime(float);
        float getPriority();
        float getArrivalTime();
        float getDepartureTime();
        float getStartOfServiceTime();
};

#endif