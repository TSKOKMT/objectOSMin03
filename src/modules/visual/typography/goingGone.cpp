#include "goingGone.h"

//--------------------------------------------------------------
goingGone::goingGone() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void goingGone::draw(ofRectangle frame_, float time_) {
    
    myPressRoom.setText(text_);
    
    bool bHorizontal = myPressRoom.getAspect() > frame_.getAspectRatio();
    
    if (bHorizontal) myPressRoom.setWidth(frame_.width);
    else myPressRoom.setHeight(frame_.height);
    
    for (int i = 0; i < count_; i++) {
        ofFbo fbo;
        if (bHorizontal) fbo.allocate(frame_.width / count_, frame_.height, GL_RGBA, 4);
        else fbo.allocate(frame_.width, frame_.height / count_, GL_RGBA, 4);
        fbo.begin();
        
        ofPushMatrix();
        if (bHorizontal) ofTranslate(-i * (frame_.width / count_), 0);
        else ofTranslate(0, -i * (frame_.height / count_));
        
        float theTime = time_ - delay_ * i;
        
        float motion;
        if (ofWrap(theTime / term_, 0, 2.5) < 1.5) {
            motion = ofNormalize(ofWrap(theTime / term_, 0, 2.5), 0, 1);
            motion = ofxTskokmtMath::cubicBezierByX(ofPoint(1, 0), ofPoint(1, 0), motion);
            motion = ofLerp(0, -1, motion);
        }
        else {
            motion = ofNormalize(ofWrap(theTime / term_, 0, 2.5), 1.5, 2.5);
            motion = ofxTskokmtMath::cubicBezierByX(ofPoint(0, 1), ofPoint(0, 1), motion);
            motion = ofLerp(1, 0, motion);
        }
        
        if (bHorizontal) myPressRoom.draw(frame_.width * motion, frame_.height / 2. - myPressRoom.getHeight() / 2.);
        else myPressRoom.draw(frame_.width / 2. - myPressRoom.getWidth() / 2., frame_.height * motion);
        
        ofPopMatrix();
        
        fbo.end();
        
        if (bHorizontal) fbo.draw(frame_.x + i * (frame_.width / count_), frame_.y);
        else fbo.draw(frame_.x, frame_.y + i * (frame_.height / count_));
    }
}
