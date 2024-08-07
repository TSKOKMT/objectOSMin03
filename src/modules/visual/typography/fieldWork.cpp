#include "fieldWork.h"

//--------------------------------------------------------------
fieldWork::fieldWork() {
    
    font.setPath("font.ttf");
}

//--------------------------------------------------------------
void fieldWork::draw(ofRectangle frame_, float time_) {
    
    //UPDATE
    
    float unit = sqrt(frame_.width * frame_.height) / 120.;
    
    float height_ = height * unit;
    
    font.setText(text_);
    font.setHeight(height_);
    
    auto widthes = font.getWidthes();
    
    ofPoint speedByUnit = ofPoint(-4, -16);
    
    ofPoint position = ofPoint(time_ * speedByUnit.x * unit, time_ * speedByUnit.y * unit);
    
    vector<ofRectangle> frames0 = VStack::get(frame_, height_, 4 * unit, position.y);
    vector<ofRectangle> frames;
    for (int i = 0; i < frames0.size(); i++) {
        float theAspect = font.getWidth() / font.getHeight();
        auto frames1P = HStack::get(frames0[i], frames0[i].height * theAspect, 16 * unit, position.x + frames0[i].y);
        frames.insert(frames.end(), frames1P.begin(), frames1P.end());
    }
    
    //DRAW
    
    ofFbo fbo;
    fbo.allocate(frame_.width, frame_.height, GL_RGBA, 4);
    fbo.begin();
    ofClear(0);
    ofPushMatrix();
    ofTranslate(-frame_.position);
    
    for (int i = 0; i < frames.size(); i++) {
        float h = frames[i].height;
        float x = frames[i].x;
        float y = frames[i].y;
        for (int j = 0; j < text_.size(); j++) {
            font.setText(ofToString(text_[j]));
            
            float w = widthes[j];
            ofRectangle frame = ofRectangle(x, y, w, h);
            vector<ofRectangle> framesV = VStack::get(frame, frame.height, 4 * unit, time_ * (j % 2 ? -1 : 1) * speedByUnit.y * unit + j * 4 * unit);
            ofFbo fbo;
            fbo.allocate(frame.width, frame.height);
            fbo.begin();
            ofClear(0);
            ofPushMatrix();
            ofTranslate(-frame.position);
            for (int k = 0; k < framesV.size(); k++) {
                ofPushMatrix();
                ofTranslate(framesV[k].position);
                font.draw();
                ofPopMatrix();
            }
            ofPopMatrix();
            fbo.end();
            fbo.draw(frame.position);
            x += w;
        }
    }
    
    ofPopMatrix();
    fbo.end();
    fbo.draw(frame_.position);
}
