#pragma once

#include "core/Core.h"
#include "core/log.h"

namespace Hawk {


	enum class EventType {

		None = 0,
		WindowClose, WindowResize, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		All

	};



	enum class EventCategory {

		None = 0,
		Application = BIT(0),
		Input = BIT(1),
		Keyboard = BIT(2),
		Mouse = BIT(3),
		MouseButton = BIT(4)

	};

	template<typename T>
	using EventCallback = std::function<bool(T&)>;

	constexpr std::size_t TOTAL_EVENT_COUNT = static_cast<std::size_t>(EventType::All);


	inline int operator &(EventCategory a, EventCategory b) {

		return static_cast<int>(a) & static_cast<int>(b);
	}

	inline EventCategory operator |(EventCategory a, EventCategory b) {

		return static_cast<EventCategory> (static_cast<int>(a) | static_cast<int>(b));
	}




	class Event {

		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual EventCategory GetCategory() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string toString() const { return GetName(); };


		inline bool isInCategory(EventCategory category) { return category & GetCategory(); }

	protected:

		bool m_handled = false;
	};


#define EVENT_TYPE(type) static EventType GetStaticType() { return EventType::##type; } \
						 virtual EventType GetEventType() const override { return GetStaticType(); } \
						 virtual const char* GetName() const override { return #type; }


#define EVENT_CATEGORY(category) \
						virtual EventCategory GetCategory() const override { return category; };




	class EventDispatcher {

	public:

		template<typename E>
		void unSubscribe(int handlerIndex) {

			auto& callbacks = m_GlobalLayer.at<E>();
			callbacks.erase(callbacks.begin() + handlerIndex);

		}

		template<typename E>
		int	 Subscribe(EventCallback<E> callback) {

			auto& callbacks = m_GlobalLayer.at<E>();
			callbacks.push_back(CallbackWrapper<E>(callback));

			return (callbacks.size() - 1);

		}

		template<typename E>
		void Post(E& event) {


			//global callbacks
			for (auto& callback : m_GlobalLayer.at<E>()) {

				callback(event);
			}

			//layered callbacks
			for (auto layer : m_EventLayers) {

				if (!layer.m_Disabled) {

					event.m_handled = layer.at<E>()(event);
					if (event.m_handled)
						break;

				}
			}


		}


		void CreateEventLayer(int& layerIndex) {

			EventLayer<EventCallback<Event>> layer;
			layer.m_table.fill([](Event& event) {return false; });

			m_EventLayers.push_back(layer);
			layerIndex = m_EventLayers.size() - 1;
		}



		template<typename E>
		void SubscribeToLayer(EventCallback<E> callback, int layerIndex) {

			auto& layer = m_EventLayers[layerIndex];
			layer.at<E>() = CallbackWrapper<E>(callback);

		}

		void DisableLayer(int layerIndex) {

			m_EventLayers[layerIndex].m_Disabled = true;
		}

	private:


		template<typename T>
		class CallbackWrapper {

		public:
			CallbackWrapper(EventCallback<T> callback) :
				m_callback(callback) {};

			bool operator()(Event& event) {
				return m_callback(static_cast<T&>(event));
			}

		private:
			EventCallback<T> m_callback;

		};

		template<typename T>
		struct EventLayer {

		public:


			bool m_Disabled = false;
			std::array<T, TOTAL_EVENT_COUNT> m_table;

			template<typename E>
			T& at() { return m_table[static_cast<std::size_t>(E::GetStaticType())]; };

		};

		EventLayer<std::vector<EventCallback<Event> >> m_GlobalLayer;
		std::vector<EventLayer<EventCallback<Event> >> m_EventLayers;


	};


}