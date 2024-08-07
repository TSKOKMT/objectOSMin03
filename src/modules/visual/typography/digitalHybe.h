#pragma once

#include "ofMain.h"

#include "ofxTskokmtFont.h"
#include "ofxFrameOcean.h"

class digitalHybe {

public:
    digitalHybe();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Greet";
    float height = 12;
    float margin = 2;
    float term_ = 1;
    float interval = 2;
    
    ofxTskokmtFont font;
        
private:
};
