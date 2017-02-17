#include "GoapState.h"

GoapState::GoapState()
{

}

GoapState::GoapState(const GoapState&)
{

}

GoapState::~GoapState()
{

}

void GoapState::SetUp(GoapAgent* agent, void(GoapAgent::*Func)(BaseObject*))
{
	m_Agent = agent;
	UpdateFunc = Func;
}

void GoapState::Update(BaseObject* object)
{
	((m_Agent)->*(UpdateFunc))(object);
}