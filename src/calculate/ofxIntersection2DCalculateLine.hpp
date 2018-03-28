#ifndef ofxIntersection2DCalculateLine_hpp
#define ofxIntersection2DCalculateLine_hpp

#include "ofMain.h"
#include "BaseIntersection.hpp"

namespace ofxIntersection2D {

class Line2D : public BaseIntersection {
   public:
    Line2D(){};
    ~Line2D(){};

    //--------------------------------------------------------------
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectLine> data) {
        vector<ofVec2f> position;

        int total = data.size();
        for (int i = 0; i < total; ++i) {
            for (int j = 0; j < total; ++j) {
                if (i != j) {
                    position.push_back(getLineIntersection(data[i].p1, data[i].p2, data[j].p1, data[j].p2));
                } else if (i == j) {
                    continue;
                }
            }
        }
        return position;
    };

    //--------------------------------------------------------------
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofVec2f> tmpLineBeginPosList, vector<ofVec2f> tmpLineEndPosList) {
        vector<ofVec2f> position;

        int total = tmpLineBeginPosList.size();
        for (int i = 0; i < total; ++i) {
            for (int j = 0; j < total; ++j) {
                if (i != j) {
                    position.push_back(getLineIntersection(tmpLineBeginPosList[i], tmpLineEndPosList[i], tmpLineBeginPosList[j], tmpLineEndPosList[j]));
                } else if (i == j) {
                    continue;
                }
            }
        }
        return position;
    };

    //--------------------------------------------------------------
    inline ofVec2f getLineIntersection(ofVec2f p1_1, ofVec2f p1_2, ofVec2f p2_1, ofVec2f p2_2) {
        ofVec2f pos;

        double dev = (p1_2.y - p1_1.y) * (p2_2.x - p2_1.x) - (p1_2.x - p1_1.x) * (p2_2.y - p2_1.y);

        double d1, d2;
        d1 = (p2_1.y * p2_2.x - p2_1.x * p2_2.y);
        d2 = (p1_1.y * p1_2.x - p1_1.x * p1_2.y);

        pos.x = d1 * (p1_2.x - p1_1.x) - d2 * (p2_2.x - p2_1.x);
        pos.x /= dev;
        pos.y = d1 * (p1_2.y - p1_1.y) - d2 * (p2_2.y - p2_1.y);
        pos.y /= dev;

        return pos;
    };

   public:
    void clear() override;
    void addLine(ofVec2f &beginPosition, ofVec2f &endPosition) override;
    void render(vector<ofVec2f> &lineBeginPosList, vector<ofVec2f> &lineEndPosList) override;
    void render(vector<ofxIntersection2D::ObjectLine> &lineList) override;
    void update() override;
    void updateInThread() override;

   private:
    vector<ofxIntersection2D::ObjectLine> data;

    vector<ofVec2f> lineBeginPosList;
    vector<ofVec2f> lineEndPosList;
};
}
#endif /* ofxIntersection2DCalculateLine_hpp */
