#pragma once

#include "ofMain.h"

#include "ofxTskokmtMath.h"
#include "ofxFrameOcean.h"

#include "pressRoom.h"

//Biview!

class threeStep {

public:
    threeStep();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Reducting";
    float margin = 2;
    float term_ = 1;
    
    pressRoom myPressRoom;
        
private:
};
