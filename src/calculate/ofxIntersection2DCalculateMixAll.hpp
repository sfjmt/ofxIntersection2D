#ifndef ofxIntersection2DCalculateMixAll_hpp
#define ofxIntersection2DCalculateMixAll_hpp

#include "ofMain.h"
#include "ofxIntersection2DStore.hpp"

namespace ofxIntersection2D {

class MixAll2D : public BaseIntersection {
   public:
    MixAll2D(){};
    ~MixAll2D(){};

   public:
    void clear() override;
    void addCircle(ofVec2f &centralPosition, double &radius) override;
    void addLine(ofVec2f &beginPosition, ofVec2f &endPosition) override;
    void render(vector<ofVec2f> &lineBeginPosList, vector<ofVec2f> &lineEndPosList, vector<ofVec2f> &centralPositionList, vector<double> &radiusList) override;
    void render(vector<ofxIntersection2D::ObjectLine> &lineList, vector<ofxIntersection2D::ObjectCircle> &circleList) override;
    void update() override;
    void updateInThread() override;

   private:
    void updateCircle();
    void updateLine();
    void updateLineAndCircle();

    void updateInThreadCircle(vector<ofVec2f> &tmpIntersectionList);
    void updateInThreadLine(vector<ofVec2f> &tmpIntersectionList);
    void updateInThreadLineAndCircle(vector<ofVec2f> &tmpIntersectionList);

    void updateIntersectionList(vector<ofVec2f> &list, vector<ofVec2f> &tmpList);

    ofxIntersection2D::Circle2D managementCircle;
    ofxIntersection2D::Line2D managementLine;
    ofxIntersection2D::LineAndCircle2D managementLineAndCircle;

    vector<ofxIntersection2D::ObjectCircle> dataCircleList;
    vector<ofxIntersection2D::ObjectLine> dataLineList;

    vector<ofVec2f> lineBeginPosList;
    vector<ofVec2f> lineEndPosList;
    vector<ofVec2f> centralPositionList;
    vector<double> radiusList;
};
}
#endif /* ofxIntersection2DCalculateMixAll_hpp */
