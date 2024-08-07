#include "blueCrown.h"

//--------------------------------------------------------------
blueCrown::blueCrown() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void blueCrown::draw(ofRectangle frame_, float time_) {
    
    //UPDATE
    
    auto unit = sqrt(frame_.width * frame_.height) / 120.;
    
    myPressRoom.setText(text_);
    
    float margin = height_ / 6.;
    
    myPressRoom.setHeight(height_ - margin * 2);
    
    int count = round((radius_ * TWO_PI) / myPressRoom.getWidth());
    
    float width = (myPressRoom.getWidth() + margin) * count;
    
    auto frameM = marginBand::get(ofRectangle(0, 0, width, height_), ofPoint(0, margin));
    
    float radius = width / TWO_PI;
    
    auto framesH = HStack::get(frameM, myPressRoom.getAspect() * frameM.height, margin, time_ / hour * width);
    
    ofCamera camera;
    camera.setPosition(0, 0, 500);
    camera.setFov(atan2(frame_.height, sqrt(frame_.width * frame_.height)) * 2 * 1.25 * RAD_TO_DEG);
    
    //DRAW
    
    ofDisableArbTex();
    ofEnableDepthTest();
    
    ofFbo texFbo;
    texFbo.allocate(width, height_, GL_RGB, 4);
    texFbo.begin();
    ofClear(0);
    ofSetColor(255);
    for (int h = 0; h < framesH.size(); h++) {
        myPressRoom.draw(framesH[h]);
    }
    texFbo.end();
    
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    int res = 128;
    mesh.clear();
    for (int i = 0; i < res; i++) {
        float theAngle0 = ofMap(i, 0, res, 0, TWO_PI);
        float theAngle1 = ofMap(i + 1, 0, res, 0, TWO_PI);
        
        float u0 = ofNormalize(i, 0, res);
        float u1 = ofNormalize(i + 1, 0, res);
        
        mesh.addVertex(ofPoint(cos(theAngle0) * radius, height_ / 2., sin(theAngle0) * radius));
        mesh.addTexCoord(ofVec2f(u0, 0));
        
        for (int j = 0; j < 2; j++) {
            mesh.addVertex(ofPoint(cos(theAngle1) * radius, height_ / 2., sin(theAngle1) * radius));
            mesh.addTexCoord(ofVec2f(u1, 0));
            
            mesh.addVertex(ofPoint(cos(theAngle0) * radius, -height_ / 2., sin(theAngle0) * radius));
            mesh.addTexCoord(ofVec2f(u0, 1));
        }
        
        mesh.addVertex(ofPoint(cos(theAngle1) * radius, -height_ / 2., sin(theAngle1) * radius));
        mesh.addTexCoord(ofVec2f(u1, 1));
    }

    ofFbo fbo;
    fbo.allocate(frame_.width, frame_.height, GL_RGBA, 4);
    fbo.begin();
    ofClear(0);
    ofPushMatrix();
    ofTranslate(-frame_.position);
    
    camera.begin();
    ofRotateXRad(-PI / 12.);
    
    texFbo.getTexture().bind();
    mesh.draw();
    texFbo.getTexture().unbind();
    
    camera.end();
    
    ofPopMatrix();
    fbo.end();
    fbo.draw(frame_.position);
    
    ofDisableDepthTest();
    ofEnableArbTex();
}
