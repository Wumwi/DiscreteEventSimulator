#ifndef MAKEPASTRYEVENT_H
#define MAKEPASTRYEVENT_H

#include "Event.h"

class MakePastryEvent : public Event {
public:
    MakePastryEvent(double t);
    void execute(State& s) override;
};

#endif
