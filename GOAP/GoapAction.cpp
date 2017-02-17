#include "GoapAction.h"

GoapAction::GoapAction()
{
	m_Target = nullptr;
	//m_Preconditions = new std::unordered_map<std::string, bool>();
}

GoapAction::GoapAction(const GoapAction&)
{

}

GoapAction::~GoapAction()
{
	if (m_Target)
	{
		delete m_Target;
		m_Target = nullptr;
	}
}

void GoapAction::GoapAction::doReset()
{

}

bool GoapAction::IsInRange()
{
	return m_InRange;
}

void GoapAction::SetIsInRange(bool inRange)
{
	m_InRange = inRange;
}

void GoapAction::AddPrecondition(std::string key, bool value)
{
	m_Preconditions.insert(m_Preconditions.end(), std::pair<std::string, bool>(key, value));
}

void GoapAction::RemovePrecondition(std::string key)
{
	m_Preconditions.erase(key);
}

void GoapAction::AddEffect(std::string key, bool value)
{
	m_Effects.insert(m_Effects.end(), std::pair<std::string, bool>(key, value));
}

void GoapAction::RemoveEffect(std::string key)
{
	m_Effects.erase(key);
}

std::unordered_map<std::string, bool> GoapAction::Preconditions()
{
	return m_Preconditions;
}
std::unordered_map<std::string, bool> GoapAction::Effects()
{
	return m_Effects;
}