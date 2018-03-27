#include "ofxIntersection2DCalculateLine.hpp"

//--------------------------------------------------------------
void ofxIntersection2D::Line2D::clear() {
    if (data.size()) data.clear();
    if (intersectionPositionList.size()) intersectionPositionList.clear();
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

//--------------------------------------------------------------
vector<ofVec2f> ofxIntersection2D::Line2D::getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectLine> data) {
    vector<ofVec2f> position;

    int total = data.size();
    for (int i = 0; i < total; ++i) {
        for (int j = 0; j < total; ++j) {
            if (i != j) {
                position.push_back(getLineIntersection(data[i].p1, data[i].p2, data[j].p1, data[j].p2));
            } else if (i == j) {
                continue;
            }
        }
    }
    return position;
}

//--------------------------------------------------------------
vector<ofVec2f> ofxIntersection2D::Line2D::getMultipleIntersectionsManagement(vector<ofVec2f> tmpLineBeginPosList, vector<ofVec2f> tmpLineEndPosList) {
    vector<ofVec2f> position;

    int total = tmpLineBeginPosList.size();
    for (int i = 0; i < total; ++i) {
        for (int j = 0; j < total; ++j) {
            if (i != j) {
                position.push_back(getLineIntersection(tmpLineBeginPosList[i], tmpLineEndPosList[i], tmpLineBeginPosList[j], tmpLineEndPosList[j]));
            } else if (i == j) {
                continue;
            }
        }
    }
    return position;
}

//--------------------------------------------------------------
ofVec2f ofxIntersection2D::Line2D::getLineIntersection(ofVec2f p1_1, ofVec2f p1_2, ofVec2f p2_1, ofVec2f p2_2) {
    ofVec2f pos;

    double dev = (p1_2.y - p1_1.y) * (p2_2.x - p2_1.x) - (p1_2.x - p1_1.x) * (p2_2.y - p2_1.y);

    double d1, d2;
    d1 = (p2_1.y * p2_2.x - p2_1.x * p2_2.y);
    d2 = (p1_1.y * p1_2.x - p1_1.x * p1_2.y);

    pos.x = d1 * (p1_2.x - p1_1.x) - d2 * (p2_2.x - p2_1.x);
    pos.x /= dev;
    pos.y = d1 * (p1_2.y - p1_1.y) - d2 * (p2_2.y - p2_1.y);
    pos.y /= dev;

    return pos;
}