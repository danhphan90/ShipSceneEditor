//
//  WaveButton.hpp
//  ShipSceneEditor
//
//  Created by Dao Hoang Tung on 12/1/16.
//
//

#ifndef WaveButton_hpp
#define WaveButton_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace std;
using namespace cocos2d;
using namespace cocos2d::ui;

class WaveButton : public Button{
public:
    void clear();
    CREATE_FUNC(WaveButton);
    
private:
    virtual bool init();
    
    
};
#endif /* WaveButton_hpp */
