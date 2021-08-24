#include "Hawk.h"


class ExampleLayer2 : public Hawk::Layer {

public:
	ExampleLayer2() :Layer("example1") {};

	void setupEvents(Hawk::EventDispatcher& dispatcher) override {

		Subscribe<Hawk::MouseMovedEvent>(dispatcher, BIND_EVENT_FN_DEFAULT(ExampleLayer2::onMouseMoveEvent));
	}

	bool onMouseMoveEvent(Hawk::MouseMovedEvent& event) {

		HK_INFO("layer2 reporting!!!!");

		return false;
	}

};

class Sandbox : public Hawk::Application {

public:

	Sandbox() {

		PushLayer(new ExampleLayer2());
		PushLayer(new Hawk::ImGuiLayer());

	}
	~Sandbox() = default;


};

Hawk::Application* Hawk::CreateApplication() {

	return new Sandbox();

}
