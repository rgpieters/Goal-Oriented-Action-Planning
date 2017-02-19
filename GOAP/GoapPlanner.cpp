#include "GoapPlanner.h"
#include "GoapAction.h"
#include "BaseObject.h"

GoapPlanner::GoapPlanner()
{

}

GoapPlanner::GoapPlanner(const GoapPlanner&)
{

}

GoapPlanner::~GoapPlanner()
{

}

std::queue<GoapAction*> GoapPlanner::Plan(BaseObject* object, std::set<GoapAction*> possibleActions, std::unordered_map<std::string, bool> worldState, std::unordered_map<std::string, bool> goal)
{
	std::set<GoapAction*>::iterator iter;
	for (iter = possibleActions.begin(); iter != possibleActions.end(); iter++)
	{
		((GoapAction*)*iter)->Reset();
	}

	std::set< GoapAction*> usableActions;
	for (iter = possibleActions.begin(); iter != possibleActions.end(); iter++)
	{
		if (((GoapAction*)*iter)->CheckPrecondition(object))
		{
			usableActions.insert(usableActions.begin(), ((GoapAction*)*iter));
		}
	}

	std::list<Node*> leaves;
	Node* start = new Node(nullptr, 0, worldState, nullptr);
	bool success = BuildGraph(start, leaves, usableActions, goal);

	if (!success)
	{
		return std::queue<GoapAction*>();
	}

	Node* cheapest = nullptr;

	std::list<Node*>::iterator listIter;
	for (listIter = leaves.begin(); listIter != leaves.end(); listIter++)
	{
		if (cheapest == nullptr)
		{
			cheapest = ((Node*)*listIter);
		}
		else
		{
			if (((Node*)*listIter)->weight < cheapest->weight)
			{
				cheapest = ((Node*)*listIter);
			}
		}
	}

	std::list<GoapAction*> result;
	Node* n = cheapest;
	while (n != nullptr)
	{
		if (n->action != nullptr)
		{
			result.insert(result.end(), n->action);
		}
		n = n->parent;
	}

	std::queue<GoapAction*> endResult;
	std::list<GoapAction*>::iterator endResultIter;
	for (endResultIter = result.begin(); endResultIter != result.end(); endResultIter++)
	{
		endResult.push(((GoapAction*)*endResultIter));
	}

	delete start;
	start = nullptr;

	return endResult;
}

bool GoapPlanner::BuildGraph(Node* parent, std::list<Node*>& leaves, std::set<GoapAction*> possibleActions, std::unordered_map<std::string, bool> goal)
{
	bool foundOne = false;

	std::set<GoapAction*>::iterator iter;
	for (iter = possibleActions.begin(); iter != possibleActions.end(); iter++)
	{
		if (InState(((GoapAction*)*iter)->Preconditions(), parent->state))
		{
			std::unordered_map<std::string, bool> currentState = PopulateState(parent->state, ((GoapAction*)*iter)->Effects());
			Node* tempNode = new Node(parent, parent->weight + ((GoapAction*)*iter)->Cost(), currentState, ((GoapAction*)*iter));

			if (InState(goal, currentState))
			{
				leaves.insert(leaves.end(), tempNode);
				foundOne = true;
			}
			else
			{
				std::set<GoapAction*> subset = ActionSubset(possibleActions, ((GoapAction*)*iter));
				bool found = BuildGraph(tempNode, leaves, subset, goal);
				if (found)
				{
					foundOne = true;
				}
			}
		}
	}

	return foundOne;
}

std::set<GoapAction*> GoapPlanner::ActionSubset(std::set<GoapAction*> actions, GoapAction* removeMe)
{
	std::set<GoapAction*> subset;

	std::set<GoapAction*>::iterator iter;
	for (iter = actions.begin(); iter != actions.end(); iter++)
	{
		if(*iter != removeMe)
		{
			subset.insert(subset.end(), iter);
		}
	}

	return subset;
}

bool GoapPlanner::InState(std::unordered_map<std::string, bool> test, std::unordered_map<std::string, bool> state)
{
	bool allMatch = true;

	std::unordered_map<std::string, bool>::iterator outerIter;
	for (outerIter = test.begin(); outerIter != test.end(); outerIter++)
	{
		bool match = false;

		std::unordered_map<std::string, bool>::iterator innerIter;
		for (innerIter = state.begin(); innerIter != state.end(); innerIter++)
		{
			if (*innerIter == *outerIter)
			{
				match = true;
				break;
			}
		}

		if (!match)
		{
			allMatch = false;
		}
	}

	return allMatch;
}

std::unordered_map<std::string, bool> GoapPlanner::PopulateState(std::unordered_map<std::string, bool> currentState, std::unordered_map<std::string, bool> stateChange)
{
	std::unordered_map<std::string, bool> state;

	std::unordered_map<std::string, bool>::iterator outerIter;
	for (outerIter = currentState.begin(); outerIter != currentState.end(); outerIter++)
	{
		state.insert(state.end(), *outerIter);
	}

	std::unordered_map<std::string, bool>::iterator innerIter;
	for (outerIter = stateChange.begin(); outerIter != stateChange.end(); outerIter++)
	{
		bool exists = false;

		for (innerIter = state.begin(); innerIter != state.end(); innerIter++)
		{
			if (innerIter->first == innerIter->first)
			{
				exists = true;
				break;
			}
		}

		if (exists)
		{
			state.erase(outerIter->first);
			state.insert(state.end(), *outerIter);
		}
		else
		{
			state.insert(state.end(), *outerIter);
		}
	}

	return state;
}