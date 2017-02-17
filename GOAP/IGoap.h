#ifndef _IGOAP_H_
#define _IGOAP_H_

#include <unordered_map>
#include <string>
#include <queue>

class GoapAction;

class IGoap
{
public:
	virtual std::unordered_map<std::string, bool> GetWorldState() = 0;
	virtual std::unordered_map<std::string, bool> CreateGoalState() = 0;
	virtual void PlanFailed(std::unordered_map<std::string, bool> failedGoal) = 0;
	virtual void PlanFound(std::unordered_map<std::string, bool> goal, std::queue<GoapAction*> actions) = 0;
	virtual void ActionsFinished() = 0;
	virtual void PlanAborted(GoapAction* aborter) = 0;
	virtual bool MoveAgent(GoapAction* afterMoveAction) = 0;
};

#endif