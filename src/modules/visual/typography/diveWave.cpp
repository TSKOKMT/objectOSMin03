#include "diveWave.h"

//--------------------------------------------------------------
diveWave::diveWave() {
    
    myPressRoom.loadFont("font.ttf");
}

//--------------------------------------------------------------
void diveWave::draw(ofRectangle frame_, float time_) {
    
    ofDisableArbTex();
    ofEnableDepthTest();
    
    //UPDATE
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    myPressRoom.setText(text_);
    
    //Create tex
    ofRectangle texFrame = ofRectangle(0, 0, 1080, 1080 / frame_.getAspectRatio() * 2);
    float texUnit = sqrt(texFrame.width * texFrame.height) / 120.;
    
    ofFbo texFbo;
    texFbo.allocate(texFrame.width,texFrame.height, GL_RGB, 4);
    texFbo.begin();
    ofClear(0);
    auto framesV = VStack::get(texFrame, countV, 2 * texUnit);
    for (int v = 0; v < framesV.size(); v++) {
        myPressRoom.setHeight(framesV[v].height);
        
        float thePosition = textSpeed * texUnit * time_ * (v % 2 ? -1 : 1);
        
        auto framesH = HStack::get(framesV[v], myPressRoom.getWidth(), 2 * texUnit, thePosition);
        
        for (int h = 0; h < framesH.size(); h++) {
            myPressRoom.draw(framesH[h].position);
        }
    }
    texFbo.end();
    
    //Create mesh
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    int resolutionH = 30;
    int resolutionD = 30;
    for (int d = 0; d < resolutionD; d++) {
        for (int h = 0; h < resolutionH; h++) {
            float x = ofMap(h, 0, resolutionH, -fieldSizeH / 2., fieldSizeH / 2.);
            float z = ofMap(d, 0, resolutionD, -fieldSizeD / 2., fieldSizeD / 2.);
            float nextX = ofMap(h + 1, 0, resolutionH, -fieldSizeH / 2., fieldSizeH / 2.);
            float nextZ = ofMap(d + 1, 0, resolutionD, -fieldSizeD / 2., fieldSizeD / 2.);
            
            mesh.addVertex(ofPoint(x, getWave(x, z, time_), z));
            mesh.addTexCoord(ofVec2f(h / (float)resolutionH, d / (float)resolutionD));
            
            for (int j = 0; j < 2; j++) {
                mesh.addVertex(ofPoint(nextX, getWave(nextX, z, time_), z));
                mesh.addTexCoord(ofVec2f((h + 1) / (float)resolutionH, d / (float)resolutionD));
                
                mesh.addVertex(ofPoint(x, getWave(x, nextZ, time_), nextZ));
                mesh.addTexCoord(ofVec2f(h / (float)resolutionH, (d + 1) / (float)resolutionD));
            }
            
            mesh.addVertex(ofPoint(nextX, getWave(nextX, nextZ, time_), nextZ));
            mesh.addTexCoord(ofVec2f((h + 1) / (float)resolutionH, (d + 1) / (float)resolutionD));
        }
    }
    
    //Create camera
    ofEasyCam cam;
    cam.setNearClip(.01);
    cam.setFarClip(100000);
    cam.enableOrtho();
    cam.setPosition(0, 3000, 1500);
    cam.lookAt(ofPoint(0, 0, 200));
    
    //DRAW
    
    ofFbo fbo;
    fbo.allocate(frame_.width, frame_.height, GL_RGBA, 4);
    fbo.begin();
    ofClear(0);
    ofPushMatrix();
    ofTranslate(-frame_.position);
    
    cam.begin();
    
    ofPushMatrix();
    ofScale(120 * unit / 1080.);
    
    texFbo.getTexture().bind();
    mesh.draw();
    texFbo.getTexture().unbind();
    
    ofPopMatrix();
    
    cam.end();
    
    ofPopMatrix();
    fbo.end();
    fbo.draw(frame_.position);
    
    
    
    ofDisableDepthTest();
    ofEnableArbTex();
}

//--------------------------------------------------------------
float diveWave::getWave(float x_, float z_, float time_) {
    
    //return 0;
    
    z_ += time_ * waveSpeedD;
    
    return ofSignedNoise(x_ / waveSize, z_ / waveSize, time_ * waveSpeed) * waveHeight;
}
