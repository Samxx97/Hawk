#pragma once
#include "Events/Event.h"
#include "Core/TimeStep.h"

struct ImGuiContext;


namespace Hawk {


	class HAWK_API Layer {

	public:
		Layer(const std::string& name = "Layer") :m_DebugName(name) {};
		virtual ~Layer() {};


		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(TimeStep ts) {};
		virtual void OnImGuiRender(ImGuiContext* context) {};

		virtual void setupEvents(EventDispatcher& dispatcher) = 0;

		void disableEvents() {

			if (m_EventData)
				m_EventData->Disable();

		}

		inline const std::string& GetName()const { return m_DebugName; };

	protected:

		std::string m_DebugName;


		struct EventLayerData {
		public:

			EventLayerData(int index, EventDispatcher& dispatcher) :m_LayerIndex(index), m_Dispatcher(dispatcher) {};

			void Disable() {
				m_Dispatcher.DisableLayer(m_LayerIndex);
			}
			void Enable() {

			}

			int m_LayerIndex;
			EventDispatcher& m_Dispatcher;

		};

		template<class T>
		void Subscribe(EventDispatcher& dispatcher, EventCallback<T> callback) {

			if (m_EventData) {

				dispatcher.SubscribeToLayer<T>(callback, m_EventData->m_LayerIndex);

			}
			else {

				int layerindex;
				dispatcher.CreateEventLayer(layerindex);
				m_EventData = std::make_unique<EventLayerData>(layerindex, dispatcher);
				dispatcher.SubscribeToLayer<T>(callback, m_EventData->m_LayerIndex);

			}

		}

		std::unique_ptr<EventLayerData> m_EventData;
	};


}