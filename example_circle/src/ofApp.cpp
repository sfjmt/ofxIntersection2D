#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetCircleResolution(100);

    intersection = new ofxIntersection2D::Circle2D();

    total = 10;
    for (int i = 0; i < total; i++) {
        circleCentralPosList.push_back(ofVec2f(ofRandom(0.0, ofGetWidth()), ofRandom(0.0, ofGetHeight())));
        circleRadList.push_back(ofRandom(100.0, 300.0));
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
    for (int i = 0; i < total; i++) {
        intersection->add(circleCentralPosList[i], circleRadList[i]);
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
    ofFill();
    for (int i = 0; i < totalIntersection; i++) {
        ofDrawCircle(tmpIntersectionList[i], 10);
    }

    // draw circles
    ofSetColor(0, 0, 255);
    ofNoFill();
    for (int i = 0; i < total; i++) {
        ofDrawCircle(circleCentralPosList[i], circleRadList[i]);
    }

    // draw caption
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofPoint(10, 20));
}
