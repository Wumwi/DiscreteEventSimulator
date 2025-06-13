#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <string>
#include "KalmanLinearRegression.h"
#include "eigen/Eigen/Dense"
#include <cmath>

class Simulator {
    public:
        KalmanLinearRegression kl; 
        Simulator() : kl(6) {}
        double run(double make_param, double bake_param, double sell_param, int trials, const std::string& csv_path);
        double acquisition(const Eigen::VectorXd& x_feat, double k = 2) const {
            return kl.predictMean(x_feat) + k * std::sqrt(kl.predictVariance(x_feat));
        }
        static Eigen::VectorXd expandFeatures(double a, double b, double c) {
            Eigen::VectorXd x_feat(6);
            x_feat << a, b, c, a*a, b*b, c*c;
            return x_feat;
        }
};

#endif