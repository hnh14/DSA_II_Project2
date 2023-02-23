#include <iostream>
#include "priority.hpp"
#include "stats.hpp"


int main() {
    int n, lambda, mu, M, nCount;

    std::cout << "Please enter the number of arrivals to simulate (n): ";
    std::cin >> n;
    nCount = n;

    std::cout << "Please enter the average arrivals in a time period (lambda): ";
    std::cin >> lambda;

    std::cout << "Please enter the average number served in a time period (mu): ";
    std::cin >> mu;

    while(M < 1 || M > 10) {
        std::cout << "Please enter the the number of service channels (1 to 10): ";
        std::cin >> M;
    }
    
    Stats model(lambda, mu, M);
    model.Print();

    PriorityQueue priority(mu, M);

    for(int i = 0; i < M; i++) {
        priority.Add();
        nCount--;
    }

    while(priority.getSize() > 1) {
        priority.processNextEvent();
        if(nCount > 0 && priority.getSize() <= M+1) {
            priority.Add();
            nCount--;
        }
        if(priority.getSize() <= 1)
            break;
    }

    priority.Print(n);      
    
}
