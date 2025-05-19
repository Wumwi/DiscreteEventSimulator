#include "Simulator.h"
#include "State.h"
#include "MakePastryEvent.h"
#include "SellPastryEvent.h"
#include "BakePastryEvent.h"
#include <memory>
#include <iostream>
#include <random>
#include <fstream>
#include <iomanip>
#include <string>

double Simulator::run(double make_param, double bake_param, double sell_param, int trials, const std::string& csv_path) {
    std::random_device rd;
    std::mt19937 genX(rd());
    std::mt19937 genY(rd());
    std::mt19937 genZ(rd());
    std::uniform_real_distribution<> distrX(std::numeric_limits<double>::epsilon(), make_param);
    std::uniform_real_distribution<> distrY(std::numeric_limits<double>::epsilon(), bake_param);
    std::uniform_real_distribution<> distrZ(std::numeric_limits<double>::epsilon(), sell_param);

    double totalRevenue = 0;
    for (int i=0; i<trials; i++) {
        State s(make_param, bake_param, sell_param);

        s.scheduleEvent(new MakePastryEvent(distrX(genX)));
        s.scheduleEvent(new BakePastryEvent(distrY(genY)));
        s.scheduleEvent(new SellPastryEvent(distrZ(genZ)));
  
        s.run();
        
        s.revenue -= s.pastriesMade + s.pastriesBaked;
        totalRevenue += s.revenue;
    }

    double averageRevenue = totalRevenue / trials;

    if (!csv_path.empty()) {
        std::ofstream file(csv_path, std::ios::app);  
        if (file.is_open()) {
            file << std::fixed << std::setprecision(4);
            file << make_param << "," << bake_param << "," << sell_param << "," << averageRevenue << "\n";
            file.close();
        }
    }

    return averageRevenue;
}