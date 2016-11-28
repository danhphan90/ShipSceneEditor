//
//  LightningSprite.hpp
//  Ship
//
//  Created by KuKulKan on 8/17/16.
//
//

#ifndef _Lightning_Sprite_hpp
#define _Lightning_Sprite_hpp

#include "cocos2d.h"
#include "EnumManager.h"
#include "Lightning.hpp"
#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

//#include "Mission.h"

USING_NS_CC;

class LightningSprite : public Layer{
public:
    Vector<Lightning*> lightningMember;
    
    Sprite* target;
    bool isRecycle;
    LightningClass _class;
    int sound;
    
    float fromAngle,toAngle,duration;
    
    static void ReleaseAllObject();
    static void loadResource();
    static void loadMissionLayer(Layer* _layer);
    static LightningSprite* CreateLightningEffect(Sprite* _target, float _fromAngle, float _toAngle, float _duration,LightningClass _class2);
    
    static LightningSprite* createLightning(LightningClass _class);
    bool initLightningSprite(LightningClass _class);
    
    void updatePosition(float dt);
    void callFadeOutLightning();
    void start();
    void stop(float dt);
    
    
    
};

#endif /* LightningSprite_hpp */
