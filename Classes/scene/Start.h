#ifndef _START_H_
#define _START_H_

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "SimpleAudioEngine.h" 
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace CocosDenshion;


class Start : public Layer
{
	Size visibleSize;
	Node* nodeSavelot;
	bool Saveshow;
	Button* btn_Exit;
	Button* btn_Music;
	Button* btn_Effect;
	Button* btn_Close;

public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Start);


	void img_M_E_Down();
	void img_M_E_Up();
	void Savelot_Down(Ref* pSender,Widget::TouchEventType type);
	void btn_Music_CallBack(Ref* pSender,Widget::TouchEventType type);
	void btn_Effect_CallBack(Ref* pSender,Widget::TouchEventType type);
	void btn_Start_CallBack(Ref* pSender,Widget::TouchEventType type);
};

#endif 