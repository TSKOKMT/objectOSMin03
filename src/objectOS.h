#pragma once

#include "ofMain.h"

//screen
#include "vipGrid.h"
#include "slideGrid.h"
#include "pushGrid.h"
#include "emergeScreen.h"

//visual
#include "alphaDelta.h"
#include "blueCrown.h"
#include "curvePara.h"
#include "deepVibe.h"
#include "digitalHybe.h"
#include "diveWave.h"
#include "echoChamber.h"
#include "fieldWork.h"
#include "goingGone.h"
#include "graviTas.h"
#include "kuruKuri.h"
#include "longLonger.h"
#include "merryRound.h"
#include "moreGet.h"
#include "quickBrown.h"
#include "rectAnd.h"
#include "roundFace.h"
#include "slideLane.h"
#include "spaceBold.h"
#include "squareScape.h"
#include "threeStep.h"
#include "wipVip.h"

//word
#include "wordCloud.h"

//pixel
#include "boredomWindow.h"
#include "criticalWindow.h"
#include "fromDip.h"
#include "radioWindow.h"
#include "noizArc.h"
#include "rapFlee.h"
#include "rollingRoll.h"
#include "slitShut.h"
#include "synMeme.h"
#include "zigZig.h"

//palette
#include "colorCloud.h"

//chrome
#include "twoTone.h"
#include "colorWorld.h"

//cover
#include "flashCover.h"
#include "oddCover.h"
#include "pikaCover.h"
#include "blackCover.h"

class objectOS {

public:
    objectOS();
    
    void draw(ofRectangle frame_, float time_);
    
    float newTime_ = 0;
    
    int screenIndex = 0;
    int englishIndex = 0;
    int moduleIndex = 0;
    int paletteIndex = 0;
    int chromeIndex = 0;
    int pixelIndex = 0;
    int coverIndex = 0;
    
    int frameRate = -1;
    int paletteShift = 0;
    float screenDelay = 0;
    float paletteShiftTerm = -1;
    
    //word
    void previousWord();
    void nextWord();
    
    //visual
    void previousGraphic();
    void nextGraphic();
    
    //color
    void setColorNothing();
    void setColorMono();
    void setColorRGBTwo();
    void setColorRGBWorld();
    void setColorSakamotoTwo();
    void setColorSakamotoWorld();
    void setColorIkkoTwo();
    void setColorIkkoWorld();
    
    //pixel
    void previousPixel();
    void nextPixel();
    
private:
    float previousTime = 0;
    
    //screen
    vipGrid myVipGrid;
    slideGrid mySlideGrid;
    pushGrid myPushGrid;
    emergeScreen myEmergeScreen;
    
    //visual
    alphaDelta myAlphaDelta;
    blueCrown myBlueCrown;
    curvePara myCurvePara;
    deepVibe myDeepVibe;
    digitalHybe myDigitalHybe;
    diveWave myDiveWave;
    echoChamber myEchoChamber;
    fieldWork myFieldWork;
    goingGone myGoingGone;
    graviTas myGraviTas;
    kuruKuri myKuruKuri;
    longLonger myLongLonger;
    merryRound myMerryRound;
    moreGet myMoreGet;
    quickBrown myQuickBrown;
    rectAnd myRectAnd;
    roundFace myRoundFace;
    slideLane mySlideLane;
    spaceBold mySpaceBold;
    squareScape mySquareScape;
    threeStep myThreeStep;
    wipVip myWipVip;
    
    //word
    wordCloud myWordCloud;
    
    //palette
    colorCloud myColorCloud;
    
    //chrome
    twoTone myTwoTone;
    colorWorld myColorWorld;
    
    //pixel
    boredomWindow myBoredomWindow;
    criticalWindow myCriticalWindow;
    fromDip myFromDip;
    radioWindow myRadioWindow;
    noizArc myNoizArc;
    rapFlee myRapFlee;
    rollingRoll myRollingRoll;
    slitShut mySlitShut;
    synMeme mySynMeme;
    zigZig myZigZig;
    
    //cover
    flashCover myFlashCover;
    oddCover myOddCover;
    pikaCover myPikaCover;
    blackCover myBlackCover;
};
