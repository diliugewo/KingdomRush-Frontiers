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

    //m_mapFlagVector.p
    
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
{}

void MainWorldScene::addNewMapFlag(int num)
{}

void MainWorldScene::onEnterTransitionDidFinish()
{}
