#pragma once

#include "hawk_exports.h"
#include "core/Events/Event.h"

namespace Hawk {

	struct WindowProps {

		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Hawk Engine",
			unsigned int width = 1200,
			unsigned int height = 720)
			:Title(title), Width(width), Height(height) {}

	};

	//Interface representing a desktop system based window
	class HAWK_API Window {

	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};

		virtual void OnUpdate() = 0;

		//window attributes
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		//to be defined by Implementing Windows
		template <typename T>
		static Window* Create(T& eventHandler, const WindowProps& props = WindowProps());
	};


}