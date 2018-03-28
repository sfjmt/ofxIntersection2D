#ifndef ofxIntersection2DCalculatePerpendicularLine_hpp
#define ofxIntersection2DCalculatePerpendicularLine_hpp

#include "ofMain.h"
#include "BaseIntersection.hpp"

namespace ofxIntersection2D {

class PerpendicularLine2D : public BaseIntersection {
   public:
    PerpendicularLine2D(){};
    ~PerpendicularLine2D(){};

    //--------------------------------------------------------------
    inline ofVec2f getPerpendicularPosition(ofVec2f lineBeginPos, ofVec2f lineEndPos, ofVec2f pointPos) {
        ofVec2f pos;

        if (lineEndPos.x == lineBeginPos.x) {
            pos.x = lineEndPos.x;
            pos.y = pointPos.y;
        } else if (lineEndPos.y == lineBeginPos.y) {
            pos.x = pointPos.x;
            pos.y = lineEndPos.y;
        } else {
            double m1, m2, b1, b2;
            m1 = (lineBeginPos.y - lineEndPos.y) / (lineBeginPos.x - lineEndPos.x);
            b1 = lineEndPos.y - (m1 * lineEndPos.x);
            m2 = -1.0 / m1;
            b2 = pointPos.y - (m2 * pointPos.x);
            pos.x = (b2 - b1) / (m1 - m2);
            pos.y = (b2 * m1 - b1 * m2) / (m1 - m2);
        }
        return pos;
    };

    //--------------------------------------------------------------
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectLine> lineList, vector<ofVec2f> 	pointList) {
        vector<ofVec2f> positions;

        int totalLine = lineList.size();
        int totalPoint = pointList.size();

        for (int i = 0; i < totalLine; i++) {
            for (int j = 0; j < totalPoint; j++) {
                ofPoint perpendicularPos = getPerpendicularPosition(dataLineList[i].p1, dataLineList[i].p2, pointList[j]);
                positions.push_back(perpendicularPos);
            }
        }

        return positions;
    };

   public:
    void clear() override;
    void addLine(ofVec2f &p1, ofVec2f &p2) override;
    void addPoint(ofVec2f &pt) override;
    void update() override;

   private:
    vector<ofxIntersection2D::ObjectLine> dataLineList;
    vector<ofVec2f> dataPointList;
};
}
#endif /* ofxIntersection2DCalculatePerpendicularLine_hpp */
