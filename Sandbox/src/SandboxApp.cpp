#include "Hawk.h"

class Sandbox : public Hawk::Application {

public:

	Sandbox() = default;
	~Sandbox() = default;


};

Hawk::Application* Hawk::CreateApplication() {

	return new Sandbox();


}