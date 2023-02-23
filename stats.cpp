#include "stats.hpp"
#include <math.h>
#include <iostream>

Stats::Stats(float lambda, float mu, float M) {
    this->lambda = lambda;
    this->mu = mu;
    this->M = M;
}

float Stats::calcPo(){
    return 1.0 / (Summation() + ((1/tgamma(M+1.0)) * pow(lambda / mu, M) * ((M*mu) / (M*mu - lambda)) ));
}

float Stats::calcL() {
    return ((lambda * mu * pow((lambda/mu), M)) / (tgamma(M) * pow(M*mu - lambda, 2))) * calcPo() + (lambda / mu);
}

float Stats::calcW() { 
    return calcL() / lambda;
}

float Stats::calcLq() {
    return calcL() - (lambda / mu);
}

float Stats::calcWq() {
    return calcLq() / lambda;
}

float Stats::calcRho() {
    return (lambda / (M * mu));
}

float Stats::Summation() {
    float sum = 0;
    for(float i = 0; i < M; i++) {
        sum += (1/tgamma(i+1)) * pow(lambda / mu, i);
    }

    return sum;
}

void Stats::Print() {
    std::cout << "\nEntered values:\n" << std::endl
              << "Lambda: " << lambda << std::endl
              << "mu: " << mu << std::endl
              << "M: " << M << std::endl << std::endl

              << "Analytic Model:\n"
              << "Po: " << calcPo() << std::endl
              << "L: " << calcL() << std::endl
              << "W: " << calcW() << std::endl
              << "Lq: " << calcLq() << std::endl
              << "Wq: " << calcWq() << std::endl
              << "Rho: " << calcRho() << std::endl;
              
}