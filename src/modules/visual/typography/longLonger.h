#pragma once

#include "ofMain.h"

#include "ofxTskokmtFont.h"
#include "ofxFrameOcean.h"

class longLonger {

public:
    longLonger();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Plastic";
    float term = 2;
    float delay = .5;
    
    ofxTskokmtFont font;
        
private:
};
