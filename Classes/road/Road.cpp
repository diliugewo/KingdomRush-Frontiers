//
//  Road.cpp
//  BattleScene
//
//  Created by Dee on 17/10/27.
//
//

#include <stdio.h>
#include "Road.h"
#include "GameManager.h"

Road::Road()
{}

Road::~Road()
{}

bool Road::init()
{
    if (!Sprite::init())return false;
    
    auto road_0 = Sprite::createWithSpriteFrameName("mapRoad_1to1_5_0007.png");
    auto road_1 = Sprite::createWithSpriteFrameName("mapRoad_1_5_to2_0013.png");
    auto road_2 = Sprite::createWithSpriteFrameName("mapRoad_2to3_0010.png");
    auto road_3 = Sprite::createWithSpriteFrameName("mapRoad_3to4_0019.png");
    auto road_4 = Sprite::createWithSpriteFrameName("mapRoad_4to5_0136.png");
    auto road_5 = Sprite::createWithSpriteFrameName("mapRoad_5to6_0025.png");
    auto road_6 = Sprite::createWithSpriteFrameName("mapRoad_6to7_0025.png");
    auto road_7 = Sprite::createWithSpriteFrameName("mapRoad_7to8_0022.png");
    auto road_8 = Sprite::createWithSpriteFrameName("mapRoad_8to9_0022.png");
    auto road_9 = Sprite::createWithSpriteFrameName("mapRoad_9to10_0010.png");
    auto road_10 = Sprite::createWithSpriteFrameName("mapRoad_10to11_0013.png");
    auto road_11 = Sprite::createWithSpriteFrameName("mapRoad_11to12_0010.png");
    auto road_12 = Sprite::createWithSpriteFrameName("mapRoad_12to13_0007.png");
    auto road_13 = Sprite::createWithSpriteFrameName("mapRoad_13to14_0010.png");
    
    roadVector.pushBack(road_0);
    roadVector.pushBack(road_1);
    roadVector.pushBack(road_2);
    roadVector.pushBack(road_3);
    roadVector.pushBack(road_4);
    roadVector.pushBack(road_5);
    roadVector.pushBack(road_6);
    roadVector.pushBack(road_7);
    roadVector.pushBack(road_8);
    roadVector.pushBack(road_9);
    roadVector.pushBack(road_10);
    roadVector.pushBack(road_11);
    roadVector.pushBack(road_12);
    roadVector.pushBack(road_13);
    
    addChild(road_0);
    addChild(road_1);
    addChild(road_2);
    addChild(road_3);
    addChild(road_4);
    addChild(road_5);
    addChild(road_6);
    addChild(road_7);
    addChild(road_8);
    addChild(road_9);
    addChild(road_10);
    addChild(road_11);
    addChild(road_12);
    addChild(road_13);
    
    setRoadReady();
    initRoadAni();
    return true;
}

void Road::buildRoadAni(int num)
{
    roadVector.at(num)->setVisible(true);
    roadVector.at(num)->runAction(Animate::create(roadAniVector.at(num)));
}

void Road::setRoadReady()
{
    int curLevel = UserDefault::getInstance()->getIntegerForKey(GameManager::getInstance()->LevelDownNum);
    if (curLevel != 0)
    {
        for (int i = 0; i < curLevel; i++)
            roadVector.at(i)->setVisible(true);
    }
}

