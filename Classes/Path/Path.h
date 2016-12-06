#ifndef _PATH_HEAD_
#define _PATH_HEAD_

#include "cocos2d.h"

USING_NS_CC;

enum class PathDirection{
    LeftToRight = 1,
    RightToLeft = -1,
    TopToBot = -1,
    BotToTop = 1
};

class KKPoint : public Ref{
public:
    Vec2 point;
    KKPoint(Vec2 _point);
};

class Path
{
public:
    Vector<KKPoint*> arrVector;
    
    static void loadResource();
    
    inline void add(Path* _path){
        this->arrVector.pushBack(_path->arrVector);
        _path->arrVector.clear();
    }
};


class PathReturn : public Path{
public:
    static PathReturn* createAt_Y(float _y, float _toY,float _openWidth, float _distance,PathDirection _direction);
    
    static PathReturn* createAt_X(float _x,float _toX, float _openHeight, float _distance,PathDirection _direction);
};

class PathAcross : public Path{
public:
    static PathAcross* createAt_Y(float _fromY,float _toY,PathDirection _direction);
    
    static PathAcross* createAt_X(float _fromX,float _toX,PathDirection _direction);
    
};

class PathZicZac : public Path{
public:
    static PathZicZac* createAt_Y_With_Height(float _percentY, float _height,int _countZic,PathDirection _direction);
    
    static PathZicZac* createAt_X_With_Height(float _percentX, float _height,int _countZic,PathDirection _direction);
    
};

class PathParabon : public Path{
public:
    static PathParabon* createAt_Y_With_Height(float _percentY, float _height, PathDirection _direction);
    
    static PathParabon* createAt_X_With_Height(float _percenX, float _height, PathDirection _direction);
    
};




#endif
