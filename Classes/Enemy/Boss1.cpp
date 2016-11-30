//
//  Boss1.cpp
//  Ship
//
//  Created by KuKulKan on 7/29/16.
//
//

#include "Boss1.hpp"

Boss1* Boss1::createBoss(int _hp){
    
    auto boss = new (std::nothrow) Boss1();
    
    if (boss->initBoss1(_hp)){
    }else{
        CC_SAFE_DELETE(boss);
    }
    
    return boss;
    
}

bool Boss1::initBoss1(int _hp){
    
    if (!Boss::initBoss("Boss1.png", _hp)){
        return false;
    }
    
    this->countItem = 20;
    
    this->mainWeapon = GunHarasBot::createGunHarasBotWithNDirection(11, 6, BulletType::RED_EXTRA);
    this->superWeapon = AOEGun::createAOEGunWithShootingPerAngle(20, BulletType::GREEN_EXTRA);
    
    this->largeWeapon = AOEGun::createAOEGunWithShootingPerAngle(30, BulletType::RED_MEDIUM);
    //body = PhysicsBody::createCircle(this->getContentSize().width/3, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    this->start();
    
    return true;
}

void Boss1::start(){
    
    float sizeW = 640;
    float sizeH = 960;
    
    this->initPosition = Vec2(sizeW/2,sizeH-this->getContentSize().height*2.5);
    auto moveToCenter = MoveTo::create(5, this->initPosition);
    
    this->runAction(moveToCenter);
    this->scheduleOnce(schedule_selector(Boss1::startAttack), 8);
    
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("Sound/Sfx_EnemyBossSiren.mp3",false);
    
}

void Boss1::startAttack(float dt){
    float sizeW = Director::getInstance()->getWinSize().width;
    //float sizeH =Director::getInstance()->getWinSize().height;
    
    this->invunerable = false;
    
    auto jump1 = JumpTo::create(2, Vec2(sizeW*0.2,this->getPositionY()), 150, 1);
    
    auto jump2 = JumpTo::create(2, Vec2(sizeW*0.4,this->getPositionY()), 100, 1);
    
    auto jump3 = JumpTo::create(2, Vec2(sizeW*0.5,this->getPositionY()), 150, 1);
    
    auto jump4 = JumpTo::create(2, Vec2(sizeW*0.6,this->getPositionY()), 100, 1);
    
    auto jump5 = JumpTo::create(2, Vec2(sizeW*0.8,this->getPositionY()), 150, 1);
    
    
    
    auto fire1 = CallFuncN::create(CC_CALLBACK_0(Boss1::mainFire, this));
    auto fire2 = CallFuncN::create(CC_CALLBACK_0(Boss1::superFire, this));
    auto fire3 = CallFuncN::create(CC_CALLBACK_0(Boss1::largeFire, this));
    
    auto listAction = Sequence::create(jump2,fire1,jump1,fire2,jump2,fire1,jump3,fire2,jump4,fire1,jump5,fire2,jump4,fire1,jump3,fire2, NULL);
    
    
    auto move1 = MoveTo::create(0.5, Vec2(this->getPositionX(),this->getPositionY()-100));
    
    auto move2 = MoveTo::create(0.5, Vec2(this->getPositionX(),this->getPositionY()-200));
    
    auto move3 = MoveTo::create(0.5, Vec2(this->getPositionX(),this->getPositionY()-300));
    
    auto move4 = MoveTo::create(0.5, Vec2(this->getPositionX(),this->getPositionY()-400));
    
    auto move5 = MoveTo::create(2, this->initPosition);
    
    
    
    auto listAction2 = Sequence::create(move1,fire3,move2,fire3,move3,fire3,move4,fire3,move5, NULL);
    
    auto delay1 = DelayTime::create(1);
    auto delay2 = DelayTime::create(1);
    
    auto compileAction = Sequence::create(listAction,delay1, listAction2,delay2, NULL);
    
    auto repeatAction = RepeatForever::create(compileAction);
    
    this->runAction(repeatAction);
    
}


static Vec2 gunPos;

void Boss1::mainFire(){
    gunPos.x = 0;
    gunPos.y = this->getContentSize().height*0.6;
    this->mainWeapon->fire(this->getPosition() + gunPos);
}

void Boss1::superFire(){
    gunPos.x = 0;
    gunPos.y = this->getContentSize().height*0.6;
    this->superWeapon->fire(this->getPosition() + gunPos,15);
    
}

void Boss1::largeFire(){
    gunPos.x = 0;
    gunPos.y = this->getContentSize().height*0.6;
    
    this->largeWeapon->fire(this->getPosition() + gunPos,15);
    
}

void Boss1::clear(){
    this->stopAllActions();
    
    CC_SAFE_RELEASE_NULL(mainWeapon);
    CC_SAFE_RELEASE_NULL(superWeapon);
    CC_SAFE_RELEASE_NULL(largeWeapon);
    this->removeFromParent();
    Boss::setCurrentBoss(NULL);
    this->release();
}

