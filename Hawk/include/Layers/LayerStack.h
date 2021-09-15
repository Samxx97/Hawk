#include "Layers/Layer.h"

namespace Hawk {

	class HAWK_API LayerStack {
	public:

		using LayerIterator = std::vector<Layer*>::iterator;

		LayerStack();
		~LayerStack();


		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		void SetupEvents(EventDispatcher& dispatcher);

		LayerIterator begin() { return m_Layers.begin(); };
		LayerIterator end() { return m_Layers.end(); };


	private:

		std::vector<Layer*> m_Layers;
		std::size_t m_LayerInsert;
	};


}