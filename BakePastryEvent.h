#ifndef BAKEPASTRYEVENT_H
#define BAKEPASTRYEVENT_H

#include "Event.h"

class BakePastryEvent : public Event {
public:
    BakePastryEvent(double t);
    void execute(State& s) override;
};

#endif
