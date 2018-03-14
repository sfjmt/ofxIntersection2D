#include "ofxIntersection2DCalculateCircle.hpp"

//--------------------------------------------------------------
void ofxIntersection2D::Circle2D::clear() {
    if (data.size()) data.clear();
    if (intersectionPositionList.size()) intersectionPositionList.clear();
}

//--------------------------------------------------------------
void ofxIntersection2D::Circle2D::add(ofVec2f &centralPosition, double &radius) {
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
void ofxIntersection2D::Circle2D::update() {
    vector<vector<ofVec2f> > list = getMultipleIntersectionsManagement(data);

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
    vector<vector<ofVec2f> > list = getMultipleIntersectionsManagement(centralPositionList, radiusList);
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

//--------------------------------------------------------------
vector<vector<ofVec2f> > ofxIntersection2D::Circle2D::getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectCircle> data) {
    vector<vector<ofVec2f> > positions;

    int total = data.size();
    for (int i = 0; i < total; ++i) {
        for (int j = 0; j < total; ++j) {
            if (i != j) {
                positions.push_back(getIntersection(data[i].position, data[i].radius, data[j].position, data[j].radius));
            } else if (i == j) {
                continue;
            }
        }
    }
    return positions;
}

//--------------------------------------------------------------
vector<vector<ofVec2f> > ofxIntersection2D::Circle2D::getMultipleIntersectionsManagement(vector<ofVec2f> tmpCentralPositionList, vector<double> tmpRadiusList) {
    vector<vector<ofVec2f> > positions;

    int total = tmpCentralPositionList.size();
    for (int i = 0; i < total; ++i) {
        for (int j = 0; j < total; ++j) {
            if (i != j) {
                positions.push_back(getIntersection(tmpCentralPositionList[i], tmpRadiusList[i], tmpCentralPositionList[j], tmpRadiusList[j]));
            } else if (i == j) {
                continue;
            }
        }
    }
    return positions;
}

//--------------------------------------------------------------
vector<ofVec2f> ofxIntersection2D::Circle2D::getIntersection(ofVec2f p1, double r1, ofVec2f p2, double r2) {
    vector<ofVec2f> positions;

    double distance = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    double angle = atan2((p2.y - p1.y), (p2.x - p1.x));
    double theta = acos((pow(distance, 2) + pow(r1, 2) - pow(r2, 2)) / (2 * distance * r1));

    ofVec2f intersection1;
    ofVec2f intersection2;

    intersection1.x = p1.x + r1 * cos(angle + theta);
    intersection1.y = p1.y + r1 * sin(angle + theta);
    intersection2.x = p1.x + r1 * cos(angle - theta);
    intersection2.y = p1.y + r1 * sin(angle - theta);

    positions.push_back(intersection1);
    positions.push_back(intersection2);
    return positions;
}