#include "merryRound.h"

//--------------------------------------------------------------
merryRound::merryRound() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void merryRound::draw(ofRectangle frame_, float time_) {
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    float radius_ = radius * unit;
    float minHeight_ = minHeight * unit;
    float maxHeight_ = maxHeight * unit;
    
    float clock_ = time_ / clockTerm * TWO_PI;
    float rotation_ = time_ / rotaionTerm * TWO_PI;
    
    myPressRoom.setText(text_);
    
    ofPushMatrix();
    ofTranslate(frame_.getCenter());
    ofRotateRad(clock_);
    
    for (int i = 0; i < count_; i++) {
        float theTime = time_ - delay_ * i;

        float theMotion = ofClamp(ofWrap(theTime / term_, 0, 1), 0, 1);
        theMotion = ofxTskokmtMath::cubicBezierByX(ofPoint(.85, 0), ofPoint(.15, 1), theMotion);
        if (ofWrap(theTime / term_, 0, 2) < 1) theMotion = 1 - theMotion;
        
        myPressRoom.setHeight(ofLerp(minHeight_, maxHeight_, theMotion));
        
        float theAngle = ofMap(i, 0, count_, 0, TWO_PI);
        ofPushMatrix();
        ofRotateRad(theAngle);
        ofTranslate(radius_, 0);
        ofRotateRad(rotation_);
        myPressRoom.draw(-myPressRoom.getWidth() / 2., -myPressRoom.getHeight() / 2.);
        ofPopMatrix();
    }
    
    ofPopMatrix();
}
