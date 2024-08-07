#pragma once

#include "ofMain.h"

#include "ofxTskokmtFont.h"
#include "ofxFrameOcean.h"

class fieldWork {

public:
    fieldWork();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Shibuya";
    float height = 30;
    
    ofxTskokmtFont font;
        
private:
};
