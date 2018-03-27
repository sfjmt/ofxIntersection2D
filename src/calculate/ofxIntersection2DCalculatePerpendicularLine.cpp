#include "ofxIntersection2DCalculatePerpendicularLine.hpp"

//--------------------------------------------------------------
void ofxIntersection2D::PerpendicularLine2D::clear() {
    if (dataLineList.size()) dataLineList.clear();
    if (dataPointList.size()) dataPointList.clear();
    if (intersectionPositionList.size()) intersectionPositionList.clear();
}

//--------------------------------------------------------------
void ofxIntersection2D::PerpendicularLine2D::addLine(ofVec2f &p1, ofVec2f &p2) {
    dataLineList.push_back(ofxIntersection2D::ObjectLine());

    int index = dataLineList.size() - 1;
    dataLineList[index].set(p1, p2);
}

//--------------------------------------------------------------
void ofxIntersection2D::PerpendicularLine2D::addPoint(ofVec2f &pt) { dataPointList.push_back(pt); }

//--------------------------------------------------------------
void ofxIntersection2D::PerpendicularLine2D::update() {
    vector<ofVec2f> list = getMultipleIntersectionsManagement(dataLineList, dataPointList);

    int total = list.size();
    int totalIntersection;
    bool pushEnabled;

    for (int i = 0; i < total; ++i) {
        pushEnabled = true;
        totalIntersection = intersectionPositionList.size();
        for (int j = 0; j < totalIntersection; ++j) {
            if (list[i] == intersectionPositionList[j]) {
                pushEnabled = false;
                break;
            }
        }
        if (pushEnabled) intersectionPositionList.push_back(list[i]);
    }
}

//--------------------------------------------------------------
ofVec2f ofxIntersection2D::PerpendicularLine2D::getPerpendicularPosition(ofVec2f &lineBeginPos, ofVec2f &lineEndPos, ofVec2f &pointPos) {
    ofVec2f pos;

    if (lineEndPos.x == lineBeginPos.x) {
        pos.x = lineEndPos.x;
        pos.y = pointPos.y;
    } else if (lineEndPos.y == lineBeginPos.y) {
        pos.x = pointPos.x;
        pos.y = lineEndPos.y;
    } else {
        double m1, m2, b1, b2;
        m1 = (lineBeginPos.y - lineEndPos.y) / (lineBeginPos.x - lineEndPos.x);
        b1 = lineEndPos.y - (m1 * lineEndPos.x);
        m2 = -1.0 / m1;
        b2 = pointPos.y - (m2 * pointPos.x);
        pos.x = (b2 - b1) / (m1 - m2);
        pos.y = (b2 * m1 - b1 * m2) / (m1 - m2);
    }
    return pos;
}

//--------------------------------------------------------------
vector<ofVec2f> ofxIntersection2D::PerpendicularLine2D::getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectLine> &lineList, vector<ofVec2f> &pointList) {
    vector<ofVec2f> positions;

    int totalLine = lineList.size();
    int totalPoint = pointList.size();

    for (int i = 0; i < totalLine; i++) {
        for (int j = 0; j < totalPoint; j++) {
            ofPoint perpendicularPos = getPerpendicularPosition(dataLineList[i].p1, dataLineList[i].p2, pointList[j]);
            positions.push_back(perpendicularPos);
        }
    }

    return positions;
}