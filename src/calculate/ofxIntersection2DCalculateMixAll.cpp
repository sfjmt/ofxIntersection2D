#include "ofxIntersection2DCalculateMixAll.hpp"

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::clear() {
    clearArray<ofxIntersection2D::ObjectLine>(dataLineList);
    clearArray<ofxIntersection2D::ObjectCircle>(dataCircleList);
    clearArray<ofVec2f>(intersectionPositionList);
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::addCircle(ofVec2f &centralPosition, float &radius) {
    dataCircleList.push_back(ofxIntersection2D::ObjectCircle());

    int index = dataCircleList.size() - 1;
    dataCircleList[index].central = centralPosition;
    dataCircleList[index].radius = radius;
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::addLine(ofVec2f &beginPosition, ofVec2f &endPosition) {
    dataLineList.push_back(ofxIntersection2D::ObjectLine());

    int index = dataLineList.size() - 1;
    dataLineList[index].set(beginPosition, endPosition);
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::update() {
    //--------------------------------------------------------------
    // update : circle
    //--------------------------------------------------------------
    updateCircle(intersectionPositionList);

    //--------------------------------------------------------------
    // update : line
    //--------------------------------------------------------------
    updateLine(intersectionPositionList);

    //--------------------------------------------------------------
    // update : line & circle
    //--------------------------------------------------------------
    updateLineAndCircle(intersectionPositionList);
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::updateCircle(vector<ofVec2f> &tmpList) {
    vector<vector<ofVec2f>> list = managementCircle.getMultipleIntersectionsManagement(dataCircleList);

    int total = list.size();
    int totalElement;

    for (int i = 0; i < total; ++i) {
        totalElement = list[i].size();
        for (int j = 0; j < totalElement; ++j) {
            tmpList.push_back(list[i][j]);
        }
    }
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::updateLine(vector<ofVec2f> &tmpList) {
    vector<ofVec2f> list = managementLine.getMultipleIntersectionsManagement(dataLineList);
    updateIntersectionList(list, tmpList);
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::updateLineAndCircle(vector<ofVec2f> &tmpList) {
    vector<ofVec2f> list = managementLineAndCircle.getMultipleIntersectionsManagement(dataLineList, dataCircleList);
    updateIntersectionList(list, tmpList);
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::updateIntersectionList(vector<ofVec2f> &list, vector<ofVec2f> &tmpList) {
    int total = list.size();
    for (int i = 0; i < total; ++i) {
        if (!isAlreadyInList(list[i], tmpList)) {
            tmpList.push_back(list[i]);
        } else {
            // ignore
            continue;
        }
    }
}
