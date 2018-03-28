#include "ofxIntersection2DCalculateLine.hpp"

//--------------------------------------------------------------
void ofxIntersection2D::Line2D::clear() {
    clearArray<ofxIntersection2D::ObjectLine>(data);
    clearArray<ofVec2f>(intersectionPositionList);
}

//--------------------------------------------------------------
void ofxIntersection2D::Line2D::addLine(ofVec2f &beginPosition, ofVec2f &endPosition) {
    data.push_back(ofxIntersection2D::ObjectLine());

    int index = data.size() - 1;
    data[index].set(beginPosition, endPosition);
}

//--------------------------------------------------------------
void ofxIntersection2D::Line2D::render(vector<ofVec2f> &lineBeginPosList, vector<ofVec2f> &lineEndPosList) {
    this->lineBeginPosList = lineBeginPosList;
    this->lineEndPosList = lineEndPosList;
}

//--------------------------------------------------------------
void ofxIntersection2D::Line2D::render(vector<ofxIntersection2D::ObjectLine> &lineList) {
    vector<ofVec2f> tmpLineBeginPosList;
    vector<ofVec2f> tmpLineEndPosList;

    int totalLine = lineList.size();

    for (int i = 0; i < totalLine; i++) {
        tmpLineBeginPosList.push_back(lineList[i].p1);
        tmpLineEndPosList.push_back(lineList[i].p2);
    }

    this->lineBeginPosList = tmpLineBeginPosList;
    this->lineEndPosList = tmpLineEndPosList;
}

//--------------------------------------------------------------
void ofxIntersection2D::Line2D::update() {
    vector<ofVec2f> list = getMultipleIntersectionsManagement(data);

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
void ofxIntersection2D::Line2D::updateInThread() {
    vector<ofVec2f> list = getMultipleIntersectionsManagement(lineBeginPosList, lineEndPosList);
    vector<ofVec2f> tmpIntersectionList;

    int total = list.size();
    int totalIntersection;
    bool pushEnabled;

    for (int i = 0; i < total; ++i) {
        pushEnabled = true;
        totalIntersection = tmpIntersectionList.size();
        for (int j = 0; j < totalIntersection; ++j) {
            if (list[i] == tmpIntersectionList[j]) {
                pushEnabled = false;
                break;
            }
        }
        if (pushEnabled) tmpIntersectionList.push_back(list[i]);
    }

    intersectionPositionList = tmpIntersectionList;
}