void Road::initRoadAni()
{
    SpriteFrame* frame0 = NULL;
    Vector<SpriteFrame*> vecFrame0;
    for (int i = 1; i <= 7; i += 3)
    {
        frame0 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_1to1_5_00%02d.png",i).c_str());
        if (frame0 != NULL)
            vecFrame0.pushBack(frame0);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame0, 0.1f));
 
    SpriteFrame* frame1 = NULL;
    Vector<SpriteFrame*> vecFrame1;
    for (int i = 1; i <= 13; i += 3)
    {
        frame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_1_5_to2_00%02d.png",i).c_str());
        if (frame1 != NULL)
            vecFrame1.pushBack(frame1);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame1, 0.1f));
    
    SpriteFrame* frame2 = NULL;
    Vector<SpriteFrame*> vecFrame2;
    for (int i = 1; i <= 10; i += 3)
    {
        frame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_2to3_00%02d.png",i).c_str());
        if (frame2 != NULL)
            vecFrame2.pushBack(frame2);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame2, 0.1f));
    
    SpriteFrame* frame3 = NULL;
    Vector<SpriteFrame*> vecFrame3;
    for (int i = 1; i <= 19; i += 3)
    {
        frame3 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_3to4_00%02d.png",i).c_str());
        if (frame3 != NULL)
            vecFrame3.pushBack(frame3);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame3, 0.1f));
    
    //!!!
    SpriteFrame* frame4 = NULL;
    Vector<SpriteFrame*> vecFrame4;
    frame4 = SpriteFrameCache::getInstance()->getSpriteFrameByName("mapRoad_4to5_0001.png");
    if (frame4 != NULL)
        vecFrame4.pushBack(frame4);
    for (int i = 10; i <= 136; i += 7)
    {
        frame4 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_4to5_00%02d.png",i).c_str());
        if (frame4 != NULL)
            vecFrame4.pushBack(frame4);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame4, 0.1f));
    
    SpriteFrame* frame5 = NULL;
    Vector<SpriteFrame*> vecFrame5;
    for (int i = 1; i <= 25; i += 3)
    {
        frame5 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_5to6_00%02d.png",i).c_str());
        if (frame5 != NULL)
            vecFrame5.pushBack(frame5);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame5, 0.1f));
    
    SpriteFrame* frame6 = NULL;
    Vector<SpriteFrame*> vecFrame6;
    for (int i = 1; i <= 25; i += 3)
    {
        frame6 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_6to7_00%02d.png",i).c_str());
        if (frame6 != NULL)
            vecFrame6.pushBack(frame6);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame6, 0.1f));
    
    SpriteFrame* frame7 = NULL;
    Vector<SpriteFrame*> vecFrame7;
    for (int i = 1; i <= 25; i += 3)
    {
        frame7 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_7to8_00%02d.png",i).c_str());
        if (frame7 != NULL)
            vecFrame7.pushBack(frame7);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame7, 0.1f));
    
    SpriteFrame* frame8 = NULL;
    Vector<SpriteFrame*> vecFrame8;
    for (int i = 1; i <= 22; i += 3)
    {
        frame8 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_8to9_00%02d.png",i).c_str());
        if (frame8 != NULL)
            vecFrame8.pushBack(frame8);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame8, 0.1f));
    
    SpriteFrame* frame9 = NULL;
    Vector<SpriteFrame*> vecFrame9;
    for (int i = 1; i <= 10; i += 3)
    {
        frame9 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_9to10_00%02d.png",i).c_str());
        if (frame9 != NULL)
            vecFrame9.pushBack(frame9);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame9, 0.1f));
    
    SpriteFrame* frame10 = NULL;
    Vector<SpriteFrame*> vecFrame10;
    for (int i = 1; i <= 13; i += 3)
    {
        frame10 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_10to11_00%02d.png",i).c_str());
        if (frame10 != NULL)
            vecFrame10.pushBack(frame10);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame10, 0.1f));
    
    SpriteFrame* frame11 = NULL;
    Vector<SpriteFrame*> vecFrame11;
    for (int i = 1; i <= 10; i += 3)
    {
        frame11 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_11to12_00%02d.png",i).c_str());
        if (frame11 != NULL)
            vecFrame11.pushBack(frame11);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame11, 0.1f));
    
    SpriteFrame* frame12 = NULL;
    Vector<SpriteFrame*> vecFrame12;
    for (int i = 1; i <= 7; i += 3)
    {
        frame12 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_12to13_00%02d.png",i).c_str());
        if (frame12 != NULL)
            vecFrame12.pushBack(frame12);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame12, 0.1f));
    
    SpriteFrame* frame13 = NULL;
    Vector<SpriteFrame*> vecFrame13;
    for (int i = 1; i <= 7; i += 3)
    {
        frame13 = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("mapRoad_13to14_00%02d.png",i).c_str());
        if (frame13 != NULL)
            vecFrame13.pushBack(frame13);
    }
    roadAniVector.pushBack(Animation::createWithSpriteFrames(vecFrame13, 0.1f));

}
