#pragma once
#include <unordered_map>
#include <vector>
#include <functional>
#include <typeindex>
#include <Backend/Types.h>

namespace PKMD::Backend::Events
{
    class EventBus
    {
    public:
        using Callback = std::function<void(const void*)>;
        using CallbackMap = std::unordered_map<size_t, Callback>;
        using ListenerMap = std::unordered_map<std::type_index, CallbackMap>;

        // ---------------------------------------------
        // Subscribe: returns a unique ID for unsubscribe
        // ---------------------------------------------
        template<typename T>
        size_t Subscribe(std::function<void(const T&)> callback)
        {
            auto& callbackMap = m_eventsMap[typeid(T)];

            size_t id = nextID++;
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
        void Unsubscribe(size_t eventHandle)
        {
            ListenerMap::iterator callbackMap = m_eventsMap.find(typeid(T));
            if (callbackMap == m_eventsMap.end())
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
        void Emit(const T& event, size_t eventHandle)
        {
            ListenerMap::iterator callbackMap = m_eventsMap.find(typeid(T));
            if (callbackMap == m_eventsMap.end())
            {
                PKMD_INFO_ASSERT(callbackMap != m_eventsMap.end(), "Could not find regitered event");
                return;
            }

            callbackMap->second[eventHandle](&event);
        }

        /// @brief Clear all maps
        void Reset();

    private:
        ListenerMap m_eventsMap;
        size_t nextID = 1;
    };
}
