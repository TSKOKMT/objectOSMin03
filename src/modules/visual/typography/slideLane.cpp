#include "slideLane.h"

//--------------------------------------------------------------
slideLane::slideLane() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void slideLane::draw(ofRectangle frame_, float time_) {
    
    //UPDATE
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    myPressRoom.setText(text_);
    
    float height = heightC * unit;
    float margin = marginC * unit;
    float speed = speedC * unit;
    
    ofRectangle bigFrame;
    bigFrame.width = abs(cos(PI / 4.)) * frame_.width + abs(sin(PI / 4.)) * frame_.height;
    bigFrame.height = abs(sin(PI / 4.)) * frame_.width + abs(cos(PI / 4.)) * frame_.height;
    bigFrame.x = -bigFrame.width / 2.;
    bigFrame.y = -bigFrame.height / 2.;
    
    auto frameM = marginBand::get(bigFrame, ofPoint(0, margin));
    
    vector<ofRectangle> framesL;
    if (myPressRoom.getAspect() > 1) framesL = VStack::get(frameM, (int)round(frameM.height / height), margin);
    else framesL = HStack::get(frameM, (int)round(frameM.width / height), margin);
    
    //DRAW
    
    ofFbo fbo;
    fbo.allocate(frame_.width, frame_.height, GL_RGBA, 4);
    fbo.begin();
    ofClear(0);
    ofPushMatrix();
    ofTranslate(-frame_.position);
    
    ofTranslate(frame_.getCenter());
    ofRotateRad(tilt);
    
    for (int l = 0; l < framesL.size(); l++) {
        auto frameL = framesL[l];
        
        float theTime = time_ - delay_ * l;
        float thePosition = speed * theTime * (l % 2 ? -1 : 1);
        
        vector<ofRectangle> framesI;
        if (myPressRoom.getAspect() > 1) {
            myPressRoom.setHeight(frameL.height);
            framesI = HStack::get(frameL, myPressRoom.getWidth(), margin, frameL.width / 2. + thePosition);
        }
        else {
            myPressRoom.setWidth(frameL.width);
            framesI = VStack::get(frameL, myPressRoom.getHeight(), margin, frameL.height / 2. + thePosition);
        }
        
        for (int i = 0; i < framesI.size(); i++) {
            myPressRoom.draw(framesI[i].position);
        }
    }
    
    ofPopMatrix();
    fbo.end();
    fbo.draw(frame_.position);
}
