#include "core/Layer.h"
#include "core/Events/KeyEvent.h"
#include "core/Events/MouseEvent.h"
#include "core/Events/ApplicationEvent.h"

namespace Hawk {

	class HAWK_API ImGuiLayer : public Layer {
	public:

		ImGuiLayer();
		~ImGuiLayer();

		void OnUpdate();
		void OnAttach();
		void OnDetach();

		void setupEvents(EventDispatcher&);

	private:

		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);
		bool OnKeyTyped(KeyTypedEvent& event);
		bool OnMouseMove(MouseMovedEvent& event);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

		float m_Time = 0.0f;


	};


}