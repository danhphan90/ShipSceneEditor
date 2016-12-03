//
//  EnemySpriteSelectionLayer.hpp
//  ShipSceneEditor
//
//  Created by KuKulKan on 12/3/16.
//
//

#ifndef EnemySpriteSelectionLayer_hpp
#define EnemySpriteSelectionLayer_hpp


#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ResourcesNew.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

class EnemySpriteSelectionLayer : public Layer{
    
public:
    EnemySpriteSelectionLayer();
    CREATE_FUNC(EnemySpriteSelectionLayer);
    
    void open();
    void close();
    void clear();
    
    typedef std::function<void(string,SpriteType)> ccSpriteChangeCallback;
    
    ccSpriteChangeCallback onSpriteChange;

private:
    Node* rootNode;
    
    ListView* listViewMain;
        
    EventListenerTouchOneByOne* _event;
    
    Vector<Button*> vecBtnSpriteImage;
    
    
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
#endif /* EnemySpriteSelectionLayer_hpp */
