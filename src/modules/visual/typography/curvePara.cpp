#include "curvePara.h"

//--------------------------------------------------------------
curvePara::curvePara() {
    
    font.setPath("font.ttf");
    
    ofxSvg svg;
    svg.load("curve.svg");
    ofPath path = svg.getPaths().back();
    path.setPolyWindingMode(OF_POLY_WINDING_ODD);
    polyline_ = path.getOutline().front();
}

//--------------------------------------------------------------
void curvePara::draw(ofRectangle frame_, float time_) {
    
    //UPDATE
    
    auto unit = sqrt(frame_.width * frame_.height) / 120.;
    
    float height_ = height * unit;
    
    polyline_.translate(-polyline_.getBoundingBox().getCenter());
    polyline_.translate(frame_.getCenter());
    polyline_.scale(frame_.width / polyline_.getBoundingBox().width, frame_.height / polyline_.getBoundingBox().height);
    
    font.setHeight(height_);
    font.setHorizontalAlignment(1);
    //font.setVerticalAlignment(2);
    font.setText(text_);
    auto widthes = font.getWidthes();
    
    ofPolyline polyline;
    int resolution = 1000;
    for (int i = 0; i < resolution; i++) {
        polyline.addVertex(polyline_.getPointAtPercent(i / (float)resolution));
    }
    polyline.close();
    int size = polyline.size();
    
    float length = 0;
    for (int i = 0; i < size - 1; i++) {
        length += ofDist(polyline.getVertices()[i].x, polyline.getVertices()[i].y, polyline.getVertices()[i + 1].x, polyline.getVertices()[i + 1].y);
    }
    
    //DRAW
    
    ofPushStyle();
    ofSetColor(myColorCloud.six[0]);
    
    for (int i = 0; i < text_.size(); i++) {
        font.setText(ofToString(text_[i]));
        
        float theMotion = ofWrap(-time_ / 12., 0, 1);
        for (int j = 1; j < i; j++) theMotion += widthes[j] / length;
        if (i > 0) {
            theMotion += widthes[0] / 2. / length;
            theMotion += widthes[i] / 2. / length;
        }
        theMotion = ofWrap(theMotion, 0, 1);
        
        float theIndex = theMotion * size;
        theIndex = ofWrap(theIndex, 0, size);
        
        ofPoint thePosition = polyline.getPointAtIndexInterpolated(theIndex);
        
        ofPoint previousVertex = polyline.getVertices()[(int)ofWrap(floor(theIndex), 0, size)];
        ofPoint nextVertex = polyline.getVertices()[(int)ofWrap(ceil(theIndex), 0, size)];
        float theAngle = atan2(nextVertex.y - previousVertex.y, nextVertex.x - previousVertex.x);
        
        ofPushMatrix();
        ofTranslate(thePosition);
        ofRotateRad(theAngle);
        
        font.draw();
        
        ofPopMatrix();
    }
    
    ofPopStyle();
    
    /*font.draw();
    
    ofPushMatrix();
    ofTranslate(0, font.getHeight() * 1.5);
    
    float position = 0;
    for (int i = 0; i < text_.size(); i++) {
        font.setText(ofToString(text_[i]));
        
        ofPushMatrix();
        ofTranslate(position, 0);
        font.draw();
        ofPopMatrix();
        
        position += widthes[i];
    }
    
    ofPopMatrix();*/
}
