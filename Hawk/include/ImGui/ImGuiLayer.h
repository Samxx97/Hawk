#include "Layers/Layer.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"

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