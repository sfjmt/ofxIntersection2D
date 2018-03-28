#ifndef ofxIntersection2DCalculateLineAndCircle_hpp
#define ofxIntersection2DCalculateLineAndCircle_hpp

#include "ofMain.h"
#include "BaseIntersection.hpp"
#include "ofxIntersection2DCalculatePerpendicularLine.hpp"

namespace ofxIntersection2D {

class LineAndCircle2D : public BaseIntersection {
   public:
    LineAndCircle2D(){};
    ~LineAndCircle2D(){};

    //--------------------------------------------------------------
    inline vector<ofVec2f> getIntersection(ofVec2f central, double rad, ofVec2f lineBeginPos, ofVec2f lineEndPos) {
        vector<ofVec2f> list;

        ofVec2f perpendicular = management.getPerpendicularPosition(lineBeginPos, lineEndPos, central);
        float k = central.distance(perpendicular);

        if (k < rad) {
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

    //--------------------------------------------------------------
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectLine> lineList, vector<ofxIntersection2D::ObjectCircle> circleList) {
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
    };

    //--------------------------------------------------------------
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofVec2f> tmpLineBeginPosList, vector<ofVec2f> tmpLineEndPosList, vector<ofVec2f> tmpCentralPositionList,
                                                              vector<double> tmpRadiusList) {
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
    };

   public:
    void clear() override;
    void addCircle(ofVec2f &centralPosition, double &radius) override;
    void addLine(ofVec2f &beginPosition, ofVec2f &endPosition) override;
    void render(vector<ofVec2f> &lineBeginPosList, vector<ofVec2f> &lineEndPosList, vector<ofVec2f> &centralPositionList, vector<double> &radiusList) override;
    void render(vector<ofxIntersection2D::ObjectLine> &lineList, vector<ofxIntersection2D::ObjectCircle> &circleList) override;
    void update() override;
    void updateInThread() override;

   private:
    ofxIntersection2D::PerpendicularLine2D management;

    vector<ofxIntersection2D::ObjectLine> dataLineList;
    vector<ofxIntersection2D::ObjectCircle> dataCircleList;

    vector<ofVec2f> lineBeginPosList;
    vector<ofVec2f> lineEndPosList;
    vector<ofVec2f> centralPositionList;
    vector<double> radiusList;
};
}
#endif /* ofxIntersection2DCalculateLineAndCircle_hpp */
