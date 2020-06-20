#ifndef _STATE_H_
#define _STATE_H_
#include"cocos2d.h"
#include"Component/Constant.h"
USING_NS_CC;

//������isImmutable�ж�
#define STATE_DATA(varType, varName, funName)\
protected: varType varName; \
public:inline varType get##funName(void) const { return varName; } \
inline void set##funName##By(varType deta){ if(!isImmutable()){varName += deta;setStateInLim();} }\
inline void set##funName##To(varType num){ if(!isImmutable()){varName = num;setStateInLim();} }

//State���Ըĳ�ģ��
class State
{
	CC_SYNTHESIZE(INT32, _state, State);
	//getState,setStateBy,setStateTo

	CC_SYNTHESIZE(INT32, _stateMax, StateMax);
	//getStateMax,setStateMaxBy,setStateMaxTo

	CC_SYNTHESIZE(bool, _immutable, Immutable);
	//״̬����

	CC_SYNTHESIZE(float, _recoverGap, RecoverGap);
	//�ָ����
public:
	bool isImmutable()
	{
		return _immutable;
	}

	void setStateBy(int deta)
	{
		if (!isImmutable())
		{
			_state += deta;
			setStateInLim();
		}
	}

	void setStateTo(int num)
	{
		if (!isImmutable())
		{
			_state = num;
			setStateInLim();
		}
	}

	//��ʼ���ɱ��˺�,1HP
	State(INT32 max = 1)
		:_stateMax(max), _state(max), _immutable(false), _recoverGap(0)
	{}

	State(ValueMap valueMap)
		:_state(VALUE_AT(valueMap, "State", Int))
		, _stateMax(_state)
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
		return 100 * static_cast<float> (_state) / _stateMax;
	}

	//+1
	void updateRecover(float dt)
	{
		if (_recoverGap)
			setStateBy(1);
	}
	ProgressTimer* createBar(std::string file);
};

#endif