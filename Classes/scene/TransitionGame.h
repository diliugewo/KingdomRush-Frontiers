#ifndef _TRANSITIONGAME_H_
#define _TRANSITIONGAME_H_

#include "cocos2d.h"

USING_NS_CC;

class TransitionGame : public TransitionScene
{
public:
    TransitionGame();
    virtual ~TransitionGame();
    void onEnter();
    static TransitionGame *create(float t, Scene* scene);
private:
    void LRFinish();
    void OnSecondActionFinish();
    
    int m_iFinshCnt;
};


#endif