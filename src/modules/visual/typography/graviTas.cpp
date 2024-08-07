#include "graviTas.h"

//--------------------------------------------------------------
graviTas::graviTas() {
    
    font.setPath("font.ttf");
}

//--------------------------------------------------------------
void graviTas::draw(ofRectangle frame_, float time_) {
    
    //UPDATE
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    float margin_ = margin * unit;
    
    auto frameM = marginBand::get(frame_, margin_);
    
    font.setText(text_);
    font.setWidth(frameM.width);
    
    //DRAW
    
    ofFbo fbo;
    fbo.allocate(frame_.width, frame_.height, GL_RGBA, 4);
    fbo.begin();
    ofClear(0);
    ofPushMatrix();
    ofTranslate(-frame_.position);
    
    for (int i = 0; i < text_.size(); i++) {
        for (int j = 0; j < count_; j++) {
            float delayedTime = time_ - delayH_ * i + delayV_ * j;
            float motion = ofClamp(ofWrap(delayedTime, 0, interval_) / term_, 0, 1);
            motion = pow(motion, 6);
            //motion = ofxTskokmtMath::cubicBezierByX(ofPoint(1, 0), ofPoint(1, .5), motion);
            font.setPosition(frame_.x, ofLerp(frameM.getTop(), frame_.getBottom() + margin_, motion));
            font.draw(i);
        }
    }
    
    ofPopMatrix();
    fbo.end();
    fbo.draw(frame_.position);
}
