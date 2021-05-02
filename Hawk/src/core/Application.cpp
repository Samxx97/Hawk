#include "core/Application.h"
#include "core/log.h"

namespace Hawk {

	Application::Application() = default;

	Application::~Application() = default;


	void Application::Run() {

		while (true);
	}

	void Application::Init() {


		Log::init();
		HK_CORE_TRACE("Initialization started!");


	}

}