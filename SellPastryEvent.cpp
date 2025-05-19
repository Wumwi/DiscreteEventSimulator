#include "SellPastryEvent.h"
#include "State.h"
#include <iostream>
#include <random>
#include <cmath>

SellPastryEvent::SellPastryEvent(double t) : Event(t) {}

void SellPastryEvent::execute(State& s) {
    //std::cout << "[Time " << time << "] Selling pastry\n";

    // Cost function
    double ideal_ratio = 6.0;
    double sigma = 10.0;
    double base_price = 0.2*s.sell_param + 0.25;

    double ratio_term = 0.0;
    double ratio = s.bake_param / s.make_param;
    ratio_term = std::exp(-std::pow(ratio - ideal_ratio, 2) / (2 * sigma * sigma));

    double price = base_price * ratio_term;

    if (s.pastriesBaked > 0) {
        s.pastriesBaked--;
        s.pastriesSold++;
        s.revenue += price;
    } else {
        s.revenue -= price / 10;  // Penalty for trying to sell nothing
    }

    std::random_device rd;
    std::mt19937 genX(rd());
    std::uniform_real_distribution<> distrX(std::numeric_limits<double>::epsilon(), s.sell_param);
    
    double x = distrX(genX);
    if (time + x < s.max()) {
        s.scheduleEvent(new SellPastryEvent(time + x));
    }
}
