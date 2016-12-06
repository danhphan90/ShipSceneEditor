#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ResourcesNew.h"
USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    Unit::loadResource();
    Bullet::loadBullet();
    Path::loadResource();
    LightningSprite::loadResource();
    CoinLayer::loadResource();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld::HelloWorld(){
    mission = NULL;
    _indexWave = 1;
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Enemy/EnemySpriteEditor.plist");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->scheduleUpdate();
    
    rootNode = CSLoader::createNode("MainScene.csb");
    
#ifdef MACBOOK_PRO
    rootNode->setScale(0.75);
#endif
    
    this->addChild(rootNode,ZTag::zRootNode);
    this->saveChildToLocalVariable();
    this->modifyLocalVariable();
    this->modifyButtonEvent();
    this->modifyOtherEvents();
    
    return true;
}

void HelloWorld::startMission(){
    if (mission != NULL) return;
    mission = Mission_1_::create();
    
    Bullet::setMissionLayer((Layer*)mission);
    Unit::setMissionLayer((Layer*)mission);
    Wave::setMissionlayer((Layer*)mission);
    LightningSprite::loadMissionLayer((Layer*)mission);
    rootNode->addChild(mission,0);
    
    mission->start();

}

void HelloWorld::stopMission(){
    if (mission != NULL){
        
        mission->clear();
        this->removeChild(mission);
        Bullet::reloadBullet();
        
        mission= NULL;
    }
    
}

void HelloWorld::saveChildToLocalVariable(){
    panel = (ImageView*)rootNode->getChildByTag(MainSceneChild::tagPanel);
    
    btnPanel_Start = (Button*)panel->getChildByTag(PanelChild::tagStart);
    btnPanel_Reset = (Button*)panel->getChildByTag(PanelChild::tagReset);
    
    btnPanel_Add = (Button*)panel->getChildByTag(tagAdd);
    btnPanel_Remove = (Button*)panel->getChildByTag(tagRemove);
    
    listWave = (ListView*)panel->getChildByTag(tagListWave);
}

void HelloWorld::modifyLocalVariable(){
    panel->setLocalZOrder(2);
}

void HelloWorld::modifyButtonEvent(){
    btnPanel_Start->addTouchEventListener(CC_CALLBACK_2(HelloWorld::callBackButton, this));
    btnPanel_Reset->addTouchEventListener(CC_CALLBACK_2(HelloWorld::callBackButton, this));
    btnPanel_Add->addTouchEventListener(CC_CALLBACK_2(HelloWorld::callBackButton, this));
    btnPanel_Remove->addTouchEventListener(CC_CALLBACK_2(HelloWorld::callBackButton, this));
}

void HelloWorld::modifyOtherEvents(){
    WaveLayer::saveMainPanel(panel);
}

void HelloWorld::onEnterTransitionDidFinish(){
    Node::onEnterTransitionDidFinish();
    
}

static Vector<Bullet*> arrBulletRemoving;

void HelloWorld::update(float dt){
    
    for (auto bullet : Bullet::getArrBulletMoving()){
        bullet->setPosition(bullet->getPosition() + bullet->vectorMove);
        if (bullet->getPositionX() > 640 || bullet->getPositionX() < 0 || bullet->getPositionY() > 960 || bullet->getPositionY() < 0){
            arrBulletRemoving.pushBack(bullet);
        }
    }
    
    for (auto bullet : arrBulletRemoving){
        bullet->stop();
    }
    
    arrBulletRemoving.clear();
    
    if (Unit::getArrUnitCurrentOnMap().size() > 0){
        for (auto unit : Unit::getArrUnitCurrentOnMap()){
            unit->attack(dt);
        }
    }
}

Layout* HelloWorld::createButtonWave(){
    auto _layout = Layout::create();
    _layout->setContentSize(Size(listWave->getContentSize().width,80));
    
    auto _button = WaveButton::create();
    _button->setPosition(Vec2(60,_layout->getContentSize().height/2));
    _button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::callBackWaveButton, this));
    _layout->addChild(_button);
    _layout->setTag(_button->getTag());
    
    _layout->addChild(_button->panelInfo);
    _button->panelInfo->setPosition(Vec2(90,0));
    
    
    return _layout;
}

void HelloWorld::callBackButton(cocos2d::Ref *pSender, Widget::TouchEventType type){
    auto _button = (Button*)pSender;
    
    if (_button == NULL) return;
    
    
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            switch (_button->getTag()) {
                case PanelChild::tagStart :
                    startMission();
                    break;
                    
                case PanelChild::tagReset :
                    stopMission();
                    break;
                    
                case PanelChild::tagAdd :
                    listWave->pushBackCustomItem(createButtonWave());
                    listWave->forceDoLayout();
                    break;
                    
                case PanelChild::tagRemove :
                    if (listWave->getItems().size() > 0){
                        auto _layout = (WaveButton*)listWave->getItems().back();
                        auto _waveButton = (WaveButton*)_layout->getChildByTag(_layout->getTag());
                        _waveButton->clear();
                        listWave->removeLastItem();
                    }
                  
                    break;

                    
                default:
                    break;
            }
            
            
            break;
        }
            
        default:
            break;
    }
}

void HelloWorld::callBackWaveButton(cocos2d::Ref *pSender, Widget::TouchEventType type){
//    auto _button = (WaveButton*)pSender;
//    
//    if (_button == NULL) return;
//    
//    
//    switch (type) {
//        case cocos2d::ui::Widget::TouchEventType::ENDED:
//        {
//            auto _panelInfo = _button->panelInfo;
//            if (_panelInfo != NULL){
//                _panelInfo->setNormalizedPosition(Vec2(0.35,0.32));
//                this->addChild(_panelInfo,ZTag::zPanelInfo);
//                _panelInfo->open();
//                
//                _panelInfo->setScale(0.3);
//                _panelInfo->runAction(EaseElasticOut::create(ScaleTo::create(0.5, 1), 0.5));
//            }
//            break;
//        }
//            
//        default:
//            break;
//    }
}

