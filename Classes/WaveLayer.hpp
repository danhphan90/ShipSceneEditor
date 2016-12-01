//
//  WaveLayer.hpp
//  ShipSceneEditor
//
//  Created by Dao Hoang Tung on 12/1/16.
//
//

#ifndef WaveLayer_hpp
#define WaveLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

enum PropertiesTag{
    tagHP = 0,
    tagCount = 1,
    tagAttackSpeed = 2,
    tagAfterTime = 3,
    tagPriority = 4,
    tagMoveSpeed = 5,
    tagPeriod = 6
};

class WaveLayer : public Layer{
public:
    void open();
    void close();
    void clear();

    CREATE_FUNC(WaveLayer);
    
private:
    Node* rootNode;
    
    Button* btnSprite;
    Button* btnShow;
    
    Layout* panel;
    
    Vector<TextField*> vecField;
    
    EventListenerTouchOneByOne* _event;
    

    virtual bool init();
    void saveChildToLocalVariable();
    void modifyButtonEvent();
    void modifyTouchEvent();
    
    
    int getValue(PropertiesTag type);
    
    void callBackButton(Ref* pSender, Widget::TouchEventType type);
    
    
    bool onTouchBegan(Touch* touch, Event* event);
   	void onTouchMoved(Touch* touch, Event* event);
   	void onTouchEnded(Touch* touch, Event* event);
    
    void callBackClose();
};

#endif /* WaveLayer_hpp */
