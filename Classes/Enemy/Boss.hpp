//
//  Boss.hpp
//  Ship
//
//  Created by KuKulKan on 7/29/16.
//
//

#ifndef Boss_hpp
#define Boss_hpp

#include "cocos2d.h"
#include <SimpleAudioEngine.h>
#include "CocosGUI.h"
#include "EnumManager.h"
#include "Gun.h"
#include "Path.h"
#include "MyMoveTo.h"

USING_NS_CC;
class Boss : public Sprite{
public:
    int countItem;
    
    static Boss* getCurrentBoss();
    static void setCurrentBoss(Boss* _boss);
    
    bool initBoss(__String _path,int _hp);
    
    bool invunerable;
    int hp,maxHp;
    
    float dmgAbort;
    
    virtual void clear();
};

#endif /* Boss_hpp */
