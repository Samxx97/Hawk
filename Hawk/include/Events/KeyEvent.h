#pragma once

#include "Event.h"


namespace Hawk {

	class KeyEvent : public Event {

	public:

		inline unsigned int GetKeyCode() const { return m_KeyCode; };

		EVENT_CATEGORY(EventCategory::Input | EventCategory::Keyboard);

	protected:
		KeyEvent(unsigned int keycode) :
			m_KeyCode(keycode) {};

		unsigned int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {

	public:

		KeyPressedEvent(unsigned int keyCode, unsigned int repeatCount)
			: KeyEvent(keyCode), m_RepeatCount(repeatCount) {};

		inline unsigned int GetRepeatCount() const { return m_RepeatCount; };

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";

			return ss.str();

		}

		EVENT_TYPE(KeyPressed);


	private:
		unsigned int m_RepeatCount;
	};


	class KeyReleasedEvent : public KeyEvent {

	public:
		KeyReleasedEvent(unsigned int keyCode)
			: KeyEvent(keyCode) {};



		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;

			return ss.str();

		}

		EVENT_TYPE(KeyReleased);


	};

	class KeyTypedEvent : public KeyEvent {

	public:

		KeyTypedEvent(unsigned int keyCode)
			: KeyEvent(keyCode) {};


		std::string toString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;

			return ss.str();

		}

		EVENT_TYPE(KeyTyped);


	};

}