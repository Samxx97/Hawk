#include "Layers/LayerStack.h"

namespace Hawk {

	LayerStack::LayerStack() {
		m_LayerInsert = 0;

	};

	LayerStack::~LayerStack() {

		for (Layer* layer : m_Layers) {
			delete layer;
		}
	}

	void LayerStack::pushLayer(Layer* layer) {

		m_Layers.emplace(begin() + m_LayerInsert, layer);
		m_LayerInsert++;
	}

	void LayerStack::pushOverlay(Layer* layer) {
		m_Layers.emplace_back(layer);
	}

	/*TOFIX : Possible Memory Leak when Popping a Layer and also  possible Invalidation of
			m_LayerInsert because of the erasing of elements

	 to avoid Memory Leak, the Popping of a layer has to be temperory
			and should later be pushed back in to be deleted by the destructer
	*/
	void LayerStack::popLayer(Layer* layer) {

		auto iter = std::find(begin(), end(), layer);
		if (iter != end()) {
			m_Layers.erase(iter);
			m_LayerInsert--;
		}
	}

	void LayerStack::popOverlay(Layer* overlay) {

		auto iter = std::find(begin(), end(), overlay);

		if (iter != end()) {
			m_Layers.erase(iter);
		}

	}

	void LayerStack::SetupEvents(EventDispatcher& dispatcher) {

		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it) {
			(*it)->setupEvents(dispatcher);
		}
	}

}