#pragma once

#include "ofMain.h"

#include "ofxFrameOcean.h"

#include "pressRoom.h"

//Biview!

class wipVip {

public:
    wipVip();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Async";
    int count = 7;
    float margin = 0;
    float term_ = 2;
    float motionStrength = .9;
    
    pressRoom myPressRoom;
        
private:
};
