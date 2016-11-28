#include "Wave.h"
static Layer* missionLayer;
static Vector<Wave*> vecReleaseWave;

void Wave::ReleaseWave(){
    vecReleaseWave.clear();
}

void Wave::setMissionlayer(cocos2d::Layer *_layer){
    missionLayer = _layer;
}

Wave* Wave::createWaveWithPriority(int _priority, float _delay, float _moveSpeed, float _period)
{
    Wave *wave = new (std::nothrow) Wave();
    
    if (wave){
        if (wave->init(_priority, _delay, _moveSpeed, _period)){
            wave->autorelease();
        }
        else
        {
            delete wave;
            wave = nullptr;
        }
    }
    
    return wave;
    
}

bool Wave::init(int _priority, float _delay, float _moveSpeed, float _period)
{
    if (!Layer::init()){
        return false;
    }
    
    this->priority = _priority;
    this->delay = _delay;
    this->moveSpeed = _moveSpeed;
    this->period = _period;
    this->countRemainUnitAlive = 0;
    this->bonusScore = 0;
    this->isDone = false;
    
    
    return true;
}

void Wave::start()
{
    missionLayer->addChild(this);
    
    if (delay > 0){
        this->schedule(CC_SCHEDULE_SELECTOR(Wave::moveUnit), period, CC_REPEAT_FOREVER, delay);
        this->scheduleUpdate();
    }
    else{
        this->schedule(CC_SCHEDULE_SELECTOR(Wave::moveUnit), period);
        this->scheduleUpdate();
    }
}

//void Wave::stop()
//{
//    this->unscheduleAllCallbacks();
//    for (auto movingUnit : arrUnitMoving){
//        movingUnit->recycle();
//        this->arrUnitAlive.pushBack(movingUnit);
//    }
//    
//    this->arrUnitMoving.clear();
//    
//    this->isDone = false;
//    
//    this->removeFromParent();
//    
//}

void Wave::moveUnit(float dt)
{
    if (arrUnitAlive.size() > 0){
        auto tempU = this->arrUnitAlive.at(0);
        tempU->start();
        arrUnitMoving.pushBack(tempU);
        arrUnitAlive.eraseObject(tempU);
    }
}

void Wave::update(float delta){
    Vector<Unit*> arrTemp;
    
    for (auto movingUnit : this->arrUnitMoving){
        if (movingUnit->getState() == UnitState::Dead){
            arrTemp.pushBack(movingUnit);
            lastUnitPos = movingUnit->getPosition();
            if (movingUnit->getUnitHp() > 0){
                countRemainUnitAlive++;
            }else{
                //this->bonusScore+= movingUnit->getMaxHp() * GLOBAL::GET_SCORE_FACTOR();
            }
        }
    }
    
//    for(auto rocket : Rocket::getArrRocketMoving()) {
//        auto unit = static_cast<Unit*>(rocket->target);
//        if (unit != NULL && unit->getState() == UnitState::Dead){
//            rocket->target = NULL;
//        }
//    }
    
    for (auto tempUnit : arrTemp){
        tempUnit->clear();
        this->arrUnitMoving.eraseObject(tempUnit);
        if (tempUnit->getReferenceCount() >= 1){
            Unit::getArrReleaseUnit().pushBack(tempUnit);
            //tempUnit->release();
            
            tempUnit = NULL;
        }
        
    }
    
    
    if (this->arrUnitAlive.size() == 0 && this->arrUnitMoving.size() == 0 && !isDone){
        if (countRemainUnitAlive == 0){
            //GLOBAL::SET_SCORE(bonusScore);
            //MyText::CreateAtLoc(lastUnitPos,1., __String::create("Point X 2"),MyFont::BrownGradient);
        }
        
        isDone = true;
        this->unscheduleUpdate();
        this->unschedule(CC_SCHEDULE_SELECTOR(Wave::moveUnit));
    }
    
}

void Wave::clear()
{
    vecReleaseWave.pushBack(this); //This keep wave not removed.
    
    for (auto unit : arrUnitMoving){
        unit->clear();
    }
    for (auto unit : arrUnitAlive){
        unit->clear();
    }
    
    this->arrUnitAlive.clear();
    this->arrUnitDead.clear();
    this->arrUnitMoving.clear();
    this->unscheduleAllCallbacks();
    this->unscheduleUpdate();
    this->removeFromParent();
    
}

AnimateWave* AnimateWave::createAnimateWave(__String _unitName, int _hp, int _count, Gun* _gun, float _atkInterval, float _afterTime, int _priority, Path* _path, float _moveSpeed, float _periodTime)
{
    AnimateWave* wave = new (std::nothrow) AnimateWave();
    if (wave){
        if (wave->initAnimateWave(_unitName,_hp,_count,_gun,_atkInterval,_afterTime,_priority,_path,_moveSpeed,_periodTime)){
            wave->autorelease();
            return wave;
        }
    }
    
    CC_SAFE_DELETE(wave);
    return nullptr;
}

