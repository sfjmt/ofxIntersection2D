#ifndef ofxIntersection2DCalculateLine_hpp
#define ofxIntersection2DCalculateLine_hpp

#include "ofMain.h"
#include "BaseIntersection.hpp"

namespace ofxIntersection2D {

class Line2D : public BaseIntersection {
   public:
    Line2D(){};
    ~Line2D(){};

    void clear() override;
    void add(ofVec2f &p1, ofVec2f &p2) override;
    void render(vector<ofVec2f> &list1, vector<ofVec2f> &list2) override;
    void update() override;
    void updateInThread() override;

   private:
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectLine> data);
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofVec2f> tmpList1, vector<ofVec2f> tmpList2);
    inline ofVec2f getLineIntersection(ofVec2f p1_1, ofVec2f p1_2, ofVec2f p2_1, ofVec2f p2_2);

    vector<ofxIntersection2D::ObjectLine> data;

    vector<ofVec2f> list1;
    vector<ofVec2f> list2;
};
}
#endif /* ofxIntersection2DCalculateLine_hpp */
