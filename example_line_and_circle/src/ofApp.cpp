#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetCircleResolution(100);
    
    intersection = new ofxIntersection2D::LineAndCircle2D();

    totalCircle = 10;
    totalLine = 30;

    for (int i = 0; i < totalCircle; i++) {
        circleList.push_back(ofxIntersection2D::ObjectCircle());
    }

    for (int i = 0; i < totalLine; i++) {
        lineList.push_back(ofxIntersection2D::ObjectLine());
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
    float timef = ofGetElapsedTimef();

    for (int i = 0; i < totalCircle; i++) {
        circleList[i].central.x = cos((timef + 1.0 * i) * 0.2) * 100 + ofGetWidth() * 0.5;
        circleList[i].central.y = sin((timef + 1.0 * i) * 0.2) * 100 + ofGetWidth() * 0.5;
        circleList[i].radius = cos((timef + 1.0 * i) * 1.0) * 50 + 50;
        intersection->addCircle(circleList[i].central, circleList[i].radius);
    }

    for (int i = 0; i < totalLine; i++) {
        lineList[i].p1 = ofPoint(0, cos((timef + 0.1 * i) * 0.2) * ofGetHeight() * 0.5 + ofGetHeight() * 0.5);
        lineList[i].p2 = ofPoint(ofGetWidth(), sin((timef + 1.0 * i) * 0.2) * ofGetHeight() * 0.5 + ofGetHeight() * 0.5);
        intersection->addLine(lineList[i].p1, lineList[i].p2);
    }

    //--------------------------------------------------------------
    // 3. Update
    //--------------------------------------------------------------
    intersection->update();

    intersectionList = intersection->getIntersections();
}

//--------------------------------------------------------------
void ofApp::draw() {
    // draw : circle
    ofNoFill();
    ofSetColor(255, 0, 0);
    for (int i = 0; i < totalCircle; i++) {
        ofDrawCircle(circleList[i].central, circleList[i].radius);
    }

    // draw : line
    ofSetColor(0, 0, 255);
    for (int i = 0; i < totalLine; i++) {
        ofDrawLine(lineList[i].p1, lineList[i].p2);
    }

    // draw : intersection
    ofFill();
    ofSetColor(0);
    for (int i = 0; i < intersectionList.size(); i++) {
        ofDrawCircle(intersectionList[i], 5);
    }

    // draw : caption
    ofDrawBitmapStringHighlight(caption(), ofPoint(10, 20));
}

//--------------------------------------------------------------
string ofApp::caption() {
    stringstream ss;
    ss << ofGetFrameRate() << endl;
    ss << endl;
    ss << "total line : " << totalLine << endl;
    ss << "total circle : " << totalCircle << endl;
    return ss.str();
}