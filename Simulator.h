#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <string>
#include "KalmanLinearRegression.h"
#include "eigen/Eigen/Dense"
#include <cmath>

class Simulator {
    public:
        KalmanLinearRegression kl; 
        Simulator() : kl(3) {}
        double run(double make_param, double bake_param, double sell_param, int trials, const std::string& csv_path);
        double acquisition(const Eigen::VectorXd& x, double k = 2) const {
            return kl.predictMean(x) + k * std::sqrt(kl.predictVariance(x));
        }
};

#endif