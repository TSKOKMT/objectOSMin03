#include "roundFace.h"

//--------------------------------------------------------------
roundFace::roundFace() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void roundFace::draw(ofRectangle frame_, float time_) {
    
    ofDisableArbTex();
    ofEnableDepthTest();
    
    //UPDATE
    
    myPressRoom.setText(text_);
    
    bool bHorizontal = myPressRoom.getAspect() > 1;
    
    //Create cylinder
    ofCylinderPrimitive cylinder;
    cylinder.setResolution(60, 60);
    if (bHorizontal) {
        cylinder.rotateRad(HALF_PI, 0, 0, 1);
        cylinder.setHeight(frame_.width);
        cylinder.setRadius(frame_.height / 2.);
    }
    else {
        cylinder.setHeight(frame_.height);
        cylinder.setRadius(frame_.width / 2.);
    }
    
    //Draw typoFbo
    ofFbo typoFbo;
    float position = time_ * speed;
    if (bHorizontal) {
        float typeFboH = 540;
        float typeFboW = typeFboH / frame_.getAspectRatio() * PI;
        float typeFboUnit = sqrt(typeFboW * typeFboH) / 120.;
        
        float typeFboMargin = typeFboH / 18.;
        
        typoFbo.allocate(typeFboW, typeFboH, GL_RGB, 4);
        typoFbo.begin();
        ofPushMatrix();
        ofTranslate(typeFboW, 0);
        ofRotateRad(HALF_PI);
        float hegiht = typeFboH / myPressRoom.getAspect();
        float spacing = 30 * typeFboUnit;
        auto framesV = VStack::get(ofRectangle(typeFboMargin + 4.5, 0, typeFboH - typeFboMargin * 2, typeFboW), hegiht, spacing, typeFboW / 4. + (hegiht + spacing) * position);
        for (int v = 0; v < framesV.size(); v++) {
            myPressRoom.draw(framesV[v]);
        }
        ofPopMatrix();
        typoFbo.end();
    }
    else {
        float typeFboH = 540;
        float typeFboW = typeFboH * frame_.getAspectRatio() * PI;
        float typeFboUnit = sqrt(typeFboW * typeFboH) / 120.;
        
        float typeFboMargin = typeFboH / 18.;
        
        typoFbo.allocate(typeFboW, typeFboH, GL_RGB, 4);
        typoFbo.begin();
        ofPushMatrix();
        float width = typeFboH * myPressRoom.getAspect();
        float spacing = 30 * typeFboUnit;
        auto framesH = HStack::get(ofRectangle(0, typeFboMargin + 4.5, typeFboW, typeFboH - typeFboMargin * 2), width, spacing, typeFboW / 4. + (width + spacing) * position);
        for (int h = 0; h < framesH.size(); h++) {
            myPressRoom.draw(framesH[h]);
        }
        ofPopMatrix();
        typoFbo.end();
    }
    
    //Create carmera
    ofEasyCam camera;
    camera.enableOrtho();
    camera.setPosition(0, 0, 2000);
    
    //DRAW
    
    ofFbo fbo;
    fbo.allocate(frame_.width, frame_.height, GL_RGB, 4);
    fbo.begin();
    
    camera.begin();
    
    typoFbo.getTexture().bind();
    cylinder.draw();
    typoFbo.getTexture().unbind();
    
    camera.end();
    
    fbo.end();
    
    fbo.draw(frame_.position);
    
    ofDisableDepthTest();
    ofEnableArbTex();
}
