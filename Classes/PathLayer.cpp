//
//  PathLayer.cpp
//  ShipSceneEditor
//
//  Created by Dao Hoang Tung on 12/6/16.
//
//

#include "PathLayer.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ResourcesNew.h"
USING_NS_CC;

using namespace cocostudio::timeline;

static bool load = false;

void PathLayer::loadResource(){
    if (!load){
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Item/SingleItem.plist");
        load = true;
    }
}

PathLayer::PathLayer(){
    onItemChange = NULL;
}

void PathLayer::open(){
    this->setScale(0.3);
    this->runAction(EaseElasticOut::create(ScaleTo::create(0.5, 1), 0.5));
    
    this->setVisible(true);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_event, this);
}

void PathLayer::close(){
    auto _callBackClose = CallFuncN::create(CC_CALLBACK_0(PathLayer::callBackClose, this));
    
    this->runAction(Sequence::create(EaseElasticOut::create(ScaleTo::create(0.5, 0.),0.5),
                                     _callBackClose, NULL));
    
}


void PathLayer::clear(){
    vecBtnItem.clear();
    _event->release();
    this->removeAllChildren();
}

bool PathLayer::init(){
    
    if (!Layer::init()){
        return false;
    }
    
    this->setContentSize(Size(330,120));
    
    rootNode = CSLoader::createNode("ItemLayer.csb");
    
    this->addChild(rootNode);
    
    saveChildToLocalVariable();
    modifyButtonEvent();
    modifyTouchEvent();
    modifyListView();
    return true;
}


void PathLayer::saveChildToLocalVariable(){
    
    /*Get button from listview in rootNode
     rootNode->listViewMain ->panel->child button
     
     */
    {
        auto _panel = (Layout*)rootNode->getChildByTag(1);
        
        if (_panel == NULL) return;
        
        for(auto item : _panel->getChildren()){
            auto _button = (Button*)item;
            vecBtnItem.pushBack(_button);
            _button->setTag(_panel->getTag());
        }
    }
    
}

void PathLayer::modifyButtonEvent(){
    for(auto item : vecBtnItem){
        item->addTouchEventListener(CC_CALLBACK_2(PathLayer::callBackButton, this));
    }
}

void PathLayer::modifyTouchEvent(){
    _event = EventListenerTouchOneByOne::create();
    _event->onTouchBegan = CC_CALLBACK_2(PathLayer::onTouchBegan, this);
    _event->onTouchMoved = CC_CALLBACK_2(PathLayer::onTouchMoved, this);
    _event->onTouchEnded = CC_CALLBACK_2(PathLayer::onTouchEnded, this);
    _event->setSwallowTouches(true);
    _event->retain();
}

void PathLayer::modifyListView(){
    
}


bool PathLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    
    return true;
}

void PathLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void PathLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    if (!rootNode->getBoundingBox().containsPoint(touch->getLocation())){
        this->close();
    }
}

void PathLayer::callBackClose(){
    this->setVisible(false);
    this->removeFromParent();
    getEventDispatcher()->removeEventListener(_event);
    this->setScale(1);
}
void PathLayer::callBackButton(cocos2d::Ref *pSender, Widget::TouchEventType type){
    auto _button = (Button*)pSender;
    
    if (_button == NULL) return;
    
    if (onItemChange != NULL){
        switch (_button->getTag()) {
            case 1:
                this->onItemChange(_button->getName(),TypeCoin::typeSilverCoin);
                break;
            case 2:
                this->onItemChange(_button->getName(),TypeCoin::typeGoldCoin);
                break;
            case 3:
                this->onItemChange(_button->getName(),TypeCoin::typeGoldBar);
                break;
            case 4:
                this->onItemChange(_button->getName(),TypeCoin::typeDiamond);
                break;
                
                
            default:
                break;
        }
        this->close();
    }
    
}
