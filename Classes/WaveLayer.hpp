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

enum WaveLayerChild{
    WaveLayerChild_tagBtnSprite = 204,
    WaveLayerChild_tagBtnItem = 9
};

class WaveLayer : public Layer{
public:
    WaveLayer();
    
    void clear();

    static void saveMainPanel(ImageView* _panel);
    
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
    
    ImageView* imgFieldItemCount;

    virtual bool init();
    void saveChildToLocalVariable();
    void modifyLocalVariable();
    void modifyButtonEvent();
    void modifyTouchEvent();
    void modifyOtherEvent();
    
    
    int getValue(PropertiesTag type);
    
    void callBackButton(Ref* pSender, Widget::TouchEventType type);
    
    
    void callBackClose();
    void callBackBtnSprite();
    void callBackBtnItem();
    
    
    void callBackSpriteSelection(std::string _spriteName, SpriteType type);
    void callBackItemSelection(std::string _itemName, TypeCoin type);
    
    
    
    
    
    
    
    
};

#endif /* WaveLayer_hpp */
