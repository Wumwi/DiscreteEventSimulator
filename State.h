#ifndef STATE_H
#define STATE_H

#include "Event.h"
#include <queue>
#include <vector>
#include <memory>

class State {
private:
    struct EventComparator {
        bool operator()(const Event* a, const Event* b) const {
            return a->time > b->time; 
        }
    };

    std::priority_queue<
        Event*,
        std::vector<Event*>,
        EventComparator
    > eventQueue;

    double currentTime = 0.0;
    double maxTime = 100.0;

public:
    State() : make_param(1), bake_param(1), sell_param(1) {}
    State(double p1, double p2, double p3) : make_param(p1), bake_param(p2), sell_param(p3) {}
    void scheduleEvent(Event* event);
    void run();
    double now() const;
    double max() const;

    int pastriesMade = 0;
    int pastriesBaked = 0;
    int pastriesSold = 0;
    double revenue = 0;

    double make_param;
    double bake_param;
    double sell_param;  
};

#endif
