#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <string>

class Simulator {
    public:
        double run(double make_param, double bake_param, double sell_param, int trials, const std::string& csv_path);
};

#endif