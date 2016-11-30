#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <iostream>
#include "MissionMap.h"

#include "Bullet.h"
#include "Unit.h"
#include "Wave.h"
#include "LightningSprite.hpp"

using namespace std;


enum MainSceneChild{
    tagPanel = 9,
};

enum PanelChild{
    tagStart = 123,
    tagReset = 124,
    tagAdd = 15,
    tagRemove = 16,
    tagListWave = 8
};

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    HelloWorld();
    CREATE_FUNC(HelloWorld);
    
private:
    Mission* mission;
    Node* rootNode;
    
    ImageView* panel;
    
    ListView* listWave;
    
    Button* btnPanel_Start;
    Button* btnPanel_Reset;
    Button* btnPanel_Add, *btnPanel_Remove;
    
    int _indexWave;
    
    void startMission();
    void stopMission();
    void saveChildToLocalVariable();
    void modifyLocalVariable();
    void modifyButtonEvent();
    
    Layout* createButtonWave();
    
    
    void update(float dt);
    
    virtual void onEnterTransitionDidFinish();

    void callBackButton(Ref* pSender, Widget::TouchEventType type);
};

#endif // __HELLOWORLD_SCENE_H__
