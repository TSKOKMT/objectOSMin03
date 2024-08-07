#pragma once

#include "ofMain.h"

#include "ofxTskokmtFont.h"

class rectAnd {

public:
    rectAnd();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_;
    float height = 12;
    float radius = 3;
    
    ofxTskokmtFont font;
        
private:
};
