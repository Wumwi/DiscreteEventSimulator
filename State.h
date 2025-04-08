#ifndef STATE_H
#define STATE_H

#include "Event.h"
#include <queue>
#include <vector>
#include <memory>

class State {
private:
    struct EventComparator {
        bool operator()(const std::shared_ptr<Event>& a, const std::shared_ptr<Event>& b) const {
            return a->time > b->time; 
        }
    };

    std::priority_queue<
        std::shared_ptr<Event>,
        std::vector<std::shared_ptr<Event>>,
        EventComparator
    > eventQueue;

    double currentTime = 0.0;

public:
    void scheduleEvent(std::shared_ptr<Event> event);
    void run();
    double now() const;
};

#endif
