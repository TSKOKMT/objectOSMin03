#include "ofxTskokmtFont.h"

//--------------------------------------------------------------
void ofxTskokmtFont::loadText(string path_){
    
    file.open(path_);
    text = file.readToBuffer().getText();
}

//--------------------------------------------------------------
void ofxTskokmtFont::setText(string text_){
    
    text = text_;
}

//--------------------------------------------------------------
void ofxTskokmtFont::setPath(string path_){
    
    if (fontStash.setup(path_)) path = path_;
    else fontStash.setup(path);
    magnification = virtualHeight / fontStash.getBBox("X", virtualHeight, 0, 0).height;
}

//--------------------------------------------------------------
bool ofxTskokmtFont::isLoaded() {
    
    string textShelter = getText();
    setText("A");
    bool bLoaded = getWidth() > 0;
    setText(textShelter);
    
    return bLoaded;
}

//--------------------------------------------------------------
void ofxTskokmtFont::setPosition(float x_, float y_){
    
    setPosition(ofPoint(x_, y_));
}

//--------------------------------------------------------------
void ofxTskokmtFont::setPosition(ofPoint position_){
    
    position = position_;
}

//--------------------------------------------------------------
void ofxTskokmtFont::setHeight(float height_){
    
    scaleRatio = 1;
    
    height = height_;
}

//--------------------------------------------------------------
void ofxTskokmtFont::setWidth(float width_){
    
    scaleRatio = 1;
    
    setHeight(virtualHeight);
    float aspect = virtualHeight / getWidth();
    setHeight(width_ * aspect);
}

//--------------------------------------------------------------
void ofxTskokmtFont::setWidthAndHeight(float width_, float height_) {
    
    setHeight(height_);
    scaleRatio = width_ / getWidthRaw();
}

//--------------------------------------------------------------
void ofxTskokmtFont::setFrame(ofRectangle frame_) {
    
    setPosition(frame_.position);
    setWidthAndHeight(frame_.width, frame_.height);
}

//--------------------------------------------------------------
void ofxTskokmtFont::setHorizontalAlignment(int alignment_) {
 
    horizontalAlignment = alignment_;
}

//--------------------------------------------------------------
void ofxTskokmtFont::setVerticalAlignment(int alignment_) {
    
    verticalAlignment = alignment_;
}

//--------------------------------------------------------------
void ofxTskokmtFont::setCharacterSpacing(float spacing_) {
    
    characterSpacing = spacing_;
}

//--------------------------------------------------------------
string ofxTskokmtFont::getText(){
    
    return text;
}

//--------------------------------------------------------------
float ofxTskokmtFont::getWidthRaw(){
    
    float width = 0;
    for (int i = 0; i < text.size(); i++) {
        width += fontStash.getBBox({text[i]}, virtualHeight, 0, 0).width;
        if (i < text.size() - 1) width += (virtualHeight / magnification) * characterSpacing;
    }
    float s = height / (virtualHeight / magnification);
    return width * s;
}

//--------------------------------------------------------------
float ofxTskokmtFont::getWidth(){
    
    return getWidthRaw() * scaleRatio;
}

//--------------------------------------------------------------
float ofxTskokmtFont::getHeight(){
    
    return height;
}

//--------------------------------------------------------------
float ofxTskokmtFont::getAspect() {
    
    return getWidthRaw() / height;
}

//--------------------------------------------------------------
ofRectangle ofxTskokmtFont::getBoundingBox(){
    
    return ofRectangle(position.x - getWidth() / 2. * horizontalAlignment, position.y - height / 2. * verticalAlignment, getWidth(), height);
}

//--------------------------------------------------------------
void ofxTskokmtFont::draw(int only_){
    
    ofPushMatrix();
    ofTranslate(position);
    ofTranslate(-getWidth() / 2. * horizontalAlignment, -height / 2. * verticalAlignment);
    ofScale(scaleRatio, 1);
    ofScale((height * magnification) / virtualHeight);
    
    float x = 0;
    for (int i = 0; i < text.size(); i++) {
        if (only_ < 0 || i == only_) {
            fontStash.draw({text[i]}, virtualHeight, x, virtualHeight / magnification);
        }
        x += fontStash.getBBox({text[i]}, virtualHeight, 0, 0).width + (virtualHeight / magnification) * characterSpacing;
    }
    
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofxTskokmtFont::draw(float x_, float y_) {
    
    setPosition(x_, y_);
    draw();
}

//--------------------------------------------------------------
void ofxTskokmtFont::draw(ofPoint position_) {
    
    setPosition(position_);
    draw();
}

//--------------------------------------------------------------
void ofxTskokmtFont::draw(ofRectangle frame_) {
 
    setFrame(frame_);
    draw();
}

//--------------------------------------------------------------
vector<float> ofxTskokmtFont::getWidthes() {
    
    vector<float> widthes;
    widthes.resize(text.size());
    
    float s = height / (virtualHeight / magnification);
    for (int i = 0; i < text.size(); i++) {
        widthes[i] = fontStash.getBBox({text[i]}, virtualHeight, 0, 0).width;
        widthes[i] *= s;
        widthes[i] *= scaleRatio;
        //if (i < text.size() - 1) widthes[i] += (virtualHeight / magnification) * characterSpacing;
    }
    
    return widthes;
}

//--------------------------------------------------------------
vector<float> ofxTskokmtFont::getPositions() {
    
    vector<float> positions;
    positions.resize(text.size());
    
    auto ws = getWidthes();
    for (int i = 0; i < positions.size(); i++) {
        positions[i] = 0;
        for (int j = 0; j < i; j++) {
            positions[i] += ws[j];
            float s = height * characterSpacing;
            s *= scaleRatio;
            positions[i] += s;
        }
    }
    
    return positions;
}
