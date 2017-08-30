#include "AppDelegate.h"
#include "scene/LoadtoStart.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("KingdomRush2", Rect(0, 0, 960, 640));
        glview->setFrameSize(1136, 640);
        director->setOpenGLView(glview);
    }

    //director->getOpenGLView()->setDesignResolutionSize(1136, 640, ResolutionPolicy::SHOW_ALL);
    //���ִ������Ʒֱ��ʸ߶Ȳ��䣬������Ļ�ֱ���������Ʒֱ��ʵĿ�ȡ�
    director->getOpenGLView()->setDesignResolutionSize(960, 640, ResolutionPolicy::FIXED_HEIGHT);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");
    
    bool isFirstPlay = UserDefault::getInstance()->getBoolForKey("isFirstPlay");

    if (!isFirstPlay)
    {
        UserDefault::getInstance()->setBoolForKey("isPlayMusic", true);
        UserDefault::getInstance()->setBoolForKey("isPlayEffect", true);
        UserDefault::getInstance()->setBoolForKey("isFirstPlay", true);
    }

    // create a scene. it's an autorelease object
    auto scene = LoadtoStart::createScene();
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
