#pragma once

#include "ofMain.h"

#include "ofxTskokmtMath.h"

#include "pressRoom.h"

//Biview!

class moreGet {

public:
    moreGet();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "What";
    int count_ = 120;
    float term_ = 2;
    
    pressRoom myPressRoom;
        
private:
};
