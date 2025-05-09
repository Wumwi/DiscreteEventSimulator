#include "BakePastryEvent.h"
#include "SellPastryEvent.h"
#include "State.h"
#include <iostream>
#include <memory>
#include <random>

BakePastryEvent::BakePastryEvent(double t) : Event(t) {}

void BakePastryEvent::execute(State& s) {
    //std::cout << "[Time " << time << "] Baking pastry\n";

    // Can bake up to 6 in a single batch
    if (s.pastriesMade <= 6 && s.pastriesMade > 0) {
        s.pastriesBaked = s.pastriesMade;
        s.pastriesMade = 0;
        // Cost for baking
        s.revenue -= 0.3;
    } else if (s.pastriesMade > 6) {   
        s.pastriesMade -= 6;
        s.pastriesBaked += 6;
        // Cost for baking
        s.revenue -= 0.3;
    } else {
        // Cost for baking nothing
        s.revenue -= 1.3;
    }

    std::random_device rd;
    std::mt19937 genX(rd());
    std::uniform_real_distribution<> distrX(std::numeric_limits<double>::epsilon(), s.bake_param);
    
    double x = distrX(genX);
    if (time + x < s.max()) {
        s.scheduleEvent(new BakePastryEvent(time + x));
    }
}
