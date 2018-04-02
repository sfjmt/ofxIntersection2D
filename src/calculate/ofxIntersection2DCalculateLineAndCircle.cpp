#include "ofxIntersection2DCalculateLineAndCircle.hpp"

//--------------------------------------------------------------
void ofxIntersection2D::LineAndCircle2D::clear() {
    clearArray<ofxIntersection2D::ObjectLine>(dataLineList);
    clearArray<ofxIntersection2D::ObjectCircle>(dataCircleList);
}

//--------------------------------------------------------------
void ofxIntersection2D::LineAndCircle2D::addCircle(ofVec2f &centralPosition, float &radius) {
    dataCircleList.push_back(ofxIntersection2D::ObjectCircle());

    int index = dataCircleList.size() - 1;
    dataCircleList[index].central = centralPosition;
    dataCircleList[index].radius = radius;
}

//--------------------------------------------------------------
void ofxIntersection2D::LineAndCircle2D::addLine(ofVec2f &beginPosition, ofVec2f &endPosition) {
    dataLineList.push_back(ofxIntersection2D::ObjectLine());

    int index = dataLineList.size() - 1;
    dataLineList[index].set(beginPosition, endPosition);
}

//--------------------------------------------------------------
void ofxIntersection2D::LineAndCircle2D::update() { intersectionPositionList = getMultipleIntersectionsManagement(dataLineList, dataCircleList); }