#include "customer.hpp"

Customer::Customer(float time) {
    arrivalTime = time;
    priority = arrivalTime;
    nextCust = nullptr;
    IsDeparture = false;
    departureTime = 0;
}

void Customer::setPriority(float time) {
    priority = time;
}

void Customer::setNext(Customer* next) {
    nextCust = next;
}

void Customer::setStartOfServiceTime(float time) {
    startOfServiceTime = time;
}

void Customer::setDepartureTime(float time) {
    IsDeparture = true;
    priority = time;
    departureTime = time;
}

bool Customer::isDeparture() {
    return IsDeparture;
}

float Customer::getPriority() {
    return priority;
}

float Customer::getArrivalTime() {
    return arrivalTime;
}

float Customer::getDepartureTime() {
    return departureTime;
}

float Customer::getStartOfServiceTime() {
    return startOfServiceTime;
}
