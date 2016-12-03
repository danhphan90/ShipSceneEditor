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
#include "EnemySpriteSelectionLayer.hpp"
#include "ResourcesNew.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;



class WaveLayer : public Layer{
public:
    void open();
    void close();
    void clear();

    CREATE_FUNC(WaveLayer);
    
private:
    EnemySpriteSelectionLayer* spriteSelectionLayer;
    
    Node* rootNode;
    
    Button* btnSprite;
    Button* btnShow;
    
    Layout* panel;
    
    Vector<TextField*> vecField;
    
    EventListenerTouchOneByOne* _event;
    
    Text* txtSpriteType;
    Text* txtSpriteName;
    

    virtual bool init();
    void saveChildToLocalVariable();
    void modifyButtonEvent();
    void modifyTouchEvent();
    void modifyOtherEvent();
    
    
    int getValue(PropertiesTag type);
    
    void callBackButton(Ref* pSender, Widget::TouchEventType type);
    
    
    bool onTouchBegan(Touch* touch, Event* event);
   	void onTouchMoved(Touch* touch, Event* event);
   	void onTouchEnded(Touch* touch, Event* event);
    
    void callBackClose();
    void callBackBtnSprite();
    void callBackSpriteSelection(std::string _spriteName, SpriteType type);
    
};

#endif /* WaveLayer_hpp */
