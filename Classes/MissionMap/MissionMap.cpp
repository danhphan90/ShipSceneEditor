#include "MissionMap.h"

//static AnimateWave* createAnimateWave(__String _unitName, int _hp, int _count, Gun* _gun, float _atkInterval, float _afterTime, int _priority, Path* _path, float _moveSpeed, float _periodTime);

bool Mission_1_::init()
{
    if (!Mission::initLevel()){
        return false;
    }
    
    this->initWave();
    
    return true;
}

static Gun* gun;
static Path* path;
static Wave* wave;

#define _count 20
#define _atkInterval 1
#define _moveSpeed 160
#define _periodTime 0.4


void Mission_1_::initWave()
{
    int priority = 0;
    
    ///////////      WAVE 1
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathReturn::createAt_Y(0.7, 0.6, 100, 400, PathDirection::LeftToRight);
    wave = NonAnimateWave::createNonAnimateWave("FleaWing", 100, _count, gun, _atkInterval, 0, priority++, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    ///////////      WAVE 2
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathReturn::createAt_Y(0.7, 0.6, 100, 400, PathDirection::RightToLeft);
    wave = NonAnimateWave::createNonAnimateWave("FleaTie", 100, _count, gun, _atkInterval, 0, priority++, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    ///////////      WAVE 3
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathAcross::createAt_Y(0.8, 0.8, PathDirection::LeftToRight);
    wave = NonAnimateWave::createNonAnimateWave("FleaWing", 100, _count, gun, _atkInterval, 0, priority, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathAcross::createAt_Y(0.7, 0.7, PathDirection::LeftToRight);
    wave = NonAnimateWave::createNonAnimateWave("FleaWing", 100, _count, gun, _atkInterval, 0, priority, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathAcross::createAt_Y(0.6, 0.6, PathDirection::LeftToRight);
    wave = NonAnimateWave::createNonAnimateWave("FleaWing", 100, _count, gun, _atkInterval, 0, priority++, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    ///////////      WAVE 4
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathAcross::createAt_Y(0.8, 0.8, PathDirection::RightToLeft);
    wave = NonAnimateWave::createNonAnimateWave("FleaTie", 100, _count, gun, _atkInterval, 0, priority, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathAcross::createAt_Y(0.7, 0.7, PathDirection::RightToLeft);
    wave = NonAnimateWave::createNonAnimateWave("FleaTie", 100, _count, gun, _atkInterval, 0, priority, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathAcross::createAt_Y(0.6, 0.6, PathDirection::RightToLeft);
    wave = NonAnimateWave::createNonAnimateWave("FleaTie", 100, _count, gun, _atkInterval, 0, priority++, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    ///////////      WAVE 5
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathAcross::createAt_Y(0.6, 0.6, PathDirection::LeftToRight);
    wave = NonAnimateWave::createNonAnimateWave("FleaWing", 100, _count, gun, _atkInterval, 0, priority, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathAcross::createAt_Y(0.5, 0.5, PathDirection::LeftToRight);
    wave = NonAnimateWave::createNonAnimateWave("FleaTie", 100, _count, gun, _atkInterval, 0, priority, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathAcross::createAt_Y(0.4, 0.4, PathDirection::LeftToRight);
    wave = NonAnimateWave::createNonAnimateWave("FleaWing", 100, _count, gun, _atkInterval, 0, priority, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    gun = GunLightning::createGunLightning(3);
    path = PathAcross::createAt_Y(1, 0, PathDirection::LeftToRight);
    wave = SpecialWave::createSpecialWave("EnergiserEA", 100*5, 1, gun, 3, 0, 1, path, 30, 0,20,TypeCoin::typeGoldCoin);
    this->arrWave.pushBack(wave);
    
    
    ///////////      WAVE 6
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathAcross::createAt_Y(0.6, 0.6, PathDirection::RightToLeft);
    wave = NonAnimateWave::createNonAnimateWave("FleaTie", 100, _count, gun, _atkInterval, 0, priority, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathAcross::createAt_Y(0.5, 0.5, PathDirection::RightToLeft);
    wave = NonAnimateWave::createNonAnimateWave("FleaWing", 100, _count, gun, _atkInterval, 0, priority, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    gun = NormalGun::createNormalGunWithShootingPerAngle(30, BulletType::RED_SMALL);
    path = PathAcross::createAt_Y(0.4, 0.4, PathDirection::RightToLeft);
    wave = NonAnimateWave::createNonAnimateWave("FleaTie", 100, _count, gun, _atkInterval, 0, priority, path, _moveSpeed, _periodTime);
    this->arrWave.pushBack(wave);
    
    gun = GunLightning::createGunLightning(3);
    path = PathAcross::createAt_Y(1, 0, PathDirection::RightToLeft);
    wave = SpecialWave::createSpecialWave("EnergiserEA", 100*5, 1, gun, 3, 0, priority++, path, 30, 0,20,TypeCoin::typeGoldCoin);
    
    this->arrWave.pushBack(wave);
    
    for (auto wave : this->arrWave){
        this->addChild(wave);
    }
    
}

