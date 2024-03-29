#include "Hawk.h"

class Sandbox2D : public Hawk::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Hawk::TimeStep ts) override;
	void OnImGuiRender(ImGuiContext* context)  override;
	void setupEvents(Hawk::EventDispatcher& dispatcher) override;

	bool OnMouseScroll(Hawk::MouseScrolledEvent& event);

private:
	Hawk::OrthoGraphicCameraController m_CameraController;
	Hawk::Ref<Hawk::Texture2D> m_Texture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};