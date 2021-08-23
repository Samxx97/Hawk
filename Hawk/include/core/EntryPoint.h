#pragma once

int main(int argc, char** argv) {



	auto app = Hawk::CreateApplication();
	app->Run();

	delete app;

	return 0;

}