#include "Path.h"

static float sizeH;
static float sizeW;


void Path::loadResource()
{
    sizeW = 640;
    sizeH = 960;
}

KKPoint::KKPoint(Vec2 _point){
    point = _point;
    this->autorelease();
}


PathReturn* PathReturn::createAt_Y(float _y, float _toY, float _openWidth, float _distance, PathDirection _direction){
    auto path = new (std::nothrow) PathReturn();
    if (!path){
        CC_SAFE_DELETE(path);
        return nullptr;
    }
    
    float y = _y * sizeH;
    float toY = _toY * sizeH;
    
    float _gapHeight = y - toY;
    if (_gapHeight < 0){_gapHeight*=-1;}
    
    Vec2 startPoint,endPoint,nextStartPoint,nextEndPoint;
    
    switch (_direction) {
        case PathDirection::LeftToRight:
            startPoint = Vec2(-100,y);
            endPoint = Vec2(-100,y + _gapHeight);
            break;
            
        case PathDirection::RightToLeft:
            startPoint = Vec2(sizeW+100,y);
            endPoint = Vec2(sizeW+100,y+_gapHeight);
            break;
            
        default:
            break;
    }
    
    nextStartPoint  = startPoint    + Vec2((int)_direction * _distance,0);
    nextEndPoint    = endPoint      + Vec2((int)_direction * _distance,0);
    
    path->arrVector.pushBack(new KKPoint( startPoint));
    path->arrVector.pushBack(new KKPoint( nextStartPoint));
    
    float factorHeight = 180./40.;
    float factorDistance = _gapHeight/40.;
    
    for(int i = 0; i<=40;i++){
        float xx = i*factorDistance;
        float yy = (int)_direction * _openWidth * sin(CC_DEGREES_TO_RADIANS(i*factorHeight));
        path->arrVector.pushBack(new KKPoint( nextStartPoint+ Vec2(yy,xx)));
    }
    
    
    path->arrVector.pushBack(new KKPoint( nextEndPoint));
    path->arrVector.pushBack(new KKPoint( endPoint));
    
    return path;

}

PathReturn* PathReturn::createAt_X(float _x, float _toX, float _openHeight, float _distance, PathDirection _direction){
    auto path = new (std::nothrow) PathReturn();
    if (!path){
        CC_SAFE_DELETE(path);
        return nullptr;
    }

    float x = _x * sizeW;
    float toX = _toX * sizeW;
    float _gapWidth = x - toX;
    
    if (_gapWidth < 0){_gapWidth*=-1;}
    
    Vec2 startPoint,endPoint,nextStartPoint,nextEndPoint;
    
    switch (_direction) {
        case PathDirection::BotToTop:
            startPoint = Vec2(x,-100);
            endPoint = Vec2(toX,-100);
            break;
            
        case PathDirection::TopToBot:
            startPoint = Vec2(x,sizeH+100);
            endPoint = Vec2(toX,sizeH + 100);
            break;
            
        default:
            break;
    }
    
    nextStartPoint  = startPoint    + Vec2(0,(int)_direction * _distance);
    nextEndPoint    = endPoint      + Vec2(0,(int)_direction * _distance);
    
    path->arrVector.pushBack(new KKPoint( startPoint));
    path->arrVector.pushBack(new KKPoint( nextStartPoint));
    
    float factorHeight = 180./80;
    float factorDistance = _gapWidth/80;
    
    for(int i = 0; i<=80;i++){
        float xx = i*factorDistance;
        float yy = (int)_direction * _openHeight * sin(CC_DEGREES_TO_RADIANS(i*factorHeight));
        CCLOG("x: %f",xx);
        CCLOG("y: %f",yy);

        path->arrVector.pushBack(new KKPoint( nextStartPoint+ Vec2(xx,yy)));
    }
    
    
    path->arrVector.pushBack(new KKPoint( nextEndPoint));
    path->arrVector.pushBack(new KKPoint( endPoint));
    
    return path;
    
}

