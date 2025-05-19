#pragma once
#include "eigen/Eigen/Dense"

class KalmanLinearRegression {
using Vector = Eigen::VectorXd;
using Matrix = Eigen::MatrixXd;
private:
    int n;
    double R;
    Matrix Q, P;
    Vector theta;
public:
    KalmanLinearRegression(int dim, double initial_variance = 1e-5, double measurement_noise_variance = 1.0)
        : n(dim), Q(initial_variance * Matrix::Identity(dim, dim)), R(measurement_noise_variance),
        theta(Vector::Zero(dim)), P(Matrix::Identity(dim, dim)) {}

    void update(const Vector& x, double y) {
        P += Q;  // Predict covariance update

        double S = (x.transpose() * P * x)(0) + R;  // Innovation covariance
        Vector K = P * x / S;                        // Kalman gain

        double y_est = x.dot(theta);
        theta += K * (y - y_est);                    // Update estimate
        P -= K * x.transpose() * P;                  // Update covariance
    }

    Vector getTheta() const { return theta; }
};
