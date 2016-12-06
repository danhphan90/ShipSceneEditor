//
//  PathLayer.hpp
//  ShipSceneEditor
//
//  Created by Dao Hoang Tung on 12/6/16.
//
//

#ifndef PathLayer_hpp
#define PathLayer_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ResourcesNew.h"
#include "EnumManager.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

class PathLayer : public Layer{
    
public:
    static void loadResource();
    
    PathLayer();
    CREATE_FUNC(PathLayer);
    
    void open();
    void close();
    void clear();
    
    typedef std::function<void(string,TypeCoin)> ccItemChangeCallback;
    
    ccItemChangeCallback onItemChange;
    
private:
    Node* rootNode;
    
    EventListenerTouchOneByOne* _event;
    
    Vector<Button*> vecBtnItem;
    
    Vector<TextField*> vecField;
    
    
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
#endif /* PathLayer_hpp */
