#include "Start.h"
#include "GameManager.h"
#include "TransitionGame.h"
#include "LoadtoStart.h"

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

    //��ȡ���� ��Ч��ť
    btn_Music = (Button*)rootNode->getChildByName("btn_Music");
    btn_Effect = (Button*)rootNode->getChildByName("btn_Effect");
    btn_Music->addTouchEventListener(CC_CALLBACK_2(Start::btn_Music_CallBack, this));
    btn_Effect->addTouchEventListener(CC_CALLBACK_2(Start::btn_Effect_CallBack, this));

    //��ȡLOG����
    auto sp_Log = (Sprite*)rootNode->getChildByName("sp_Log");
    sp_Log->setScale(0.2);

    //��ȡ��ʼ ������ť
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

    //KLGĬ������£���
    //���Ҫ�趨���ʽ�ܹ������ⲿ������������ [] ��д�� & ���� = ���ϱ����������� & ��ʾ�����÷��ʣ�
    //= ��ʾ��ֵ���ʣ�����֮���ö��ŷָ������� [=factor, &total] ��ʾ��ֵ���ʱ��� factor���������÷��� total��
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
    
    //��ȡ�浵�ڵ�
    m_nodeSavelot = CSLoader::createNode("Savelot.csb");
    m_nodeSavelot->setAnchorPoint(Vec2(0.5, 0.5));
    addChild(m_nodeSavelot);
    m_nodeSavelot->setPosition(Vec2(visibleSize.width / 2, -300));
    
    //���� �д浵1
    UserDefault::getInstance()->setBoolForKey("SavaGame1", true);
    UserDefault::getInstance()->setIntegerForKey("SavaGame1_Star", 50);
    
    initSaveMenu();
    
    btn_Close = (Button*)Helper::seekWidgetByName(static_cast<Layout*>(m_nodeSavelot), "btn_Close");
    btn_Close->addTouchEventListener(CC_CALLBACK_2(Start::Savelot_Down, this));

    //start��ť��Ӧ
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
        sprintf(txt, "%s%d", "img_Star_", i+1);
        //��ȡstarͼƬ
        ImageView * img = (ImageView*)m_nodeSavelot->getChildByName(txt);
        
        memset(txt, 0, sizeof(txt));
        sprintf(txt, "%s%d", "txt_", i+1);
        Text* text1 = (Text*)m_nodeSavelot->getChildByName(txt);
        
        memset(txt, 0, sizeof(txt));
        sprintf(txt, "%s%d", "txtnum_", i+1);
        Text* text2 = (Text*)m_nodeSavelot->getChildByName(txt);
        
        memset(txt, 0, sizeof(txt));
        sprintf(txt, "%s%d", "SavaGame", i+1);
        bool havegamesave = UserDefault::getInstance()->getBoolForKey(txt);
        //�д浵 ��ʼ���浵��Ϣ
        if (havegamesave)
        {
            int getStars = UserDefault::getInstance()->getIntegerForKey(String::createWithFormat("SavaGame%d_Star", i+1)->getCString());
            memset(txt, 0, sizeof(txt));
            //KLG��ʽ���ַ��� ���Լӻ���\n
            //sprintf(txt, "SLOT 1 \n%d/100", getStars);
            sprintf(txt, "%d/100", getStars);
            text2->setString(txt);
            delete_->addTouchEventListener(CC_CALLBACK_2(Start::btn_Deletegame_CallBack, this));
        }
        else
        {
            save->setTitleText("new game");
            delete_->setVisible(false);
            img->setVisible(false);
            text1->setVisible(false);
            text2->setVisible(false);
        }
        //��ʼ�� / ���� ��Ϸ
        save->addTouchEventListener(CC_CALLBACK_2(Start::btn_Newgame_CallBack, this));
    }
}

void Start::deleteGameRecord(int sid)
{
    //�����浵
    UserDefault::getInstance()->setBoolForKey(String::createWithFormat("SavaGame%d", sid)->getCString(), false);
    //
    for(int i=0;i<13;i++)
    {
        UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("SavaGame%d_Level_%d", sid, i)->getCString(),0);
    }
    
    for(int i=0;i<13;i++)
    {
        UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("SavaGame%d_Level_%d_star", sid, i)->getCString(),0);
    }
    
    UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("SavaGame%d_DownCount", sid)->getCString(),0);
    
    UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("SavaGame%d_NewDown", sid)->getCString(),0);
    
    UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("SavaGame%d_StarLeft", sid)->getCString(),0);
    
    //������
    UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("SavaGame%d_Star", sid)->getCString(),0);
    
    //��ʯ
    UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("SavaGame%d_Gem", sid)->getCString(),0);
    
    //��Ʒ����
    for(int i = 0;i<6;i++)
        UserDefault::getInstance()->setIntegerForKey(String::createWithFormat("SavaGame%d_Shop_%d", sid, i)->getCString(),0);
}

