#pragma once

#include "ofMain.h"

#include "ofxFrameOcean.h"

#include "pressRoom.h"

//Biview!

class quickBrown {

public:
    quickBrown();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Cristal";
    float height = 24;
    float margin = 2;
    float term_ = 1;
    float motionStrength_ = .9;
    float delay_ = .3;
    
    pressRoom myPressRoom;
        
private:
};
