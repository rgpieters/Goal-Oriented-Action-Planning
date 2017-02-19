#include "WriteApplicationAction.h"
#include <time.h>

WriteApplicationAction::WriteApplicationAction()
{
	AddPrecondition("hasKnowledge", true);
	AddEffect("applicationWritten", true);
}

WriteApplicationAction::WriteApplicationAction(const WriteApplicationAction&)
{

}

WriteApplicationAction::~WriteApplicationAction()
{

}

void WriteApplicationAction::Reset()
{
	m_ApplicationWritten = false;
	m_StartTime = 0.0f;
	m_WorkDuration = 50.0f;
}

bool WriteApplicationAction::IsDone()
{
	return m_ApplicationWritten;
}

bool WriteApplicationAction::RequiresInRange()
{
	return false;
}

bool WriteApplicationAction::CheckPrecondition(BaseObject* object)
{
	int x = 10;
	return true;
}

bool WriteApplicationAction::PerformAction(BaseObject* object)
{
	time_t timer;

	if (m_StartTime == 0.0f)
	{
		m_StartTime = 1.0f;
	}

	if(m_StartTime > m_WorkDuration)
	{
		m_ApplicationWritten = true;
	}

	return true;
}