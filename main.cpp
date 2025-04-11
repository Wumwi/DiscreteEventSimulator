#include "State.h"
#include "MakePastryEvent.h"
#include "SellPastryEvent.h"
#include "BakePastryEvent.h"
#include "Simulator.h"
#include <memory>
#include <iostream>
#include <random>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: ./pastry_sim.exe <make_param> <bake_param> <sell_param> <sim_trials>" << std::endl;
        return 1;
    }

    double make_param = 1.0;
    double bake_param = 1.0;
    double sell_param = 1.0;
    int trials = 5000;

    try {
        make_param = std::stod(argv[1]);
        bake_param = std::stod(argv[2]);
        sell_param = std::stod(argv[3]);
        trials = std::stoi(argv[4]);
    } catch (...) {
        std::cerr << "Invalid parameters" << std::endl;
        return 1;
    }

    Simulator sim;
    std::string csv_path = "sim_log.csv";
    
    std::cout << sim.run(make_param, bake_param, sell_param, trials, csv_path) << std::endl;
    return 0;
}
