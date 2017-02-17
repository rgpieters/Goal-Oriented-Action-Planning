#ifndef _GOAP_STATE_H_
#define _GOAP_STATE_H_

class BaseObject;
class GoapAgent;

class GoapState
{
private:
	void(GoapAgent::*UpdateFunc)(BaseObject*);
	GoapAgent* m_Agent;
public:
	GoapState();
	GoapState(const GoapState&);
	~GoapState();

	void SetUp(GoapAgent* agent, void(GoapAgent::*Func)(BaseObject*));
	void Update(BaseObject* object);
};

#endif
