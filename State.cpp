#include "State.h"

void State::scheduleEvent(std::shared_ptr<Event> event) {
    eventQueue.push(event);
}

void State::run() {
    while (!eventQueue.empty()) {
        auto event = eventQueue.top();
        eventQueue.pop();
        currentTime = event->time;
        event->execute(*this);
    }
}

double State::now() const {
    return currentTime;
}
