#include "State.h"

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
