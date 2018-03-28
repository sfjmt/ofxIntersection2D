#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetCircleResolution(100);

    intersection = new ofxIntersection2D::LineAndCircle2D();
    intersection->start();  // start threadedFunction

    totalCircle = 100;
    totalLine = 100;

    for (int i = 0; i < totalCircle; i++) {
        circleList.push_back(ofxIntersection2D::ObjectCircle());
    }

    for (int i = 0; i < totalLine; i++) {
        lineList.push_back(ofxIntersection2D::ObjectLine());
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    float timef = ofGetElapsedTimef();

    for (int i = 0; i < totalCircle; i++) {
        circleList[i].central.x = cos((timef + 10.0 * i) * 0.2) * 300 + ofGetWidth() * 0.5;
        circleList[i].central.y = sin((timef + 10.0 * i) * 0.2) * 300 + ofGetHeight() * 0.5;
        circleList[i].radius = cos((timef + 1.0 * i) * 1.0) * 50 + 50;
    }

    for (int i = 0; i < totalLine; i++) {
        lineList[i].p1 = ofPoint(0, cos((timef + 0.1 * i) * 0.2) * ofGetHeight() * 0.5 + ofGetHeight() * 0.5);
        lineList[i].p2 = ofPoint(ofGetWidth(), sin((timef + 1.0 * i) * 0.2) * ofGetHeight() * 0.5 + ofGetHeight() * 0.5);
    }

    //--------------------------------------------------------------
    // Add object list. You have to execute this function in update.
    //--------------------------------------------------------------
    intersection->render(lineList, circleList);
}

//--------------------------------------------------------------
void ofApp::draw() {
    //--------------------------------------------------------------
    // Get intersections
    //--------------------------------------------------------------
    if (intersection->getIntersectionTotal() > 0) intersectionList = intersection->getIntersections();

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