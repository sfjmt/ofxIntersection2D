#include "ofxIntersection2DCalculateCircle.hpp"

//--------------------------------------------------------------
void ofxIntersection2D::Circle2D::clear() {
    clearArray<ofxIntersection2D::ObjectCircle>(dataCircleList);
    clearArray<ofVec2f>(intersectionPositionList);
}

//--------------------------------------------------------------
void ofxIntersection2D::Circle2D::addCircle(ofVec2f &centralPosition, float &radius) {
    dataCircleList.push_back(ofxIntersection2D::ObjectCircle());

    int index = dataCircleList.size() - 1;
    dataCircleList[index].set(centralPosition, radius);
}

//--------------------------------------------------------------
void ofxIntersection2D::Circle2D::update() {
    vector<vector<ofVec2f>> list = getMultipleIntersectionsManagement(dataCircleList);

    int total = list.size();
    int totalElement;

    for (int i = 0; i < total; ++i) {
        totalElement = list[i].size();
        for (int j = 0; j < totalElement; ++j) {
            intersectionPositionList.push_back(list[i][j]);
        }
    }
}
