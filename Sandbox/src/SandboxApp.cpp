#include "Hawk.h"
#include <iostream>


class Sandbox : public Hawk::Application {

public:

	Sandbox() = default;
	~Sandbox() = default;


};

Hawk::Application* Hawk::CreateApplication() {

	Sandbox* sandbox = new Sandbox();
	return sandbox;


}