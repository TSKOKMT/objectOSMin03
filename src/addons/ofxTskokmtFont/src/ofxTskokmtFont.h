#pragma once

#include "ofMain.h"

#include "ofxFontStash.h"

class ofxTskokmtFont {
    
public:
    void loadText(string path_);
    void setText(string text_);
    void setPath(string path_);
    bool isLoaded();
    void setPosition(float x_, float y_);
    void setPosition(ofPoint position_);
    void setHeight(float height_);
    void setWidth(float width_);
    void setWidthAndHeight(float width_, float height_);
    void setFrame(ofRectangle frame_);
    void setHorizontalAlignment(int alignment_);
    void setVerticalAlignment(int alignment_);
    void setCharacterSpacing(float spacing_);
    
    string getText();
    float getWidthRaw();
    float getWidth();
    float getHeight();
    float getAspect();
    ofRectangle getBoundingBox();
    
    void draw(int only_ = -1);
    void draw(float x_, float y_);
    void draw(ofPoint position_);
    void draw(ofRectangle frame_);
    
    vector<float> getWidthes();
    vector<float> getPositions();
    
private:
    string text = "Hello?";
    string path = "/Users/tskokmt/Library/Fonts/NHaasGroteskTXPro-65Md.ttf";
    ofPoint position = ofPoint(0, 0);
    float height = 120;
    float virtualHeight = 540;
    float magnification = 1;
    int horizontalAlignment = 0;
    int verticalAlignment = 0;
    float characterSpacing = 0;
    float scaleRatio = 1;
    
    ofxFontStash fontStash;
    
    ofFile file;
};
