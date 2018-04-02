#ifndef ofxIntersection2DCalculateMixAll_hpp
#define ofxIntersection2DCalculateMixAll_hpp

#include "ofMain.h"
#include "ofxIntersection2D.hpp"

namespace ofxIntersection2D {

class MixAll2D : public BaseIntersection {
   public:
    MixAll2D(){};
    ~MixAll2D(){};

   public:
    void clear() override;
    void addCircle(ofVec2f &centralPosition, float &radius) override;
    void addLine(ofVec2f &beginPosition, ofVec2f &endPosition) override;
    void update() override;

   private:
    void updateCircle(vector<ofVec2f> &tmpList);
    void updateLine(vector<ofVec2f> &tmpList);
    void updateLineAndCircle(vector<ofVec2f> &tmpList);

    void updateIntersectionList(vector<ofVec2f> &list, vector<ofVec2f> &tmpList);

    ofxIntersection2D::Circle2D managementCircle;
    ofxIntersection2D::Line2D managementLine;
    ofxIntersection2D::LineAndCircle2D managementLineAndCircle;

    vector<ofxIntersection2D::ObjectCircle> dataCircleList;
    vector<ofxIntersection2D::ObjectLine> dataLineList;

    vector<ofVec2f> lineBeginPosList;
    vector<ofVec2f> lineEndPosList;
    vector<ofVec2f> centralPositionList;
    vector<float> radiusList;
};
}
#endif /* ofxIntersection2DCalculateMixAll_hpp */
