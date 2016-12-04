//
//  CoinLayer.hpp
//  ShipSceneEditor
//
//  Created by KuKulKan on 12/3/16.
//
//

#ifndef CoinLayer_hpp
#define CoinLayer_hpp



#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ResourcesNew.h"
#include "EnumManager.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

class CoinLayer : public Layer{
    
public:
    static void loadResource();
    
    CoinLayer();
    CREATE_FUNC(CoinLayer);
    
    void open();
    void close();
    void clear();
    
    typedef std::function<void(string,TypeCoin)> ccItemChangeCallback;
    
    ccItemChangeCallback onItemChange;
    
private:
    Node* rootNode;
    
    
    EventListenerTouchOneByOne* _event;
    
    Vector<Button*> vecBtnItem;
    
    
    virtual bool init();
    void saveChildToLocalVariable();
    void modifyButtonEvent();
    void modifyTouchEvent();
    void modifyListView();
    
    
    void callBackButton(Ref* pSender, Widget::TouchEventType type);
    
    
    bool onTouchBegan(Touch* touch, Event* event);
   	void onTouchMoved(Touch* touch, Event* event);
   	void onTouchEnded(Touch* touch, Event* event);
    
    void callBackClose();
    
    
};

#endif /* CoinLayer_hpp */
