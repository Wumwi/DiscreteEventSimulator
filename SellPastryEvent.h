#ifndef SELLPASTRYEVENT_H
#define SELLPASTRYEVENT_H

#include "Event.h"

class SellPastryEvent : public Event {
public:
    SellPastryEvent(double t);
    void execute(State& s) override;
};

#endif
