//
//  Lightning.cpp
//  Ship
//
//  Created by KuKulKan on 8/17/16.
//
//

#include "Lightning.hpp"

Lightning* Lightning::createLightning(cocos2d::Vec2 _pos,LightningClass _class){
    Lightning* lightning = new (std::nothrow) Lightning();
    
    if (lightning){
        if (lightning->initLightning(_pos,_class)){
            //lightning->autorelease();
        }else{
            CC_SAFE_DELETE(lightning);
        }
    }
    
    return lightning;
}

bool Lightning::initLightning(cocos2d::Vec2 _pos,LightningClass _class){
    
    if (!Sprite::init()){
        return false;
    }
    
    Vector<SpriteFrame*> vecFrame;
    for (int i = 1; i < 7; i++){
        auto _name = __String::createWithFormat("%i.png",i);
        vecFrame.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(_name->getCString()));
        
    }
    
    auto animationFrame = Animation::createWithSpriteFrames(vecFrame,0.08);
    auto animateFrame = Animate::create(animationFrame);
    this->animation = RepeatForever::create(animateFrame);
    this->animation->retain();
    
    this->setSpriteFrame(vecFrame.at(0));
    this->fadeOut = FadeOut::create(1);
    this->fadeOut->retain();
    
    this->setAnchorPoint(Vec2(0.5,0));
    
    this->setPosition(_pos);
    pos = _pos;
    
    //this->setColor(Color3B::YELLOW);
    
    isRecycle = false;
    
    return true;
}

void Lightning::start(){
    if (!isRecycle){
        isRecycle = true;
        this->setOpacity(255); //If not, this sprite seem to disapear from layer because it's invisible due to opacity = 0.
        
        this->dmg = 50;
        this->setPosition(pos);
        this->runAction(animation);
    }
}

void Lightning::stop(){
    
}

void Lightning::stopImmediately(){
    if (isRecycle){
        this->stopAllActions();
        this->removeFromParent();
        isRecycle = false;
    }
}

void Lightning::startFadeOut(){
    
    auto callBackFadeOut = CallFuncN::create(CC_CALLBACK_0(Lightning::callBackFadeOut, this));
    
    auto sequenceAct = Sequence::create(fadeOut,callBackFadeOut, NULL);
    
    this->runAction(sequenceAct);
}

void Lightning::callBackFadeOut(){
    if (isRecycle){
        this->stopAllActions();
        this->removeFromParent();
        isRecycle = false;
    }
}