PathAcross* PathAcross::createAt_Y(float _fromY, float _toY, PathDirection _direction){
    auto path = new (std::nothrow) PathAcross();
    if (!path){
        CC_SAFE_DELETE(path);
        return nullptr;
    }
    

    Vec2 startPoint,endPoint;
    
    switch (_direction) {
        case PathDirection::LeftToRight:
            startPoint = Vec2(-100,_fromY*sizeH);
            endPoint = Vec2(sizeW+100,_toY*sizeH);
            break;
            
        case PathDirection::RightToLeft:
            endPoint = Vec2(-100,_fromY*sizeH);
            startPoint = Vec2(sizeW+100,_toY*sizeH);
            break;
            
        default:
            break;
    }
    
    path->arrVector.pushBack(new KKPoint( startPoint));
    path->arrVector.pushBack(new KKPoint( endPoint));
    
    
    return path;

    
}

PathAcross* PathAcross::createAt_X(float _fromX, float _toX, PathDirection _direction){
    auto path = new (std::nothrow) PathAcross();
    if (!path){
        CC_SAFE_DELETE(path);
        return nullptr;
    }
    
    
    Vec2 startPoint,endPoint;
    
    switch (_direction) {
        case PathDirection::BotToTop:
            startPoint = Vec2(_fromX*sizeW,-100);
            endPoint = Vec2(_toX*sizeW,sizeH+100);
            break;
            
        case PathDirection::TopToBot:
            endPoint = Vec2(_fromX*sizeW,-100);
            startPoint = Vec2(_toX*sizeW,sizeH+100);
            break;
            
        default:
            break;
    }
    
    path->arrVector.pushBack(new KKPoint( startPoint));
    path->arrVector.pushBack(new KKPoint( endPoint));
    
    
    return path;
    
    
}


PathZicZac* PathZicZac::createAt_Y_With_Height(float _percentY, float _height, int _countZic, PathDirection _direction){
    auto path = new (std::nothrow) PathZicZac();
    if (!path){
        CC_SAFE_DELETE(path);
        return nullptr;
    }
    
    float y = _percentY * sizeH;
    
    Vec2 startPoint,endPoint;
    switch (_direction) {
        case PathDirection::LeftToRight:
            startPoint = Vec2(-100,y);
            endPoint = Vec2(sizeW+100,y);
            break;
        case PathDirection::RightToLeft:
            endPoint = Vec2(-100,y);
            startPoint = Vec2(sizeW+100,y);
            break;
        default:
            break;
    }
    
    path->arrVector.pushBack(new KKPoint( startPoint));
    
    float range = startPoint.getDistance(endPoint)/_countZic;
    
    for(int i = 1; i <= _countZic;i++){
        if (i%2 == 0){
            auto vecNextPoint = startPoint + Vec2((int)_direction * range*i,0);
            path->arrVector.pushBack(new KKPoint(vecNextPoint));
        }else{
            auto vecNextPoint = startPoint + Vec2((int)_direction *range*i,_height);
            path->arrVector.pushBack(new KKPoint(vecNextPoint));
        }
    }
    
    path->arrVector.pushBack(new KKPoint( endPoint));
    
    return path;
}

