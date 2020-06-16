#ifndef _STATE_H_
#define _STATE_H_
#include"cocos2d.h"
#include"Component/Constant.h"
USING_NS_CC;

//加入了isImmutable判断
#define STATE_DATA(varType, varName, funName)\
protected: varType varName; \
public:inline varType get##funName(void) const { return varName; } \
inline void set##funName##By(varType deta){ if(isImmutable()){varName += deta;setStateInLim();} }\
inline void set##funName##To(varType num){ if(isImmutable()){varName = num;setStateInLim();} }

//State可以改成模板
<<<<<<< HEAD
class State:public Ref
=======
class State
>>>>>>> DOGGY_LEE
{
	STATE_DATA(INT32, _state, State);
	//getState,setStateBy,setStateTo

	STATE_DATA(INT32, _stateMax, StateMax);
	//getStateMax,setStateMaxBy,setStateMaxTo

	CC_SYNTHESIZE(bool, _immutable, Immutable);
	//状态锁定

	CC_SYNTHESIZE(float, _recoverGap, RecoverGap);
	//恢复间隔
public:
	bool isImmutable()
	{
		return _immutable;
	}

	//初始不可被伤害,1HP
	State(INT32 max = 1)
		:_stateMax(max), _state(max), _immutable(false), _recoverGap(0)
	{}

	State(ValueMap valueMap)
<<<<<<< HEAD
		:_stateMax(VALUE_AT(valueMap, "State", Int))
		, _state(_stateMax)
=======
		:_state(VALUE_AT(valueMap, "State", Int))
		, _stateMax(_state)
>>>>>>> DOGGY_LEE
		, _immutable(false)
		, _recoverGap(VALUE_AT(valueMap, "RecoverGap", Int))
	{}

	bool isEmpty()
	{
		if (_state == 0)
			return true;
		return false;
	}

	void setStateInLim()
		//set _state InLim
	{
		_state = _state > _stateMax ? _stateMax : _state;
		_state = _state < 0 ? 0 : _state;
	}

	float getPercentage()
	{
		return static_cast<float> (_state) / _stateMax;
	}

	//+1
<<<<<<< HEAD
	void update(float dt)
	{
		setStateBy(1);
=======
	void updateRecover(float dt)
	{
		if (_recoverGap)
			setStateBy(1);
>>>>>>> DOGGY_LEE
	}
};

#endif