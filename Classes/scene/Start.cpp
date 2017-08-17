#include "Start.h"

Scene* Start::createScene()
{
    auto scene = Scene::create();
    auto layer = Start::create();
    scene->addChild(layer);

    return scene;
}

bool Start::init()
{
    if (!Layer::init())
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    m_bSaveshow = false;
    SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/savage_music_theme.wav", true);

    auto rootNode = CSLoader::createNode("Start.csb");

    addChild(rootNode, -1);

    //获取音乐 音效按钮
    btn_Music = (Button*)rootNode->getChildByName("btn_Music");
    btn_Effect = (Button*)rootNode->getChildByName("btn_Effect");
    btn_Music->addTouchEventListener(CC_CALLBACK_2(Start::btn_Music_CallBack, this));
    btn_Effect->addTouchEventListener(CC_CALLBACK_2(Start::btn_Effect_CallBack, this));

    //获取LOG精灵
    auto sp_Log = (Sprite*)rootNode->getChildByName("sp_Log");
    sp_Log->setScale(0.2);

    //获取开始 结束按钮
    btn_Exit = (Button*)rootNode->getChildByName("btn_Exit");
    btn_Exit->addTouchEventListener([=](Ref* pSender,Widget::TouchEventType type)
    {
        if (type == Widget::TouchEventType::ENDED)
        {
            Director::getInstance()->end();
            #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
                        exit(0);
            #endif
        }
    });
    auto btn_Start = (Button*)rootNode->getChildByName("btn_Start");

    //默认情况下，。
    //如果要设定表达式能够访问外部变量，可以在 [] 内写入 & 或者 = 加上变量名，其中 & 表示按引用访问，
    //= 表示按值访问，变量之间用逗号分隔，比如 [=factor, &total] 表示按值访问变量 factor，而按引用访问 total。
    sp_Log->runAction(Sequence::create(
                                        ScaleTo::create(0.3f, 1.4),
                                        ScaleTo::create(0.2f, 1.0),
     CallFunc::create([=]()
    {
        img_M_E_Down();
        btn_Start->setPosition(Vec2(sp_Log->getPositionX(), 440));
        auto seq = Sequence::create(EaseBackInOut::create(MoveTo::create(0.3f, Vec2(sp_Log->getPositionX(), sp_Log->getPositionY() - 190))),
            CallFunc::create([=]()                                                                                                 {                                                                                                                                                                                                                btn_Exit->setPosition(btn_Start->getPosition());
                btn_Exit->runAction(EaseBackInOut::create(MoveTo::create(0.2f, Vec2(sp_Log->getPositionX(), 88))));
                }),
            DelayTime::create(0.1f),
            CallFunc::create([=]()
            {
                auto sprite = Sprite::createWithSpriteFrameName("logo_brillo_0001.png");
                sprite->setPosition(sp_Log->getPosition());
                addChild(sprite,1);

                //auto log_anmt = Animation::create();

                Vector<SpriteFrame *> arr;
                SpriteFrame* sf;
                for (int len = 1; len <= 21; len++)
                {
                    if (len < 10)
                        sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("logo_brillo_000%d.png",len));
                    else
                        sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("logo_brillo_00%d.png",len));
                    //log_anmt->addSpriteFrame(sf);
                    if (sf != nullptr)
                        arr.pushBack(sf);
                }
                //log_anmt->setDelayPerUnit(3.0f / 21.0f);
                //log_anmt->setRestoreOriginalFrame(true);
                auto animation = Animation::createWithSpriteFrames(arr, 1.0f / 20.0f);
                auto log_ante = Animate::create(animation);
                sprite->runAction(RepeatForever::create(Sequence::create(log_ante, DelayTime::create(5.0f), NULL)));
                }), NULL);
            btn_Start->runAction(seq);
    }),NULL));

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("image/mainmenu_spritesheet_32_2-hd.plist");
    
    //获取存档节点
    m_nodeSavelot = CSLoader::createNode("Savelot.csb");
    m_nodeSavelot->setAnchorPoint(Vec2(0.5, 0.5));
    addChild(m_nodeSavelot);
    m_nodeSavelot->setPosition(Vec2(visibleSize.width / 2, -300));
    
    initSaveMenu();
    
    btn_Close = (Button*)Helper::seekWidgetByName(static_cast<Layout*>(m_nodeSavelot), "btn_Close");
    btn_Close->addTouchEventListener(CC_CALLBACK_2(Start::Savelot_Down, this));

    //start按钮响应
    btn_Start->addTouchEventListener(CC_CALLBACK_2(Start::btn_Start_CallBack, this));
    
    
    
    return true;
}

