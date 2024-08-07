#include "kuruKuri.h"

//--------------------------------------------------------------
kuruKuri::kuruKuri() {
    
    font.setPath("font.ttf");
}

//--------------------------------------------------------------
void kuruKuri::draw(ofRectangle frame_, float time_) {
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    float margin_ = margin * unit;
    
    auto frameM = marginBand::get(frame_, margin_);
        
    auto framesVV = framesV(frameM, time_, 2, margin_, term_, false);
    for (int i = 0; i < framesVV.size(); i++) {
        vector<ofRectangle> frames = framesH(framesVV[i], time_, count_, margin_, term_, bAssend_);
        
        for (int i = 0; i < frames.size(); i++) {
            font.setText(ofToString(text_[ofWrap(-floor(i - time_ / (term_ / (float)count_)), 0, text_.size())]));
            font.draw(frames[i]);
        }
    }
}

//--------------------------------------------------------------
vector<ofRectangle> kuruKuri::framesH(ofRectangle frame_, float time_, int count_, float margin_, float term_, bool bAssend_) {
    
    auto frameM = marginBand::get(frame_, ofPoint(-margin_ / 2., 0));
    
    vector<float> progresses;
    progresses.push_back(0);
    for (int i = 0; i < count_; i++) {
        float theTime = time_ - ofMap(i, 0, count_, 0, term_);
        float theProgress = ofNormalize(cos(ofWrap(theTime / term_ * (bAssend_ ? -1 : 1), 0, 1) * PI), 1, -1);
        theProgress = ofNormalize(cos(theProgress * PI), 1, -1);
        theProgress = ofNormalize(cos(theProgress * PI), 1, -1);
        theProgress = ofNormalize(cos(theProgress * PI), 1, -1);
        progresses.push_back(theProgress);
    }
    progresses.push_back(1);
    sort(progresses.rbegin(), progresses.rend());
    
    vector<ofRectangle> frames;
    for (int i = 0; i < progresses.size() - 1; i++) {
        float theX0 = ofLerp(frameM.getLeft(), frameM.getRight(), progresses[i]);
        float theX1 = ofLerp(frameM.getLeft(), frameM.getRight(), progresses[i + 1]);
        float theWidth = ofClamp(theX0 - theX1 - margin_, 0, FLT_MAX);
        auto theFrame = ofRectangle(theX1 + margin_ / 2., frameM.y, theWidth, frameM.height);
        frames.push_back(theFrame);
    }
    
    return frames;
}

//--------------------------------------------------------------
vector<ofRectangle> kuruKuri::framesV(ofRectangle frame_, float time_, int count_, float margin_, float term_, bool bAssend_) {
    
    auto frameM = marginBand::get(frame_, ofPoint(0, -margin_ / 2.));
    
    vector<float> progresses;
    progresses.push_back(0);
    for (int i = 0; i < count_; i++) {
        float theTime = time_ - ofMap(i, 0, count_, 0, term_);
        float theProgress = ofNormalize(cos(ofWrap(theTime / term_ * (bAssend_ ? -1 : 1), 0, 1) * PI), 1, -1);
        theProgress = ofNormalize(cos(theProgress * PI), 1, -1);
        theProgress = ofNormalize(cos(theProgress * PI), 1, -1);
        theProgress = ofNormalize(cos(theProgress * PI), 1, -1);
        progresses.push_back(theProgress);
    }
    progresses.push_back(1);
    sort(progresses.rbegin(), progresses.rend());
    
    vector<ofRectangle> frames;
    for (int i = 0; i < progresses.size() - 1; i++) {
        float theY0 = ofLerp(frameM.getTop(), frameM.getBottom(), progresses[i]);
        float theY1 = ofLerp(frameM.getTop(), frameM.getBottom(), progresses[i + 1]);
        float theHeight = ofClamp(theY0 - theY1 - margin_, 0, FLT_MAX);
        auto theFrame = ofRectangle(frameM.x, theY1 + margin_ / 2., frameM.width, theHeight);
        frames.push_back(theFrame);
    }
    
    return frames;
}
