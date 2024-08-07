#pragma once

#include "ofMain.h"

#include "ofxFrameOcean.h"

#include "pressRoom.h"

//Biview!

class slideLane {

public:
    slideLane();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Much";
    int heightC = 15;
    float marginC = 2;
    float speedC = 12;
    float delay_ = 1;
    float tilt = PI / 6.;
    
    pressRoom myPressRoom;
        
private:
};
