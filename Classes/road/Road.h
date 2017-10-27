//
//  Road.h
//  BattleScene
//
//  Created by Dee on 17/10/27.
//
//

#ifndef Road_h
#define Road_h

#include "cocos2d.h"

USING_NS_CC;

class Road : public Sprite
{
public:
    Road();
    ~Road();
    
    virtual bool init();
    CREATE_FUNC(Road);
    //执行 打开下一关卡动画
    virtual void buildRoadAni(int num);
    //显示关卡间路径
    virtual void setRoadReady();
    //加载动画资源
    void initRoadAni();
    
    Vector<Sprite*> roadVector;
    Vector<Animation*> roadAniVector;
};

#endif /* Road_h */
