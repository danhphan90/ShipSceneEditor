#include "Unit.h"

static bool unitToFrameCache = false;
static Vector<Unit*> arrUnitCurrentOnMap;
static Vector<Unit*> arrReleaseUnit;
static Vector<RepeatForever*> arrReleaseAnimateAct;
static Layer* missionLayer;
static SpriteFrameCache* spriteCache;

void Unit::setMissionLayer(cocos2d::Layer *_layer){
    missionLayer = _layer;
}

Vector<RepeatForever*> Unit::getArrReleaseAnimate(){
    return arrReleaseAnimateAct;
}

Vector<Unit*> Unit::getArrReleaseUnit(){
    return arrReleaseUnit;
}
void Unit::loadResource(){
    if (!unitToFrameCache){
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Enemy/EnemySprite.plist");
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Enemy/BossSprite.plist");
        
        spriteCache = SpriteFrameCache::getInstance();
        unitToFrameCache = true;
    }
}

Unit* Unit::CreateUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown, Path* _path, float _moveSpeed){
    
    auto unit = new (std::nothrow) Unit();
    
    if (unit){
        if (unit->initUnit(_name,_hp,_gun,_atkCooldown,_path,_moveSpeed,false)){
        }
        else{
            delete unit;
            unit = nullptr;
        }
        
        return unit;
    }
    
    return unit;
    
}


bool Unit::initUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown, Path* _path, float _moveSpeed,bool _animate)
{
    if (!Sprite::init()){
        return false;
    }
    
    this->currentNodePath = 0;
    this->state = UnitState::Alive;
    this->maxHp = _hp;
    this->hp = maxHp;
    this->startingPoint = _path->arrVector.at(0)->point;
    this->atkCooldown = _atkCooldown;
    this->facing = 0;
    this->mainGun = _gun;
    this->animate = NULL;
    this->orderAttack = false;
    this->attackElapseTime = 0;
    this->vecFrame.clear();
    this->unitName = _name;
    this->isAnimate = _animate;
    this->isCleared = false;
    this->isSpecialUnit = false;
    this->setScale(1.3);
    
    if (_animate){
        for (int i = 0; i <= 15; i++){
            this->vecFrame.reserve(30);
            char name[40] = { 0 };
            sprintf(name, "%s%d.png", _name.getCString(), i);;
            auto sprite = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
            this->vecFrame.pushBack(sprite);
        }
        
        this->setSpriteFrame(this->vecFrame.at(0));
    }else{
        char name[40] = { 0 };
        sprintf(name, "%s%d.png", unitName.getCString(), 0);;
        this->setSpriteFrame(name);
    }
    
    this->didFinishMove = CallFuncN::create(CC_CALLBACK_0(Unit::didFinishPath,this));
    this->didFinishMove->retain();
    
    
    //this->setScale(1.5);
       return true;
}



void Unit::setUnitFacing(float _angle, bool _radian)
{
    float angle;
    if (_radian){
        angle = CC_RADIANS_TO_DEGREES(_angle);
    }
    else{
        angle = _angle;
    }
    
    //CCLOG("%f", angle);
    if (angle < 0){ //Neu goc < 0 tuc la nam trong khoang 0 -> -180 theo chieu trai qua phai, ta chuyen ve goc do duong theo chieu kim dong ho 0 -> 360
        angle*= -1;
        angle += 270;
    }
    else
    {
        angle = 270 - angle; //Neu goc > 0 tuc la nam trong khoang 0 -> 180 theo chieu trai qua phai, ta chuyen ve goc do duong theo chieu kim dong ho 0 -> 360
    }
    //CCLOG("%f", angle);
    while (angle>360)
    {
        angle -= 360;          //Goc phai luon nam trong khoang 0 -> 360 de khi tinh ra index khong bi sai
    }
    //CCLOG("%f", angle);
    int index = angle / 22.5;
    //CCLOG("%f", index);
    float nearbyAngle = index * 22.5;
    
    if (angle - nearbyAngle >= 11.25){
        index++;
    }
    if (index >= 16) {
        index = 0;
    }
    
    this->setFacing(index * 22.5 - 90);
    
    if (!this->isAnimate){
        char name[40] = { 0 };
        sprintf(name, "%s%d.png", unitName.getCString(), index);;
        this->setSpriteFrame(name);
    }
    //this->setSpriteFrame(this->vecFrame.at(index));
}

Vector<Unit*> Unit::getArrUnitCurrentOnMap()
{
    return arrUnitCurrentOnMap;
}

void Unit::startAttack()
{
    this->orderAttack = true;
    //this->schedule(schedule_selector(Unit::attack), atkCooldown, CC_REPEAT_FOREVER,1);
}

void Unit::attack(float dt)
{
    if (getState() == UnitState::Dead){return;}
    
    if (this->orderAttack){
        if (this->attackElapseTime >= this->getAtkCoolDown()){
            if (this->mainGun->bulletType == BulletType::LIGHTNING){
                this->mainGun->fire(this);
            }else{
                this->mainGun->fire(this->getPosition(), facing);
                //SimpleAudioEngine::getInstance()->playEffect("Sound/Sfx_EnemyBulletShoot.mp3",false);
            }
            this->attackElapseTime = 0;
        }else{
            this->attackElapseTime+= dt;
        }
    }
}

void Unit::didFinishPath()
{
    this->state = UnitState::Dead;
    
}

void Unit::start()
{
    this->runAction(moveActions);
    if (animate != NULL){
        this->runAction(animate);
    }
    this->startAttack();
    this->setVisible(true);
    arrUnitCurrentOnMap.pushBack(this);
    missionLayer->addChild(this,1);
}


