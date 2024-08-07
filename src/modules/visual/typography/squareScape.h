#pragma once

#include "ofMain.h"

#include "ofxTskokmtMath.h"
#include "ofxFrameOcean.h"

#include "pressRoom.h"

//Biview!

class squareScape {

public:
    squareScape();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Worth";
    int count_ = 3;
    float height = 16;
    float margin = 2;
    float speed = 30;
    ofColor backgroundColor_ = ofColor(0);
    
    pressRoom myPressRoom;
        
private:
    void drawOne(ofRectangle frame_, float time_, float height_, float margin_, float speed_);
};
