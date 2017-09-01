//
//  MapFlag.h
//  kingdom rush2
//
//  Created by Dee on 17/9/1.
//
//

#ifndef MapFlag_h
#define MapFlag_h

#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

class MapFlag : public Sprite
{
public:
    MapFlag();
    ~MapFlag();
    
    bool initwithLevel(int level);
    CREATE_FUNC(MapFlag);
    
    static MapFlag* createWithLevel(int Level);
    void changeType(int type);
private:
    void startGame();
    void initStar();
    void addStar();
    void startSuccessAnimation();
    void startDropdownAnimation();
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void startAnimation();
    void setStarShine(int num);
    void setStarClose();
    
    Sprite* m_pwings;
    CC_SYNTHESIZE(int, type, Type);
    CC_SYNTHESIZE(int, level, Level);
    Sprite* m_psflag;
    Sprite* m_pStar_0;
    Sprite* m_pStar_1;
    Sprite* m_pStar_2;
    Vector<Sprite*> m_pstarVector;
    GameManager* instance;

};

#endif /* MapFlag_h */
