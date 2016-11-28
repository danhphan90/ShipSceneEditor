//
//  Boss1.hpp
//  Ship
//
//  Created by KuKulKan on 7/29/16.
//
//

#ifndef Boss1_hpp
#define Boss1_hpp

#include "Boss.hpp"
class Boss1 : public Boss{
public:
        
    static Boss1* createBoss(int _hp);
    
    bool initBoss1(int _hp);
    
    void start();
    void startAttack(float dt);
    void mainFire();
    void superFire();
    void largeFire();
    void clear();
    
    Gun* mainWeapon;
    Gun* superWeapon;
    Gun* largeWeapon;
    
    Vec2 initPosition;
};

#endif /* Boss1_hpp */
