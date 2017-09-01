//
//  GameManager.cpp
//  Kingdom Rush
//
//  Created by Dee on 17/8/21.
//
//
#include "GameManager.h"

GameManager* GameManager::instance;

void GameManager::CreateGameManager(int sid)
{

}

GameManager* GameManager::getInstance()
{
    if (instance == NULL)
        instance = new GameManager;
    return instance;
}


void GameManager::setInstance(int sid)
{
    sprintf(SaveGame, "SaveGame%d", sid);
    
    sprintf(LevelIsDown, "SaveGame%d", sid);
    strcat(LevelIsDown,"_Level_%d");
    
    sprintf(LevelStarnum, "SaveGame%d", sid);
    strcat(LevelStarnum,"_Level_%d_star");
    
    sprintf(LevelDownNum, "SaveGame%d_DownCount", sid);
    
    sprintf(LevelNewOpen, "SaveGame%d_NewDown", sid);
    
    sprintf(SaveStar, "SavaGame%d_Star", sid);
    
    sprintf(SaveStarLeft, "SaveGame%d_StarLeft", sid);
    
    sprintf(SaveGem, "SaveGame%d_Gem", sid);
    
    sprintf(SaveShop, "SaveGame%d", sid);
    strcat(SaveShop,"_Shop_%d");
}

void GameManager::eraseAll()
{
    //instance->monsterVector.clear();
}

