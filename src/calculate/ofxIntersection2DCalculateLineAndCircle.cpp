#include "ofxIntersection2DCalculateLineAndCircle.hpp"

//--------------------------------------------------------------
void ofxIntersection2D::LineAndCircle2D::clear() {
    if (dataLineList.size()) dataLineList.clear();
    if (dataCircleList.size()) dataCircleList.clear();
    if (intersectionPositionList.size()) intersectionPositionList.clear();
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

//--------------------------------------------------------------
vector<ofVec2f> ofxIntersection2D::LineAndCircle2D::getIntersection(ofVec2f &central, double &rad, ofVec2f &lineBeginPos, ofVec2f &lineEndPos) {
    vector<ofVec2f> list;

    ofVec2f perpendicular = intersectionPerpendicularLine.getPerpendicularPosition(lineBeginPos, lineEndPos, central);
    float k = central.distance(perpendicular);

    if (k > rad) {
        // Not found intersections.
        return list;
    } else if (k < rad) {
        // Found two intersection.
        float L = lineBeginPos.distance(lineEndPos);
        float S = sqrt(pow(rad, 2) - pow(k, 2));

        float ex = (lineEndPos.x - lineBeginPos.x) / L;
        float ey = (lineEndPos.y - lineBeginPos.y) / L;

        ofVec2f v1;
        ofVec2f v2;

        v1.x = perpendicular.x + S * ex;
        v1.y = perpendicular.y + S * ey;

        v2.x = perpendicular.x - S * ex;
        v2.y = perpendicular.y - S * ey;

        list.push_back(v1);
        list.push_back(v2);
        return list;
    } else {
        // Found one intersection.
        list.push_back(perpendicular);
        return list;
    }

    return list;
}

//--------------------------------------------------------------
vector<ofVec2f> ofxIntersection2D::LineAndCircle2D::getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectLine> &lineList, vector<ofxIntersection2D::ObjectCircle> &circleList) {
    vector<ofVec2f> list;

    int totalLine = lineList.size();
    int totalCircle = circleList.size();

    for (int i = 0; i < totalLine; i++) {
        for (int j = 0; j < totalCircle; j++) {
            vector<ofVec2f> tmpList = getIntersection(circleList[j].central, circleList[j].radius, lineList[i].p1, lineList[i].p2);

            int totalTmpList = tmpList.size();
            if (totalTmpList > 0) {
                for (int k = 0; k < totalTmpList; k++) {
                    list.push_back(tmpList[k]);
                }
            }
        }
    }
    return list;
}

//--------------------------------------------------------------
vector<ofVec2f> ofxIntersection2D::LineAndCircle2D::getMultipleIntersectionsManagement(vector<ofVec2f> &tmpLineBeginPosList, vector<ofVec2f> &tmpLineEndPosList,
                                                                                       vector<ofVec2f> &tmpCentralPositionList, vector<double> &tmpRadiusList) {
    vector<ofVec2f> list;

    int totalLine = tmpLineBeginPosList.size();
    int totalCircle = tmpCentralPositionList.size();

    for (int i = 0; i < totalLine; i++) {
        for (int j = 0; j < totalCircle; j++) {
            vector<ofVec2f> tmpList = getIntersection(tmpCentralPositionList[j], tmpRadiusList[j], tmpLineBeginPosList[i], tmpLineEndPosList[i]);

            int totalTmpList = tmpList.size();
            if (totalTmpList > 0) {
                for (int k = 0; k < totalTmpList; k++) {
                    list.push_back(tmpList[k]);
                }
            }
        }
    }
    return list;
}
