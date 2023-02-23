#ifndef STATS_H
#define STATS_H

class Stats {
    private:
        float lambda, mu, M;
    public:
        Stats(float, float, float);
        float calcPo();
        float calcL();
        float calcW();
        float calcLq();
        float calcWq();
        float calcRho();
        float Summation();
        void Print();
};

#endif