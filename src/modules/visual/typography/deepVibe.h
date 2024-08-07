#pragma once

#include "ofMain.h"

#include "ofxTskokmtMath.h"
#include "ofxTskokmtFont.h"
#include "ofxFrameOcean.h"

#include "pressRoom.h"

//Biview!

class deepVibe {

public:
    deepVibe();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Ok";
    int lane = 3;
    int count_ = 4;
    float margin = 2;
    float term_ = 1;
    
    pressRoom myPressRoom;
    
private:
    void drawOne(ofRectangle frame_, float time_);
};
