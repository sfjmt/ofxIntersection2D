#include "ofxIntersection2DCalculateMixAll.hpp"

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::clear() {
    clearArray<ofxIntersection2D::ObjectLine>(dataLineList);
    clearArray<ofxIntersection2D::ObjectCircle>(dataCircleList);
    clearArray<ofVec2f>(intersectionPositionList);
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::addCircle(ofVec2f &centralPosition, double &radius) {
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
void ofxIntersection2D::MixAll2D::render(vector<ofVec2f> &lineBeginPosList, vector<ofVec2f> &lineEndPosList, vector<ofVec2f> &centralPositionList, vector<double> &radiusList) {
    this->lineBeginPosList = lineBeginPosList;
    this->lineEndPosList = lineEndPosList;
    this->centralPositionList = centralPositionList;
    this->radiusList = radiusList;
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::render(vector<ofxIntersection2D::ObjectLine> &lineList, vector<ofxIntersection2D::ObjectCircle> &circleList) {
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
void ofxIntersection2D::MixAll2D::update() {
    // update : circle
    updateCircle();

    // update : line
    updateLine();

    // update : line & circle
    updateLineAndCircle();
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::updateInThread() {
    vector<ofVec2f> tmpIntersectionList;

    // update(in thread) : circle
    updateInThreadCircle(tmpIntersectionList);

    // update(in thread) : line
    updateInThreadLine(tmpIntersectionList);

    // update(in thread) : line & circle
    updateInThreadLineAndCircle(tmpIntersectionList);

    // update : intersection
    intersectionPositionList = tmpIntersectionList;
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::updateCircle() {
    vector<vector<ofVec2f> > list = managementCircle.getMultipleIntersectionsManagement(dataCircleList);

    int total = list.size();
    int totalElement;
    int totalIntersection;

    ofVec2f v;
    bool pushEnabled;

    for (int i = 0; i < total; ++i) {
        totalElement = list[i].size();
        for (int j = 0; j < totalElement; ++j) {
            v = list[i][j];

            pushEnabled = true;
            totalIntersection = intersectionPositionList.size();
            for (int k = 0; k < intersectionPositionList.size(); ++k) {
                if (v == intersectionPositionList[k]) {
                    pushEnabled = false;
                    break;
                }
            }
            if (pushEnabled) intersectionPositionList.push_back(v);
        }
    }
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::updateLine() {
    vector<ofVec2f> list = managementLine.getMultipleIntersectionsManagement(dataLineList);
    updateIntersectionList(list, intersectionPositionList);
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::updateLineAndCircle() {
    vector<ofVec2f> list = managementLineAndCircle.getMultipleIntersectionsManagement(dataLineList, dataCircleList);
    updateIntersectionList(list, intersectionPositionList);
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::updateInThreadCircle(vector<ofVec2f> &tmpIntersectionList) {
    vector<vector<ofVec2f> > list = managementCircle.getMultipleIntersectionsManagement(centralPositionList, radiusList);

    int total = list.size();
    int totalElement;
    int totalIntersection;

    ofVec2f v;
    bool pushEnabled;

    for (int i = 0; i < total; ++i) {
        totalElement = list[i].size();
        for (int j = 0; j < totalElement; ++j) {
            v = list[i][j];

            pushEnabled = true;
            totalIntersection = tmpIntersectionList.size();
            for (int k = 0; k < totalIntersection; ++k) {
                if (v == tmpIntersectionList[k]) {
                    pushEnabled = false;
                    break;
                }
            }
            if (pushEnabled) tmpIntersectionList.push_back(v);
        }
    }
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::updateInThreadLine(vector<ofVec2f> &tmpIntersectionList) {
    vector<ofVec2f> list = managementLine.getMultipleIntersectionsManagement(lineBeginPosList, lineEndPosList);
    updateIntersectionList(list, tmpIntersectionList);
}

//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::updateInThreadLineAndCircle(vector<ofVec2f> &tmpIntersectionList) {
    vector<ofVec2f> list = managementLineAndCircle.getMultipleIntersectionsManagement(lineBeginPosList, lineEndPosList, centralPositionList, radiusList);
    updateIntersectionList(list, tmpIntersectionList);
}
//--------------------------------------------------------------
void ofxIntersection2D::MixAll2D::updateIntersectionList(vector<ofVec2f> &list, vector<ofVec2f> &tmpList) {
    int total = list.size();
    int totalIntersection;
    bool pushEnabled;

    for (int i = 0; i < total; ++i) {
        pushEnabled = true;
        totalIntersection = tmpList.size();
        for (int j = 0; j < totalIntersection; ++j) {
            if (list[i] == tmpList[j]) {
                pushEnabled = false;
                break;
            }
        }
        if (pushEnabled) tmpList.push_back(list[i]);
    }
}
