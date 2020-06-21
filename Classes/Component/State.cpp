#include"State.h"
USING_NS_CC;

 ProgressTimer * State::createBar(std::string file)
{
	auto state = Sprite::create(file);
	auto bar = ProgressTimer::create(state);
	bar->setType(ProgressTimer::Type::BAR);        //���ͣ���״
												   //���ҵ������Ѫ��
	bar->setMidpoint(Point(0, 0.5));     //����Ǵ����ҵĻ����ĳ�(1,0.5)����
	bar->setBarChangeRate(Point(1, 0));
	auto label=Label::createWithTTF(std::to_string(_state)+"\\"+std::to_string(_stateMax),"fonts/arial.ttf",20);
	label->setName("label");
	label->setPosition(bar->getContentSize()/2);
	bar->addChild(label);
	return bar;
}
