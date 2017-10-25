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
#include "GameManager.h"

USING_NS_CC;


//GameView
//主世界地图
class MainWorldScene : public Layer
{
public:
    static Scene* createScene();
    
    bool init();
    
    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
    CREATE_FUNC(MainWorldScene);

    void addMapFlag();
    void addRoad();
    void addNewMapFlag(int num);
    
    void onEnterTransitionDidFinish();
    Size m_winSize;
    Sprite* m_pbgSprite;
    //Road* m_proad;
    //Vector<MapFlag*> m_mapFlagVector;
    std::vector<Point> m_mapFlagPointVector;
    GameManager *m_pinstance;
};

#endif /* 
*/
