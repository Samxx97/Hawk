#pragma once

#include "Event.h"

namespace Hawk {

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Height(height), m_Width(width) {};

		inline unsigned int GetHeight() const { return m_Height; }
		inline unsigned int GetWidth() const { return m_Width; }

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;

			return ss.str();

		}

		EVENT_TYPE(WindowResize);
		EVENT_CATEGORY(EventCategory::Application);

	private:
		unsigned int m_Height, m_Width;

	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {};

		std::string toString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent ";

			return ss.str();

		}

		EVENT_TYPE(WindowClose);
		EVENT_CATEGORY(EventCategory::Application);



	};


}