void Unit::clear()
{
    if (!isCleared){
        for(auto bullet : this->mainGun->vecLightningBullet){
            bullet->stop(0);
        }
        this->mainGun->vecLightningBullet.clear();
        
        this->stopAllActions();
        this->unscheduleAllCallbacks();

        
        this->orderAttack = false;
        

        CC_SAFE_RELEASE_NULL(this->moveActions);
        if (this->isAnimate){
            vecFrame.clear();
            CC_SAFE_RELEASE_NULL(this->animate);
            //arrReleaseAnimateAct.pushBack(this->animate);
        }
        CC_SAFE_RELEASE_NULL(this->didFinishMove);
        CC_SAFE_RELEASE_NULL(this->mainGun);
        
        arrUnitCurrentOnMap.eraseObject(this);
        this->removeFromParent();
        
        isCleared = true;
    }
}

int Unit::getUnitHp()
{
    return this->hp;
}



Unit* AnimateUnit::CreateAnimateUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown, Path* _path, float _moveSpeed)
{
    auto unit = new (std::nothrow) AnimateUnit();
    
    if (unit){
        if (unit->initAnimateUnit(_name, _hp, _gun, _atkCooldown, _path, _moveSpeed)){
            unit->autorelease();
        }
        else
        {
            delete unit;
            unit = nullptr;
        }
    }
    
    return unit;
}

bool AnimateUnit::initAnimateUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown, Path* _path, float _moveSpeed)
{
    if (!Unit::initUnit(_name, _hp, _gun, _atkCooldown, _path, _moveSpeed,true)){
        return false;
    }
    
    auto animation = Animation::createWithSpriteFrames(vecFrame, 0.09f);
    auto animate = Animate::create(animation);
    
    this->animate = RepeatForever::create(animate);
    this->animate->retain();
    
    int nextNodePath = this->currentNodePath + 1;
    Vector<FiniteTimeAction*> arrMoveAction;
    
    Vector<Unit*> vec;
    
    while (nextNodePath < _path->arrVector.size())
    {
        Vec2 currentPoint = _path->arrVector.at(currentNodePath)->point;
        Vec2 nextPoint = _path->arrVector.at(nextNodePath)->point;
        float distance = currentPoint.getDistance(nextPoint);
        float duration = distance / _moveSpeed;
        
        arrMoveAction.pushBack(MyMoveTo::create(duration, nextPoint));
        
        currentNodePath++;
        nextNodePath = currentNodePath + 1;
    }
    
//    for(auto point : _path->arrVector){
//        point->release();
//    }
//    
//    _path->arrVector.clear();
    
    auto makeActionMove = Sequence::create(arrMoveAction);
    this->moveActions = Sequence::createWithTwoActions(makeActionMove,didFinishMove);
    this->moveActions->retain();
    
    return true;
}

Unit* NonAnimateUnit::CreateNonAnimateUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown, Path* _path, float _moveSpeed)
{
    auto unit = new (std::nothrow) NonAnimateUnit();
    
    if (unit){
        if (unit->initNonAnimateUnit(_name, _hp, _gun, _atkCooldown, _path, _moveSpeed)){
            unit->autorelease();
        }
        else
        {
            delete unit;
            unit = nullptr;
        }
    }
    
    return unit;
}

bool NonAnimateUnit::initNonAnimateUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown, Path* _path, float _moveSpeed)
{
    if (!Unit::initUnit(_name, _hp, _gun, _atkCooldown, _path, _moveSpeed,false)){
        return false;
    }
    
    int nextNodePath = this->currentNodePath + 1;
    Vector<FiniteTimeAction*> arrMoveAction;
    
    while (nextNodePath < _path->arrVector.size())
    {
        Vec2 currentPoint = _path->arrVector.at(currentNodePath)->point;
        Vec2 nextPoint = _path->arrVector.at(nextNodePath)->point;
        float distance = currentPoint.getDistance(nextPoint);
        float duration = distance / _moveSpeed;
        
        arrMoveAction.pushBack(MyMoveTo::create(duration, nextPoint));
        
        currentNodePath++;
        nextNodePath = currentNodePath + 1;
    }
    
//    for(auto point : _path->arrVector){
//        point->release();
//    }
//    
//    _path->arrVector.clear();
    
    auto makeActionMove = Sequence::create(arrMoveAction);
    this->moveActions = Sequence::createWithTwoActions(makeActionMove, didFinishMove);
    this->moveActions->retain();
    
    return true;
}


Unit* SpecialUnit::CreateSpecialUnit(cocos2d::__String _name, int _hp, Gun *_gun, float _atkCooldown, Path *_path, float _moveSpeed, int _countItem, TypeCoin _typeCoin){
    
    auto unit = new (std::nothrow) SpecialUnit();
    
    if (unit){
        if (unit->initSpecialUnit(_name, _hp, _gun, _atkCooldown, _path, _moveSpeed, _countItem, _typeCoin)){
            unit->autorelease();
        }
        else
        {
            delete unit;
            unit = nullptr;
        }
    }
    
    return unit;
}

bool SpecialUnit::initSpecialUnit(cocos2d::__String _name, int _hp, Gun *_gun, float _atkCooldown, Path *_path, float _moveSpeed, int _countItem, TypeCoin _typeCoin){
    
    if (!AnimateUnit::initAnimateUnit(_name, _hp, _gun, _atkCooldown, _path, _moveSpeed)){
        return false;
    }
    
    this->countItemDrop = _countItem;
    this->typeCoin = typeCoin;
    this->isSpecialUnit = true;
    
    return true;
}



