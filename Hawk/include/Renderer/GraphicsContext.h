#pragma once
#include "Renderer/RenderAPI.h"

namespace Hawk {

	class GraphicsContext {

	public:

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		template<typename ... Ts>
		static GraphicsContext* CreateContext(Ts ... Args);


	};


}