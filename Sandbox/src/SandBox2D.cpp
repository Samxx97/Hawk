#include "SandBox2D.h"

#include "glm/ext.hpp" 
#include "imgui.h"

#include "Renderer/Opengl/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{

}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Hawk::TimeStep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Hawk::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Hawk::RenderCommand::Clear();

	Hawk::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Hawk::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Hawk::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender(ImGuiContext* context)
{
	ImGui::SetCurrentContext(context);

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::setupEvents(Hawk::EventDispatcher& dispatcher) {

	Subscribe<Hawk::MouseScrolledEvent>(dispatcher, BIND_EVENT_FN_DEFAULT(Sandbox2D::OnMouseScroll));
}

bool Sandbox2D::OnMouseScroll(Hawk::MouseScrolledEvent& event) {

	m_CameraController.OnMouseScroll(event);
	return false;
}
