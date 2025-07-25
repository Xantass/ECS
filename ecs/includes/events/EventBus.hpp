#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <typeindex>
#include <memory>

class EventBus {
public:
    template<typename Event>
    using Handler = std::function<void(const Event&)>;

    template<typename Event>
    void subscribe(Handler<Event> handler) {
        auto& handlers = getHandlers<Event>();
        handlers.push_back(std::move(handler));
    }

    template<typename Event>
    void emit(const Event& event) {
        for (auto& handler : getHandlers<Event>()) {
            handler(event);
        }
    }

private:
    template<typename Event>
    std::vector<Handler<Event>>& getHandlers() {
        static std::vector<Handler<Event>> handlers;
        return handlers;
    }
};