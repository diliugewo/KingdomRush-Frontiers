//
//  Header.h
//  Kingdom Rush
//
//  Created by Dee on 17/8/21.
//
//
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <stdio.h>

USING_NS_CC;

class GameManager
{
public:
    void CreateGameManager(int sid);
    
    //Vector<BaseMonster*> monsterVector;
    static GameManager* getInstance();
    
    //已开存档 true新建 false未新建
    char SaveGame[20];
    
    //某关卡已完成 0未完成 1完成
    char LevelIsDown[20];
    
    //某关卡得星数
    char LevelStarnum[20];
    
    //剩余星星数量
    char SaveStarLeft[20];
    
    //存档通关数
    char LevelDownNum[20];
    
    //当前关卡
    char LevelNewOpen[20];
    
    //总星星数量
    char SaveStar[20];
    
    //商店
    char SaveShop[20];
    
    //宝石
    char SaveGem[20];
    
    int SaveNum;
    
    //实时金钱
    int Money;
    
    //实时生命
    int Life;
    
    int Level;
    
    void setInstance(int sid);
    static void eraseAll();
private:
    static GameManager* instance;
};

#endif