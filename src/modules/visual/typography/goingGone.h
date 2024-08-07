#pragma once

#include "ofMain.h"

#include "ofxTskokmtMath.h"

#include "pressRoom.h"

//Biview!

class goingGone {

public:
    goingGone();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "After";
    float term_ = 1;
    int count_ = 12;
    float delay_ = .06;
    
    pressRoom myPressRoom;
        
private:
};
