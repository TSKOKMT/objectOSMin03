#include "alphaDelta.h"

//--------------------------------------------------------------
alphaDelta::alphaDelta() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void alphaDelta::draw(ofRectangle frame_, float time_) {
    
    //UPDATE
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    float margin_ = margin * unit;
    
    myPressRoom.setText(text_);
    
    auto frameM = marginBand::get(frame_, margin_);
    
    float motion = ofClamp(ofWrap(time_ / term_, 0, 1), 0, 1);
    motion = ofxTskokmtMath::cubicBezierByX(ofPoint(.95, 0), ofPoint(.05, 1), motion);
    if (ofWrap(time_ / term_, 0, 4) > 2) motion = 1 - motion;
    
    vector<float> weights;
    weights.resize(count_);
    for (int i = 0; i < count_; i++) {
        /*float index = ofLerp(i, count_ - 1 - i, motion);
        float theWeight = ofMap(index, -1, count_ - 1, 0, 1) * pow(1.5, index);
        weights[i] = 1 - theWeight;*/
        
        float weight0 = ofMap(i, -1, count_, 0, 1);
        weight0 = pow(weight0, 2);
        float weight1 = ofMap(i, -1, count_, 1, 0);
        weight1 = pow(weight1, 2);
        weights[i] = ofLerp(weight0, weight1, motion);
    }
    
    //DRAW
    
    ofFbo fbo;
    fbo.allocate(frame_.width, frame_.height, GL_RGBA, 4);
    fbo.begin();
    ofClear(0);
    ofPushMatrix();
    ofTranslate(-frame_.position);
    
    vector<ofRectangle> framesL;
    if (myPressRoom.getAspect() > 1) framesL = VStack::get(frameM, weights, margin_);
    else framesL = HStack::get(frameM, weights, margin_);
    
    for (int l = 0; l < framesL.size(); l++) {
        auto frameL = framesL[l];
        
        //ofDrawRectangle(frameL);
        
        vector<ofRectangle> framesI;
        if (myPressRoom.getAspect() > 1) {
            myPressRoom.setHeight(frameL.height);
            float position = ofWrap(time_, 0, 10) * frameL.height * speed + frameL.getCenter().x;
            framesI = HStack::get(frameL, frameL.height * myPressRoom.getAspect(), margin_, position);
        }
        else {
            myPressRoom.setWidth(frameL.width);
            float position = ofWrap(time_, 0, 10) * frameL.width * speed + frameL.getCenter().x;
            framesI = VStack::get(frameL, frameL.width / myPressRoom.getAspect(), margin_, position);
        }
        
        for (int i = 0; i < framesI.size(); i++) {
            //font.draw(framesH[h].position);
            myPressRoom.draw(framesI[i]);
        }
    }
    
    ofPopMatrix();
    fbo.end();
    fbo.draw(frame_.position);
}
