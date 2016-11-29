#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

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
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

HelloWorld::HelloWorld(){
    mission = NULL;
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
    
    this->addChild(rootNode,1);
    this->saveChildToLocalVariable();
    this->modifyLocalVariable();
    this->modifyButtonEvent();
    return true;
}

void HelloWorld::startMission(){
    if (mission != NULL) return;
    mission = Mission_1_::create();
    
    Bullet::setMissionLayer((Layer*)mission);
    Unit::setMissionLayer((Layer*)mission);
    Wave::setMissionlayer((Layer*)mission);
    LightningSprite::loadMissionLayer((Layer*)mission);
    this->addChild(mission,2);
    
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
}

void HelloWorld::modifyLocalVariable(){
    panel->setLocalZOrder(2);
}

void HelloWorld::modifyButtonEvent(){
    btnPanel_Start->addTouchEventListener(CC_CALLBACK_2(HelloWorld::callBackButton, this));
    btnPanel_Reset->addTouchEventListener(CC_CALLBACK_2(HelloWorld::callBackButton, this));
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
                    
                default:
                    break;
            }
            
            
            break;
        }
            
        default:
            break;
    }
}

