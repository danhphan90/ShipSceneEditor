//
//  LightningSprite.cpp
//  Ship
//
//  Created by KuKulKan on 8/17/16.
//
//

#include "LightningSprite.hpp"


static bool isLoad = false;
static Vector<LightningSprite*> vecLightning[2];

static Vector<LightningSprite*> vecLightningMoving;
static Vector<LightningSprite*> vecReleaseLightning;

static Layer* missionLayer;


void LightningSprite::ReleaseAllObject(){
    vecReleaseLightning.clear();
}
void LightningSprite::loadMissionLayer(cocos2d::Layer *_layer){
    missionLayer = _layer;
}

void LightningSprite::loadResource(){
    if (!isLoad){
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("CustomSprite/Lightning.plist");
        for(int i = 0; i < 50;i++){
            vecLightning[(int)LightningClass::forEnemy].pushBack(LightningSprite::createLightning(LightningClass::forEnemy));
        }
        
        isLoad = true;
    }
}


LightningSprite* LightningSprite::CreateLightningEffect(cocos2d::Sprite *_target, float _fromAngle, float _toAngle, float _duration,LightningClass _class){
    
    if (vecLightning[(int)_class].size()>0){
        auto sprite = vecLightning[(int)_class].at(0);
        sprite->target = _target;
        sprite->fromAngle = _fromAngle;
        sprite->toAngle = _toAngle;
        sprite->duration = _duration;
        sprite->start();
        vecLightningMoving.pushBack(sprite);
        vecLightning[(int)_class].eraseObject(sprite);
        return sprite;
    }
    
    return NULL;
}


LightningSprite* LightningSprite::createLightning(LightningClass _class){

    LightningSprite* layer = new (std::nothrow) LightningSprite();
    
    if (layer){
        
        if (layer->initLightningSprite(_class)){;
            //layer->autorelease();
        }else{
            CC_SAFE_DELETE(layer);
        }
    }
    
    return layer;
}

bool LightningSprite::initLightningSprite(LightningClass _class2){
    if (!Layer::init()){
        return false;
    }
    
    this->_class = _class2;
    this->setAnchorPoint(Vec2(0,0));
    //this->setColor(Color3B::GRAY);
    
    Vec2 tempPos = Vec2(0,0);
    this->isRecycle = true;
    
    for(int i = 0;i<6;i++){
        auto lightning = Lightning::createLightning(tempPos,_class);
        //lightning->start();
        this->lightningMember.pushBack(lightning);
        
        tempPos = tempPos + Vec2(0,lightning->getContentSize().height);
    }
    
    return true;
}

void LightningSprite::start(){
    this->isRecycle = false;
    this->sound = SimpleAudioEngine::getInstance()->playEffect("Sound/Sfx_Electro.mp3",true);
    this->setPosition(target->getPosition());
    this->setRotation(fromAngle);
    
    
    for(auto lightning : this->lightningMember){
        lightning->start();
        this->addChild(lightning);
    }
    
    auto rotate = RotateTo::create(duration, toAngle);
    auto callBackRotate = CallFuncN::create(CC_CALLBACK_0(LightningSprite::callFadeOutLightning, this));
    auto sequenceAct = Sequence::create(rotate,callBackRotate, NULL);
    
    this->runAction(sequenceAct);
    
    this->schedule(schedule_selector(LightningSprite::updatePosition), 1/32);
    
    missionLayer->addChild(this);

}

void LightningSprite::stop(float dt){
    if (!isRecycle){
        for(auto lightning : this->lightningMember){
            lightning->stopImmediately();
        }
        
        SimpleAudioEngine::getInstance()->stopEffect(sound);
        
        this->unscheduleAllCallbacks();
        this->stopAllActions();
        this->removeFromParent();
        target = NULL;
        vecLightning[(int)_class].pushBack(this);
        vecLightningMoving.eraseObject(this);
        isRecycle = true;
    }
    
    
}

void LightningSprite::updatePosition(float dt){
    if (target){
        this->setPosition(target->getPosition());
    }
}

void LightningSprite::callFadeOutLightning(){
    for(auto lightning : this->lightningMember){
        lightning->startFadeOut();
    }

    SimpleAudioEngine::getInstance()->stopEffect(sound);
    scheduleOnce(schedule_selector(LightningSprite::stop), 1.1);
}
