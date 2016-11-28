//
//  Boss.cpp
//  Ship
//
//  Created by KuKulKan on 7/29/16.
//
//

#include "Boss.hpp"
static Boss* staticBoss = NULL;


Boss* Boss::getCurrentBoss(){
    return staticBoss;
}

void Boss::setCurrentBoss(Boss *_boss){
    staticBoss = _boss;
}

bool Boss::initBoss(__String _path, int _hp){
    
    if (!this->Sprite::init()){
        return false;
    }
    
    auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(_path.getCString());
    
    this->setSpriteFrame(frame);
    this->maxHp = _hp;
    this->hp = this->maxHp;
    this->invunerable = true;
    
    float sizeW = Director::getInstance()->getWinSize().width;
    float sizeH =Director::getInstance()->getWinSize().height;
    
    this->setPosition(Vec2(sizeW/2,sizeH + this->getContentSize().height));
    
    return true;
}

void Boss::clear(){
    
}


