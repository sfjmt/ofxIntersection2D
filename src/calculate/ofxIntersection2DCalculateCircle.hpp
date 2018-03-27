#ifndef ofxIntersection2DCalculateCircle_hpp
#define ofxIntersection2DCalculateCircle_hpp

#include "ofMain.h"
#include "BaseIntersection.hpp"

namespace ofxIntersection2D {

class Circle2D : public BaseIntersection {
   public:
    Circle2D(){};
    ~Circle2D(){};

    void clear() override;
    void addCircle(ofVec2f &centralPosition, double &radius) override;
    void render(vector<ofVec2f> &centralPositionList, vector<double> &radiusList) override;
    void update() override;
    void updateInThread() override;

   private:
    inline vector<vector<ofVec2f> > getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectCircle> data);
    inline vector<vector<ofVec2f> > getMultipleIntersectionsManagement(vector<ofVec2f> tmpCentralPositionList, vector<double> tmpRadiusList);
    inline vector<ofVec2f> getIntersection(ofVec2f p1, double r1, ofVec2f p2, double r2);

    vector<ofxIntersection2D::ObjectCircle> data;

    vector<ofVec2f> centralPositionList;
    vector<double> radiusList;
};
}

#endif