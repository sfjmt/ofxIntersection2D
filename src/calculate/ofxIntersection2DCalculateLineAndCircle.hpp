#ifndef ofxIntersection2DCalculateLineAndCircle_hpp
#define ofxIntersection2DCalculateLineAndCircle_hpp

#include "ofMain.h"
#include "BaseIntersection.hpp"
#include "ofxIntersection2DCalculatePerpendicularLine.hpp"

namespace ofxIntersection2D {

class LineAndCircle2D : public BaseIntersection {
   public:
    LineAndCircle2D() { toggleUsingOutsidePoints = true; };
    ~LineAndCircle2D(){};

    //--------------------------------------------------------------
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectLine> lineList, vector<ofxIntersection2D::ObjectCircle> circleList) {
        vector<ofVec2f> tmpPositions;
        vector<ofVec2f> tmpRawPositions;
        int totalTmpList;

        ofVec2f p1;
        ofVec2f p2;

        int totalLine = lineList.size();
        int totalCircle = circleList.size();

        for (int i = 0; i < totalLine; i++) {
            for (int j = 0; j < totalCircle; j++) {
                tmpRawPositions = getIntersection(circleList[j].central, circleList[j].radius, lineList[i].p1, lineList[i].p2);

                totalTmpList = tmpRawPositions.size();
                if (totalTmpList == 2) {
                    p1 = tmpRawPositions[0];
                    p2 = tmpRawPositions[1];

                    // compere
                    if (!std::isnan(p1.x) && !std::isnan(p1.y) && !std::isnan(p2.x) && !std::isnan(p2.y)) {
                        // Don't push same pos
                        if (!isAlreadyInList(p1, tmpPositions) || !isAlreadyInList(p2, tmpPositions)) {
                            if (toggleUsingOutsidePoints) {
                                tmpPositions.push_back(p1);
                                tmpPositions.push_back(p2);
                            } else {
                                if (isInWindow(p1) && isInWindow(p2)) {
                                    tmpPositions.push_back(p1);
                                    tmpPositions.push_back(p2);
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
                } else if (totalTmpList == 1) {
                    p1 = tmpRawPositions[0];

                    // compere
                    if (!std::isnan(p1.x) && !std::isnan(p1.y)) {
                        // Don't push same pos
                        if (!isAlreadyInList(p1, tmpPositions)) {
                            if (toggleUsingOutsidePoints) {
                                tmpPositions.push_back(p1);
                            } else {
                                if (isInWindow(p1)) {
                                    tmpPositions.push_back(p1);
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
                } else {
                    // ignore
                    continue;
                }
            }
        }
        return tmpPositions;
    };

    //--------------------------------------------------------------
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofVec2f> tmpLineBeginPosList, vector<ofVec2f> tmpLineEndPosList, vector<ofVec2f> tmpCentralPositionList,
                                                              vector<float> tmpRadiusList) {
        vector<ofxIntersection2D::ObjectLine> tmpLineList;
        int totalLine = tmpLineBeginPosList.size();
        for (int i = 0; i < totalLine; ++i) {
            tmpLineList.push_back(ofxIntersection2D::ObjectLine());
            tmpLineList[i].set(tmpLineBeginPosList[i], tmpLineEndPosList[i]);
        }

        vector<ofxIntersection2D::ObjectCircle> tmpCircleList;
        int totalCircle = tmpCentralPositionList.size();
        for (int i = 0; i < totalCircle; ++i) {
            tmpCircleList.push_back(ofxIntersection2D::ObjectCircle());
            tmpCircleList[i].central = tmpCentralPositionList[i];
            tmpCircleList[i].radius = tmpRadiusList[i];
        }

        vector<ofVec2f> tmpPositions = getMultipleIntersectionsManagement(tmpLineList, tmpCircleList);
        return tmpPositions;
    };

    //--------------------------------------------------------------
    inline vector<ofVec2f> getIntersection(ofVec2f central, float rad, ofVec2f lineBeginPos, ofVec2f lineEndPos) {
        vector<ofVec2f> list;

        ofVec2f perpendicular = management.getPerpendicularPosition(lineBeginPos, lineEndPos, central);

        float k = central.distance(perpendicular);
        float L, S, ex, ey;

        ofVec2f v1;
        ofVec2f v2;

        if (k < rad) {
            // Found two intersection.
            L = lineBeginPos.distance(lineEndPos);
            S = sqrt(pow(rad, 2) - pow(k, 2));

            ex = (lineEndPos.x - lineBeginPos.x) / L;
            ey = (lineEndPos.y - lineBeginPos.y) / L;

            v1.x = perpendicular.x + S * ex;
            v1.y = perpendicular.y + S * ey;

            v2.x = perpendicular.x - S * ex;
            v2.y = perpendicular.y - S * ey;

            list.push_back(v1);
            list.push_back(v2);
            return list;
        } else if (k > rad) {
            // Not found intersections.
            return list;
        } else {
            // Found one intersection.
            list.push_back(perpendicular);
            return list;
        }

        return list;
    };

   public:
    void clear() override;
    void addCircle(ofVec2f &centralPosition, float &radius) override;
    void addLine(ofVec2f &beginPosition, ofVec2f &endPosition) override;
    void update() override;

   private:
    ofxIntersection2D::PerpendicularLine2D management;

    vector<ofxIntersection2D::ObjectLine> dataLineList;
    vector<ofxIntersection2D::ObjectCircle> dataCircleList;

    vector<ofVec2f> lineBeginPosList;
    vector<ofVec2f> lineEndPosList;
    vector<ofVec2f> centralPositionList;
    vector<float> radiusList;
};
}
#endif /* ofxIntersection2DCalculateLineAndCircle_hpp */
