#include "WriteApplicationAction.h"

WriteApplicationAction::WriteApplicationAction()
{
	AddPrecondition("applicationWritten", false);
	AddEffect("applicationWritten", true);
	m_Cost = 5.0f;

	Reset();
}

WriteApplicationAction::WriteApplicationAction(const WriteApplicationAction&)
{

}

WriteApplicationAction::~WriteApplicationAction()
{

}

void WriteApplicationAction::Reset()
{
	doReset();

	m_ApplicationWritten = false;
	m_StartTime = 0.0f;
	m_WorkDuration = 50000.0f;
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
	if (m_StartTime == 0.0f)
	{
		m_StartTime = 1.0f;
	}

	m_StartTime++;

	if(m_StartTime > m_WorkDuration)
	{
		m_ApplicationWritten = true;
	}

	return true;
}