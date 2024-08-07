#pragma once

#include "ofMain.h"

#include "ofxFrameOcean.h"

#include "pressRoom.h"

//Biview!

class alphaDelta {

public:
    alphaDelta();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Yoo";
    int count_ = 5;
    float margin = 2;
    float term_ = 3;
    float speed = 4;
    
    pressRoom myPressRoom;
        
private:
};
