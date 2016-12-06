//
//  WaveButton.cpp
//  ShipSceneEditor
//
//  Created by Dao Hoang Tung on 12/1/16.
//
//

#include "WaveButton.hpp"
#include "ResourcesNew.h"

static int _indexWave = 1;

bool WaveButton::init(){
    
    if (!Button::init()){
        return false;
    }
    
    this->loadTextures(srcPNG_backtotopnormal,srcPNG_backtotoppressed,srcPNG_backtotopnormal);
    
    this->setTitleFontName(srcTFF_Roboto_Bold);
    this->setTag(_indexWave);
    this->setScale9Enabled(true);
    this->setContentSize(Size(120,50));
    this->setTitleFontSize(18);
    this->setName(StringUtils::format("Wave %zd",_indexWave));
    this->setTitleText(StringUtils::format("Wave %zd",_indexWave));
    this->setScale(0.8);
    _indexWave++;
    
    panelInfo = WaveLayer::create();
    panelInfo->retain();
    
    panelInfo->setTag(_indexWave+1);
    return true;
}

void WaveButton::clear(){
    _indexWave--;
    
    panelInfo->clear();
    panelInfo->release();
}
