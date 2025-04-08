#ifndef EVENT_H
#define EVENT_H

#include <memory>

class State;

class Event {
public:
    double time;

    Event(double t) : time(t) {}

    virtual void execute(State& sim) = 0;

    virtual ~Event() = default;
};

#endif
