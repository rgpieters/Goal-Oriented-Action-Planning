#ifndef _WRITE_APPLICATION_ACTION_H_
#define _WRITE_APPLIACTION_ACTION_H_

#include "GoapAction.h"

class WriteApplicationAction : GoapAction
{
public:
	WriteApplicationAction();
	WriteApplicationAction(const WriteApplicationAction&);
	~WriteApplicationAction();

	void Reset();
	bool IsDone();
	bool RequiresInRange();
	bool CheckPrecondition(BaseObject* object);
	bool PerformAction(BaseObject* object);

private:
	bool m_ApplicationWritten;
	float m_StartTime;
	float m_WorkDuration;
};

#endif