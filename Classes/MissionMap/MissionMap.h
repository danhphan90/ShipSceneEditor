#ifndef _MISSION_1_H_
#define _MISSION_1_H_

#include "cocos2d.h"
#include "Mission.h"

USING_NS_CC;

class Mission_1_ : public Mission{
public:
    virtual bool init();
    void initWave();
    CREATE_FUNC(Mission_1_);
};

#endif