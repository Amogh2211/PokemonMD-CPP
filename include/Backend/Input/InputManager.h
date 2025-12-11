#pragma once
#include <raylib.h>
#include <Backend/Events/EventBus.h>
#include <Backend/Input/InputTypes.h>

using namespace PKMD::Backend::Events;

namespace PKMD::Backend::Input
{
    enum class InputEventType {
        InputEvent_KeyPressed,
        InputEvent_KeyReleased,
        InputEvent_KeyHeld,
        InputEvent_MouseButtonPressed,
        InputEvent_MouseButtonReleased,
        InputEvent_MouseButtonHeld,
        InputEvent_MouseMoved,
        InputEvent_Scroll,
    };

    const std::vector<int> keys =
    {
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_ENTER,
        KEY_SPACE,
    };

    struct InputEvent {
        InputEventType type;
        int key;       // for keys or mouse buttons
        int mouseX;
        int mouseY;  // for mouse events
        float scrollY;       // for scroll
    };

    class InputManager : public Singleton<InputManager, true>
	{
    public:
        // ---------------- Input Polling ------------------
        static void PollInput(EventBus& bus)
        {
            for (int k : keys)
            {
                if (IsKeyDown(k))
                {
                    bus.Broadcast(KeyPressedEvent{ k }, EventChannels::EVENT_TYPE_INPUT);
                }
            }

            for (int k : keys)
            {
                if (IsKeyReleased(k))
                {
                    bus.Broadcast(KeyReleasedEvent{ k }, EventChannels::EVENT_TYPE_INPUT);
                }
            }
        }
	};
}