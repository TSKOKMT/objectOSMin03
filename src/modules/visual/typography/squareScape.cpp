#include "squareScape.h"

//--------------------------------------------------------------
squareScape::squareScape() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void squareScape::draw(ofRectangle frame_, float time_) {
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    myPressRoom.setText(text_);
    
    float height_ = height * unit;
    float margin_ = margin * unit;
    float speed_ = speed * unit;
    
    for (int i = 0; i < count_; i++) {
        auto theFrame = marginBand::get(frame_, height_ * i);
        
        ofFbo fbo;
        fbo.allocate(theFrame.width, theFrame.height, GL_RGBA, 4);
        fbo.begin();
        ofClear(0);
        drawOne(ofRectangle(0, 0, theFrame.width, theFrame.height), time_, height_, margin_, speed_ * (i % 2 ? -1 : 1));
        fbo.end();
        fbo.draw(theFrame.position);
    }
}

//--------------------------------------------------------------
void squareScape::drawOne(ofRectangle frame_, float time_, float height_, float margin_, float speed_) {
    
    if (frame_.width <= height_ * 2 || frame_.height <= height_ * 2) return;
    
    //font.setText(text_);
    
    if (myPressRoom.getAspect() > 1) {
        myPressRoom.setHeight(height_ - margin_ * 2);
        
        ofPushStyle();
        ofSetColor(backgroundColor_);
        ofDrawRectangle(frame_.getTopLeft(), frame_.width, height_);
        ofDrawRectangle(frame_.getBottomLeft() - ofPoint(0, height_), frame_.width, height_);
        ofPopStyle();
        
        auto framesH = HStack::get(marginBand::get(ofRectangle(0, 0, frame_.width - height_ * 2, height_), ofPoint(0, margin_)), myPressRoom.getWidth(), margin_, frame_.width / 2. - height_ + time_ * speed_);
        
        ofPushMatrix();
        ofTranslate(frame_.getTopLeft());
        ofTranslate(height_, 0);
        for (int i = 0; i < framesH.size(); i++) {
            myPressRoom.draw(framesH[i].position);
        }
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(frame_.getBottomRight());
        ofRotateRad(PI);
        ofTranslate(height_, 0);
        for (int i = 0; i < framesH.size(); i++) {
            myPressRoom.draw(framesH[i].position);
        }
        ofPopMatrix();
        
        ofPushStyle();
        ofSetColor(backgroundColor_);
        ofDrawRectangle(frame_.getTopLeft(), height_, frame_.height);
        ofDrawRectangle(frame_.getTopRight() - ofPoint(height_, 0), height_, frame_.height);
        ofPopStyle();
        
        auto framesV = HStack::get(marginBand::get(ofRectangle(0, 0, frame_.height, height_), ofPoint(0, margin_)), myPressRoom.getWidth(), margin_, frame_.height / 2. + time_ * speed_);
        
        ofPushMatrix();
        ofTranslate(frame_.getTopRight());
        ofRotateRad(HALF_PI);
        for (int i = 0; i < framesV.size(); i++) {
            myPressRoom.draw(framesV[i].position);
        }
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(frame_.getBottomLeft());
        ofRotateRad(-HALF_PI);
        for (int i = 0; i < framesV.size(); i++) {
            myPressRoom.draw(framesV[i].position);
        }
        ofPopMatrix();
    }
    else {
        myPressRoom.setWidth(height_ - margin_ * 2);
        
        ofPushStyle();
        ofSetColor(backgroundColor_);
        ofDrawRectangle(frame_.getTopLeft(), frame_.width, height_);
        ofDrawRectangle(frame_.getBottomLeft() - ofPoint(0, height_), frame_.width, height_);
        ofPopStyle();
        
        auto framesH = VStack::get(marginBand::get(ofRectangle(0, 0, height_, frame_.width - height_ * 2), ofPoint(margin_, 0)), myPressRoom.getHeight(), margin_, frame_.width / 2. - height_ + time_ * speed_);
        
        ofPushMatrix();
        ofTranslate(frame_.getTopLeft());
        ofTranslate(height_, height_);
        ofRotateRad(-HALF_PI);
        for (int i = 0; i < framesH.size(); i++) {
            myPressRoom.draw(framesH[i].position);
        }
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(frame_.getBottomRight());
        ofTranslate(-height_, -height_);
        ofRotateRad(HALF_PI);
        for (int i = 0; i < framesH.size(); i++) {
            myPressRoom.draw(framesH[i].position);
        }
        ofPopMatrix();
        
        ofPushStyle();
        ofSetColor(backgroundColor_);
        ofDrawRectangle(frame_.getTopLeft(), height_, frame_.height);
        ofDrawRectangle(frame_.getTopRight() - ofPoint(height_, 0), height_, frame_.height);
        ofPopStyle();
        
        auto framesV = VStack::get(marginBand::get(ofRectangle(0, 0, height_, frame_.height), ofPoint(margin_, 0)), myPressRoom.getHeight(), margin_, frame_.height / 2. + time_ * speed_);
        
        ofPushMatrix();
        ofTranslate(frame_.getTopRight());
        ofTranslate(-height_, 0);
        for (int i = 0; i < framesV.size(); i++) {
            myPressRoom.draw(framesV[i].position);
        }
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(frame_.getBottomLeft());
        ofTranslate(height_, 0);
        ofRotateRad(PI);
        for (int i = 0; i < framesV.size(); i++) {
            myPressRoom.draw(framesV[i].position);
        }
        ofPopMatrix();
    }
}
