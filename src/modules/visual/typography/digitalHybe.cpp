#include "digitalHybe.h"

//--------------------------------------------------------------
digitalHybe::digitalHybe() {
    
    font.setPath("font.ttf");
}

//--------------------------------------------------------------
void digitalHybe::draw(ofRectangle frame_, float time) {
    
    //UPDATE
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    float height_ = height * unit;
    float margin_ = margin * unit;
    
    float beginTime = floor(time / interval) * interval;
    
    font.setText(text_);
    //font.setWidth(frame_.width - margin_ * 2);
    font.setHeight(height_);
    font.setHorizontalAlignment(1);
    font.setVerticalAlignment(1);
    font.setPosition(frame_.getCenter());
    
    float motion = ofNormalize(time - beginTime, 0, term_);
    motion = ofxTskokmtMath::cubicBezierByX(ofPoint(0, 0), ofPoint(.5, 1), motion);
    string newText = "";
    if (motion < .5) {
        float p = ofNormalize(motion, 0, .5);
        for (int i = 0; i < text_.size(); i++) {
            if (ofRandom(1) < p) newText.push_back((char)ofRandom(33, 125 + 1));
            else newText.push_back(' ');
        }
    }
    else {
        float p = ofNormalize(motion, .5, 1);
        for (int i = 0; i < text_.size(); i++) {
            if (ofRandom(1) < p) newText.push_back(text_[i]);
            else newText.push_back((char)ofRandom(33, 125 + 1));
        }
    }
    font.setText(newText);
    
    //DRAW
    
    for (int i = 0; i < text_.size(); i++) {
        font.draw(i);
    }
}
