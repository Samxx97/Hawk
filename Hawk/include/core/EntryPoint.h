
namespace Hawk {

	extern Application* CreateApplication();


}


int main(int argc, char** argv) {



	auto app = Hawk::CreateApplication();
	app->Init();

	HK_INFO("Program starting !!");
	HK_CORE_INFO("program starting!!");

	app->Run();
	delete app;


}