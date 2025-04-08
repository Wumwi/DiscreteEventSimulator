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

public:
    void scheduleEvent(Event* event);
    void run();
    double now() const;

    int pastriesMaking = 0;
    int pastriesBaking = 0;
    int pastriesSold = 0;
};

#endif
