#ifndef ofxIntersection2DCalculateCircle_hpp
#define ofxIntersection2DCalculateCircle_hpp

#include "ofMain.h"
#include "BaseIntersection.hpp"

namespace ofxIntersection2D {

class Circle2D : public BaseIntersection {
   public:
    Circle2D(){};
    ~Circle2D(){};

    //--------------------------------------------------------------
    inline vector<vector<ofVec2f> > getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectCircle> &data) {
        vector<vector<ofVec2f> > positions;

        int total = data.size();
        for (int i = 0; i < total; ++i) {
            for (int j = 0; j < total; ++j) {
                if (i != j) {
                    positions.push_back(getIntersection(data[i].central, data[i].radius, data[j].central, data[j].radius));
                } else if (i == j) {
                    continue;
                }
            }
        }
        return positions;
    };

    //--------------------------------------------------------------
    inline vector<vector<ofVec2f> > getMultipleIntersectionsManagement(vector<ofVec2f> &tmpCentralPositionList, vector<double> &tmpRadiusList) {
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
    };

    //--------------------------------------------------------------
    inline vector<ofVec2f> getIntersection(ofVec2f &p1, double &r1, ofVec2f &p2, double &r2) {
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
    };

   public:
    void clear() override;
    void addCircle(ofVec2f &centralPosition, double &radius) override;
    void render(vector<ofVec2f> &centralPositionList, vector<double> &radiusList) override;
    void render(vector<ofxIntersection2D::ObjectCircle> &circleList) override;
    void update() override;
    void updateInThread() override;

   private:
    vector<ofxIntersection2D::ObjectCircle> data;

    vector<ofVec2f> centralPositionList;
    vector<double> radiusList;
};
}

#endif