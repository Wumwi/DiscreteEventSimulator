#include "MakePastryEvent.h"
#include "BakePastryEvent.h"
#include "State.h"
#include <iostream>
#include <memory>
#include <random>

MakePastryEvent::MakePastryEvent(double t) : Event(t) {}

void MakePastryEvent::execute(State& s) {
    //std::cout << "[Time " << time << "] Making pastry\n";
    // cap unbaked pastries at 16
    if (s.pastriesMade < 16) {
        s.pastriesMade++;
        s.revenue -= 0.2;
    } else {
        // Inflict revenue penalty of 0.4
        s.revenue -= 0.4;
    }

    std::random_device rd;
    std::mt19937 genX(rd());
    std::uniform_real_distribution<> distrX(std::numeric_limits<double>::epsilon(), s.make_param);
    
    double x = distrX(genX);
    if (time + x < s.max()) {
        s.scheduleEvent(new MakePastryEvent(time + x));
    }
}
