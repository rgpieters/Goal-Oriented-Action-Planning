#ifndef _GOAP_STATE_H_
#define _GOAP_STATE_H_

class BaseObject;
class GoapAgent;

typedef int(GoapAgent::*FUNC_PTR)(BaseObject*);

class GoapState
{
public:
	GoapState();
	GoapState(FUNC_PTR Func, GoapAgent* agent);
	GoapState(const GoapState&);
	~GoapState();

	void Update(BaseObject* object);

private:
	FUNC_PTR UpdateFunc;
	GoapAgent* m_Agent;
};

#endif
