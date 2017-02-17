#ifndef _GOAP_PLANNER_H_
#define _GOAP_PLANNER_H_

#include <queue>
#include <unordered_map>
#include <set>
#include <list>

class GoapAction;
class BaseObject;

struct Node
{
	Node* parent;
	float weight;
	GoapAction* action;
	std::unordered_map<std::string, bool> state;

	Node(Node* _parent, float _weight, std::unordered_map<std::string, bool> _state, GoapAction* _action)
	{
		parent = _parent;
		weight = _weight;
		action = _action;
		state = _state;
	}
};

class GoapPlanner
{
public:
	GoapPlanner();
	GoapPlanner(const GoapPlanner&);
	~GoapPlanner();

	std::queue<GoapAction*> Plan(BaseObject* object, std::set<GoapAction*> possibleActions, std::unordered_map<std::string, bool> worldState, std::unordered_map<std::string, bool> goal);

private:
	bool BuildGraph(Node* parent, std::list<Node*> leaves, std::set<GoapAction*> possibleActions, std::unordered_map<std::string, bool> goal);
	std::set<GoapAction*> ActionSubset(std::set<GoapAction*> actions, GoapAction* removeMe);
	bool InState(std::unordered_map<std::string, bool> test, std::unordered_map<std::string, bool> state);
	std::unordered_map<std::string, bool> PopulateState(std::unordered_map<std::string, bool> currentState, std::unordered_map<std::string, bool> stateChange);
};



#endif