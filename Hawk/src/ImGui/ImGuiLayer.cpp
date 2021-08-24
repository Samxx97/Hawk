#include "ImGui/ImGuiLayer.h"

#include "imgui.h"
#include "Platforms/Opengl/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"
#include "Core/Application.h"



namespace Hawk {

	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{


	}


	ImGuiLayer::~ImGuiLayer()
	{



	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		//ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//TEMPORARY Use Hawk Key codes in future
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnUpdate()
	{


		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetInstance();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();


		ImGui::Text("Test paragraph 2:");

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


	}

	void ImGuiLayer::setupEvents(EventDispatcher& dispatcher)
	{
		Subscribe<KeyPressedEvent>(dispatcher, BIND_EVENT_FN_DEFAULT(ImGuiLayer::OnKeyPressed));
		Subscribe<KeyReleasedEvent>(dispatcher, BIND_EVENT_FN_DEFAULT(ImGuiLayer::OnKeyReleased));
		Subscribe<MouseMovedEvent>(dispatcher, BIND_EVENT_FN_DEFAULT(ImGuiLayer::OnMouseMove));
		Subscribe<MouseButtonPressedEvent>(dispatcher, BIND_EVENT_FN_DEFAULT(ImGuiLayer::OnMouseButtonPressed));
		Subscribe<MouseButtonReleasedEvent>(dispatcher, BIND_EVENT_FN_DEFAULT(ImGuiLayer::OnMouseButtonReleased));
		Subscribe<WindowResizeEvent>(dispatcher, BIND_EVENT_FN_DEFAULT(ImGuiLayer::OnWindowResize));
		Subscribe<KeyTypedEvent>(dispatcher, BIND_EVENT_FN_DEFAULT(ImGuiLayer::OnKeyTyped));
	}

	bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];


		return false;
	}
	bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[event.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMove(MouseMovedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.GetXpos(), event.GetYpos());

		return false;
	}

	bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[event.GetButton()] = false;
		return false;

	}

	bool ImGuiLayer::OnWindowResize(WindowResizeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());

		return false;

	}

	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(event.GetKeyCode());

		return false;
	}

}