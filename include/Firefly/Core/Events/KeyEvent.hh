#pragma once

#include <sstream>

#include "Event.hh"

namespace flyCore {

    /// @class KeyEvent
    /// Abstract class, it is never going to be directly constructed. Therefore it doesn't have to
    /// implement the virtual methods from Event, its derived classes will.
    class KeyEvent : public Event
    {
    public:
        inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(int key_code)
            : m_KeyCode(key_code) {}

        int m_KeyCode;
    };

    /// @class KeyPressedEvent
    /// This class represents the action of a key being pressed, for now it will keep track of how
    /// many repeated key events are sent when a key is hold pressed for a period of time.
    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int key_code, int repeat_count)
            : KeyEvent(key_code), m_RepeatCount(repeat_count) {}

        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        int m_RepeatCount;
    };

    /// @class KeyReleasedEvent
    /// The opposite of KeyPressedEvent.
    class KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int key_code)
            : KeyEvent(key_code) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    /// @class KeyTypedEvent
    /// This class represents what you would imagine, a key being pressed in the keyboard.
    class KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int key_code)
            : KeyEvent(key_code) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };

}
