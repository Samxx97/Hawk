
namespace Hawk {

	class TimeStep {
	public:
		TimeStep() : m_Elapsed(0), m_LastFrame(0) {};

		void Tick();
		void Reset();

		operator float() const { return m_Elapsed; }

		float GetSeconds() const { return m_Elapsed; };
		float GetMilliSeconds() const { return m_Elapsed * 1000.0f; };

	private:
		float m_Elapsed, m_LastFrame;

	};

}