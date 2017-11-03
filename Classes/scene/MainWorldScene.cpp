//
//  MainWorldScene.cpp
//  BattleScene
//
//  Created by Dee on 17/9/1.
//
//

#include "MainWorldScene.h"
#include "TransitionGame.h"
#include "Start.h"
//#include "editor-support/cocostudio/cccom
#include "SimpleAudioEngine.h"

#include "MapFlag.h"


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
    
    m_rootNode = CSLoader::createNode("mainworld.csb");
    addChild(m_rootNode);
    
    if(UserDefault::getInstance()->getBoolForKey("isPlayMusic"))
        SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/Map_Theme_1.wav", true);
    
    m_pinstance = GameManager::getInstance();
    m_winSize = Director::getInstance()->getWinSize();
    
    //获取 世界地图
    m_pbgSprite = (Sprite*)m_rootNode->getChildByName("sp_MainWorld");

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
    
    btn_Setting = dynamic_cast<Button*>(Helper::seekWidgetByName((Layout*)m_rootNode, "btn_Setting"));
    btn_Setting->addTouchEventListener(CC_CALLBACK_2(MainWorldScene::btn_Settings,this));
    
    addSceneElements();
    
    //添加移动触摸
    auto listener = EventListenerTouchAllAtOnce::create();
    //listener->setSwallowTouches(true);
    //listener->onTouchBegan = CC_CALLBACK_2(MainWorldScene::onTouchBegan, this);
    //listener->onTouchMoved = CC_CALLBACK_2(MainWorldScene::onTouchMoved, this);
    listener->onTouchesBegan = CC_CALLBACK_2(MainWorldScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(MainWorldScene::onTouchesMoved, this);
    
    //添加监听器
    EventDispatcher*eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener, m_pbgSprite);
    return true;
}
bool MainWorldScene::onTouchBegan(Touch *touch, Event *unused_event)
{
    log("onTouchBegan");
    return  true;
}

void MainWorldScene::onTouchMoved(Touch *touch, Event *unused_event)
{
    log("onTouchMoved");
}

void MainWorldScene::onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    log("onTouchesBegan");
}

void MainWorldScene::onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event)
{
    log("onTouchesMoved");
    // 单点进行移动
    if(touches.size() == 1)
    {
        // 单点时，touches中只有一个Touch对象，所以通过touches[0]就可以得到触摸对象
        auto touch = touches[0];
        // 计算滑动过程中的滑动增量
        auto diff = touch->getDelta();
        // 得到当前bgSprite的位置
        auto currentPos = m_pbgSprite->getPosition();
        // 得到滑动后bgSprite应该所在的位置
        auto pos = currentPos + diff;
        // 得到此刻bgSprite的尺寸
        auto bgSpriteCurrSize = m_pbgSprite->getBoundingBox().size;
        log("size:%f ~~~ %f", bgSpriteCurrSize.width, bgSpriteCurrSize.height);
        
        //边界控制，约束pos的位置 跟max比取小 跟min比取大
        pos.x = MIN(pos.x, bgSpriteCurrSize.width * m_pbgSprite->getAnchorPoint().x);
        pos.x = MAX(pos.x, -bgSpriteCurrSize.width + m_winSize.width + bgSpriteCurrSize.width * m_pbgSprite->getAnchorPoint().x);
        pos.y = MIN(pos.y, bgSpriteCurrSize.height * m_pbgSprite->getAnchorPoint().y);
        pos.y = MAX(pos.y, -bgSpriteCurrSize.height + m_winSize.height + bgSpriteCurrSize.height * m_pbgSprite->getAnchorPoint().y);
        
        m_pbgSprite->setPosition(pos);
    }
}

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
    m_pbgSprite->addChild(m_proad);
    
    int count = UserDefault::getInstance()->getIntegerForKey(m_pinstance->LevelNewOpen, 0);
    log("当前关卡数:%d", count);
    m_proad->buildRoadAni(2);
}

