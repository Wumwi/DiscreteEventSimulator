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
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: One of the arguments is not a valid double." << std::endl;
        return 1;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: One of the arguments is out of range for a double." << std::endl;
        return 1;
    }

    Simulator sim;
    std::cout << sim.run(make_param, bake_param, sell_param, trials) << std::endl;
    return 0;
}
