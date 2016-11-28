
#include "Bullet.h"
#define  MAX_AMOUNT_BULLET_PER_TYPE 50

static bool bulletIsLoad = false;
static Vector<Bullet*> arrBulletWaiting[10];
static Vector<Bullet*> arrBulletMoving;
static Layer* missonLayer;


void Bullet::setMissionLayer(Layer* _layer){
    missonLayer = _layer;
}
Vector<Bullet*> Bullet::getArrBullet(int _index){
    return arrBulletWaiting[_index];
}


Vector<Bullet*> Bullet::getArrBulletMoving()
{
    return arrBulletMoving;
}


void Bullet::createBulletAtPos(Vec2 _pos, float _angle, float _speed, BulletType _bulletType)
{
    if (arrBulletWaiting[(int)_bulletType].size() > 0){
        auto tempBullet = arrBulletWaiting[(int)_bulletType].at(0);
        
        tempBullet->setPosition(_pos);

        tempBullet->vectorMove.x = _speed*cos(CC_DEGREES_TO_RADIANS(_angle));
        tempBullet->vectorMove.y = _speed*sin(CC_DEGREES_TO_RADIANS(_angle));
        tempBullet->start();
        
        
        if (tempBullet->isLazerBullet){
            tempBullet->SetLazerFacing(_angle);
        }
        
        arrBulletWaiting[(int)_bulletType].eraseObject(tempBullet);
        arrBulletMoving.pushBack(tempBullet);
        
       // return tempBullet;
    }
    
   // return nullptr;
}


void Bullet::loadBullet()
{
    if (!bulletIsLoad){
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/EnemyBullet.plist");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Bullet/Lazer.plist");
        
        
        for (int i = 0; i < 500; i++){
            arrBulletWaiting[0].pushBack((NormalBullet::createNormalBulletWithType(BulletType::RED_SMALL)));
            arrBulletWaiting[1].pushBack(NormalBullet::createNormalBulletWithType(BulletType::RED_MEDIUM));
            arrBulletWaiting[2].pushBack(NormalBullet::createNormalBulletWithType(BulletType::RED_LARGE));
            arrBulletWaiting[3].pushBack(NormalBullet::createNormalBulletWithType(BulletType::RED_EXTRA));
            arrBulletWaiting[4].pushBack(NormalBullet::createNormalBulletWithType(BulletType::GREEN_SMALL));
            arrBulletWaiting[5].pushBack(NormalBullet::createNormalBulletWithType(BulletType::GREEN_MEDIUM));
            arrBulletWaiting[6].pushBack(NormalBullet::createNormalBulletWithType(BulletType::GREEN_LARGE));
            arrBulletWaiting[7].pushBack(NormalBullet::createNormalBulletWithType(BulletType::GREEN_EXTRA));
            arrBulletWaiting[8].pushBack(LazerBullet::createLazerBulletWithType(BulletType::LAZER_RED));
            arrBulletWaiting[9].pushBack(LazerBullet::createLazerBulletWithType(BulletType::LAZER_NONRED));
        }
        bulletIsLoad = true;
    }
}

void Bullet::reloadBullet()
{
    Vector<Bullet*> arrEnemyBulletTemp;
    
    for (Bullet* bullet : arrBulletMoving)
    {
        arrEnemyBulletTemp.pushBack(bullet);
    }
    
    for (Bullet* bullet : arrEnemyBulletTemp)
    {
        bullet->stop();
    }
    
    arrEnemyBulletTemp.clear();
    
}

Bullet* Bullet::createBulletWithType(BulletType _bulletType)
{
    auto bullet = new (std::nothrow) Bullet();
    
    if (bullet){
        if (bullet->initBulletWithType(_bulletType)){
            bullet->autorelease();
        }
        else{
            delete bullet;
            bullet = nullptr;
        }
    }
    return bullet;
}

bool Bullet::initBulletWithType(BulletType _bulletType)
{
    if (!Sprite::init()){
        return false;
    }
    
    this->isLazerBullet = false;
    this->bulletType = _bulletType;
    
    return true;
}

void Bullet::SetLazerFacing(float _angle)
{
    
}

void Bullet::move()
{
    this->setPosition(this->getPosition() + vectorMove);
}

void Bullet::start()
{
    this->setVisible(true);
}

void Bullet::stop()
{
    this->setVisible(false);
    arrBulletWaiting[(int)bulletType].pushBack(this);
    arrBulletMoving.eraseObject(this, false);
}






//Implement class NormalBullet
//Implement class NormalBullet
//Implement class NormalBullet

NormalBullet* NormalBullet::createNormalBulletWithType(BulletType _bulletType)
{
    auto normalBullet = new (std::nothrow) NormalBullet();
    
    if (normalBullet){
        if (normalBullet->initNormalBulletWithType(_bulletType)){
            normalBullet->autorelease();
        }
        else
        {
            delete normalBullet;
            normalBullet = nullptr;
        }
    }
    return normalBullet;
}

