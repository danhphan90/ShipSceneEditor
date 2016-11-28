//
//  Lightning.hpp
//  Ship
//
//  Created by KuKulKan on 8/17/16.
//
//

#ifndef Lightning_hpp
#define Lightning_hpp

#include "cocos2d.h"
#include "EnumManager.h"
#include "Bullet.h"
//#include "Mission.h"

USING_NS_CC;

enum class LightningClass{
    forPlayer = 0,
    forEnemy = 1
};

class Lightning : public Sprite{
public:
    
    RepeatForever* animation;
    FadeOut* fadeOut;
    Vec2 pos;
    
    int dmg;
    
    bool isRecycle;
    static Lightning* createLightning(Vec2 _pos,LightningClass _class);
    bool initLightning(Vec2 _pos,LightningClass _class);
    
    void start();
    void startFadeOut();
    void callBackFadeOut();
    void stop();
    void stopImmediately();
    
};
#endif /* Lightning_hpp */