PathZicZac* PathZicZac::createAt_X_With_Height(float _percentX, float _height, int _countZic, PathDirection _direction){
    auto path = new (std::nothrow) PathZicZac();
    if (!path){
        CC_SAFE_DELETE(path);
        return nullptr;
    }
    
    float x = _percentX * sizeW;
    
    Vec2 startPoint,endPoint;
    switch (_direction) {
        case PathDirection::BotToTop:
            startPoint = Vec2(x,-100);
            endPoint = Vec2(x,sizeH+100);
            break;
        case PathDirection::TopToBot:
            endPoint = Vec2(x,-100);
            startPoint = Vec2(x,sizeH+100);
            break;
        default:
            break;
    }
    
    path->arrVector.pushBack(new KKPoint( startPoint));
    
    float range = startPoint.getDistance(endPoint)/_countZic;
    
    for(int i = 1; i <= _countZic;i++){
        if (i%2 == 0){
            auto vecNextPoint = startPoint + Vec2(0,(int)_direction * range*i);
            path->arrVector.pushBack(new KKPoint(vecNextPoint));
        }else{
            auto vecNextPoint = startPoint + Vec2(_height,(int)_direction *range*i);
            path->arrVector.pushBack(new KKPoint(vecNextPoint));
        }
    }
    
    path->arrVector.pushBack(new KKPoint( endPoint));
    
    return path;
}

PathParabon* PathParabon::createAt_Y_With_Height(float _percentY, float _height, PathDirection _direction){

    auto path = new (std::nothrow) PathParabon();
    if (!path){
        CC_SAFE_DELETE(path);
        return nullptr;
    }
    
    float y = _percentY * sizeH;
    Vec2 startPoint = Vec2(-100,y);
    Vec2 endPoint = Vec2(sizeW+100,y);
    switch (_direction) {
        case PathDirection::LeftToRight:
            startPoint = Vec2(-100,y);
            endPoint = Vec2(sizeW+100,y);
            break;
        case PathDirection::RightToLeft:
            endPoint = Vec2(-100,y);
            startPoint = Vec2(sizeW+100,y);
            break;
        default:
            break;
    }
    
    auto distance = startPoint.getDistance(endPoint);
    
    path->arrVector.pushBack(new KKPoint( startPoint));

    int loop = 40;
    float factorHeight = 180./40.;
    float factorDistance = distance/40.;
    
    for(int i = 0; i <= loop;i++){
        float xx = i*factorDistance;
        float yy = _height * sin(CC_DEGREES_TO_RADIANS(i*factorHeight));
        if (_direction == PathDirection::LeftToRight){
            auto vecNextPoint = startPoint + Vec2(xx,yy);
            path->arrVector.pushBack(new KKPoint(vecNextPoint));
        }else{
            auto vecNextPoint = startPoint + Vec2(-xx,yy);
            path->arrVector.pushBack(new KKPoint(vecNextPoint));
        }

    }
    
    path->arrVector.pushBack(new KKPoint( endPoint));
    return path;

}

PathParabon* PathParabon::createAt_X_With_Height(float _percentX, float _height, PathDirection _direction){
    
    auto path = new (std::nothrow) PathParabon();
    if (!path){
        CC_SAFE_DELETE(path);
        return nullptr;
    }
    
    float x = _percentX * sizeW;
    Vec2 startPoint,endPoint;
    
    switch (_direction) {
        case PathDirection::BotToTop:
            startPoint = Vec2(x,-100);
            endPoint = Vec2(x,sizeH + 100);
            break;
        case PathDirection::TopToBot:
            endPoint = Vec2(x,sizeH + 100);
            startPoint = Vec2(x+100,-100);
            break;
        default:
            break;
    }
    
    auto distance = startPoint.getDistance(endPoint);
    
    path->arrVector.pushBack(new KKPoint( startPoint));
    
    int loop = 40;
    float factorHeight = 180./40.;
    float factorDistance = distance/40.;
    
    for(int i = 0; i <= loop;i++){
        float yy = i*factorDistance;
        float xx = _height * sin(CC_DEGREES_TO_RADIANS(i*factorHeight));
        if (_direction == PathDirection::BotToTop){
            auto vecNextPoint = startPoint + Vec2(xx,yy);
            path->arrVector.pushBack(new KKPoint(vecNextPoint));
        }else{
            auto vecNextPoint = startPoint + Vec2(-xx,yy);
            path->arrVector.pushBack(new KKPoint(vecNextPoint));
        }
        
    }
    
    path->arrVector.pushBack(new KKPoint( endPoint));
    return path;
    
}



