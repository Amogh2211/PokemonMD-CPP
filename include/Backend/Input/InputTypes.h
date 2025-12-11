#pragma once


namespace PKMD::Backend::Input
{

    struct KeyEventBase
    {
        int keyCode;
    };

    struct KeyPressedEvent : KeyEventBase
    {
        
    };

    struct KeyReleasedEvent : KeyEventBase
    {
        
    };

    struct KeyHeldEvent : KeyEventBase
    {
        double timeHeld = 0;
    };
}