#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    intersection = new ofxIntersection2D::Line2D();
    intersection->start();  // start threadedFunction

    total = 100; /* About 100 limit... */
    for (int i = 0; i < total; i++) {
        lineBeginPosList.push_back(ofVec2f(0, ofRandom(0.0, ofGetHeight())));
        lineEndPosList.push_back(ofVec2f(ofGetWidth(), ofRandom(0.0, ofGetHeight())));
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    //--------------------------------------------------------------
    // draw : lines
    //--------------------------------------------------------------
    float beginX;
    float beginY;
    float endX;
    float endY;

    float timef = ofGetElapsedTimef();

    float w = ofGetWidth();
    float h = ofGetHeight();

    for (int i = 0; i < total; i++) {
        beginX = 0.0;
        beginY = cos((timef + 0.5 * i) * 0.1) * (h * 0.5) + (h * 0.5);

        endX = w;
        endY = sin((timef + 0.5 * i) * 0.1) * (h * 0.5) + (h * 0.5);

        lineBeginPosList[i] = ofVec2f(beginX, beginY);
        lineEndPosList[i] = ofVec2f(endX, endY);
    }

    //--------------------------------------------------------------
    // Add object list. You have to execute this function in update.
    //--------------------------------------------------------------
    intersection->render(lineBeginPosList, lineEndPosList);
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
    for (int i = 0; i < totalIntersection; i++) {
        ofDrawCircle(tmpIntersectionList[i], 5);
    }

    //--------------------------------------------------------------
    // draw : lines
    //--------------------------------------------------------------
    ofSetColor(0, 0, 255);
    for (int i = 0; i < total; i++) {
        ofDrawLine(lineBeginPosList[i], lineEndPosList[i]);
    }

    //--------------------------------------------------------------
    // draw : caption
    //--------------------------------------------------------------
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofPoint(10, 20));
}