bool AnimateWave::initAnimateWave(__String _unitName, int _hp, int _count, Gun* _gun, float _atkInterval, float _afterTime, int _priority, Path* _path, float _moveSpeed, float _periodTime)
{
    if (!Wave::init(_priority, _afterTime, _moveSpeed, _periodTime)){
        return false;
    }
    
    Vec2 startPoint = _path->arrVector.at(0)->point;
    Vec2 nextPoint = _path->arrVector.at(1)->point;
    
    float angle = (startPoint -nextPoint).getAngle();
    
    for (int i = 0; i < _count; i++)
    {
        auto unit = AnimateUnit::CreateAnimateUnit(_unitName,_hp,_gun->clone(),_atkInterval,_path,_moveSpeed);
        unit->setPosition(startPoint);
        unit->setUnitFacing(angle, true);

        this->arrUnitAlive.pushBack(unit);
        unit->setVisible(false);
    }
    
    CC_SAFE_RELEASE_NULL(_gun);
    
    return true;
}

NonAnimateWave* NonAnimateWave::createNonAnimateWave(__String _unitName, int _hp, int _count, Gun* _gun, float _atkInterval, float _afterTime, int _priority, Path* _path, float _moveSpeed, float _periodTime)
{
    NonAnimateWave* wave = new (std::nothrow) NonAnimateWave();
    if (wave){
        if (wave->initNonAnimateWave(_unitName, _hp, _count, _gun, _atkInterval, _afterTime, _priority, _path, _moveSpeed, _periodTime)){
            wave->autorelease();
            return wave;
        }
    }
    
    CC_SAFE_DELETE(wave);
    return nullptr;
}

bool NonAnimateWave::initNonAnimateWave(__String _unitName, int _hp, int _count, Gun* _gun, float _atkInterval, float _afterTime, int _priority, Path* _path, float _moveSpeed, float _periodTime)
{
    if (!Wave::init(_priority, _afterTime, _moveSpeed, _periodTime)){
        return false;
    }
    
    Vec2 startPoint = _path->arrVector.at(0)->point;
    Vec2 nextPoint = _path->arrVector.at(1)->point;
    
    float angle = (startPoint -nextPoint).getAngle();

    
    for (int i = 0; i < _count; i++)
    {
        auto unit = NonAnimateUnit::CreateNonAnimateUnit(_unitName, _hp, _gun->clone(), _atkInterval, _path, _moveSpeed);
        unit->setPosition(startPoint);
        unit->setUnitFacing(angle, true);

        this->arrUnitAlive.pushBack(unit);
        unit->setVisible(false);
    }
    
    CC_SAFE_RELEASE_NULL(_gun);
    
    return true;
}

SpecialWave* SpecialWave::createSpecialWave(cocos2d::__String _unitName, int _hp, int _count, Gun *_gun, float _atkInterval, float _afterTime, int _priority, Path *_path, float _moveSpeed, float _periodTime, int _countItem, TypeCoin _typeCoin){
    
    SpecialWave* wave = new (std::nothrow) SpecialWave();
    if (wave){
        if (wave->initSpecialWave(_unitName, _hp, _count, _gun, _atkInterval, _afterTime, _priority, _path, _moveSpeed, _periodTime, _countItem, _typeCoin)){
            wave->autorelease();
            return wave;
        }
    }
    
    CC_SAFE_DELETE(wave);
    return nullptr;

    
    
}


bool SpecialWave::initSpecialWave(cocos2d::__String _unitName, int _hp, int _count, Gun *_gun, float _atkInterval, float _afterTime, int _priority, Path *_path, float _moveSpeed, float _periodTime, int _countItem, TypeCoin _typeCoin){
    
    if (!Wave::init(_priority, _afterTime, _moveSpeed, _periodTime)){
        return false;
        
    }
    
    Vec2 startPoint = _path->arrVector.at(0)->point;
    Vec2 nextPoint = _path->arrVector.at(1)->point;
    
    float angle = (startPoint -nextPoint).getAngle();

    
    
    for (int i = 0; i < _count; i++)
    {
        auto unit = SpecialUnit::CreateSpecialUnit(_unitName,_hp,_gun->clone(),_atkInterval,_path,_moveSpeed,_countItem,_typeCoin);
        unit->setPosition(startPoint);
        unit->setUnitFacing(angle, true);
        this->arrUnitAlive.pushBack(unit);
        unit->setVisible(false);
    }
    
    CC_SAFE_RELEASE_NULL(_gun);

    
    
    return true;
}
