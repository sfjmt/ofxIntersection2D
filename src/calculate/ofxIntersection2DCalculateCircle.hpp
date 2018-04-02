#ifndef ofxIntersection2DCalculateCircle_hpp
#define ofxIntersection2DCalculateCircle_hpp

#include "ofMain.h"
#include "BaseIntersection.hpp"

namespace ofxIntersection2D {

class Circle2D : public BaseIntersection {
   public:
    Circle2D() { toggleUsingOutsidePoints = true; };
    ~Circle2D(){};

    //--------------------------------------------------------------
    inline vector<vector<ofVec2f> > getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectCircle> data) {
        vector<vector<ofVec2f> > tmpPositions;
        vector<ofVec2f> tmpAllPositions;
        vector<ofVec2f> tmpRawPositions;
        ofVec2f p1;
        ofVec2f p2;

        int total = data.size();

        ofVec2f central_1;
        float rad_1;

        ofVec2f central_2;
        float rad_2;

        for (int i = 0; i < total; ++i) {
            for (int j = 0; j < total; ++j) {
                if (j != i) {
                    // set central
                    central_1 = data[i].central;
                    central_2 = data[j].central;

                    // set rad
                    rad_1 = data[i].radius;
                    rad_2 = data[j].radius;

                    // get intersection list
                    tmpRawPositions = getIntersection(central_1, rad_1, central_2, rad_2);

                    // get intersection
                    p1 = tmpRawPositions[0];
                    p2 = tmpRawPositions[1];

                    // compere
                    if (!std::isnan(p1.x) && !std::isnan(p1.y) && !std::isnan(p2.x) && !std::isnan(p2.y)) {
                        // Don't push same pos
                        if (!isAlreadyInList(p1, tmpAllPositions) || !isAlreadyInList(p2, tmpAllPositions)) {
                            if (toggleUsingOutsidePoints) {
                                tmpAllPositions.push_back(p1);
                                tmpAllPositions.push_back(p2);

                                tmpPositions.push_back(tmpRawPositions);
                            } else {
                                if (isInWindow(p1) && isInWindow(p2)) {
                                    tmpAllPositions.push_back(p1);
                                    tmpAllPositions.push_back(p2);

                                    tmpPositions.push_back(tmpRawPositions);
                                } else {
                                    // ignore
                                    continue;
                                }
                            }
                        } else {
                            // ignore
                            continue;
                        }
                    } else {
                        // ignore
                        continue;
                    }
                } else if (j == i) {
                    // ignore
                    continue;
                } else {
                    // ignore
                    continue;
                }
            }
        }
        return tmpPositions;
    };

    //--------------------------------------------------------------
    inline vector<vector<ofVec2f> > getMultipleIntersectionsManagement(vector<ofVec2f> tmpCentralPositionList, vector<float> tmpRadiusList) {
        vector<ofxIntersection2D::ObjectCircle> tmpData;
        int total = tmpCentralPositionList.size();

        for (int i = 0; i < total; ++i) {
            tmpData.push_back(ofxIntersection2D::ObjectCircle());
            tmpData[i].central = tmpCentralPositionList[i];
            tmpData[i].radius = tmpRadiusList[i];
        }

        vector<vector<ofVec2f> > tmpPositions = getMultipleIntersectionsManagement(tmpData);
        return tmpPositions;
    };

    //--------------------------------------------------------------
    inline vector<ofVec2f> getIntersection(ofVec2f p1, float r1, ofVec2f p2, float r2) {
        vector<ofVec2f> positions;

        float distance = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
        float angle = atan2((p2.y - p1.y), (p2.x - p1.x));
        float theta = acos((pow(distance, 2) + pow(r1, 2) - pow(r2, 2)) / (2 * distance * r1));

        ofVec2f intersection1;
        ofVec2f intersection2;

        intersection1.x = p1.x + r1 * cos(angle + theta);
        intersection1.y = p1.y + r1 * sin(angle + theta);
        intersection2.x = p1.x + r1 * cos(angle - theta);
        intersection2.y = p1.y + r1 * sin(angle - theta);

        positions.push_back(intersection1);
        positions.push_back(intersection2);
        return positions;
    };

   public:
    void clear() override;
    void addCircle(ofVec2f &centralPosition, float &radius) override;
    void update() override;

   private:
    vector<ofxIntersection2D::ObjectCircle> dataCircleList;

    vector<ofVec2f> centralPositionList;
    vector<float> radiusList;
};
}

#endif