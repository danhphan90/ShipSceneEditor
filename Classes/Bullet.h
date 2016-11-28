#ifndef _BULLET_H_
#define  _BULLET_H_

#include "cocos2d.h"
#include "EnumManager.h"
//#include "Mission.h"

USING_NS_CC;

class Bullet : public Sprite
{
public:
    
    PhysicsBody* body;
    int dmg;
    
    bool isLazerBullet;
    bool isRecycle;
    
    Vec2 vectorMove;
    BulletType bulletType;
    
    
    static void setMissionLayer(Layer* _layer);
    
    static void loadBullet();
    static void reloadBullet();
    static Vector<Bullet*> getArrBullet(int _index);
    static Vector<Bullet*> getArrBulletMoving();
    
    static void createBulletAtPos(Vec2 _pos, float _angle, float _speed, BulletType _bulletType);
    
    static Bullet* createBulletWithType(BulletType _bulletType);
    bool initBulletWithType(BulletType _bulletType);
    
    virtual void SetLazerFacing(float _angle);
    virtual void move();
    virtual void start();
    virtual void stop();
    
    
};


class NormalBullet : public Bullet
{
public:
    
    CC_SYNTHESIZE(RepeatForever*, animate, bulletAnimate);
    static NormalBullet* createNormalBulletWithType(BulletType _bulletType);
    bool initNormalBulletWithType(BulletType _bulletType);
    virtual void start();
    virtual void stop();
    
private:
    
};

class LazerBullet : public Bullet
{
public:
    
    static LazerBullet* createLazerBulletWithType(BulletType _bulletType);
    bool initLazerBulletWithType(BulletType _bulletType);
    
    virtual void SetLazerFacing(float _angle);
    virtual void start();
    virtual void stop();
private:
    
};
#endif