bool NormalBullet::initNormalBulletWithType(BulletType _bulletType)
{
    if (!Bullet::initBulletWithType(_bulletType)){
        return false;
    }
    
    __String bulletSpriteName;
    switch (_bulletType)
    {
        case BulletType::RED_SMALL:
            bulletSpriteName = "EnemyBulletA";
            dmg = 5;
            break;
        case BulletType::RED_MEDIUM:
            bulletSpriteName = "EnemyBulletB";
            dmg = 10;
            break;
        case BulletType::RED_LARGE:
            bulletSpriteName = "EnemyBulletC";
            dmg = 15;
            break;
        case BulletType::RED_EXTRA:
            bulletSpriteName = "EnemyBulletD";
            dmg = 20;
            break;
        case BulletType::GREEN_SMALL:
            bulletSpriteName = "EnemyBulletXA";
            dmg = 10;
            break;
        case BulletType::GREEN_MEDIUM:
            bulletSpriteName = "EnemyBulletXB";
            dmg = 15;
            break;
        case BulletType::GREEN_LARGE:
            bulletSpriteName = "EnemyBulletXC";
            dmg = 20;
            break;
        case BulletType::GREEN_EXTRA:
            bulletSpriteName = "EnemyBulletXD";
            dmg = 25;
            break;
            
        default:
            bulletSpriteName = "EnemyBulletD";
            dmg = 20;
            break;
    }
    
    Vector<SpriteFrame*> vecFrame;
    for (int i = 9; i > 0;i--)
    {
        char spriteName[20] = { 0 };
        sprintf(spriteName, "%s%d.png", bulletSpriteName.getCString(), i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName);
        vecFrame.pushBack(frame);
    }
    
    for (int i = 1; i < 10; i++)
    {
        char spriteName[20] = { 0 };
        sprintf(spriteName, "%s%d.png", bulletSpriteName.getCString(), i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteName);
        vecFrame.pushBack(frame);
    }
    
    auto animationSprite = Animation::createWithSpriteFrames(vecFrame, 0.05f);
    auto animateSprite = Animate::create(animationSprite);
    
    this->setScale(2);
    
    auto repeatAnimate = RepeatForever::create(animateSprite);
    
    this->setbulletAnimate(repeatAnimate);
    getbulletAnimate()->retain();
    this->setSpriteFrame(vecFrame.at(0));
    
    this->body = PhysicsBody::createBox(Size(this->_contentSize.width, this->_contentSize.height), PhysicsMaterial(0.1f, 1.0f, 0.0f));
    this->body->setDynamic(true);
    this->body->setCategoryBitmask((int)PhysicCategory::EnemyBullet);
    this->body->setCollisionBitmask((int)PhysicCategory::None);
    this->body->setContactTestBitmask((int)PhysicCategory::PlayerShip);
    this->body->retain();
    
    this->setTag((int)PhysicCategory::EnemyBullet);
    this->setVisible(false);
    
    
    return true;
}

void NormalBullet::start()
{
    missonLayer->addChild(this,2);
    this->setVisible(true);
    this->runAction(this->getbulletAnimate());
    isRecycle = false;
}

void NormalBullet::stop()
{
    if (!isRecycle){
        this->setVisible(false);
        this->stopAllActions();


        arrBulletWaiting[(int)bulletType].pushBack(this);

        arrBulletMoving.eraseObject(this,false);
        this->removeFromParent();
        isRecycle = true;
    }
    
}

//Implement class LazerBullet
//Implement class LazerBullet
//Implement class LazerBullet

LazerBullet* LazerBullet::createLazerBulletWithType(BulletType _bulletType)
{
    auto lazerBullet = new (std::nothrow) LazerBullet();
    
    if (lazerBullet){
        if (lazerBullet->initLazerBulletWithType(_bulletType)){
            lazerBullet->autorelease();
        }
        else
        {
            delete lazerBullet;
            lazerBullet = nullptr;
        }
    }
    return lazerBullet;
}

bool LazerBullet::initLazerBulletWithType(BulletType _bulletType)
{
    if (!Bullet::initBulletWithType(_bulletType)){
        return false;
    }
    
    __String bulletSpriteName;
    
    switch (_bulletType)
    {
        case BulletType::LAZER_RED:
            bulletSpriteName = "bulletLazerA.png";
            dmg = 10;
            break;
        case BulletType::LAZER_NONRED:
            bulletSpriteName = "bulletLazerB.png";
            dmg = 20;
            break;
        default:
            bulletSpriteName = "bulletLazerA.png";
            dmg = 10;
            break;
    }
    this->isLazerBullet = true;
    this->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(bulletSpriteName.getCString()));
    this->setVisible(false);
    
    return true;
}

void LazerBullet::SetLazerFacing(float _angle)
{
    this->setRotation(-_angle);
}

void LazerBullet::start()
{
    this->setVisible(true);
}

void LazerBullet::stop()
{
    if (!isRecycle){
        this->setVisible(false);
        arrBulletWaiting[(int)bulletType].pushBack(this);
        arrBulletMoving.eraseObject(this,false);
        isRecycle = true;
    }
}