void Start::initSaveMenu()
{
    for (int i = 0; i < 3; i++)
    {
        char txt[100];
        
        memset(txt, 0, sizeof(txt));
        sprintf(txt, "%s%d", "btn_", i+1);
        Button* save = (Button*)m_nodeSavelot->getChildByName(txt);
        
        memset(txt, 0, sizeof(txt));
        sprintf(txt, "%s%d", "btn_", i+1+3);
        Button* delete_ = (Button*)m_nodeSavelot->getChildByName(txt);
        
        memset(txt, 0, sizeof(txt));
        sprintf(txt, "%s%d", "img_Star", i+1);
        //获取star图片
        ImageView * img = (ImageView*)m_nodeSavelot->getChildByName(txt);
        
        memset(txt, 0, sizeof(txt));
        sprintf(txt, "%s%d", "txt_", i+1);
        Text* text = (Text*)m_nodeSavelot->getChildByName(txt);
        
        memset(txt, 0, sizeof(txt));
        sprintf(txt, "%s%d", "SavaGame", i+1);
        bool havegamesave = UserDefault::getInstance()->getBoolForKey(txt);
        //有存档 初始化存档信息
        if (havegamesave)
        {
            int getStars = UserDefault::getInstance()->getIntegerForKey(txt);
            memset(txt, 0, sizeof(txt));
            sprintf(txt, "SLOT 1 \n%d/100", getStars);
            text->setString(txt);
        }
        else
        {
            save->setTitleText("new game");
            save->addTouchEventListener(CC_CALLBACK_2(Start::btn_Newgame_CallBack, this));
            delete_->setVisible(false);
            img->setVisible(false);
            text->setVisible(false);
        }
    }
}
void Start::btn_Newgame_CallBack(Ref* pSender,Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        //切换游戏大地图场景
        //createNewGame();
        
    }
}

void Start::btn_Start_CallBack(Ref* pSender,Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        if (!m_bSaveshow)//为假则打开savelot
        {
            auto seq = Sequence::create(CallFunc::create([=]()
                                                        {
                                                            img_M_E_Up();
                                                            btn_Exit->runAction(EaseBackInOut::create(MoveTo::create(0.2f, Vec2(visibleSize.width / 2, 250))));
	
                                                        }),
                                        DelayTime::create(0.1f),
                                        EaseBackInOut::create(MoveTo::create(0.3f, Vec2(visibleSize.width / 2, 220))),
                                        NULL);
            m_nodeSavelot->runAction(seq);
            m_bSaveshow = true;
        }
    }
}

void Start::btn_Music_CallBack(Ref* pSender,Widget::TouchEventType type)
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
        SimpleAudioEngine::getInstance()->playEffect("sound/dj.wav");
    }
}

void Start::btn_Effect_CallBack(Ref* pSender,Widget::TouchEventType type)
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
            //SimpleAudioEngine::getInstance()->;
            btn_Effect->loadTextureNormal("options_overlay_buttons_0003.png", TextureResType::PLIST);
            btn_Effect->loadTexturePressed("options_overlay_buttons_0004.png", TextureResType::PLIST);
            UserDefault::getInstance()->setBoolForKey("isPlayEffect", true);
        }
        SimpleAudioEngine::getInstance()->playEffect("sound/dj.wav");
    }
}

void Start::img_M_E_Down()
{
    auto move1 = MoveTo::create(0.3f, Vec2(56, 598));
    auto move2 = MoveTo::create(0.3f, Vec2(150, 598));
    btn_Music->runAction(EaseBackInOut::create(move1));
    btn_Effect->runAction(EaseBackInOut::create(move2));
}

void Start::img_M_E_Up()
{
    auto move1 = MoveTo::create(0.3f, Vec2(56, 670));
    auto move2 = MoveTo::create(0.3f, Vec2(150, 670));
    btn_Music->runAction(EaseBackInOut::create(move1));
    btn_Effect->runAction(EaseBackInOut::create(move2));
}

void Start::Savelot_Down(Ref* pSender,Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        auto seq = Sequence::create(EaseBackInOut::create(MoveTo::create(0.3f, Vec2(visibleSize.width / 2, -300))), CallFunc::create([=]()
        {
            img_M_E_Down();
			
            btn_Exit->runAction(EaseBackInOut::create(MoveTo::create(0.2f, Vec2(visibleSize.width / 2, 88))));
        }), NULL);
        m_nodeSavelot->runAction(seq);
        m_bSaveshow = false;
    }
}