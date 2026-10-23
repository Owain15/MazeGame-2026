
#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace SeraphimEngine
{
	class Logging
	{
		public:
		
			static void Init();

			inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()   { return s_CoreLogger; }
			inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		private:
		
				
			static std::shared_ptr<spdlog::logger> s_CoreLogger;
			static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	// Core engine log macros
#define Seraphim_Log_CORE_TRACE(...)    ::SeraphimEngine::Logging::GetCoreLogger()->trace(__VA_ARGS__)
#define Seraphim_Log_CORE_INFO(...)     ::SeraphimEngine::Logging::GetCoreLogger()->info(__VA_ARGS__)
#define Seraphim_Log_CORE_WARN(...)     ::SeraphimEngine::Logging::GetCoreLogger()->warn(__VA_ARGS__)
#define Seraphim_Log_CORE_ERROR(...)    ::SeraphimEngine::Logging::GetCoreLogger()->error(__VA_ARGS__)
#define Seraphim_Log_CORE_CRITICAL(...) ::SeraphimEngine::Logging::GetCoreLogger()->critical(__VA_ARGS__)

// Client/Gameplay log macros
//#define Seraphim_Log_CLIENT_TRACE(...)         ::SeraphimEngine::Logging::GetClientLogger()->trace(__VA_ARGS__)
//#define Seraphim_Log_CLIENT_INFO(...)          ::SeraphimEngine::Logging::GetClientLogger()->info(__VA_ARGS__)
//#define Seraphim_Log_CLIENT_WARN(...)          ::SeraphimEngine::Logging::GetClientLogger()->warn(__VA_ARGS__)
//#define Seraphim_Log_CLIENT_ERROR(...)         ::SeraphimEngine::Logging::GetClientLogger()->error(__VA_ARGS__)

}