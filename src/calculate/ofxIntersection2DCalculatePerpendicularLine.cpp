#include "ofxIntersection2DCalculatePerpendicularLine.hpp"

//--------------------------------------------------------------
void ofxIntersection2D::PerpendicularLine2D::clear() {
    clearArray<ofxIntersection2D::ObjectLine>(dataLineList);
    clearArray<ofVec2f>(dataPointList);
    clearArray<ofVec2f>(intersectionPositionList);
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
    for (int i = 0; i < total; ++i) {
        if (!isAlreadyInList(list[i], intersectionPositionList)) {
            intersectionPositionList.push_back(list[i]);
        } else {
            // ignore
            continue;
        }
    }
}