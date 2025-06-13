#include "State.h"
#include "MakePastryEvent.h"
#include "SellPastryEvent.h"
#include "BakePastryEvent.h"
#include "Simulator.h"
#include "KalmanLinearRegression.h"
#include <memory>
#include <iostream>
#include <iomanip>
#include <random>
#include <string>
#include <fstream>
#include "eigen/Eigen/Dense"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: ./pastry_sim.exe <make_param> <bake_param> <sell_param> <sim_trials>" << std::endl;
        return 1;
    }

    double make_param = 1.0;
    double bake_param = 1.0;
    double sell_param = 1.0;
    int trials = 1;

    Simulator sim;
    std::string csv_path = "kalman.csv";

    try {
        make_param = std::stod(argv[1]);
        bake_param = std::stod(argv[2]);
        sell_param = std::stod(argv[3]);
        trials = std::stoi(argv[4]);
    } catch (...) {
        std::cerr << "Invalid parameters" << std::endl;
        return 1;
    }

    double makeInput = make_param;
    double bakeInput = bake_param;
    double sellInput = sell_param;

    std::random_device rd;
    std::mt19937 genX(rd());
    std::uniform_real_distribution<> distrX(1, 99);

    for (int i=1; i<=300; i++) {
        Eigen::VectorXd x_feat(6);
        if (i <= 50) {
            make_param = distrX(genX);
            bake_param = distrX(genX);
            sell_param = distrX(genX);
            double y = sim.run(make_param, bake_param, sell_param, trials, csv_path);
            x_feat = sim.expandFeatures(make_param, bake_param, sell_param);
            sim.kl.update(x_feat,y);
            std::cout << "#" << i << " " << y << std::endl;
            std::string kalman_path = "kalman_convergence.csv";
            if (!kalman_path.empty()) {
                std::ofstream file(kalman_path, std::ios::app);  
                if (file.is_open()) {
                    file << std::fixed << std::setprecision(2);
                    file << i << "," << y << "\n";
                    file.close();
                }
            }
        } else {
            double best = -1000;
            double bestMake, bestBake, bestSell;
            for (double a=1; a <= 100; a += 5) {
                for (double b=1; b <= 100; b += 5) {
                    for (double c=1; c <= 100; c += 5) {
                        x_feat = sim.expandFeatures(a, b, c);
                        double acq_value = sim.acquisition(x_feat, 1);
                        if (acq_value > best) {
                            best = acq_value;
                            bestMake = a;
                            bestBake = b;
                            bestSell = c;
                        }
                    }
                }
            }
            double y = sim.run(bestMake, bestBake, bestSell, trials, csv_path);
        
            Eigen::VectorXd best_x_feat = sim.expandFeatures(bestMake, bestBake, bestSell);
            sim.kl.update(best_x_feat,y);
            std::cout << "#" << i << " " << y << std::endl;

            std::string kalman_path = "kalman_convergence.csv";
            if (!kalman_path.empty()) {
                std::ofstream file(kalman_path, std::ios::app);  
                if (file.is_open()) {
                    file << std::fixed << std::setprecision(2);
                    file << i << "," << y << "\n";
                    file.close();
                }
            }
        }
    }
    return 0;
}
