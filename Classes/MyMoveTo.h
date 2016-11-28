#ifndef _MY_MOVE_TO_H
#define _MY_MOVE_TO_H

#include "cocos2d.h"
#include "Unit.h"

USING_NS_CC;

class MyMoveTo : public MoveTo
{
public:
    static MyMoveTo* create(float duration, const Vec2& position);
    static MyMoveTo* create(float duration, const Vec3& position);
    virtual MyMoveTo* clone() const override;
    virtual MyMoveTo* reverse() const  override;
    virtual void startWithTarget(Node *target) override;
    
CC_CONSTRUCTOR_ACCESS:
    MyMoveTo() {}
    virtual ~MyMoveTo() {}
    
    /**
     * initializes the action
     * @param duration in seconds
     */
    bool initWithDuration(float duration, const Vec2& position);
    /**
     * initializes the action
     * @param duration in seconds
     */
    bool initWithDuration(float duration, const Vec3& position);
    
protected:
    Vec3 _endPosition;
    
private:
    CC_DISALLOW_COPY_AND_ASSIGN(MyMoveTo);
};

#endif