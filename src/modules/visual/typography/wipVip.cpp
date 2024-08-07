#include "wipVip.h"

//--------------------------------------------------------------
wipVip::wipVip() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void wipVip::draw(ofRectangle frame_, float time_) {
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    myPressRoom.setText(text_);
    
    float margin_ = margin * unit;
    
    auto frameM = marginBand::get(frame_, margin_);
    
    for (int i = 0; i < count; i++) {
        float theTime = time_ - ofMap(i, 0, count, 0, term_ / 2.);
        
        float theMotion = ofClamp(ofWrap(theTime / term_, 0, 1) * 2, 0, 1);
        theMotion = ofxTskokmtMath::cubicBezierByX(ofPoint(motionStrength, 0), ofPoint(1 - motionStrength, 1), theMotion);
        if (ofWrap(theTime / term_, 0, 2) > 1) theMotion = 1 - theMotion;
        
        if (myPressRoom.getAspect() > 1) {
            myPressRoom.setWidth(frameM.width);
            
            ofPushMatrix();
            ofTranslate(frameM.x, ofLerp(frameM.getTop(), frameM.getBottom() - myPressRoom.getHeight(), theMotion));
            myPressRoom.draw(0, 0);
            ofPopMatrix();
        }
        else {
            myPressRoom.setHeight(frameM.height);
            
            ofPushMatrix();
            ofTranslate(ofLerp(frameM.getLeft(), frameM.getRight() - myPressRoom.getWidth(), theMotion), frameM.y);
            myPressRoom.draw(0, 0);
            ofPopMatrix();
        }
    }
}
