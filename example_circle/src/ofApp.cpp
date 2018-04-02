#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetCircleResolution(100);

    intersection = new ofxIntersection2D::Circle2D();

    total = 5;
    for (int i = 0; i < total; i++) {
        baseCircleCentralPosList.push_back(ofVec2f(ofRandom(0.0, ofGetWidth()), ofRandom(0.0, ofGetHeight())));
        baseCircleRadList.push_back(ofRandom(100.0, 300.0));

        circleCentralPosList.push_back(baseCircleCentralPosList[i]);
        circleRadList.push_back(baseCircleRadList[i]);
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
    ofVec2f v;
    float rad;

    for (int i = 0; i < total; i++) {
        v.x = cos((ofGetElapsedTimef() + 1.0 * i) * 1.0) * 20;
        v.y = sin((ofGetElapsedTimef() + 1.0 * i) * 1.0) * 20;
        circleCentralPosList[i] = baseCircleCentralPosList[i] + v;

        rad = cos((ofGetElapsedTimef() + 1.0 * i) * 1.0) * (circleRadList[i] * 0.1);
        circleRadList[i] = baseCircleRadList[i] + rad;

        intersection->addCircle(circleCentralPosList[i], circleRadList[i]);
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
    ofDrawBitmapStringHighlight(caption(), ofPoint(10, 20));
}

//--------------------------------------------------------------
string ofApp::caption() {
    stringstream ss;
    ss << ofGetFrameRate() << endl;
    ss << endl;
    ss << "intersection total : " << intersection->getIntersectionTotal() << endl;
    return ss.str();
}