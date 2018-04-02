#include "ofxIntersection2DCalculateLine.hpp"

//--------------------------------------------------------------
void ofxIntersection2D::Line2D::clear() { clearArray<ofxIntersection2D::ObjectLine>(dataLineList); }

//--------------------------------------------------------------
void ofxIntersection2D::Line2D::addLine(ofVec2f &beginPosition, ofVec2f &endPosition) {
    dataLineList.push_back(ofxIntersection2D::ObjectLine());

    int index = dataLineList.size() - 1;
    dataLineList[index].set(beginPosition, endPosition);
}

//--------------------------------------------------------------
void ofxIntersection2D::Line2D::update() { intersectionPositionList = getMultipleIntersectionsManagement(dataLineList); }
