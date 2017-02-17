#ifndef _GOAP_ACTION_H_
#define _GOAP_ACTION_H_

#include <unordered_map>
#include <string>

class BaseObject;

class GoapAction
{
private:
	std::unordered_map<std::string, bool> m_Preconditions;
	std::unordered_map<std::string, bool> m_Effects;
	bool m_InRange = false;
	float m_Cost = 1.0f;
	BaseObject* m_Target;

public:
	GoapAction();
	GoapAction(const GoapAction&);
	~GoapAction();

	virtual void Reset() = 0;
	virtual bool IsDone() = 0;
	virtual bool CheckPrecondition(BaseObject* agent) = 0;
	virtual bool PerformAction(BaseObject* agent) = 0;
	virtual bool RequiresInRange() = 0;

	void doReset();
	bool IsInRange();
	void SetIsInRange(bool inRange);
	void AddPrecondition(std::string key, bool value);
	void RemovePrecondition(std::string key);
	void AddEffect(std::string key, bool value);
	void RemoveEffect(std::string key);
	std::unordered_map<std::string, bool> Preconditions();
	std::unordered_map<std::string, bool> Effects();

	BaseObject* Target() { return m_Target; }
	float Cost() { return m_Cost; }
};

#endif
