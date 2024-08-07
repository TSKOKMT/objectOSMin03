#pragma once

#include "ofMain.h"

#include "ofxTskokmtFont.h"
#include "ofxFrameOcean.h"

class kuruKuri {

public:
    kuruKuri();
    
    void draw(ofRectangle frame_, float time_);
    
    string text_ = "Now";
    int count_ = 11;
    float margin = 2;
    float term_ = 5;
    bool bAssend_ = true;
    
    ofxTskokmtFont font;
    
private:
    vector<ofRectangle> framesH(ofRectangle frame_, float time_, int count_, float margin_, float term_, bool bAssend_ = false);
    vector<ofRectangle> framesV(ofRectangle frame_, float time_, int count_, float margin_, float term_, bool bAssend_ = false);
};
