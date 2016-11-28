#include "MyMoveTo.h"



MyMoveTo* MyMoveTo::create(float duration, const Vec2& position)
{
    return MyMoveTo::create(duration, Vec3(position.x, position.y, 0));
}

MyMoveTo* MyMoveTo::create(float duration, const Vec3& position)
{
    MyMoveTo *ret = new (std::nothrow) MyMoveTo();
    
    if (ret)
    {
        if (ret->initWithDuration(duration, position))
        {
            ret->autorelease();
        }
        else
        {
            delete ret;
            ret = nullptr;
        }
    }
    
    return ret;
}

bool MyMoveTo::initWithDuration(float duration, const Vec2& position)
{
    return initWithDuration(duration, Vec3(position.x, position.y, 0));
}

bool MyMoveTo::initWithDuration(float duration, const Vec3& position)
{
    bool ret = false;
    
    if (ActionInterval::initWithDuration(duration))
    {
        _endPosition = position;
        ret = true;
    }
    
    return ret;
}

MyMoveTo* MyMoveTo::clone() const
{
    // no copy constructor
    auto a = new (std::nothrow) MyMoveTo();
    a->initWithDuration(_duration, _endPosition);
    a->autorelease();
    return a;
}

MyMoveTo* MyMoveTo::reverse() const
{
    CCASSERT(false, "reverse() not supported in MoveTo");
    return nullptr;
}

void MyMoveTo::startWithTarget(Node *target)
{
    MoveBy::startWithTarget(target);
    _positionDelta = _endPosition - target->getPosition3D();
    
    float angle = (target->getPosition() - Vec2(_endPosition.x, _endPosition.y)).getAngle();
    if (dynamic_cast<Unit*>(target)){
        dynamic_cast<Unit*>(target)->setUnitFacing(angle, true);
    }

    
}

