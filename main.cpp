#include "State.h"
#include "MakePastryEvent.h"
#include "SellPastryEvent.h"
#include "BakePastryEvent.h"
#include "Simulator.h"
#include "KalmanLinearRegression.h"
#include <memory>
#include <iostream>
#include <random>
#include <string>
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
    std::string csv_path = "sim_log.csv";

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

    for (int i=1; i<=11; i++) {
        std::random_device rd;
        std::mt19937 genX(rd());
        std::uniform_real_distribution<> distrX(std::numeric_limits<double>::epsilon(), 100);
        std::uniform_real_distribution<> distrY(std::numeric_limits<double>::epsilon(), 100);
        std::uniform_real_distribution<> distrZ(std::numeric_limits<double>::epsilon(), 100);

        if (i < 11) {
            make_param = distrX(genX);
            bake_param = distrY(genX);
            sell_param = distrZ(genX);
        } else {
            make_param = makeInput;
            bake_param = bakeInput;
            sell_param = sellInput;
        }

        Eigen::VectorXd x(3), t(3);
        x << make_param, bake_param, sell_param;
        
        double y = sim.run(make_param, bake_param, sell_param, trials, csv_path);
        
        sim.kl.update(x,y);
        std::cout << "#" << i << " " << y << std::endl;
        std::cout << "Mean " << sim.kl.predictMean(x) << std::endl;
        std::cout << "Variance " << sim.kl.predictVariance(x) << std::endl;
    }
    return 0;
}
