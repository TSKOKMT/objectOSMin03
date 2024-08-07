#include "quickBrown.h"

//--------------------------------------------------------------
quickBrown::quickBrown() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void quickBrown::draw(ofRectangle frame_, float time_) {
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    float margin_ = margin * unit;
    
    myPressRoom.setText(text_);
    
    auto frameM = marginBand::get(frame_, margin_);
    
    vector<ofRectangle> framesL;
    if (myPressRoom.getAspect() > 1) {
        int count_ = round(frame_.height / (height * unit));
        if (count_ < 1) count_ = 1;
        framesL = VStack::get(frameM, count_, margin_);
    }
    else {
        int count_ = round(frame_.width / (height * unit));
        if (count_ < 1) count_ = 1;
        framesL = HStack::get(frameM, count_, margin_);
    }
    
    for (int l = 0; l < framesL.size(); l++) {
        auto frameL = framesL[l];
        
        float theTime = time_ - delay_ * l;
        float motion = ofWrap(theTime / term_, 0, 1);
        motion = ofxTskokmtMath::cubicBezierByX(ofPoint(motionStrength_, 0), ofPoint(1 - motionStrength_, 1), motion);
        if (ofWrap(theTime / term_, 0, 2) > 1) motion = 1 - motion;
        
        if (myPressRoom.getAspect() > 1) {
            myPressRoom.setHeight(frameL.height);
            float theX = ofLerp(0, frameL.width - myPressRoom.getWidth(), motion);
            myPressRoom.draw(frameL.position + ofPoint(theX, 0));
        }
        else {
            myPressRoom.setWidth(frameL.width);
            float theY = ofLerp(0, frameL.height - myPressRoom.getHeight(), motion);
            myPressRoom.draw(frameL.position + ofPoint(0, theY));
        }
    }
}
