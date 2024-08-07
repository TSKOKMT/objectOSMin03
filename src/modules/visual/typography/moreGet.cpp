#include "moreGet.h"

//--------------------------------------------------------------
moreGet::moreGet() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void moreGet::draw(ofRectangle frame_, float time_) {
    
    /*font.setText(text_);
    font.setHorizontalAlignment(1);
    font.setVerticalAlignment(1);*/
    
    myPressRoom.setText(text_);
    
    float motion = ofClamp(ofWrap(time_ / term_, 0, 1) * 1.1, 0, 1);
    if (ofWrap(time_ / term_, 0, 2) < 1) motion = 1 - motion;
    motion = ofxTskokmtMath::cubicBezierByX(ofPoint(1, 0), ofPoint(0, 1), motion);
    
    for (int i = count_; i >= 0; i--) {
        float theRatio = ofLerp(1, (1 + i * 3.333) / (float)count_, motion);
        if (myPressRoom.getAspect() > frame_.getAspectRatio()) myPressRoom.setWidth(theRatio * frame_.width);
        else myPressRoom.setHeight(theRatio * frame_.height);
        
        ofPushMatrix();
        ofTranslate(frame_.getCenter());
        ofRotateRad(i * TWO_PI / count_ * motion);
        ofSetColor(i % 2 == 0 ? 255 : 0);
        myPressRoom.draw(-myPressRoom.getWidth() / 2., -myPressRoom.getHeight() / 2.);
        ofPopMatrix();
    }
}
