#pragma once
#include "eigen/Eigen/Dense"

class KalmanLinearRegression {
using Vector = Eigen::VectorXd;
using Matrix = Eigen::MatrixXd;
private:
    int n;
    Matrix Q,P;
    Vector theta;
    double R;
public:
    KalmanLinearRegression(int dim, double initial_variance = 1e-5, double measurement_noise_variance = 1.0)
        : n(dim), Q(initial_variance * Matrix::Identity(dim, dim)), P(Matrix::Identity(dim, dim)), 
        theta(Vector::Zero(dim)), R((measurement_noise_variance)) {}

    void update(const Vector& x, double y) {
        P += Q;  // Predict covariance update

        double S = (x.transpose() * P * x)(0) + R;  // Innovation covariance
        Vector K = P * x / S;                        // Kalman gain

        double y_est = x.dot(theta);
        theta += K * (y - y_est);                    // Update estimate
        P -= K * x.transpose() * P;                  // Update covariance
    }

    Vector getTheta() const { return theta; }

    double predictVariance(const Vector& x) const {
        return x.transpose() * P * x + R;
    }

    double predictMean(const Vector& x) const {
        return x.dot(theta);
    }
};
