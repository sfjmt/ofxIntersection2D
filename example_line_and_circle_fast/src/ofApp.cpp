#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetCircleResolution(100);

    intersection = new ofxIntersection2D::LineAndCircle2D();
    intersection->start();  // start threadedFunction

    totalCircle = 150;
    totalLine = 150;

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

    vector<ofVec2f> tmpCentralList;
    vector<double> tmpRadList;

    vector<ofVec2f> tmpLineBeginPosList;
    vector<ofVec2f> tmpLineEndPosList;

    for (int i = 0; i < totalCircle; i++) {
        circleList[i].central.x = cos((timef + 10.0 * i) * 0.2) * 300 + ofGetWidth() * 0.5;
        circleList[i].central.y = sin((timef + 10.0 * i) * 0.2) * 300 + ofGetHeight() * 0.5;
        circleList[i].radius = cos((timef + 1.0 * i) * 1.0) * 50 + 50;
        tmpCentralList.push_back(circleList[i].central);
        tmpRadList.push_back(circleList[i].radius);
    }

    for (int i = 0; i < totalLine; i++) {
        lineList[i].p1 = ofPoint(0, cos((timef + 0.1 * i) * 0.2) * ofGetHeight() * 0.5 + ofGetHeight() * 0.5);
        lineList[i].p2 = ofPoint(ofGetWidth(), sin((timef + 1.0 * i) * 0.2) * ofGetHeight() * 0.5 + ofGetHeight() * 0.5);

        tmpLineBeginPosList.push_back(lineList[i].p1);
        tmpLineEndPosList.push_back(lineList[i].p2);
    }

    //--------------------------------------------------------------
    // Add object list. You have to execute this function in update.
    //--------------------------------------------------------------
    intersection->render(tmpLineBeginPosList, tmpLineEndPosList, tmpCentralList, tmpRadList);
}

//--------------------------------------------------------------
void ofApp::draw() {
    //--------------------------------------------------------------
    // Get intersections
    //--------------------------------------------------------------
    intersectionList = intersection->getIntersections();

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