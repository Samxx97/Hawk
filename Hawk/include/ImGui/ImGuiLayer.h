#include "Layers/Layer.h"

struct ImGuiContext;

namespace Hawk {


	class HAWK_API ImGuiLayer : public Layer {
	public:

		ImGuiLayer() : Layer("ImGuiLayer") {};
		~ImGuiLayer() {};

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender(ImGuiContext* context) override;

		void Begin();
		void End();

		void setupEvents(EventDispatcher&);

		ImGuiContext* m_context;

	private:

		float m_Time = 0.0f;


	};


}