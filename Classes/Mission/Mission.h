#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "cocos2d.h"
#include "Wave.h"
#include "Path.h"
#include "Boss1.hpp"

USING_NS_CC;

class Mission : public Layer
{
public:
    Vector<Wave*> arrWave, arrWaveRunning, arrWaveDidFinish;
    
    int currentPriorityWave;
    
    bool initLevel();
    void start();
//    void stop();
    void clear();
    void update(float delta);
    
protected:
private:
};

#endif
