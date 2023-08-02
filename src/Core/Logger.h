#pragma once
#include <memory>
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Hydra {

	enum class LogLevel
	{
		Trace, Info, Warning, Error
	};

	class Logger
	{
	public:
		Logger() = default;
		Logger(const std::string& name);

		void Init();
		void SetLevel(LogLevel level);

		// Getters and setters
		std::shared_ptr<spdlog::logger> GetLogger() { return m_Logger; }

		// Logging functions

		// Error
		template <typename... Args>
		void Error(Args&&... args) { m_Logger->error(std::forward<Args>(args)...); }

		// Warning
		template<typename... Args>
		void Warn(Args&&... args) { m_Logger->warn(std::forward<Args>(args)...); }

		// Info
		template<typename... Args>
		void Info(Args&&... args) { m_Logger->info(std::forward<Args>(args)...); }

		// Trace
		template<typename... Args>
		void Trace(Args&&... args) { m_Logger->trace(std::forward<Args>(args)...); }

	private:
		std::shared_ptr<spdlog::logger> m_Logger;
		std::string m_LoggerName;
	};
}