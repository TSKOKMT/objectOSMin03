#pragma once

#include "ofMain.h"

#include "ofxTskokmtMath.h"
#include "ofxFrameOcean.h"

#include "pressRoom.h"

class roundFace {

public:
    roundFace();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Normal";
    float speed = -.5;
    float term_ = 2;
    
    pressRoom myPressRoom;
        
private:
};
