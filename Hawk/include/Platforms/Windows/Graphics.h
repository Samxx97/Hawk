#include "Renderer/GraphicsContext.h"
#include "Core/Core.h"

struct GLFWwindow;

namespace Hawk {

	/*OpenGL context*/
	class OpenGLContext : public GraphicsContext
	{

	public:

		OpenGLContext(GLFWwindow* window);

		void Init() override;
		void SwapBuffers() override;

	private:

		GLFWwindow* m_WindowHandle;
	};
	/*DirectX context
	.
	.
	.
	.
	.
	etc..
	*/

	template<typename ... Ts>
	GraphicsContext* GraphicsContext::CreateContext(Ts ... Args)
	{

		switch (RenderAPI::GraphicsAPI)
		{
		case RenderAPI::API::OpenGL: return new OpenGLContext(Args...);

		case RenderAPI::API::None: HK_CORE_ASSERT(false, "no behavior is implemented for RenderAPI:None yet");
			return nullptr;

		}

		HK_CORE_ASSERT(false, "No Rendering API is currently selected!");
		return nullptr;

	}

}
