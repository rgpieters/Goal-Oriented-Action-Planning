#include "GoapState.h"
#include "GoapAgent.h"

GoapState::GoapState()
{

}

GoapState::GoapState(FUNC_PTR Func, GoapAgent* agent)
{
	UpdateFunc = Func;
	m_Agent = agent;
}

GoapState::GoapState(const GoapState&)
{

}

GoapState::~GoapState()
{

}

void GoapState::Update(BaseObject* object)
{
	(m_Agent->*UpdateFunc)(object);
}