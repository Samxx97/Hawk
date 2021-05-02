#include <memory>

#include "hawk_exports.h"
#include "spdlog/spdlog.h"

namespace Hawk {


	class HAWK_API Log {

	public:

		static void init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };

	private:


		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};



}

#ifdef HAWK_BUILD_DLL

//core log macro
#define HK_CORE_TRACE(...)     Hawk::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HK_CORE_INFO(...)      Hawk::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HK_CORE_WARN(...)      Hawk::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HK_CORE_ERROR(...)     Hawk::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HK_CORE_CRITICAL(...)  Hawk::Log::GetCoreLogger()->critical(__VA_ARGS__)

#endif

//client log macro
#define HK_TRACE(...)         Hawk::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HK_INFO(...)          Hawk::Log::GetClientLogger()->info(__VA_ARGS__)
#define HK_WARN(...)          Hawk::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HK_ERROR(...)         Hawk::Log::GetClientLogger()->error(__VA_ARGS__)
#define HK_CRITICAL(...)      Hawk::Log::GetClientLogger()->critical(__VA_ARGS__)