void Start::conform_delete(Ref* pSender, int sid)
{
    //������ʾnew game
    Button* save = (Button*)m_nodeSavelot->getChildByName(String::createWithFormat("btn_%d", sid)->getCString());
    save->setTitleText("new game");
    
    save = (Button*)m_nodeSavelot->getChildByName(String::createWithFormat("btn_%d", sid + 3)->getCString());
    save->setVisible(false);
    
    Text* text = (Text*)m_nodeSavelot->getChildByName(String::createWithFormat("txt_%d", sid)->getCString());
    text->setVisible(false);
    
    m_nodeSavelot->getChildByTag(sid)->setVisible(false);
    
    //ɾ����Ϸ�浵
    deleteGameRecord(sid);
}

void Start::cancel_delete(Ref* pSender, int sid)
{
    //��ȡtxt_1.2.3
    Text* text = (Text*)m_nodeSavelot->getChildByName(String::createWithFormat("txt_%d", sid)->getCString());
    text->setString(String::createWithFormat("SLOT %d", sid)->getCString());
    text->setFontSize(36);
    
    //��ȡstarͼƬ
    ImageView* img_star = (ImageView*)m_nodeSavelot->getChildByName(String::createWithFormat("img_Star_%d", sid)->getCString());
    img_star->setVisible(true);
    
    //��ȡ�÷�text
    text = (Text*)m_nodeSavelot->getChildByName(String::createWithFormat("txtnum_%d", sid)->getCString());
    text->setVisible(true);
    
    //�˵�����Ϊfalse;
    m_nodeSavelot->getChildByTag(sid)->setVisible(false);
    
    //x��ť�������ûص�
    //Button* btn = (Button*)m_nodeSavelot->getChildByName(String::createWithFormat("btn_%d", sid + 3)->getCString());
    //btn->addTouchEventListener(CC_CALLBACK_2(Start::btn_Deletegame_CallBack, this));
}

void Start::btn_Newgame_CallBack(Ref* pSender,Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        Button* dlt_btn = dynamic_cast<Button*>(pSender);
        auto usertext = ((cocostudio::ComExtensionData*)(dlt_btn->getComponent("ComExtensionData")))->getCustomProperty();
        
        int sid = atoi((usertext.c_str()));
        
        GameManager* instance = GameManager::getInstance();
        //�л���Ϸ���ͼ����
        instance->setInstance(sid);
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        UserDefault::getInstance()->setBoolForKey(instance->SaveGame, true);
        Director::getInstance()->replaceScene(TransitionGame::create(2.0f, LoadtoStart::createScene()));
    }
}

void Start::btn_Deletegame_CallBack(Ref* pSender,Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        //��ȡ�ؼ�userdata �ж� ���ڽ���ɾ�������Ĵ浵id
        Button* dlt_btn = dynamic_cast<Button*>(pSender);
        auto usertext = ((cocostudio::ComExtensionData*)(dlt_btn->getComponent("ComExtensionData")))->getCustomProperty();
        
        int sid = atoi((usertext.c_str()));
        
        //��ȡtxt_1.2.3
        Text* text1 = (Text*)m_nodeSavelot->getChildByName(String::createWithFormat("txt_%d", sid)->getCString());
        text1->setString("Comfire delete?");
        text1->setFontSize(24);
        
        //��ȡstarͼƬ
        ImageView* img_star = (ImageView*)m_nodeSavelot->getChildByName(String::createWithFormat("img_Star_%d", sid)->getCString());
        img_star->setVisible(false);
        //��ȡ�÷�text
        Text* text2 = (Text*)m_nodeSavelot->getChildByName(String::createWithFormat("txtnum_%d", sid)->getCString());
        text2->setVisible(false);
        
        //dlt_btn->addTouchEventListener(CC_CALLBACK_1(Start::cancel_delete, this, sid));
        if (m_nodeSavelot->getChildByTag(sid))
        {
            m_nodeSavelot->getChildByTag(sid)->setVisible(true);
            return;
        }
        
        Sprite* sp1 = Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0001.png");
        Sprite* sp2 = Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0001.png");
        auto confirm_Delete = MenuItemSprite::create(sp1, sp2, CC_CALLBACK_1(Start::conform_delete, this, sid));
        confirm_Delete->setPosition(Point(text1->getPositionX() - 80, text1->getPositionY() - 50));
        
        sp1 = Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0002.png");
        sp2 = Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0002.png");
        auto cancel_Delete_1 =
        MenuItemSprite::create(sp1, sp2, CC_CALLBACK_1(Start::cancel_delete, this, sid));
        cancel_Delete_1->setPosition(Point(text1->getPositionX() + 80, text1->getPositionY() - 50));
        auto delete1_menu = Menu::create(confirm_Delete, cancel_Delete_1, NULL);
        delete1_menu->setPosition(Vec2::ZERO);
        delete1_menu->setAnchorPoint(ccp(0, 0));
        auto point = delete1_menu->getAnchorPoint();
        auto confirm = Node::create();
        confirm->addChild(delete1_menu);
        m_nodeSavelot->addChild(confirm, 1, sid);
    }
}

void Start::btn_Start_CallBack(Ref* pSender,Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED)
    {
        if (!m_bSaveshow)//Ϊ�����savelot
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
        if (isPlayMusic)//Ϊ���ֹͣ����
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
        if (isPlayEffect)//Ϊ���ֹͣ��Ч
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