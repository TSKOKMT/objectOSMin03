#pragma once

#include "ofMain.h"

#include "ofxTskokmtMath.h"
#include "ofxTskokmtFont.h"
#include "ofxFrameOcean.h"

class graviTas {

public:
    graviTas();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Success";
    float margin = 2;
    int count_ = 7;
    float interval_ = 3;
    float term_ = 2;
    float delayH_ = .2;
    float delayV_ = .2;
    
    ofxTskokmtFont font;
    
private:
};
