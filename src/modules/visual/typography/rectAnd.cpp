#include "rectAnd.h"

//--------------------------------------------------------------
rectAnd::rectAnd() {
    
    font.setPath("font.ttf");
}

//--------------------------------------------------------------
void rectAnd::draw(ofRectangle frame_, float time_) {
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    text_ = ofToString((int)ofRandom(10000));
    
    float height_ = height * unit;
    
    float radius_ = radius * unit;
    
    font.setHeight(height_ / 2.);
    font.setText(text_);
    float width = font.getWidth();
    width += height_ / 3. * 2;
    font.setHorizontalAlignment(1);
    font.setVerticalAlignment(1);
    
    ofPushMatrix();
    ofTranslate(frame_.getCenter());
    
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(unit / 2.);
    ofDrawRectRounded(-width / 2., -height_ / 2., width, height_, radius_);
    ofPopStyle();
    
    font.draw();
    
    ofPopMatrix();
}
