#include "ofxIntersection2DCalculateCircle.hpp"

//--------------------------------------------------------------
void ofxIntersection2D::Circle2D::clear() {
    clearArray<ofxIntersection2D::ObjectCircle>(data);
    clearArray<ofVec2f>(intersectionPositionList);
}

//--------------------------------------------------------------
void ofxIntersection2D::Circle2D::addCircle(ofVec2f &centralPosition, double &radius) {
    data.push_back(ofxIntersection2D::ObjectCircle());

    int index = data.size() - 1;
    data[index].set(centralPosition, radius);
}

//--------------------------------------------------------------
void ofxIntersection2D::Circle2D::render(vector<ofVec2f> &centralPositionList, vector<double> &radiusList) {
    this->centralPositionList = centralPositionList;
    this->radiusList = radiusList;
}

//--------------------------------------------------------------
void ofxIntersection2D::Circle2D::render(vector<ofxIntersection2D::ObjectCircle> &circleList) {
    vector<ofVec2f> tmpCentralPositionList;
    vector<double> tmpRadiusList;

    int totalCircle = circleList.size();

    for (int i = 0; i < totalCircle; i++) {
        tmpCentralPositionList.push_back(circleList[i].central);
        tmpRadiusList.push_back(circleList[i].radius);
    }

    this->centralPositionList = tmpCentralPositionList;
    this->radiusList = tmpRadiusList;
}

//--------------------------------------------------------------
void ofxIntersection2D::Circle2D::update() {
    vector<vector<ofVec2f>> list = getMultipleIntersectionsManagement(data);

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
void ofxIntersection2D::Circle2D::updateInThread() {
    vector<vector<ofVec2f>> list = getMultipleIntersectionsManagement(centralPositionList, radiusList);
    vector<ofVec2f> tmpIntersectionList;

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

    intersectionPositionList = tmpIntersectionList;
}