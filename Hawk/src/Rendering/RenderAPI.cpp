#include "Rendering/RenderAPI.h"

namespace Hawk {
	//TODO make choice either dynamically or based on Platform or both
	RenderAPI::API RenderAPI::GraphicsAPI = RenderAPI::API::OpenGL;

}