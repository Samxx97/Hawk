#pragma once


namespace Hawk {

	//TODO turn this into proper singleton class 
	class HAWK_API Input {

	public:
		inline static bool IsKeyPressed(int keycode) { return s_InputInstance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseKeyPressed(int button) { return s_InputInstance->IsMouseKeyPressedImpl(button); }


		inline static void setInput(Input* input) { s_InputInstance = input; }

	protected:

		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseKeyPressedImpl(int button) = 0;

	private:
		static Input* s_InputInstance;

	};


}


