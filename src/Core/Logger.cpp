#include "Logger.h"	
	

namespace Hydra {
	Logger::Logger(const std::string& name)
		: m_LoggerName(name)
	{

	}

	void Logger::Init()
	{
		m_Logger = spdlog::stdout_color_mt(m_LoggerName);
		// Pattern I made using spdlog's wiki
		m_Logger->set_pattern("%^[%n %l]: %v at [%H:%M:%S]%$");
	}

	void Logger::SetLevel(LogLevel level)
	{
		switch (level)
		{
		case (LogLevel::Trace):
			m_Logger->set_level(spdlog::level::trace);
			break;
		case (LogLevel::Info):
			m_Logger->set_level(spdlog::level::info);
			break;
		case (LogLevel::Warning):
			m_Logger->set_level(spdlog::level::warn);
			break;
		case (LogLevel::Error):
			m_Logger->set_level(spdlog::level::err);
			break;
		default:
			m_Logger->warn("Invalid log level set to logger");
			break;
		}
	}
}