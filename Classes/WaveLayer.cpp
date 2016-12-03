//
//  WaveLayer.cpp
//  ShipSceneEditor
//
//  Created by Dao Hoang Tung on 12/1/16.
//
//


#include "WaveLayer.hpp"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "ResourcesNew.h"
USING_NS_CC;

using namespace cocostudio::timeline;

void WaveLayer::open(){
    this->setVisible(true);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(_event, this);
}

void WaveLayer::close(){
    auto _callBackClose = CallFuncN::create(CC_CALLBACK_0(WaveLayer::callBackClose, this));
    
    this->runAction(Sequence::create(EaseElasticOut::create(ScaleTo::create(0.5, 0.),0.5),
                                         _callBackClose, NULL));
    
}


void WaveLayer::clear(){
    if (vecField.size() > 0){
        vecField.clear();

    }
    _event->release();
    spriteSelectionLayer->clear();
    spriteSelectionLayer->release();
    this->removeAllChildren();
}

bool WaveLayer::init(){
    
    if (!Layer::init()){
        return false;
    }
    
    spriteSelectionLayer = EnemySpriteSelectionLayer::create();
    spriteSelectionLayer->retain();
    
    this->setContentSize(Size(300,500));
    
    rootNode = CSLoader::createNode("WaveLayer.csb");
    
    this->addChild(rootNode);
    
    saveChildToLocalVariable();
    modifyButtonEvent();
    modifyTouchEvent();
    modifyOtherEvent();
    return true;
}


void WaveLayer::saveChildToLocalVariable(){
    panel = (Layout*)rootNode->getChildByTag(16);
    btnSprite = (Button*)panel->getChildByTag(0);
    
    txtSpriteType = (Text*)panel->getChildByTag(69);
    txtSpriteName = (Text*)panel->getChildByTag(497);
    
    for(int i = 1; i < 8;i++){
        auto _text = (Text*)panel->getChildByTag(i);
        if (_text != NULL){
            auto _img = (ImageView*)_text->getChildByTag(i);
            if (_img != NULL){
                auto _field = (TextField*)_img->getChildByTag(i);
                
                if (_field != NULL){
                    vecField.pushBack(_field);
                }
            }
        }
    }
}

void WaveLayer::modifyButtonEvent(){
    btnSprite->addTouchEventListener(CC_CALLBACK_2(WaveLayer::callBackButton, this));
}

void WaveLayer::modifyTouchEvent(){
    _event = EventListenerTouchOneByOne::create();
    _event->onTouchBegan = CC_CALLBACK_2(WaveLayer::onTouchBegan, this);
    _event->onTouchMoved = CC_CALLBACK_2(WaveLayer::onTouchMoved, this);
    _event->onTouchEnded = CC_CALLBACK_2(WaveLayer::onTouchEnded, this);
    _event->setSwallowTouches(true);
    _event->retain();
}

void WaveLayer::modifyOtherEvent(){
    spriteSelectionLayer->onSpriteChange = CC_CALLBACK_2(WaveLayer::callBackSpriteSelection, this);
}

int WaveLayer::getValue(PropertiesTag type){
    auto _s = __String::create(vecField.at(type)->getString());
    return _s->intValue();
}

bool WaveLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event){
    
    return true;
}

void WaveLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event){
    
}

void WaveLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event){
    if (!rootNode->getBoundingBox().containsPoint(touch->getLocation())){
        this->close();
    }
}

void WaveLayer::callBackClose(){
    this->setVisible(false);
    this->removeFromParent();
    getEventDispatcher()->removeEventListener(_event);
    this->setScale(1);
}

void WaveLayer::callBackBtnSprite(){
    spriteSelectionLayer->open();
    this->addChild(spriteSelectionLayer,1);
    spriteSelectionLayer->setPosition(-300, 0);
}

void WaveLayer::callBackSpriteSelection(std::string _spriteName, SpriteType type){
    
#if DEBUG_LOG 0
    log("callBackSpriteSelection: Can't find sprite name or sprite name == null");
#endif
    
    if (_spriteName == "") return;
    
    auto _path = StringUtils::format("%s.png",_spriteName.c_str());
    
    btnSprite->loadTextures(_path,_path,_path,Widget::TextureResType::PLIST);
    
    txtSpriteName->setString(_spriteName);
    
    switch (type) {
        case ANIMATED:
            txtSpriteType->setString("Animated");
            break;
        
        case NON_ANIMATED:
            txtSpriteType->setString("Non-Animated");
            break;
            
        case SPECIAL:
            txtSpriteType->setString("Special");
            break;

            
        default:
            break;
    }
}



void WaveLayer::callBackButton(cocos2d::Ref *pSender, Widget::TouchEventType type){
    auto _button = (Button*)pSender;
    
    if (_button == NULL) return;
    
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            switch (_button->getTag()) {
                case 0:
                {
                    this->callBackBtnSprite();
                    break;
                }
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}
