#ifndef _UNIT_HEAD_
#define _UNIT_HEAD_

#include "cocos2d.h"
#include "CocosGUI.h"
#include "EnumManager.h"
#include "Gun.h"
#include "Path.h"
#include "MyMoveTo.h"

USING_NS_CC;
using namespace cocos2d::ui;

class Unit : public Sprite
{
public:
    bool isSpecialUnit;
    
    Vec2 startingPoint;
    
    Gun* mainGun;
    __String unitName;
    Vector<SpriteFrame*> vecFrame;
    bool isAnimate;
    bool isCleared;
    
    float attackElapseTime;
    
    bool orderAttack;
    Sequence* moveActions;
    
    RepeatForever* animate;
    CallFuncN* didFinishMove;
    
    static void setMissionLayer(Layer* _layer);
    static void loadResource();
    static Unit* CreateUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown, Path* _path, float _moveSpeed);
    static Vector<Unit*> getArrUnitCurrentOnMap();
    static Vector<Unit*> getArrReleaseUnit();
    static Vector<RepeatForever*> getArrReleaseAnimate();
    bool initUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown,Path* _path,float _moveSpeed,bool _animate);
        
    void setUnitFacing(float _angle, bool _radian);
    
    void startAttack();
    void attack(float dt);
    void didFinishPath();
    void start();

    void clear();

    int getUnitHp();
    

    CC_SYNTHESIZE(int, maxHp, MaxHp);
    CC_SYNTHESIZE(int, hp, Hp);
    CC_SYNTHESIZE(int, currentNodePath, CurrentNodePath);
    
    CC_SYNTHESIZE(float, atkCooldown, AtkCoolDown);
    CC_SYNTHESIZE(float, facing, Facing);
    
    CC_SYNTHESIZE(UnitState, state, State);
    
};


class AnimateUnit : public Unit{
public:
    static Unit* CreateAnimateUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown, Path* _path, float _moveSpeed);
    bool initAnimateUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown, Path* _path, float _moveSpeed);
};



class NonAnimateUnit : public Unit{
public:
    static Unit* CreateNonAnimateUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown, Path* _path, float _moveSpeed);
    bool initNonAnimateUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown, Path* _path, float _moveSpeed);
    
};

class SpecialUnit : public AnimateUnit{
public:
    int countItemDrop;
    TypeCoin typeCoin;
    
    static Unit* CreateSpecialUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown, Path* _path, float _moveSpeed,int countItem, TypeCoin _typeCoin);
    
    bool initSpecialUnit(__String _name, int _hp, Gun* _gun, float _atkCooldown, Path* _path, float _moveSpeed,int _countItem, TypeCoin _typeCoin);
    
    
    void dropItem(int _lvlGravity);
};


#endif
