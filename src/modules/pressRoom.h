#pragma once

#include "ofMain.h"

#include "ofxTskokmtFont.h"

class pressRoom {
    
public:
    void loadFont(string path_);
    
    void setText(string text_);
    void setImage(string path_);
    
    void setWidth(float width_);
    void setHeight(float height_);
    float getWidth();
    float getHeight();
    
    float getAspect();
    
    void draw(ofRectangle frame_);
    void draw(ofPoint position_);
    void draw(float x_, float y_);
    
    bool bText = true;
    
private:
    float width;
    float height;
    
    ofxTskokmtFont font;
    ofImage image;
    
    string imagePath;
};
