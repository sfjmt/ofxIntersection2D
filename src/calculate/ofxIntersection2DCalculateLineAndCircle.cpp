#include "ofxIntersection2DCalculateLineAndCircle.hpp"

//--------------------------------------------------------------
void ofxIntersection2D::LineAndCircle2D::clear() {
    clearArray<ofxIntersection2D::ObjectLine>(dataLineList);
    clearArray<ofxIntersection2D::ObjectCircle>(dataCircleList);
    clearArray<ofVec2f>(intersectionPositionList);
}

//--------------------------------------------------------------
void ofxIntersection2D::LineAndCircle2D::addCircle(ofVec2f &centralPosition, double &radius) {
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
void ofxIntersection2D::LineAndCircle2D::render(vector<ofVec2f> &lineBeginPosList, vector<ofVec2f> &lineEndPosList, vector<ofVec2f> &centralPositionList, vector<double> &radiusList) {
    this->lineBeginPosList = lineBeginPosList;
    this->lineEndPosList = lineEndPosList;
    this->centralPositionList = centralPositionList;
    this->radiusList = radiusList;
}

//--------------------------------------------------------------
void ofxIntersection2D::LineAndCircle2D::render(vector<ofxIntersection2D::ObjectLine> &lineList, vector<ofxIntersection2D::ObjectCircle> &circleList) {
    vector<ofVec2f> tmpLineBeginPosList;
    vector<ofVec2f> tmpLineEndPosList;
    vector<ofVec2f> tmpCentralPositionList;
    vector<double> tmpRadiusList;

    int totalLine = lineList.size();
    int totalCircle = circleList.size();

    for (int i = 0; i < totalLine; i++) {
        tmpLineBeginPosList.push_back(lineList[i].p1);
        tmpLineEndPosList.push_back(lineList[i].p2);
    }

    for (int i = 0; i < totalCircle; i++) {
        tmpCentralPositionList.push_back(circleList[i].central);
        tmpRadiusList.push_back(circleList[i].radius);
    }

    this->lineBeginPosList = tmpLineBeginPosList;
    this->lineEndPosList = tmpLineEndPosList;
    this->centralPositionList = tmpCentralPositionList;
    this->radiusList = tmpRadiusList;
}

//--------------------------------------------------------------
void ofxIntersection2D::LineAndCircle2D::update() {
    vector<ofVec2f> list = getMultipleIntersectionsManagement(dataLineList, dataCircleList);

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
void ofxIntersection2D::LineAndCircle2D::updateInThread() {
    vector<ofVec2f> list = getMultipleIntersectionsManagement(lineBeginPosList, lineEndPosList, centralPositionList, radiusList);
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