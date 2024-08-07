#pragma once

#include "ofMain.h"

#include "ofxFrameOcean.h"

#include "pressRoom.h"

class blueCrown {

public:
    blueCrown();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Zebra";
    float height_ = 120;
    float radius_ = 360;
    float hour = 30;
    
    pressRoom myPressRoom;
        
private:
};
