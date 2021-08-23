#include "core/Window.h"

struct GLFWwindow;

namespace Hawk {


	template<class T>
	class HAWK_API AnyPlatformWindow : public Window {

	public:

		//AnyPlatformWindow(const WindowProps&);
		AnyPlatformWindow(T& eventHandler, const WindowProps& props);

		~AnyPlatformWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; };
		inline unsigned int GetHeight() const override { return m_Data.Height; };

		inline void  SetEventCallback(const EventCallbackFn& callback) override { m_Data.callback = callback; };
		void SetVSync(bool enabled) override;
		bool IsVSync() const override { return m_Data.IsVSync; }



	private:

		static bool s_Glfw_initiliazed;
		GLFWwindow* m_Window;


		struct WindowData {

			WindowData(T& eventHandler) : eventHandler(eventHandler) {};

			std::string Title;
			unsigned int Width, Height;
			bool IsVSync;
			EventCallbackFn callback;
			T& eventHandler;

		};

		WindowData m_Data;

		void Init(const WindowProps&);


	};

	template<typename T>
	static Window* Window::Create(T& eventHandler, const WindowProps& props) {
		return new AnyPlatformWindow<T>(eventHandler, props);
	}


}