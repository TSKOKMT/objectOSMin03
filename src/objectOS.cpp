#include "objectOS.h"

//--------------------------------------------------------------
objectOS::objectOS() {
    
    setColorMono();
}

//--------------------------------------------------------------
void objectOS::draw(ofRectangle frame_, float time_) {
    
    newTime_ += (time_ - previousTime) * (125 / 60.);
    if (frameRate > 0) newTime_ = floor(newTime_ * frameRate) / (float)frameRate;
    
    previousTime = time_;
    
    if (paletteShiftTerm > 0) paletteShift = floor(newTime_ / paletteShiftTerm);
    
    //Set screens
    vector<ofRectangle> screens;
    if (screenIndex == 0) screens.push_back(frame_);
    else if (screenIndex == 1) screens = myVipGrid.get(frame_, newTime_);
    else if (screenIndex == 2) screens = mySlideGrid.get(frame_, newTime_);
    else if (screenIndex == 3) screens = myPushGrid.get(frame_, newTime_);
    else screens = myEmergeScreen.get(frame_, newTime_);
    
    //Set english
    string englishWord = myWordCloud.englishes[englishIndex];
    if (moduleIndex == 0) myAlphaDelta.text_ = englishWord;
    if (moduleIndex == 1) myCurvePara.text_ = englishWord;
    
    //Create & begin fbo
    ofFbo fbo;
    fbo.allocate(frame_.width, frame_.height, GL_RGB, 4);
    fbo.begin();
    ofClear(0);
    
    //Draw module
    for (int i = 0; i < screens.size(); i++) {
        auto screen = screens[i];
        
        float newTime = newTime_ - i * screenDelay;
     
        //graphic
        if (moduleIndex == 0) myAlphaDelta.draw(screen, newTime);
        if (moduleIndex == 1) myCurvePara.draw(screen, newTime);
    }
    
    fbo.end();
    
    //palette
    vector<ofColor> palette;
    if (paletteIndex == 0) palette = myColorCloud.mono;
    else if (paletteIndex == 1) palette = myColorCloud.rgb;
    else if (paletteIndex == 2) palette = myColorCloud.six;
    else if (paletteIndex == 3) palette = myColorCloud.sakamoto;
    else palette = myColorCloud.ikko;
    
    auto paletteShelter = palette;
    for (int i = 0; i < palette.size(); i++) {
        palette[i] = paletteShelter[ofWrap(i + paletteShift, 0, (int)palette.size())];
    }

    //chrome
    ofFbo fboC;
    fboC.allocate(frame_.width, frame_.height, GL_RGB, 4);
    fboC.begin();
    ofClear(0);
    if (chromeIndex == 0) {
        fbo.draw(0, 0);
    }
    else if (chromeIndex == 1) {
        myTwoTone.color0 = palette[0];
        myTwoTone.color1 = palette[1];
        myTwoTone.draw(fbo.getTexture());
    }
    else {
        myColorWorld.palette = palette;
        myColorWorld.draw(fbo.getTexture());
    }
    fboC.end();
    
    //pixel
    if (pixelIndex == 0) fboC.draw(0, 0);
    else if (pixelIndex == 1) myBoredomWindow.draw(fboC.getTexture(), newTime_);
    else if (pixelIndex == 2) myCriticalWindow.draw(fboC.getTexture(), newTime_);
    else if (pixelIndex == 3) myFromDip.draw(fboC.getTexture(), newTime_);
    else if (pixelIndex == 4) myRadioWindow.draw(fboC.getTexture(), newTime_);
    else if (pixelIndex == 5) myNoizArc.draw(fboC.getTexture(), newTime_);
    else if (pixelIndex == 6) myRapFlee.draw(fboC.getTexture(), newTime_);
    else if (pixelIndex == 7) myRollingRoll.draw(fboC.getTexture(), newTime_);
    else if (pixelIndex == 8) mySlitShut.draw(fboC.getTexture(), newTime_);
    else if (pixelIndex == 9) mySynMeme.draw(fboC.getTexture(), newTime_);
    else myZigZig.draw(fboC.getTexture(), newTime_);
    
    //cover
    if (coverIndex == 0) {}
    else if (coverIndex == 1) myFlashCover.draw(frame_, newTime_);
    else if (coverIndex == 2) myOddCover.draw(frame_, newTime_);
    else if (coverIndex == 3) myPikaCover.draw(frame_, newTime_);
    else if (coverIndex == 4) myBlackCover.draw(frame_, newTime_);
}

//--------------------------------------------------------------
void objectOS::previousWord() {
    
    englishIndex = ofWrap(englishIndex - 1, 0, myWordCloud.englishes.size());
}
//--------------------------------------------------------------
void objectOS::nextWord() {
    
    englishIndex = ofWrap(englishIndex + 1, 0, myWordCloud.englishes.size());
}

//--------------------------------------------------------------
void objectOS::previousGraphic() {
    
    if (0 <= moduleIndex && moduleIndex < 2) moduleIndex = ofWrap(moduleIndex - 1, 0, 2);
    else moduleIndex = 2;
}
//--------------------------------------------------------------
void objectOS::nextGraphic() {
    
    if (0 <= moduleIndex && moduleIndex < 2) moduleIndex = ofWrap(moduleIndex + 1, 0, 2);
    else moduleIndex = 0;
}

//--------------------------------------------------------------
void objectOS::setColorNothing() {
    
    paletteIndex = 0;
    chromeIndex = 0;
}
//--------------------------------------------------------------
void objectOS::setColorMono() {
    
    paletteIndex = 0;
    chromeIndex = 1;
}
//--------------------------------------------------------------
void objectOS::setColorRGBTwo() {
    
    paletteIndex = 1;
    chromeIndex = 1;
}
//--------------------------------------------------------------
void objectOS::setColorRGBWorld() {
    
    paletteIndex = 1;
    chromeIndex = 2;
}
//--------------------------------------------------------------
void objectOS::setColorSakamotoTwo() {
    
    paletteIndex = 3;
    chromeIndex = 1;
}
//--------------------------------------------------------------
void objectOS::setColorSakamotoWorld() {
    
    paletteIndex = 3;
    chromeIndex = 2;
}
//--------------------------------------------------------------
void objectOS::setColorIkkoTwo() {
    
    paletteIndex = 4;
    chromeIndex = 1;
}
//--------------------------------------------------------------
void objectOS::setColorIkkoWorld() {
    
    paletteIndex = 4;
    chromeIndex = 2;
}

//--------------------------------------------------------------
void objectOS::previousPixel() {
    
    pixelIndex = ofWrap(pixelIndex - 1, 1, 11);
}
//--------------------------------------------------------------
void objectOS::nextPixel() {
    
    pixelIndex = ofWrap(pixelIndex + 1, 1, 11);
}
