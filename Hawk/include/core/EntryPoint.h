
namespace Hawk {

	extern Application* CreateApplication();


}

int main(int argc, char** argv) {


	auto app = Hawk::CreateApplication();
	app->Run();
	delete app;


}