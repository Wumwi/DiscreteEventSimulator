#include "State.h"

State::State(double p1, double p2, double p3) {
    make_param = p1;
    bake_param = p2;
    sell_param = p3;
}

void State::scheduleEvent(Event* event) {
    eventQueue.push(event);
}

void State::run() {
    while (!eventQueue.empty()) {
        auto event = eventQueue.top();
        eventQueue.pop();
        currentTime = event->time;
        event->execute(*this);
        delete event;
    }
}

double State::now() const {
    return currentTime;
}

double State::max() const {
    return maxTime;
}
