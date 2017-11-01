#include "TransitionGame.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

TransitionGame::TransitionGame()
{
    m_iFinshCnt = 0;
}

TransitionGame::~TransitionGame()
{}

TransitionGame* TransitionGame::create(float t, Scene* scene)
{
    TransitionGame* pScene = new TransitionGame;
    if (pScene && pScene->initWithDuration(t, scene))
    {
        pScene->autorelease();
        return pScene;
    }
    CC_SAFE_DELETE(pScene);
    return NULL;
}

void TransitionGame::onEnter()
{
    //要切入的场景
    _inScene->setVisible(false);
    TransitionScene::onEnter();
    _outScene->setPosition(0, 0);
    _inScene->setPosition(0, 0);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point LeftBegin, LeftEnd, RightBegin, RightEnd;
    LeftBegin.setPoint(0, visibleSize.height / 2.0f);
    LeftEnd.setPoint(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
    RightBegin.setPoint(visibleSize.width, visibleSize.height / 2.0f);
    RightEnd.setPoint(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
    //添加切换过度图片
    auto sp_left = Sprite::createWithSpriteFrameName("transitionDoor.png");
    auto sp_right = Sprite::createWithSpriteFrameName("transitionDoor.png");
    sp_left->setScaleX(visibleSize.width / 960);
    sp_right->setScaleX(visibleSize.width / 960);
    sp_left->setAnchorPoint(Point(1, 0.5));
    sp_right->setAnchorPoint(Point(0, 0.5));
    sp_left->setPosition(LeftBegin);
    sp_right->setPosition(RightBegin);
    addChild(sp_right, 1);
    addChild(sp_left, 1);
    sp_right->setFlippedX(true);
    
    auto sp_left_ = Sprite::createWithSpriteFrameName("transitionLoading_left.png");
    auto sp_right_ = Sprite::createWithSpriteFrameName("transitionLoading_right.png");
    sp_left_->setAnchorPoint(Point(1, 0.5));
    sp_right_->setAnchorPoint(Point(0, 0.5));
    sp_left_->setPosition(Point(sp_left->getContentSize().width, sp_left->getContentSize().height / 2));
    sp_right_->setPosition(Point(0, sp_right->getContentSize().height / 2));
    sp_left->addChild(sp_left_);
    sp_right->addChild(sp_right_);
    
    //关门动画
    auto pActionLeft = MoveTo::create(_duration / 5, LeftEnd);
    auto pActionRight = MoveTo::create(_duration / 5, RightEnd);
    
    //开门动画
    auto pActionLeft1 = MoveTo::create(_duration / 4, LeftBegin);
    auto pActionRight1 = MoveTo::create(_duration / 4, RightBegin);
    
    if (UserDefault::getInstance()->getBoolForKey("isPlayEffect"))
        SimpleAudioEngine::getInstance()->playEffect("sound/GUITransitionOpen.wav");
    sp_left->runAction(Sequence::create(EaseBackIn::create(pActionLeft),
                                    CallFunc::create(CC_CALLBACK_0(TransitionGame::OnSecondActionFinish, this)),
                                        DelayTime::create(1),
                                        EaseBackOut::create(pActionLeft1),
                                        NULL));
    sp_right->runAction(Sequence::create(EaseBackIn::create(pActionRight),
                                          DelayTime::create(1),
                                         EaseBackOut::create(pActionRight1),
                                         CallFunc::create(CC_CALLBACK_0(TransitionGame::LRFinish, this)),
                                          NULL));
}

void TransitionGame::LRFinish()
{
    TransitionScene::finish();
}

void TransitionGame::OnSecondActionFinish()
{
    if (UserDefault::getInstance()->getBoolForKey("isPlayEffect"))
        SimpleAudioEngine::getInstance()->playEffect("sound/GUITransitionClose.wav");
    //切换延迟 手动显示入场景
    _inScene->setVisible(true);
    _outScene->setVisible(false);
}
