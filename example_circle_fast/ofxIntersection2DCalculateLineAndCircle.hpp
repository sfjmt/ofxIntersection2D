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

    void clear() override;
    void addCircle(ofVec2f &centralPosition, double &radius) override;
    void addLine(ofVec2f &beginPosition, ofVec2f &endPosition) override;
    void render(vector<ofVec2f> &lineBeginPosList, vector<ofVec2f> &lineEndPosList, vector<ofVec2f> &centralPositionList, vector<double> &radiusList) override;
    void render(vector<ofxIntersection2D::ObjectLine> &lineList, vector<ofxIntersection2D::ObjectCircle> &circleList) override;
    void update() override;
    void updateInThread() override;

   private:
    inline vector<ofVec2f> getIntersection(ofVec2f &central, double &rad, ofVec2f &lineBeginPos, ofVec2f &lineEndPos);
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectLine> &lineList, vector<ofxIntersection2D::ObjectCircle> &circleList);
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofVec2f> &tmpLineBeginPosList, vector<ofVec2f> &tmpLineEndPosList, vector<ofVec2f> &tmpCentralPositionList,
                                                              vector<double> &tmpRadiusList);

    ofxIntersection2D::PerpendicularLine2D intersectionPerpendicularLine;

    vector<ofxIntersection2D::ObjectLine> dataLineList;
    vector<ofxIntersection2D::ObjectCircle> dataCircleList;

    vector<ofVec2f> lineBeginPosList;
    vector<ofVec2f> lineEndPosList;
    vector<ofVec2f> centralPositionList;
    vector<double> radiusList;
};
}
#endif /* ofxIntersection2DCalculateLineAndCircle_hpp */
