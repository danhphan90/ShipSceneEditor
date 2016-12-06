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

static ImageView* _mainPanel = NULL;

void WaveLayer::saveMainPanel(cocos2d::ui::ImageView *_panel){
    _mainPanel = _panel;
}

WaveLayer::WaveLayer(){

}

void WaveLayer::clear(){
    if (vecField.size() > 0){
        vecField.clear();

    }
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
    
    coinSelectionLayer = CoinLayer::create();
    coinSelectionLayer->retain();
    
    rootNode = CSLoader::createNode("WaveLayer.csb");

    this->setContentSize(rootNode->getContentSize());
    
    this->addChild(rootNode);
    
    saveChildToLocalVariable();
    modifyLocalVariable();
    modifyButtonEvent();
    modifyTouchEvent();
    modifyOtherEvent();
    return true;
}

void WaveLayer::saveChildToLocalVariable(){
    panel = (Layout*)rootNode->getChildByTag(16);
    btnSprite = (Button*)panel->getChildByTag(WaveLayerChild::WaveLayerChild_tagBtnSprite);
    btnItem = (Button*)panel->getChildByTag(WaveLayerChild::WaveLayerChild_tagBtnItem);
    
    for(int i = 1; i < 9;i++){
        auto _img = (ImageView*)panel->getChildByTag(i);
        if (_img != NULL){
            auto _field = (TextField*)_img->getChildByTag(i);
            
            if (_field != NULL){
                vecField.pushBack(_field);
            }
        }
    }
    
    imgFieldItemCount = (ImageView*)panel->getChildByTag(8);
}


void WaveLayer::modifyLocalVariable(){
    imgFieldItemCount->setVisible(false);
    btnItem->setVisible(false);
}

void WaveLayer::modifyButtonEvent(){
    btnSprite->addTouchEventListener(CC_CALLBACK_2(WaveLayer::callBackButton, this));
    btnItem->addTouchEventListener(CC_CALLBACK_2(WaveLayer::callBackButton, this));
}

void WaveLayer::modifyTouchEvent(){

}

void WaveLayer::modifyOtherEvent(){
    spriteSelectionLayer->onSpriteChange = CC_CALLBACK_2(WaveLayer::callBackSpriteSelection, this);
    coinSelectionLayer->onItemChange = CC_CALLBACK_2(WaveLayer::callBackItemSelection, this);
}

int WaveLayer::getValue(PropertiesTag type){
    auto _s = __String::create(vecField.at(type)->getString());
    return _s->intValue();
}

void WaveLayer::callBackBtnSprite(){
    spriteSelectionLayer->open();
    _mainPanel->addChild(spriteSelectionLayer,3);
    spriteSelectionLayer->setPosition(120, 250);
}

void WaveLayer::callBackBtnItem(){
    coinSelectionLayer->open();
    this->addChild(coinSelectionLayer,3);
    coinSelectionLayer->setPosition(540,0);
}

void WaveLayer::callBackSpriteSelection(std::string _spriteName, SpriteType type){
    if (_spriteName == "") return;
    
    auto _path = StringUtils::format("%s.png",_spriteName.c_str());
    
    btnSprite->loadTextures(_path,_path,_path,Widget::TextureResType::PLIST);
    
    
    setSpriteName(_spriteName);
    setSpriteType(type);
    
    
    switch (type) {
        case ANIMATED:
        case NON_ANIMATED:
        {
            imgFieldItemCount->setVisible(false);
            btnItem->setVisible(false);
        }
            break;
            
        case SPECIAL:
        {
            imgFieldItemCount->setVisible(true);
            btnItem->setVisible(true);
        }
            break;
            
        default:
            break;
    }
}

void WaveLayer::callBackItemSelection(std::string _itemName, TypeCoin type){
    if (_itemName == "") return;
    
    auto _path = _itemName + ".png";
    btnItem->loadTextures(_path, _path,_path,Widget::TextureResType::PLIST);
    
    setItemType(type);
}


void WaveLayer::callBackButton(cocos2d::Ref *pSender, Widget::TouchEventType type){
    auto _button = (Button*)pSender;
    
    if (_button == NULL) return;
    
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            switch (_button->getTag()) {
                case WaveLayerChild_tagBtnSprite:
                {
                    this->callBackBtnSprite();
                    break;
                }
                    
                case WaveLayerChild_tagBtnItem:
                {
                    this->callBackBtnItem();
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
