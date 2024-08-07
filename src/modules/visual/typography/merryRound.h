#pragma once

#include "ofMain.h"

#include "ofxFrameOcean.h"

#include "pressRoom.h"

class merryRound {

public:
    merryRound();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Sometime";
    int count_ = 11;
    float radius = 36;
    float minHeight = 3;
    float maxHeight = 9;
    float term_ = 1;
    float delay_ = 0;
    float clockTerm = 12;
    float rotaionTerm = 4;
    
    pressRoom myPressRoom;
        
private:
};
