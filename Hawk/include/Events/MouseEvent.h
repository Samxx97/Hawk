#pragma once
#include "Event.h"

namespace Hawk {

	class MouseButtonEvent : public Event {

	public:

		inline int GetButton() const { return m_Button; };

		EVENT_CATEGORY(EventCategory::MouseButton | EventCategory::Input);

	protected:
		MouseButtonEvent(int button) : m_Button(button) {};

		int m_Button;
	};


	class MouseButtonPressedEvent : public MouseButtonEvent {

	public:

		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {};

		std::string toString() {

			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;

			return ss.str();
		}

		EVENT_TYPE(MouseButtonPressed);

	};


	class MouseButtonReleasedEvent : public MouseButtonEvent {

	public:

		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {};

		std::string toString() const override {

			std::stringstream ss;
			ss << "MouseButtonReleaseEvent: " << m_Button;

			return ss.str();
		}

		EVENT_TYPE(MouseButtonReleased);

	};

	class MouseMovedEvent : public Event {

	public:
		inline float GetXpos() const { return m_MouseX; };
		inline float GetYpos() const { return m_MouseY; };

		MouseMovedEvent(float xpos, float ypos) : m_MouseX(xpos), m_MouseY(ypos) {};

		std::string toString() const override {

			std::stringstream ss;
			ss << "MouseMovedEvent: " << "(" << m_MouseX << "," << m_MouseY << ")";
			return ss.str();
		}


		EVENT_CATEGORY(EventCategory::Mouse | EventCategory::Input);
		EVENT_TYPE(MouseMoved);

	private:

		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event {

	public:
		inline float GetXoffset() const { return m_XOffset; };
		inline float GetYoffset() const { return m_YOffset; };

		MouseScrolledEvent(float xoffset, float yoffset) : m_XOffset(xoffset), m_YOffset(yoffset) {};

		std::string toString() const override {

			std::stringstream ss;
			ss << "MouseScrolledEvent: " << "(" << m_XOffset << "," << m_YOffset << ")";
			return ss.str();
		}


		EVENT_CATEGORY(EventCategory::Mouse | EventCategory::Input);
		EVENT_TYPE(MouseScrolled);

	private:

		float m_XOffset, m_YOffset;
	};
}