#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetCircleResolution(100);

    intersection = new ofxIntersection2D::Circle2D();
    intersection->start();

    total = 50; /* About 60 limit... */
    for (int i = 0; i < total; i++) {
        baseCircleCentralPosList.push_back(ofVec2f(ofRandom(0.0, ofGetWidth()), ofRandom(0.0, ofGetHeight())));
        circleCentralPosList.push_back(baseCircleCentralPosList[i]);
        circleRadList.push_back(ofRandom(100.0, 300.0));
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    //--------------------------------------------------------------
    // update : circles
    //--------------------------------------------------------------
    float x;
    float y;

    float timef = ofGetElapsedTimef();
    float amount = 200.0;

    for (int i = 0; i < total; i++) {
        x = cos((timef + 1.0 * i) * 0.2) * amount + baseCircleCentralPosList[i].x;
        y = sin((timef + 1.0 * i) * 0.2) * amount + baseCircleCentralPosList[i].y;
        circleCentralPosList[i] = ofVec2f(x, y);
    }

    //--------------------------------------------------------------
    // Add object list. You have to execute this function in update.
    //--------------------------------------------------------------
    intersection->render(circleCentralPosList, circleRadList);
}

//--------------------------------------------------------------
void ofApp::draw() {
    //--------------------------------------------------------------
    // Get intersections
    //--------------------------------------------------------------
    vector<ofVec2f> tmpIntersectionList = intersection->getIntersections();

    //--------------------------------------------------------------
    // draw : intersections
    //--------------------------------------------------------------
    int totalIntersection = intersection->getIntersectionTotal();

    ofSetColor(255, 0, 0);
    ofFill();
    for (int i = 0; i < totalIntersection; i++) {
        ofDrawCircle(tmpIntersectionList[i], 10);
    }

    //--------------------------------------------------------------
    // draw circles
    //--------------------------------------------------------------
    ofSetColor(0, 0, 255);
    ofNoFill();
    for (int i = 0; i < total; i++) {
        ofDrawCircle(circleCentralPosList[i], circleRadList[i]);
    }

    //--------------------------------------------------------------
    // draw caption
    //--------------------------------------------------------------
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofPoint(10, 20));
}
