#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    intersection = new ofxIntersection2D::PerpendicularLine2D();

    totalPoint = 5;

    for (int i = 0; i < totalPoint; i++) {
        pointList.push_back(ofVec2f());
    }
}

//--------------------------------------------------------------
void ofApp::update() {
    //--------------------------------------------------------------
    // 1. Clear
    //--------------------------------------------------------------
    intersection->clear();

    if (intersectionList.size()) intersectionList.clear();

    float timef = ofGetElapsedTimef();
    float speed = 1.0;
    float elementInterval = 1.0;

    // update : line
    float line_y1 = cos(timef * speed) * (ofGetHeight() * 0.5) + (ofGetHeight() * 0.5);
    float line_y2 = sin(timef * speed) * (ofGetHeight() * 0.5) + (ofGetHeight() * 0.5);
    ofVec2f lineBeginPos = ofVec2f(100, line_y1);
    ofVec2f lineEndPos = ofVec2f(ofGetWidth() - 100, line_y2);

    line.p1 = lineBeginPos;
    line.p2 = lineEndPos;

    // update : point
    for (int i = 0; i < totalPoint; i++) {
        float point_moving_x = cos((timef + elementInterval * i) * speed) * 100;
        float point_moving_y = sin((timef + elementInterval * 2 * i) * speed) * 100;
        float point_fix_x = ofGetWidth() * 0.5 + point_moving_x;
        float point_fix_y = ofGetHeight() * 0.5 + point_moving_y;
        ofVec2f pointPos = ofVec2f(point_fix_x, point_fix_y);

        pointList[i] = pointPos;
    }

    //--------------------------------------------------------------
    // 2. Add
    //--------------------------------------------------------------
    intersection->addLine(line.p1, line.p2);
    for (int i = 0; i < totalPoint; i++) {
        intersection->addPoint(pointList[i]);
    }

    //--------------------------------------------------------------
    // 3. Update
    //--------------------------------------------------------------
    intersection->update();

    intersectionList = intersection->getIntersections();
    totalIntersection = intersectionList.size();
}

//--------------------------------------------------------------
void ofApp::draw() {
    // draw : line
    ofSetColor(0, 0, 0);
    ofDrawLine(line.p1, line.p2);

    // draw : point
    ofSetColor(255, 0, 0);
    for (int i = 0; i < totalPoint; i++) {
        ofDrawCircle(pointList[i], 10);
    }

    // draw : intersection
    ofSetColor(0, 0, 255);
    for (int i = 0; i < totalIntersection; i++) {
        ofDrawLine(pointList[i], intersectionList[i]);
        ofDrawCircle(intersectionList[i], 10);
    }

    // draw : caption
    ofDrawBitmapStringHighlight(caption(), ofVec2f(10, 20));
}

//--------------------------------------------------------------
string ofApp::caption() {
    stringstream ss;
    ss << ofGetFrameRate() << endl;
    ss << endl;
    ss << "total point : " << totalPoint << endl;
    ss << "total intersection : " << totalIntersection << endl;
    return ss.str();
}