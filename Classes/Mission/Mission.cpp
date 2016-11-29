#include "Mission.h"




bool Mission::initLevel()
{
    if (!Layer::init()){
        return false;
    }
    
    this->currentPriorityWave = -1;
    
    return true;
}

void Mission::start()
{
    this->scheduleUpdate();
}

//void Mission::stop()
//{
//    this->unscheduleUpdate();
//    
//    
//    
//    for (auto wave : arrWaveDidFinish){
//        wave->stop();
//    }
//    
//    arrWaveRunning.clear();
//    arrWaveDidFinish.clear();
//    
//    this->currentPriorityWave = -1;
//}

void Mission::clear()
{
    auto _boss = (Boss*)this->getChildByName("Boss");
    if (_boss != NULL){
        static_cast<Boss*>(this->getChildByName("Boss"))->clear();
    }
    
    this->unscheduleUpdate();
    
    for (auto wave : arrWaveRunning){
        wave->clear();
        wave = nullptr;
    }
    
    for (auto wave : arrWave){
        wave->clear();
        wave = nullptr;
    }
    
    arrWaveRunning.clear();
    arrWave.clear();
    arrWaveDidFinish.clear();
    
    this->removeAllChildren();
    this->removeFromParent();
    
}

void Mission::update(float delta)
{
    Vector<Wave*> arrTemp;
    
    if (arrWaveRunning.size() <= 0){
        this->currentPriorityWave++;
        if (arrWave.size() > 0){
            for (auto wave : arrWave){
                if (wave->getPriority() == this->currentPriorityWave){
                    wave->start();
                    
                    this->arrWaveRunning.pushBack(wave);
                    arrTemp.pushBack(wave);
                }
                
            }
        }
        else{
            auto boss = Boss1::createBoss(1000);
            boss->setName("Boss");
            this->addChild(boss);
            this->unscheduleUpdate();
            Boss::setCurrentBoss(boss);
            
        }
    }
    
    if (arrTemp.size() > 0){
        for (auto wave : arrTemp){
            this->arrWave.eraseObject(wave, false);
        }
        arrTemp.clear();
    }
    
    if (this->arrWaveRunning.size() > 0){
        for (auto wave : this->arrWaveRunning){
            if (wave->getIsDone()){
                this->arrWaveDidFinish.pushBack(wave);
                arrTemp.pushBack(wave);
            }
        }
    }
    
    if (arrTemp.size() > 0){
        for (auto wave : arrTemp){
            this->arrWaveRunning.eraseObject(wave, false);
        }
        arrTemp.clear();
    }
    
    if (this->arrWaveDidFinish.size() > 0){
        for (auto wave : this->arrWaveDidFinish){
            wave->clear();
        }
        arrWaveDidFinish.clear();
    }
    
    
}







