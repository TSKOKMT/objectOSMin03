#include "echoChamber.h"

//--------------------------------------------------------------
echoChamber::echoChamber() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void echoChamber::draw(ofRectangle frame_, float time_) {
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    myPressRoom.setText(text_);
    
    float margin_ = margin * unit;
    
    bool bHorizontal = myPressRoom.getAspect() > 1;
    
    vector<ofRectangle> framesL;
    if (bHorizontal) framesL = VStack::get(marginBand::get(frame_, ofPoint(0, margin_)), count_, margin_);
    else framesL = HStack::get(marginBand::get(frame_, ofPoint(margin_, 0)), count_, margin_);
    
    for (int l = 0; l < framesL.size(); l++) {
        auto frameL = framesL[l];
        
        float theTime = time_ - delay_ * l;
        
        if (bHorizontal) myPressRoom.setHeight(frameL.height);
        else myPressRoom.setWidth(frameL.width);
        
        float w;
        if (bHorizontal) w = frameL.getCenter().x - myPressRoom.getWidth() / 2.;
        else w = frameL.getCenter().y - myPressRoom.getHeight() / 2.;
        
        if (ofWrap(theTime / term_, 0, 3) < 1) {
            float motion = ofWrap(theTime / term_, 0, 1);
            motion = ofxTskokmtMath::cubicBezierByX(ofPoint(0, 1), ofPoint(0, 1), motion);
            motion = 1 - motion;
            
            if (bHorizontal) myPressRoom.draw(w, frameL.y + motion * frameL.height);
            else myPressRoom.draw(frameL.x + motion * frameL.width, w);
        }
        else if (ofWrap(theTime / term_, 0, 3) < 1.5) {
            if (bHorizontal) myPressRoom.draw(w, frameL.y);
            else myPressRoom.draw(frameL.x, w);
        }
        else if (ofWrap(theTime / term_, 0, 3) < 2.5) {
            float motion = ofWrap((theTime + .5) / term_, 0, 1);
            motion = ofxTskokmtMath::cubicBezierByX(ofPoint(1, 0), ofPoint(1, 0), motion);
            
            if (bHorizontal) myPressRoom.draw(w, frameL.y - motion * frameL.height);
            else myPressRoom.draw(frameL.x - motion * frameL.width, w);
        }
    }
}
