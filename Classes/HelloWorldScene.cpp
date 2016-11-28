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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    mission = Mission_1_::create();
    
    Bullet::setMissionLayer((Layer*)mission);
    Unit::setMissionLayer((Layer*)mission);
    Wave::setMissionlayer((Layer*)mission);
    LightningSprite::loadMissionLayer((Layer*)mission);
    
    this->addChild(mission,1);
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
    
    
//    __Dictionary* _dic = __Dictionary::create();
//    
//    _dic->setObject(__Integer::create(5), "Point");
//    
    string filePath = FileUtils::getInstance()->getWritablePath() + "ok.plist";
//    
//    _dic->writeToFile(filePath.c_str());
    
    __Dictionary* _dic = __Dictionary::createWithContentsOfFile(filePath.c_str());
    
    log("%zd",_dic->valueForKey("Point")->intValue());
    
    this->scheduleUpdate();
    return true;
}

void HelloWorld::onEnterTransitionDidFinish(){
    Node::onEnterTransitionDidFinish();
    
    mission->start();
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


