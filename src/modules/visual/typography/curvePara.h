#pragma once

#include "ofMain.h"

#include "ofxTskokmtFont.h"
#include "ofxFrameOcean.h"
#include "ofxSvg.h"

class curvePara {

public:
    curvePara();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Superior";
    float height = 30;
    
    ofxTskokmtFont font;
        
private:
    ofPolyline polyline_;
};
