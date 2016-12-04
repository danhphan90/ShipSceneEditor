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
#include "CoinLayer.hpp"
#include "ResourcesNew.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;



class WaveLayer : public Layer{
public:
    WaveLayer();
    
    void open();
    void close();
    void clear();

    CREATE_FUNC(WaveLayer);
    
    CC_SYNTHESIZE(std::string, spriteName, SpriteName);
    CC_SYNTHESIZE(SpriteType, spriteType, SpriteType);
    CC_SYNTHESIZE(TypeCoin, itemType, ItemType);
    
private:
    EnemySpriteSelectionLayer* spriteSelectionLayer;
    CoinLayer* coinSelectionLayer;
    
    Node* rootNode;
    
    Button* btnSprite;
    Button* btnItem;
    
    Layout* panel;
    
    Vector<TextField*> vecField;
    
    EventListenerTouchOneByOne* _event;
    
    Text* txtSpriteType;
    Text* txtSpriteName;
    Text* itemItemCount;
    Text* itemItemType;
    

    virtual bool init();
    void saveChildToLocalVariable();
    void modifyLocalVariable();
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
    void callBackBtnItem();
    
    
    void callBackSpriteSelection(std::string _spriteName, SpriteType type);
    void callBackItemSelection(std::string _itemName, TypeCoin type);
    
    
    
    
    
    
    
    
};

#endif /* WaveLayer_hpp */
