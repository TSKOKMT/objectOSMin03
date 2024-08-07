#pragma once

#include "ofMain.h"

#include "ofxFrameOcean.h"

#include "pressRoom.h"

class diveWave {

public:
    diveWave();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Dive";
    float textSpeed = 12;
    int countV = 15;
    float fieldSizeH = 2000;
    float fieldSizeD = 2000;
    float waveHeight = 1000;
    float waveSpeed = .2;
    float waveSpeedD = -500;
    float waveSize = 1500;
    
    pressRoom myPressRoom;
        
private:
    float getWave(float x_, float z_, float time_);
};
