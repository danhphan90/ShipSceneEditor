#ifndef _GUN_H_
#define  _GUN_H_

#include "cocos2d.h"
#include "EnumManager.h"
#include "LightningSprite.hpp"
#include "Bullet.h"
USING_NS_CC;

class Gun : public Layer
{
public:
    Vec2 attackerPos;
    Vector<LightningSprite*> vecLightningBullet;
    BulletType bulletType;
    
    float angle;
    
    static Gun* createGun(BulletType _bulletType);
    
    bool initGun(BulletType _bulletType);
    
    virtual void fire(Vec2 _attackerPos, float angle);
    virtual void fire(Vec2 _attackerPos);
    virtual void fire(Sprite* _caster);
    virtual Gun* clone();
};




class NormalGun : public Gun
{
public:
    float addAngle;
    
    static NormalGun* createNormalGunWithShootingPerAngle(float _addAngle, BulletType _bulletType);
    bool initNormalGunWithShootingPerAngle(float _addAngle, BulletType _bulletType);
    
    void fire(Vec2 _attackerPos, float _angle);
    NormalGun* clone();
};

class AOEGun : public Gun
{
public:
    float perAngle;
    
    static AOEGun* createAOEGunWithShootingPerAngle(float _perAngle, BulletType _bulletType);
    bool initAOEGunWithShootingPerAngle(float _perAngle, BulletType _bulletType);
    
    void fire(Vec2 _attackerPos, float _angle);
    
};

class LazerGunAOE : public AOEGun
{
public:
    static LazerGunAOE* createLazerGunAOEWithShootingPerAngle(float _perAngle, BulletType _bulletType);
    bool initLazerGunAOEWithShootingPerAngle(float _perAngle, BulletType _bulletType);
    
    void fire(Vec2 _attackerPos, float _angle);
};

class GunHarasBot : public Gun
{
public:
    int count;
    float addAngle;
    
    static GunHarasBot* createGunHarasBotWithNDirection(int _count, float _addAngle,BulletType _bulletType);
    bool initGunHarasBotWithNDirection(int _count, float _addAngle, BulletType _bulletType);
    
    void fire(Vec2 _attackerPos);
};

class GunLightning : public Gun{
public:
    int countDirection;
    
    static GunLightning* createGunLightning(int _countDirection);
    bool initGunLightning(int _countDirection);
    void fire(Sprite* _caster);
    
    GunLightning* clone();
};
#endif