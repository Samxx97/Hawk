
namespace Hawk {

	using m_RenderId = uint32_t;

	class RenderAPI {

	public:

		enum API {
			None = 0,
			OpenGL = 1
		};


		static API GraphicsAPI;

	};




}