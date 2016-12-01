//
//  LayerTouchController.cpp
//  ShipSceneEditor
//
//  Created by KuKulKan on 12/1/16.
//
//

#include "LayerTouchController.hpp"


bool LayerTouchController::init(){
    if (!Layer::init()){
        return false;
    }
    
    _event = EventListenerTouchOneByOne::create();
    
    
    return true;
}


bool LayerTouchController::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    
    return true;
}

void LayerTouchController::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void LayerTouchController::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    
}
