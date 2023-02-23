#include "catch/catch.hpp"
#include "../stats.hpp"
#include <iostream>

TEST_CASE(("Test stats")) {
    Stats stats(2, 3, 2);

    std::cout << stats.calcPo() << std::endl;
    std::cout << stats.calcAvgPeople() << std::endl;
    std::cout << stats.calcAvgTimeInQueue() << std::endl;
    float cust = round(stats.calcAvgCust() * 1000) / 1000;
    std::cout << cust << std::endl;
    float wait = round(stats.calcAvgWait() * 10000) / 10000;
    std::cout << wait << std::endl;

    CHECK(abs(stats.calcPo() - 0.5) < 0.001);
    CHECK((stats.calcAvgPeople() == 0.75));
    CHECK((stats.calcAvgTimeInQueue() == 0.375));

    CHECK((cust == 0.083));

    CHECK((wait == 0.0417));
}