void MainWorldScene::addNewMapFlag(int num)
{}

void MainWorldScene::addSettings()
{
    auto setNode = CSLoader::createNode("Setting.csb");
    addChild(setNode,1,1);
    setNode->setVisible(false);
    setNode->setAnchorPoint(Vec2(0.5, 0));
    setNode->setPosition(Vec2(btn_Setting->getPositionX(), btn_Setting->getPositionY() + 40));
    btn_Music = dynamic_cast<Button*>(Helper::seekWidgetByName(static_cast<Layout*>(setNode), "btn_Music"));
    btn_Effect = dynamic_cast<Button*>(Helper::seekWidgetByName(static_cast<Layout*>(setNode), "btn_Effect"));
    btn_Music->addTouchEventListener(CC_CALLBACK_2(MainWorldScene::btn_Music_CallBack, this));
    btn_Effect->addTouchEventListener(CC_CALLBACK_2(MainWorldScene::btn_Effect_CallBack, this));
    btn_Home = dynamic_cast<Button*>(Helper::seekWidgetByName(static_cast<Layout*>(setNode), "btn_Home"));
    btn_Home->addTouchEventListener(CC_CALLBACK_2(MainWorldScene::btn_Home_CallBack,this));
    if (UserDefault::getInstance()->getBoolForKey("isPlayMusic", true))//为真就停止音乐
    {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        btn_Music->loadTextureNormal("options_overlay_buttons_0001.png", TextureResType::PLIST);
        btn_Music->loadTexturePressed("options_overlay_buttons_0002.png", TextureResType::PLIST);
    }
    else
    {
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        btn_Music->loadTextureNormal("options_overlay_buttons_0002.png", TextureResType::PLIST);
        btn_Music->loadTexturePressed("options_overlay_buttons_0001.png", TextureResType::PLIST);
    }
    if (UserDefault::getInstance()->getBoolForKey("isPlayEffect", true))//为真就停止音效
    {
        btn_Effect->loadTextureNormal("options_overlay_buttons_0003.png", TextureResType::PLIST);
        btn_Effect->loadTexturePressed("options_overlay_buttons_0004.png", TextureResType::PLIST);
    }
    else
    {
        SimpleAudioEngine::getInstance()->stopAllEffects();
        btn_Effect->loadTextureNormal("options_overlay_buttons_0004.png", TextureResType::PLIST);
        btn_Effect->loadTexturePressed("options_overlay_buttons_0003.png", TextureResType::PLIST);
    }
}

void MainWorldScene::addSceneElements()
{
    addSettings();
    //widget子类才能使用以下2种方法seekWidgetByName seekWidgetByTag
    //auto node = static_cast<Node*>(Helper::seekWidgetByName(static_cast<Layout*>(m_rootNode), "node_gem_star"));wrong
    //auto node = static_cast<Node*>(Helper::seekWidgetByTag(static_cast<Layout*>(m_rootNode), 3));wrong
    //通用方法 getChildByName getChildByTag
    //auto node = static_cast<Node*>(m_rootNode->getChildByName("node_gem_star"));//right
    auto node = static_cast<Node*>(m_rootNode->getChildByTag(3));
    //在widget子类层次下才能使用以下2种方法  Helper::seekWidgetByName可以在整个对象结构中直接查找。 但是不能查找node节点下的
    //auto atn_gem = (TextAtlas*)Helper::seekWidgetByName(static_cast<Layout*>(m_rootNode), "atn_Gem");//wrong???
    //auto atn_gem = (TextAtlas*)Helper::seekWidgetByTag(static_cast<Layout*>(m_rootNode), 1);wrong
    //否则从父节点使用通用方法
    //auto atn_gem = (TextAtlas*)node->getChildByTag(1);//right
    auto atn_gem = (TextAtlas*)node->getChildByName("atn_Gem");//right
    //否则从父节点使用以下2种方法seekWidgetByName seekWidgetByTag
    //auto atn_gem = (TextAtlas*)Helper::seekWidgetByTag(static_cast<Layout*>(node), 1);//right
    //auto atn_gem = (TextAtlas*)Helper::seekWidgetByName(static_cast<Layout*>(node), "atn_Gem");//right
    
    log("%d !!!", UserDefault::getInstance()->getIntegerForKey(m_pinstance->SaveGem, 0));
    atn_gem->setString(String::createWithFormat("%d", UserDefault::getInstance()->getIntegerForKey(m_pinstance->SaveGem, 0))->getCString());
    //auto atn_star = (TextAtlas*)Helper::seekWidgetByName(static_cast<Layout*>(m_rootNode), "atn_Star");
    //auto atn_star = (TextAtlas*)Helper::seekWidgetByTag(static_cast<Layout*>(m_rootNode), 2);
    auto atn_star = dynamic_cast<TextAtlas*>(node->getChildByTag(2));
    atn_star->setString(String::createWithFormat("%d", UserDefault::getInstance()->getIntegerForKey(m_pinstance->SaveStar, 0))->getCString());
}

