#include "emergeScreen.h"

//--------------------------------------------------------------
vector<ofRectangle> emergeScreen::get(ofRectangle frame_, float time_) {

    vector<ofRectangle> grids_;
    
    //Prepare ratios
    vector<float> ratios;
    ratios.resize(pow(2, (float)count_) - 1);
    
    //Set ratios
    for (int i = 0; i < ratios.size(); i++) {
        float delayedTime = time_ - delay_ * i;
        ratios[i] = ofWrap(delayedTime / term_, 0, 1);
        ratios[i] = ofxTskokmtMath::cubicBezierByX(ofPoint(motionStrength_, 0), ofPoint(1 - motionStrength_, 1), ratios[i]);
        if (ofWrap(delayedTime / term_, 0, 2) >= 1) ratios[i] = 1 - ratios[i];
        ratios[i] = ofLerp(ofLerp(.5, 0, strength_), ofLerp(.5, 1, strength_), ratios[i]);
    }
    
    //Set margin frame
    ofRectangle frameM = marginBand::get(frame_, margin_);
    
    //Set grids
    grids_.push_back(frameM);
    int vol = 0;
    bool bLoop = true;
    while (bLoop) {
        for (int c = 0; c < pow(2, vol); c++) {
            int i = pow(2, vol) + c - 1;
            
            if (i >= ratios.size()) {
                bLoop = false;
                break;
            }
            
            auto targetFrame = grids_[c];
            
            //Add
            grids_.push_back(targetFrame);
            
            //Devide H
            if (vol % 2 == 0) {
                grids_[c].width = ofClamp(ofLerp(-margin_, targetFrame.width, ratios[i]), 0, targetFrame.width);
                grids_.back().width = ofClamp(ofLerp(-margin_, targetFrame.width, 1 - ratios[i]), 0, targetFrame.width);
                grids_.back().x = targetFrame.getRight() - grids_.back().width;
            }
            //Devide V
            else {
                grids_[c].height = ofClamp(ofLerp(-margin_, targetFrame.height, ratios[i]), 0, targetFrame.height);
                grids_.back().height = ofClamp(ofLerp(-margin_, targetFrame.height, 1 - ratios[i]), 0, targetFrame.height);
                grids_.back().y = targetFrame.getBottom() - grids_.back().height;
            }
        }
        vol++;
    }
    
    return grids_;
}
