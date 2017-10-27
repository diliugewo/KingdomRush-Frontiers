//
//  MainWorldScene.cpp
//  BattleScene
//
//  Created by Dee on 17/9/1.
//
//

#include "MainWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MapFlag.h"

//using namespace cocos2d::ui;
using namespace cocostudio::timeline;

Scene* MainWorldScene::createScene()
{
    Scene* scene = Scene::create();
    auto layer = MainWorldScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool MainWorldScene::init()
{
    if (!Layer::init())
        return false;
    
    auto rootNode = CSLoader::createNode("mainworld.csb");
    
    addChild(rootNode);
    
    m_pinstance = GameManager::getInstance();
    
    m_winSize = Director::getInstance()->getWinSize();
    //获取 世界地图
    m_pbgSprite = (Sprite*)rootNode->getChildByName("sp_MainWorld");

    m_mapFlagPointVector.push_back(Point(375,775));
    m_mapFlagPointVector.push_back(Point(495,735));
    m_mapFlagPointVector.push_back(Point(510,620));
    m_mapFlagPointVector.push_back(Point(370,575));
    m_mapFlagPointVector.push_back(Point(205,505));
    m_mapFlagPointVector.push_back(Point(455,305));
    m_mapFlagPointVector.push_back(Point(690,420));
    m_mapFlagPointVector.push_back(Point(855,254));
    m_mapFlagPointVector.push_back(Point(1020,340));
    m_mapFlagPointVector.push_back(Point(934,490));
    m_mapFlagPointVector.push_back(Point(830,560));
    m_mapFlagPointVector.push_back(Point(795,710));
    m_mapFlagPointVector.push_back(Point(910,770));
    m_mapFlagPointVector.push_back(Point(1015,770));
    addRoad();
    
    return true;
}

void MainWorldScene::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{}

void MainWorldScene::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{}

void MainWorldScene::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{}

void MainWorldScene::addMapFlag()
{
    int count = UserDefault::getInstance()->getIntegerForKey(m_pinstance->LevelNewOpen, 0);
    
    for (int i = 0; i <= count; i++)
    {
        auto mapflag = MapFlag::createWithLevel(i);
        //MapFlag->setpo
    }
        
}

void MainWorldScene::addRoad()
{
    m_proad = Road::create();
    m_proad->setPosition(Point(635, 500));
    addChild(m_proad);
}

void MainWorldScene::addNewMapFlag(int num)
{}

void MainWorldScene::onEnterTransitionDidFinish()
{
    //当前关卡
    int curLevel = UserDefault::getInstance()->getIntegerForKey(m_pinstance->LevelNewOpen);
    
}
