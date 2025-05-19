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
    int trials = 1;

    try {
        make_param = std::stod(argv[1]);
        bake_param = std::stod(argv[2]);
        sell_param = std::stod(argv[3]);
        trials = std::stoi(argv[4]);
    } catch (...) {
        std::cerr << "Invalid parameters" << std::endl;
        return 1;
    }

    for (int i=1; i<=1000; i++) {
        std::random_device rd;
        std::mt19937 genX(rd());
        std::uniform_real_distribution<> distrX(1, 100);

        make_param = distrX(genX);
        bake_param = distrX(genX);
        sell_param = distrX(genX);

        Simulator sim;
        std::string csv_path = "sim_log.csv";
        
        std::cout << "#" << i << " " << sim.run(make_param, bake_param, sell_param, trials, csv_path) << std::endl;
    }
    return 0;
}
