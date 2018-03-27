#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    intersection = new ofxIntersection2D::Line2D();

    total = 10;
    for (int i = 0; i < total; i++) {
        baseLineBeginPosList.push_back(ofVec2f(0, ofRandom(0.0, ofGetHeight())));
        baseLineEndPosList.push_back(ofVec2f(ofGetWidth(), ofRandom(0.0, ofGetHeight())));

        lineBeginPosList.push_back(baseLineBeginPosList[i]);
        lineEndPosList.push_back(baseLineEndPosList[i]);
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    //--------------------------------------------------------------
    // 1. Clear
    //--------------------------------------------------------------
    intersection->clear();

    //--------------------------------------------------------------
    // 2. Add
    //--------------------------------------------------------------
    ofVec2f vBegin;
    ofVec2f vEnd;

    for (int i = 0; i < total; i++) {
        vBegin.x = 0;
        vBegin.y = cos((ofGetElapsedTimef() + 1.0 * i) * 1.0) * 20;

        vEnd.x = 0;
        vEnd.y = sin((ofGetElapsedTimef() + 1.0 * i) * 1.0) * 20;

        lineBeginPosList[i] = baseLineBeginPosList[i] + vBegin;
        lineEndPosList[i] = baseLineEndPosList[i] + vEnd;

        intersection->addLine(lineBeginPosList[i], lineEndPosList[i]);
    }

    //--------------------------------------------------------------
    // 3. Update
    //--------------------------------------------------------------
    intersection->update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    //--------------------------------------------------------------
    // 4. Get intersections
    //--------------------------------------------------------------
    vector<ofVec2f> tmpIntersectionList = intersection->getIntersections();

    //--------------------------------------------------------------
    // 5. Draw intersections
    //--------------------------------------------------------------
    int totalIntersection = intersection->getIntersectionTotal();

    ofSetColor(255, 0, 0);
    for (int i = 0; i < totalIntersection; i++) {
        ofDrawCircle(tmpIntersectionList[i], 10);
    }

    // draw lines
    ofSetColor(0, 0, 255);
    for (int i = 0; i < total; i++) {
        ofDrawLine(lineBeginPosList[i], lineEndPosList[i]);
    }

    // draw : caption
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofPoint(10, 20));
}
