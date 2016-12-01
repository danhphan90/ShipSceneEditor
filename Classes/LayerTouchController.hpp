//
//  LayerTouchController.hpp
//  ShipSceneEditor
//
//  Created by KuKulKan on 12/1/16.
//
//

#ifndef LayerTouchController_hpp
#define LayerTouchController_hpp

#include <stdio.h>


using namespace cocos2d;

class LayerTouchController : public Layer{
public:
    
    CREATE_FUNC(LayerTouchController);
    
private:
    virtual bool init();
    
    EventListenerTouchOneByOne* _event;
    
    bool onTouchBegan(Touch* touch, Event* event);
   	void onTouchMoved(Touch* touch, Event* event);
   	void onTouchEnded(Touch* touch, Event* event);
};

#endif /* LayerTouchController_hpp */
