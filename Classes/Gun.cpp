#include "Gun.h"

//Implement class Gun
//Implement class Gun
//Implement class Gun

Gun* Gun::createGun(BulletType _bulletType)
{
    auto gun = new (std::nothrow) Gun();
    
    if (gun){
        if (gun->initGun(_bulletType)){
            //gun->autorelease();
        }
        else
        {
            delete gun;
            gun = nullptr;
        }
    }
    
    return gun;
}


bool Gun::initGun(BulletType _bulletType)
{
    if (!Layer::init()){
        return false;
    }
    
    this->bulletType = _bulletType;
    
    return true;
}

void Gun::fire(Vec2 _attackerPos, float angle){}
void Gun::fire(Vec2 _attackerPos){}
void Gun::fire(cocos2d::Sprite *_caster){}

Gun* Gun::clone()
{
    return createGun(this->bulletType);
}


//Implement class NormalGun
//Implement class NormalGun
//Implement class NormalGun

NormalGun* NormalGun::createNormalGunWithShootingPerAngle(float _addAngle, BulletType _bulletType)
{
    auto normalGun = new (std::nothrow) NormalGun();
    
    if (normalGun){
        if (normalGun->initNormalGunWithShootingPerAngle(_addAngle, _bulletType)){
            //normalGun->autorelease();
        }
        else
        {
            delete normalGun;
            normalGun = nullptr;
        }
    }
    return normalGun;
}

bool NormalGun::initNormalGunWithShootingPerAngle(float _addAngle, BulletType _bulletType)
{
    if (!Gun::initGun(_bulletType)){
        return false;
    }
    
    this->addAngle = _addAngle;
    
    return true;
}


void NormalGun::fire(Vec2 _attackerPos, float _angle)
{
    attackerPos = _attackerPos;
    angle = _angle;
    
    Bullet::createBulletAtPos(_attackerPos, _angle + addAngle, 10, bulletType);
    Bullet::createBulletAtPos(_attackerPos, _angle - addAngle, 10, bulletType);
}

NormalGun* NormalGun::clone()
{
    return createNormalGunWithShootingPerAngle(this->addAngle, this->bulletType);
}

//Implement class AOEGun
//Implement class AOEGun
//Implement class AOEGun

AOEGun* AOEGun::createAOEGunWithShootingPerAngle(float _perAngle, BulletType _bulletType)
{
    auto aoeGun = new (std::nothrow) AOEGun();
    
    if (aoeGun){
        if (aoeGun->initAOEGunWithShootingPerAngle(_perAngle, _bulletType)){
            //aoeGun->autorelease();
        }
        else
        {
            delete aoeGun;
            aoeGun = nullptr;
        }
    }
    return aoeGun;
}

bool AOEGun::initAOEGunWithShootingPerAngle(float _perAngle, BulletType _bulletType)
{
    if (!Gun::initGun(_bulletType)){
        return false;
    }
    
    this->perAngle = _perAngle;
    return true;
}

void AOEGun::fire(Vec2 _attackerPos, float _angle)
{
    int count = 360 / perAngle;
    for (int i = 0; i < count; i++){
        Bullet::createBulletAtPos(_attackerPos, perAngle*i + _angle, 5, bulletType);
    }
    
}

//Implement class LazerGunAOE
//Implement class LazerGunAOE
//Implement class LazerGunAOE

LazerGunAOE* LazerGunAOE::createLazerGunAOEWithShootingPerAngle(float _perAngle, BulletType _bulletType)
{
    auto lazerGunAOE = new (std::nothrow) LazerGunAOE();
    
    if (lazerGunAOE){
        if (lazerGunAOE->initLazerGunAOEWithShootingPerAngle(_perAngle, _bulletType)){
            //lazerGunAOE->autorelease();
        }
        else{
            delete lazerGunAOE;
            lazerGunAOE = nullptr;
        }
    }
    return lazerGunAOE;
}

bool LazerGunAOE::initLazerGunAOEWithShootingPerAngle(float _perAngle, BulletType _bulletType)
{
    if (!Gun::initGun(_bulletType)){
        return false;
    }
    this->perAngle = _perAngle;
    return true;
}

void LazerGunAOE::fire(Vec2 _attackerPos, float _angle)
{
    int count = 360 / perAngle;
    for (int i = 0; i < count; i++){
        Bullet::createBulletAtPos(_attackerPos, perAngle*i + _angle, 5, bulletType);
    }
}

//Implement class GunHarasBot
//Implement class GunHarasBot
//Implement class GunHarasBot

GunHarasBot* GunHarasBot::createGunHarasBotWithNDirection(int _count, float _addAngle, BulletType _bulletType)
{
    auto gunHarasBot = new (std::nothrow) GunHarasBot();
    
    if (gunHarasBot){
        if (gunHarasBot->initGunHarasBotWithNDirection(_count, _addAngle,_bulletType)){
            //gunHarasBot->autorelease();
        }
        else{
            delete gunHarasBot;
            gunHarasBot = nullptr;
        }
    }
    return gunHarasBot;
}

bool GunHarasBot::initGunHarasBotWithNDirection(int _count, float _addAngle, BulletType _bulletType)
{
    if (!Gun::initGun(_bulletType)){
        return false;
    }
    
    this->count = _count;
    this->addAngle = _addAngle;
    return true;
}

void GunHarasBot::fire(Vec2 _attackerPos)
{
    for (int i = 0; i < this->count; i++) {
        if (i == 0){
            Bullet::createBulletAtPos(_attackerPos, 270, 2, bulletType);
        }
        else if (i % 2 == 0){
            Bullet::createBulletAtPos(_attackerPos, 270+(i-1)*addAngle, 2, bulletType);
        }
        else{
            Bullet::createBulletAtPos(_attackerPos, 270 + i*-addAngle, 2, bulletType);
        }
    }
}

/////////////////////////////////////////////////////


GunLightning* GunLightning::createGunLightning(int _countDirection){
    auto gunLightning = new (std::nothrow) GunLightning();
    
    if (gunLightning){
        if (gunLightning->initGunLightning(_countDirection)){;
            //gunHarasBot->autorelease();
        }
        else{
            delete gunLightning;
            gunLightning = nullptr;
        }
    }
    return gunLightning;
}

bool GunLightning::initGunLightning(int _countDirection){
    if (!Gun::initGun(BulletType::LIGHTNING)){
        return false;
    }
    
    this->countDirection = _countDirection;
    return true;
    
    
}

void GunLightning::fire(cocos2d::Sprite *_caster){
    float angle = random((float)0, (float)360);
    
    for(int i = 0;i < this->countDirection;i++){
        this->vecLightningBullet.pushBack(LightningSprite::CreateLightningEffect(_caster, angle, angle + 15, 2,LightningClass::forEnemy));
        angle+= (360/countDirection);
    }
}

GunLightning* GunLightning::clone(){
    return createGunLightning(this->countDirection);
}
