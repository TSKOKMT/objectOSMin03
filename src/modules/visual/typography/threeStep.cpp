#include "threeStep.h"

//--------------------------------------------------------------
threeStep::threeStep() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void threeStep::draw(ofRectangle frame_, float time_) {
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    myPressRoom.setText(text_);
    
    float margin_ = margin * unit;
    
    auto frameM = marginBand::get(frame_, margin_);
    
    float motion = ofClamp(ofWrap(time_ / term_ * 4, 0, 1) * 2, 0, 1);
    motion = ofxTskokmtMath::cubicBezierByX(ofPoint(.25, 0), ofPoint(.75, 1), motion);
    
    vector<ofRectangle> frames;
    frames.resize(5);
    //Up
    if (myPressRoom.getAspect() > 1) {
        frames[0] = ofRectangle(frameM.x, frameM.getBottom(), frameM.width, 0);
        frames[1] = ofRectangle(frameM.x, frameM.y + frameM.height / 4. * 3, frameM.width, frameM.height / 4.);
        frames[2] = frameM;
        frames[3] = ofRectangle(frameM.x, frameM.y, frameM.width, frameM.height / 4.);
        frames[4] = ofRectangle(frameM.x, frameM.y, frameM.width, 0);
    }
    //Left
    else {
        frames[0] = ofRectangle(frameM.getRight(), frameM.y, 0, frameM.height);
        frames[1] = ofRectangle(frameM.x + frameM.width / 4. * 3, frameM.y, frameM.width / 4., frameM.height);
        frames[2] = frameM;
        frames[3] = ofRectangle(frameM.x, frameM.y, frameM.width / 4., frameM.height);
        frames[4] = ofRectangle(frameM.x, frameM.y, 0, frameM.height);
    }
    
    ofRectangle theFrame;
    for (int i = 0; i < 4; i++) {
        float progress = ofWrap(time_ / term_, 0, 1) * 4;
        if (i <= progress && progress < i + 1) theFrame = ofxTskokmtMath::map(motion, 0, 1, frames[i], frames[i + 1]);
    }
    myPressRoom.draw(theFrame);
}