void MainWorldScene::onEnterTransitionDidFinish()
{
    //当前关卡
    int curLevel = UserDefault::getInstance()->getIntegerForKey(m_pinstance->LevelNewOpen);
    
}

void MainWorldScene::btn_Settings(Ref* pSender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        if (this->getChildByTag(1))
            this->getChildByTag(1)->setVisible(!this->getChildByTag(1)->isVisible());
    }
}

void MainWorldScene::btn_Music_CallBack(Ref* pSender,Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        bool isPlayMusic = UserDefault::getInstance()->getBoolForKey("isPlayMusic", true);
        if (isPlayMusic)//为真就停止音乐
        {
            SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
            btn_Music->loadTextureNormal("options_overlay_buttons_0002.png", TextureResType::PLIST);
            btn_Music->loadTexturePressed("options_overlay_buttons_0001.png", TextureResType::PLIST);
            UserDefault::getInstance()->setBoolForKey("isPlayMusic", false);
        }
        else
        {
            SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
            btn_Music->loadTextureNormal("options_overlay_buttons_0001.png", TextureResType::PLIST);
            btn_Music->loadTexturePressed("options_overlay_buttons_0002.png", TextureResType::PLIST);
            UserDefault::getInstance()->setBoolForKey("isPlayMusic", true);
        }
        if(UserDefault::getInstance()->getBoolForKey("isPlayEffect"))
            SimpleAudioEngine::getInstance()->playEffect("sound/dj.wav");
    }
}

void MainWorldScene::btn_Effect_CallBack(Ref* pSender,Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        bool isPlayEffect = UserDefault::getInstance()->getBoolForKey("isPlayEffect", true);
        if (isPlayEffect)//为真就停止音效
        {
            SimpleAudioEngine::getInstance()->stopAllEffects();
            btn_Effect->loadTextureNormal("options_overlay_buttons_0004.png", TextureResType::PLIST);
            btn_Effect->loadTexturePressed("options_overlay_buttons_0003.png", TextureResType::PLIST);
            UserDefault::getInstance()->setBoolForKey("isPlayEffect", false);
        }
        else
        {
            btn_Effect->loadTextureNormal("options_overlay_buttons_0003.png", TextureResType::PLIST);
            btn_Effect->loadTexturePressed("options_overlay_buttons_0004.png", TextureResType::PLIST);
            UserDefault::getInstance()->setBoolForKey("isPlayEffect", true);
        }
        if(UserDefault::getInstance()->getBoolForKey("isPlayEffect"))
            SimpleAudioEngine::getInstance()->playEffect("sound/dj.wav");
    }
}


void MainWorldScene::btn_Home_CallBack(Ref* pSender, Widget::TouchEventType type)
{
    Director::getInstance()->replaceScene(TransitionGame::create(2.0f,Start::createScene()));
}
