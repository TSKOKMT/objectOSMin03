#pragma once

#include "ofMain.h"

#include "ofxFrameOcean.h"

#include "pressRoom.h"

//Biview!

class echoChamber {

public:
    echoChamber();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Chamber";
    int count_ = 4;
    float margin = 2;
    float term_ = 1;
    float delay_ = .1;
    
    pressRoom myPressRoom;
        
private:
};
