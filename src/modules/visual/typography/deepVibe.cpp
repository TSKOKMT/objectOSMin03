#include "deepVibe.h"

//--------------------------------------------------------------
deepVibe::deepVibe() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void deepVibe::draw(ofRectangle frame_, float time_) {
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    float margin_ = margin * unit;
        
    auto frameM = marginBand::get(frame_, margin_);
    
    myPressRoom.setText(text_);

    vector<ofRectangle> framesL;
    if (myPressRoom.getAspect() > 1) framesL = HStack::get(frameM, lane, margin_);
    else framesL = VStack::get(frameM, lane, margin_);
    
    for (int l = 0; l < framesL.size(); l++) {
        ofSetColor(255);
        drawOne(framesL[l], time_ - l);
    }
}

//--------------------------------------------------------------
void deepVibe::drawOne(ofRectangle frame_, float time_) {
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    float margin_ = margin * unit;
    
    bool bHorizontal = myPressRoom.getAspect() > 1;
    
    if (bHorizontal) myPressRoom.setWidth(frame_.width);
    else myPressRoom.setHeight(frame_.height);
    
    float motion = ofClamp(ofWrap(time_ / term_, 0, 1), 0, 1);
    if (ofWrap(time_ / term_, 0, 2) < 1) motion = 1 - motion;
    motion = ofxTskokmtMath::cubicBezierByX(ofPoint(1, 0), ofPoint(0, 1), motion);
    
    float motionC = ofClamp(ofWrap(time_ / (term_), 0, 1), 0, 1);
    motionC = ofxTskokmtMath::cubicBezierByX(ofPoint(1, 0), ofPoint(0, 1), motionC);
    if (ofWrap(time_ / (term_), 0, 3) < 1) motionC = ofLerp(.5, 1, motionC);
    else if (ofWrap(time_ / (term_), 0, 3) < 2) motionC = ofLerp(1, 0, motionC);
    else motionC = ofLerp(0, .5, motionC);
    
    float center;
    if (bHorizontal) center = ofLerp(frame_.getTop() + myPressRoom.getHeight() / 2., frame_.getBottom() - myPressRoom.getHeight() / 2., motionC);
    else center = ofLerp(frame_.getLeft() + myPressRoom.getWidth() / 2., frame_.getRight() - myPressRoom.getWidth() / 2., motionC);
    
    for (int i = count_; i >= 0; i--) {
        float position = ofNormalize(i, 0, count_);
        position = sin(position * HALF_PI);
        
        if (bHorizontal) {
            //Top wing
            float beginY = center - myPressRoom.getHeight() / 2.;
            float theY = ofLerp(beginY, ofLerp(beginY, frame_.getTop(), motion), position);
            //font.setVerticalAlignment(0);
            ofSetColor(0);
            ofRectangle frameB = marginBand::get(ofRectangle(frame_.x, theY, myPressRoom.getWidth(), myPressRoom.getHeight()), ofPoint(0, -margin_));
            ofDrawRectangle(frameB);
            ofSetColor(255);
            //ofDrawRectangle(frameM.x, theY, font.getWidth(), font.getHeight());
            myPressRoom.draw(frame_.x, theY);
            
            //Bottom wing
            beginY = center + myPressRoom.getHeight() / 2.;
            theY = ofLerp(beginY, ofLerp(beginY, frame_.getBottom(), motion), position);
            //font.setVerticalAlignment(2);
            ofSetColor(0);
            frameB = marginBand::get(ofRectangle(frame_.x, theY - myPressRoom.getHeight(), myPressRoom.getWidth(), myPressRoom.getHeight()), ofPoint(0, -margin_));
            ofDrawRectangle(frameB);
            ofSetColor(255);
            //ofDrawRectangle(frameM.x, theY - font.getHeight(), font.getWidth(), font.getHeight());
            myPressRoom.draw(frame_.x, theY - myPressRoom.getHeight());
        }
        else {
            //Left wing
            float beginX = center - myPressRoom.getWidth() / 2.;
            float theX = ofLerp(beginX, ofLerp(beginX, frame_.getLeft(), motion), position);
            ofSetColor(0);
            ofRectangle frameB = marginBand::get(ofRectangle(theX, frame_.y, myPressRoom.getWidth(), myPressRoom.getHeight()), ofPoint(-margin_, 0));
            ofDrawRectangle(frameB);
            ofSetColor(255);
            myPressRoom.draw(theX, frame_.y);
            
            //Right wing
            beginX = center + myPressRoom.getWidth() / 2.;
            theX = ofLerp(beginX, ofLerp(beginX, frame_.getRight(), motion), position);
            ofSetColor(0);
            frameB = marginBand::get(ofRectangle(theX - myPressRoom.getWidth(), frame_.y, myPressRoom.getWidth(), myPressRoom.getHeight()), ofPoint(-margin_, 0));
            ofDrawRectangle(frameB);
            ofSetColor(255);
            myPressRoom.draw(theX - myPressRoom.getWidth(), frame_.y);
        }
    }
}
