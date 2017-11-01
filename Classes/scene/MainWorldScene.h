//
//  MainWorldScene.h
//  kingdom rush
//
//  Created by Dee on 17/9/1.
//
//

#ifndef _MAINWORLDSCENE_H_
#define _MAINWORLDSCENE_H_

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameManager.h"
#include "Road.h"

USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

//GameView
//主世界地图
class MainWorldScene : public Layer
{
public:
    static Scene* createScene();
    
    bool init();
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    CREATE_FUNC(MainWorldScene);

    void addMapFlag();
    void addRoad();
    void addNewMapFlag(int num);
    
    void onEnterTransitionDidFinish();
    void btn_Settings(Ref* pSender, Widget::TouchEventType type);
    void btn_Music_CallBack(Ref* pSender,Widget::TouchEventType type);
    void btn_Effect_CallBack(Ref* pSender,Widget::TouchEventType type);
    void btn_Home_CallBack(Ref* pSender, Widget::TouchEventType type);

    
    Size m_winSize;
    Sprite* m_pbgSprite;
    Road* m_proad;
    //Vector<MapFlag*> m_mapFlagVector;
    std::vector<Point> m_mapFlagPointVector;
    GameManager *m_pinstance;
private:
    Button* btn_Setting;
    Button* btn_Music;
    Button* btn_Effect;
    Button* btn_Home;
};

#endif /* 
*/
