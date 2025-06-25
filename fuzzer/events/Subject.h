#ifndef FUZZFLOW_SUBJECT_H
#define FUZZFLOW_SUBJECT_H

#include "Observer.h"

#include <map>
#include <vector>
#include <memory>

using std::map;
using std::vector;
using std::shared_ptr;

namespace FuzzFlow {

class Subject {
private:
    map<EventType,
        vector<shared_ptr<Observer>>> observers;

public:
    void add_observer(const EventType type, const shared_ptr<Observer>& observer)
    {
        if (std::find(observers[type].begin(), observers[type].end(), observer) == observers[type].end()) {
            observers[type].push_back(observer);
        }
    }

    void remove_observer(const EventType type, const shared_ptr<Observer>& observer)
    {
        auto& obsList = observers[type];
        obsList.erase(std::remove(obsList.begin(), obsList.end(), observer), obsList.end());
    }

    /// The data parameter defaults to nullptr,
    /// indicating that no data needs to be passed to the observers.
    void notify_observers(const EventType type, const shared_ptr<EventData> data=nullptr)
    {
        for (const auto& observer : observers[type]) {
            if (observer) {
                observer->onNotify(type, data);
            }
        }
    }
};

} /// end of namespace


#endif //FUZZFLOW_SUBJECT_H
