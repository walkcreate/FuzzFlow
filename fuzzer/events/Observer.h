#ifndef FUZZFLOW_OBSERVER_H
#define FUZZFLOW_OBSERVER_H

#include <memory>
using std::shared_ptr;

#include "Event.h"

namespace FuzzFlow {

class Observer {
public:
    ///
    /// Why do we need shared ptr of EventData as argument?
    ///
    /// For events, we need to pass data to the observer.
    /// For example, for CrashFound, we need to pass the crash case to Storage.
    /// The data can be passed within the Event
    ///
    virtual void onNotify(EventType eventType, const shared_ptr<EventData>& eventData) = 0;

    virtual ~Observer() = default;
};

} /// end of namespace FuzzFlow

#endif //FUZZFLOW_OBSERVER_H
