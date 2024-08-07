#include "pressRoom.h"

//--------------------------------------------------------------
void pressRoom::loadFont(string path_) {
    
    font.setPath(path_);
}

//--------------------------------------------------------------
void pressRoom::setText(string text_) {
    
    font.setText(text_);
    bText = true;
}

//--------------------------------------------------------------
void pressRoom::setImage(string path_) {
    
    if (path_ == imagePath) return;
    imagePath = path_;
    
    image.load(path_);
    bText = false;
}

//--------------------------------------------------------------
void pressRoom::setWidth(float width_) {
    
    width = width_;
    height = width / getAspect();
}

//--------------------------------------------------------------
void pressRoom::setHeight(float height_) {
    
    height = height_;
    width = height * getAspect();
}

//--------------------------------------------------------------
float pressRoom::getWidth() {
    
    return width;
}

//--------------------------------------------------------------
float pressRoom::getHeight() {
    
    return height;
}

//--------------------------------------------------------------
float pressRoom::getAspect() {
    
    if (bText) return font.getAspect();
    else return image.getWidth() / image.getHeight();
}

//--------------------------------------------------------------
void pressRoom::draw(ofRectangle frame_) {
    
    if (bText) font.draw(frame_);
    else image.draw(frame_);
    
    width = frame_.width;
    height = frame_.height;
}

//--------------------------------------------------------------
void pressRoom::draw(ofPoint position_) {
    
    draw(position_.x, position_.y);
}

//--------------------------------------------------------------
void pressRoom::draw(float x_, float y_) {
    
    if (bText) font.draw(ofRectangle(x_, y_, width, height));
    else image.draw(ofRectangle(x_, y_, width, height));
}
