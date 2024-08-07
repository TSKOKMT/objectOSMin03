#include "longLonger.h"

//--------------------------------------------------------------
longLonger::longLonger() {
    
    font.setPath("font.ttf");
}

//--------------------------------------------------------------
void longLonger::draw(ofRectangle frame_, float time_) {
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    float margin = .5 * unit;
    
    auto frameM = marginBand::get(frame_, unit);
    
    auto framesH = HStack::get(frameM, (int)text_.size(), unit);
    for (int h = 0; h < framesH.size(); h++) {
        font.setText(ofToString(text_[h]));
        
        float theTime = time_ - h * delay;
        
        float motion = ofWrap(theTime / term, 0, 1);
        if (ofWrap(theTime / term, 0, 2) < 1) motion = 1 - motion;
        
        int factor = floor(ofLerp(1, 13, pow(motion, 2)));
        factor = ofClamp(factor, 1, INT_MAX);
        factor = factor * 2 - 1;
            
        float theAspect = framesH[h].width / framesH[h].height;
        auto framesHH = HStack::get(framesH[h], factor, margin);
        for (int hh = 0; hh < framesHH.size(); hh++) {
            auto framesVV = VStack::get(framesHH[hh], factor, margin);
            for (int vv = 0; vv < framesVV.size(); vv++) {
                font.draw(framesVV[vv]);
            }
        }
    }
}
