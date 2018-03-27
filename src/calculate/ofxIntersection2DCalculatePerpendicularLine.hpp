#ifndef ofxIntersection2DCalculatePerpendicularLine_hpp
#define ofxIntersection2DCalculatePerpendicularLine_hpp

#include "ofMain.h"
#include "BaseIntersection.hpp"

namespace ofxIntersection2D {

class PerpendicularLine2D : public BaseIntersection {
   public:
    PerpendicularLine2D(){};
    ~PerpendicularLine2D(){};

    ofVec2f getPerpendicularPosition(ofVec2f &lineBeginPos, ofVec2f &lineEndPos, ofVec2f &pointPos);

   public:
    void clear() override;
    void addLine(ofVec2f &p1, ofVec2f &p2) override;
    void addPoint(ofVec2f &pt) override;
    void update() override;

   private:
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectLine> &lineList, vector<ofVec2f> &pointList);

    vector<ofxIntersection2D::ObjectLine> dataLineList;
    vector<ofVec2f> dataPointList;
};
}
#endif /* ofxIntersection2DCalculatePerpendicularLine_hpp */
