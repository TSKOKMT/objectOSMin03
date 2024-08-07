#include "spaceBold.h"

//--------------------------------------------------------------
spaceBold::spaceBold() {
    
    font.setPath("font.ttf");
}

//--------------------------------------------------------------
void spaceBold::draw(ofRectangle frame_, float time_) {
    
    auto splitTexts = splitString(text_);
    
    string textNoSpace;
    for (int i = 0; i < splitTexts.size(); i++) {
        textNoSpace += splitTexts[i];
    }
    
    font.setText(textNoSpace);
    
    auto unit = sqrt(frame_.width * frame_.height) / 120.;
    
    float margin = unit;
    
    auto frameM = marginBand::get(frame_, margin);
    
    float spacingRatio = spacingRatio_ + 1;
    
    float height = frameM.width / (font.getAspect() * spacingRatio);
    font.setHeight(height);
    
    float totalWidth = 0;
    for (int i = 0; i < splitTexts.size(); i++) {
        font.setText(splitTexts[i]);
        totalWidth += font.getWidth();
    }
    
    float spacing = (frameM.width - totalWidth) / (splitTexts.size() - 1);
    
    float x = frameM.x;
    for (int i = 0; i < splitTexts.size(); i++) {
        font.setText(splitTexts[i]);
        font.draw(x, frameM.y);
        x += font.getWidth() + spacing;
    }
}

//--------------------------------------------------------------
vector<string> spaceBold::splitString(string &input) {
    
    vector<string> result;
    
    istringstream iss(input);
    
    string token;
    while (iss >> token) {
        result.push_back(token);
    }
    
    return result;
}
