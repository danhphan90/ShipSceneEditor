//
//  EnemySpriteSelectionLayer.cpp
//  ShipSceneEditor
//
//  Created by KuKulKan on 12/3/16.
//
//

#include "EnemySpriteSelectionLayer.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ResourcesNew.h"
USING_NS_CC;

using namespace cocostudio::timeline;

EnemySpriteSelectionLayer::EnemySpriteSelectionLayer(){
    onSpriteChange = NULL;
}

void EnemySpriteSelectionLayer::open(){
    this->setScale(0.3);
    this->runAction(EaseElasticOut::create(ScaleTo::create(0.5, 1), 0.5));

    this->setVisible(true);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_event, this);
}

void EnemySpriteSelectionLayer::close(){
    auto _callBackClose = CallFuncN::create(CC_CALLBACK_0(EnemySpriteSelectionLayer::callBackClose, this));
    
    this->runAction(Sequence::create(EaseElasticOut::create(ScaleTo::create(0.5, 0.),0.5),
                                     _callBackClose, NULL));
    
}


void EnemySpriteSelectionLayer::clear(){
    vecBtnSpriteImage.clear();
        _event->release();
    this->removeAllChildren();
}

bool EnemySpriteSelectionLayer::init(){
    
    if (!Layer::init()){
        return false;
    }

    this->setContentSize(Size(300,500));
    
    rootNode = CSLoader::createNode("SpriteLayer.csb");
    
    this->addChild(rootNode);
    
    saveChildToLocalVariable();
    modifyButtonEvent();
    modifyTouchEvent();
    modifyListView();
    return true;
}


void EnemySpriteSelectionLayer::saveChildToLocalVariable(){
    
    /*Get button from listview in rootNode
    rootNode->listViewMain  ->listView1->panel->child button
                            ->listView2->panel->child button
                            ->listView3->panel->child button
                            ->listView4->panel->child button
                            ->listView5->panel->child button
     */
    {
        listViewMain = (ListView*)rootNode->getChildByName("listViewMain");
        
        for(auto item : listViewMain->getItems()){
            auto listView = (ListView*)item;
            if (listView != NULL){
                auto _panel = listView->getItems().back();
                
                if (_panel != NULL){
                    for(auto item : _panel->getChildren()){
                        auto _button = (Button*)item;
                        vecBtnSpriteImage.pushBack(_button);
                        _button->setTag(_panel->getTag());
                    }
                }
            }
        }
    }

}

void EnemySpriteSelectionLayer::modifyButtonEvent(){
    for(auto item : vecBtnSpriteImage){
        item->addTouchEventListener(CC_CALLBACK_2(EnemySpriteSelectionLayer::callBackButton, this));
    }
}

void EnemySpriteSelectionLayer::modifyTouchEvent(){
    _event = EventListenerTouchOneByOne::create();
    _event->onTouchBegan = CC_CALLBACK_2(EnemySpriteSelectionLayer::onTouchBegan, this);
    _event->onTouchMoved = CC_CALLBACK_2(EnemySpriteSelectionLayer::onTouchMoved, this);
    _event->onTouchEnded = CC_CALLBACK_2(EnemySpriteSelectionLayer::onTouchEnded, this);
    _event->setSwallowTouches(true);
    _event->retain();
}

void EnemySpriteSelectionLayer::modifyListView(){
    listViewMain->setClippingEnabled(true);
    
    for(auto item : listViewMain->getItems()){
        auto listView = (ListView*)item;
        listView->setClippingEnabled(true);
    }
    
}


bool EnemySpriteSelectionLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    
    return true;
}

void EnemySpriteSelectionLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void EnemySpriteSelectionLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    if (!rootNode->getBoundingBox().containsPoint(touch->getLocation())){
        this->close();
    }
}

void EnemySpriteSelectionLayer::callBackClose(){
    this->setVisible(false);
    this->removeFromParent();
    getEventDispatcher()->removeEventListener(_event);
    this->setScale(1);
}
void EnemySpriteSelectionLayer::callBackButton(cocos2d::Ref *pSender, Widget::TouchEventType type){
    auto _button = (Button*)pSender;
    
    if (_button == NULL) return;
    
    if (onSpriteChange != NULL){
        switch (_button->getTag()) {
            case 1:
                this->onSpriteChange(_button->getName(),SpriteType::NON_ANIMATED);
                break;
            case 2:
                this->onSpriteChange(_button->getName(),SpriteType::ANIMATED);
                break;
            case 3:
                this->onSpriteChange(_button->getName(),SpriteType::SPECIAL);
                break;

                
            default:
                break;
        }
        this->close();
    }
    
}
