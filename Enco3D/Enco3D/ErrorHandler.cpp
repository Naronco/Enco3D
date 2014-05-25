#include "ErrorHandler.h"
#include "DebugLogger.h"
#include "Enco3DEngine.h"

Enco3D::Core::ErrorHandler::ErrorHandler(Enco3DEngine *engine)
{
	m_engine = engine;
}

void Enco3D::Core::ErrorHandler::logError(const std::string &errorText)
{
	DebugLogger::log(m_errorPrefix + " " + errorText);
}

bool Enco3D::Core::ErrorHandler::logErrorAndShutdown(const std::string &errorText, bool forceShutdown)
{
	if (m_engine == nullptr)
	{
		if (forceShutdown) exit(1);
		return false;
	}

	DebugLogger::log(m_errorPrefix + " " + errorText);

	Event quitEvent;
	quitEvent.type = EventType::Quit;

	m_engine->getWindow()->postQuitMessage();

	return true;
}

void Enco3D::Core::ErrorHandler::logErrorAndForceQuit(const std::string &errorText)
{
	DebugLogger::log(m_errorPrefix + " " + errorText);
	exit(1);
}