#ifndef _LOADTOSTART_H_
#define _LOADTOSTART_H_

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "SimpleAudioEngine.h" 

USING_NS_CC;
using namespace cocostudio::timeline;
using namespace CocosDenshion;

class LoadtoStart : public Layer
{
public:
    static Scene* createScene();

    virtual bool init();

    CREATE_FUNC(LoadtoStart);

    void Loadsource();
    void Logic(float dt);
    int num;
    int m_iLoadedNum;
    int m_iAllResourceNum;

	void onLoadingCallback_texture(cocos2d::Texture2D* texture);
    void onLoadingCallback_plist(cocos2d::Texture2D* texture);
	bool m_bLoading;
};

#endif