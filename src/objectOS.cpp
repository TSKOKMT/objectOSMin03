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
    string englishWord2 = myWordCloud.englishes[ofWrap(englishIndex + 1, 0, myWordCloud.englishes.size())];
    string englishWord3 = myWordCloud.englishes[ofWrap(englishIndex + 2, 0, myWordCloud.englishes.size())];
    if (moduleIndex == 0) myAlphaDelta.text_ = englishWord;
    if (moduleIndex == 1) myBlueCrown.text_ = englishWord;
    if (moduleIndex == 2) myCurvePara.text_ = englishWord;
    if (moduleIndex == 3) myDeepVibe.text_ = englishWord;
    if (moduleIndex == 4) myDigitalHybe.text_ = englishWord;
    if (moduleIndex == 5) myDiveWave.text_ = englishWord;
    if (moduleIndex == 6) myEchoChamber.text_ = englishWord;
    if (moduleIndex == 7) myFieldWork.text_ = englishWord;
    if (moduleIndex == 8) myGoingGone.text_ = englishWord;
    if (moduleIndex == 9) myGraviTas.text_ = englishWord;
    if (moduleIndex == 10) myKuruKuri.text_ = englishWord;
    if (moduleIndex == 11) myLongLonger.text_ = englishWord;
    if (moduleIndex == 12) myMerryRound.text_ = englishWord;
    if (moduleIndex == 13) myMoreGet.text_ = englishWord;
    if (moduleIndex == 14) myQuickBrown.text_ = englishWord;
    if (moduleIndex == 15) myRectAnd.text_ = englishWord;
    if (moduleIndex == 16) myRoundFace.text_ = englishWord;
    if (moduleIndex == 17) mySlideLane.text_ = englishWord;
    if (moduleIndex == 18) mySpaceBold.text_ = englishWord + ' ' + englishWord2 + ' ' + englishWord3;
    if (moduleIndex == 19) mySquareScape.text_ = englishWord;
    if (moduleIndex == 20) myThreeStep.text_ = englishWord;
    if (moduleIndex == 21) myWipVip.text_ = englishWord;

    
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
        if (moduleIndex == 1) myBlueCrown.draw(screen, newTime);
        if (moduleIndex == 2) myCurvePara.draw(screen, newTime);
        if (moduleIndex == 3) myDeepVibe.draw(screen, newTime);
        if (moduleIndex == 4) myDigitalHybe.draw(screen, newTime);
        if (moduleIndex == 5) myDiveWave.draw(screen, newTime);
        if (moduleIndex == 6) myEchoChamber.draw(screen, newTime);
        if (moduleIndex == 7) myFieldWork.draw(screen, newTime);
        if (moduleIndex == 8) myGoingGone.draw(screen, newTime);
        if (moduleIndex == 9) myGraviTas.draw(screen, newTime);
        if (moduleIndex == 10) myKuruKuri.draw(screen, newTime);
        if (moduleIndex == 11) myLongLonger.draw(screen, newTime);
        if (moduleIndex == 12) myMerryRound.draw(screen, newTime);
        if (moduleIndex == 13) myMoreGet.draw(screen, newTime);
        if (moduleIndex == 14) myQuickBrown.draw(screen, newTime);
        if (moduleIndex == 15) myRectAnd.draw(screen, newTime);
        if (moduleIndex == 16) myRoundFace.draw(screen, newTime);
        if (moduleIndex == 17) mySlideLane.draw(screen, newTime);
        if (moduleIndex == 18) mySpaceBold.draw(screen, newTime);
        if (moduleIndex == 19) mySquareScape.draw(screen, newTime);
        if (moduleIndex == 20) myThreeStep.draw(screen, newTime);
        if (moduleIndex == 21) myWipVip.draw(screen, newTime);
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
    
    if (0 <= moduleIndex && moduleIndex < 22) moduleIndex = ofWrap(moduleIndex - 1, 0, 22);
    else moduleIndex = 22;
}
//--------------------------------------------------------------
void objectOS::nextGraphic() {
    
    if (0 <= moduleIndex && moduleIndex < 22) moduleIndex = ofWrap(moduleIndex + 1, 0, 22);
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
