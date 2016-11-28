#ifndef _WAVE_
#define  _WAVE_

#include "cocos2d.h"
#include "Unit.h"
#include "Gun.h"
USING_NS_CC;

class Wave : public Layer
{
public:
    Vector<Unit*> arrUnitAlive;
    Vector<Unit*> arrUnitDead;
    Vector<Unit*> arrUnitMoving;

    
    Vec2 lastUnitPos; //Get the position of final unit in wave
    int countRemainUnitAlive; //Check whether player kill all unit in 1 wave. this group must be equal to 0.
    int bonusScore;
    
    static void ReleaseWave();
    static void setMissionlayer(Layer* _layer);
    static Wave* createWaveWithPriority(int _priority, float _delay, float _moveSpeed, float _period);
    
    bool init(int _priority, float _delay, float _moveSpeed, float _period);
    
    void start();
//    void stop();
    void clear();
    void moveUnit(float dt);
    void update(float delta);
    
    
    CC_SYNTHESIZE(float, priority, Priority);
    CC_SYNTHESIZE(float, delay, Delay);
    CC_SYNTHESIZE(float, period, Period);
    CC_SYNTHESIZE(float, moveSpeed, MoveSpeed);
    CC_SYNTHESIZE(bool, isDone, IsDone);
    
private:
    
};


class AnimateWave : public Wave
{
public:
    static AnimateWave* createAnimateWave(__String _unitName, int _hp, int _count, Gun* _gun, float _atkInterval, float _afterTime, int _priority, Path* _path, float _moveSpeed, float _periodTime);
    
    bool initAnimateWave(__String _unitName, int _hp, int _count, Gun* _gun, float _atkInterval, float _afterTime, int _priority, Path* _path, float _moveSpeed, float _periodTime);
    
private:
    
};

class NonAnimateWave : public Wave
{
public:
    static NonAnimateWave* createNonAnimateWave(__String _unitName, int _hp, int _count, Gun* _gun, float _atkInterval, float _afterTime, int _priority, Path* _path, float _moveSpeed, float _periodTime);
    
    bool initNonAnimateWave(__String _unitName, int _hp, int _count, Gun* _gun, float _atkInterval, float _afterTime, int _priority, Path* _path, float _moveSpeed, float _periodTime);
    
};

class SpecialWave : public Wave{
public:
    static SpecialWave* createSpecialWave(__String _unitName, int _hp, int _count, Gun* _gun, float _atkInterval, float _afterTime, int _priority, Path* _path, float _moveSpeed, float _periodTime,int _countItem,TypeCoin _typeCoin);
    
    bool initSpecialWave(__String _unitName, int _hp, int _count, Gun* _gun, float _atkInterval, float _afterTime, int _priority, Path* _path, float _moveSpeed, float _periodTime,int _countItem,TypeCoin _typeCoin);
};

#endif
