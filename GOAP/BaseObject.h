#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_

#include "IGoap.h"
#include <vector>
#include <unordered_map>
#include <queue>

class GoapAction;
class GoapAgent;

class BaseObject : IGoap
{
public:
	BaseObject();
	BaseObject(const BaseObject&);
	~BaseObject();

	GoapAgent* m_GoapAgent;

	std::vector<GoapAction*> GetActions() { return m_Actions; }
	virtual std::unordered_map<std::string, bool> CreateGoalState() = 0;
	void Update();
	std::unordered_map<std::string, bool> GetWorldState();
	void PlanFailed(std::unordered_map<std::string, bool> failedGoal);
	void PlanFound(std::unordered_map<std::string, bool> goal, std::queue<GoapAction*> actions);
	void ActionsFinished();
	void PlanAborted(GoapAction* aborter);
	bool MoveAgent(GoapAction* nextAction);
private:
	std::vector<GoapAction*> m_Actions;
};

#endif