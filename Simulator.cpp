#include "Simulator.h"
#include "State.h"
#include "MakePastryEvent.h"
#include "SellPastryEvent.h"
#include "BakePastryEvent.h"
#include <memory>
#include <iostream>
#include <random>
#include <string>

double Simulator::run(double make_param, double bake_param, double sell_param, int trials) {
    std::random_device rd;
    std::mt19937 genX(rd());
    std::mt19937 genY(rd());
    std::mt19937 genZ(rd());
    std::uniform_real_distribution<> distrX(std::numeric_limits<double>::epsilon(), make_param);
    std::uniform_real_distribution<> distrY(std::numeric_limits<double>::epsilon(), bake_param);
    std::uniform_real_distribution<> distrZ(std::numeric_limits<double>::epsilon(), sell_param);

    double totalRevenue = 0;
    for (int i=0; i<trials; i++) {
        State s;
        double x = distrX(genX);
        while (x < s.max()) {
            s.scheduleEvent(new MakePastryEvent(x));
            x += distrX(genX);
        }

        double y = distrY(genY);
        while (y < s.max()) {
            s.scheduleEvent(new BakePastryEvent(y));
            y += distrY(genY);
        }

        double z = distrZ(genZ);
        while (z < s.max()) {
            s.scheduleEvent(new SellPastryEvent(z));
            z += distrY(genY);
        }

        s.run();

        totalRevenue += s.revenue;
    }

    double averageRevenue = totalRevenue / trials;
    return averageRevenue;
}