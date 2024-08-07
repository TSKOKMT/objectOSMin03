#pragma once

#include <algorithm>

#include "ofMain.h"

#include "ofxTskokmtFont.h"
#include "ofxFrameOcean.h"

class spaceBold {

public:
    spaceBold();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "One Two Three";
    float spacingRatio_ = 1;
    
    ofxTskokmtFont font;
        
private:
    vector<string> splitString(string &input);
};
