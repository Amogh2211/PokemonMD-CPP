#pragma once
#include <unordered_map>
#include <vector>
#include <functional>
#include <typeindex>
#include <raylib.h>
#include <Backend/Types.h>

namespace PKMD::Backend::Events
{
    enum class EventChannels
    {
        EVENT_TYPES_INVALID = -1,
        EVENT_TYPE_TEST = 0xDEAD,

        // Game focused events
        EVENT_TYPE_UI,
        EVENT_TYPE_GAMEPLAY,
        EVENT_TYPE_AUDIO,

        // Backend Events
        EVENT_TYPE_LEVEL,
        EVENT_TYPE_RENDERING,
        EVENT_TYPE_INPUT,

        // Sentinel
        EVENT_TYPES_MAX,
    };

    enum class EventPriority
    {
        EVENT_PRIORITY_LOW,
        EVENT_PRIORITY_NORMAL,
        EVENT_PRIORITY_High,
        EVENT_PRIORITY_MAX
    };

    class EventBase
    {
    public:
        virtual ~EventBase() = default;

        // Type and category
        virtual EventChannels GetChannel() const = 0;

        // Optional metadata
        virtual double GetTimestamp() const { return timestamp; }
        virtual EventPriority GetPriority() const { return EventPriority::EVENT_PRIORITY_NORMAL; }

        double timestamp = GetTime();
    };

    class EventBus : public Singleton<EventBus, true>
    {
    public:
        using Callback = std::function<void(const void*)>;
        using CallbackMap = std::unordered_map<size_t, Callback>;
        using ListenerMap = std::unordered_map<std::type_index, CallbackMap>;

        // ---------------------------------------------
        // Subscribe: returns a unique ID for unsubscribe
        // ---------------------------------------------
        template<typename T>
        size_t Subscribe(std::function<void(const T&)> callback, EventChannels channel)
        {
            ListenerMap& listenerMap = m_eventsMap[channel];
            CallbackMap& callbackMap = listenerMap[typeid(T)];

            size_t id = nextID;
            ++nextID;

            // wrap type-safe callback into type-erased one
            Callback safeCallback = [callback](const void* eventPtr) {
                callback(*static_cast<const T*>(eventPtr));
                };

            callbackMap[id] = safeCallback;
            return id;
        }

        // ---------------------------------------------
        // Unsubscribe: remove listener by ID
        // ---------------------------------------------
        template<typename T>
        void Unsubscribe(size_t eventHandle, EventChannels channel)
        {
            ListenerMap::iterator callbackMap = m_eventsMap[channel].find(typeid(T));
            if (callbackMap == m_eventsMap[channel].end())
            {
                PKMD_INFO_ASSERT(nullptr, "Callback map not found!");
                return;
            }
            auto& it = callbackMap->second;

            if (it.find(eventHandle) != it.end())
            {
                it.erase(eventHandle);
            }
        }

        // ---------------------------------------------
        // Emit event: safe, fast, no allocations
        // ---------------------------------------------
        template<typename T>
        void Emit(const T& event, size_t eventHandle, EventChannels channel)
        {
            ListenerMap::iterator callbackMap = m_eventsMap[channel].find(typeid(T));
            if (callbackMap == m_eventsMap[channel].end())
            {
                PKMD_INFO_ASSERT(callbackMap != m_eventsMap[channel].end(), "Could not find regitered event");
                return;
            }

            // Send event to all subscribers
            for (auto& [id, cb] : callbackMap->second)
                cb(&event);
        }


        template<typename T>
        void Broadcast(const T& event, EventChannels channel)
        {
            auto it = m_eventsMap[channel].find(typeid(T));
            if (it == m_eventsMap[channel].end()) return;

            for (auto& [id, cb] : it->second)
                cb(&event);
        }


        /// @brief Clear all maps
        void Reset();

        


    private:
        std::map<EventChannels, ListenerMap> m_eventsMap;
        size_t nextID = 1;
    };
}
