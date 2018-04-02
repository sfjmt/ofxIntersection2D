#ifndef ofxIntersection2DCalculateLine_hpp
#define ofxIntersection2DCalculateLine_hpp

#include "ofMain.h"
#include "BaseIntersection.hpp"

namespace ofxIntersection2D {

class Line2D : public BaseIntersection {
   public:
    Line2D() { toggleUsingOutsidePoints = false; };
    ~Line2D(){};

    //--------------------------------------------------------------
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofxIntersection2D::ObjectLine> data) {
        vector<ofVec2f> tmpPositions;
        vector<ofVec2f> tmpAllPositions;
        ofVec2f v;

        int total = data.size();
        for (int i = 0; i < total; ++i) {
            for (int j = 0; j < total; ++j) {
                if (j != i) {
                    // get intersection
                    v = getLineIntersection(data[i].p1, data[i].p2, data[j].p1, data[j].p2);

                    // compere
                    if (!std::isnan(v.x) && !std::isnan(v.y)) {
                        // Don't push same pos
                        if (!isAlreadyInList(v, tmpAllPositions)) {
                            if (toggleUsingOutsidePoints) {  // using outside points
                                tmpAllPositions.push_back(v);
                                tmpPositions.push_back(v);
                            } else {  // Don't using outside points
                                if (isInWindow(v)) {
                                    tmpAllPositions.push_back(v);
                                    tmpPositions.push_back(v);
                                } else {
                                    // ignore
                                    continue;
                                }
                            }
                        } else {
                            // ignore
                            continue;
                        }
                    } else {
                        // ignore
                        continue;
                    }
                } else if (j == i) {
                    // ignore
                    continue;
                } else {
                    // ignore
                    continue;
                }
            }
        }
        return tmpPositions;
    };

    //--------------------------------------------------------------
    inline vector<ofVec2f> getMultipleIntersectionsManagement(vector<ofVec2f> tmpLineBeginPosList, vector<ofVec2f> tmpLineEndPosList) {
        vector<ofxIntersection2D::ObjectLine> data;

        int total = tmpLineBeginPosList.size();
        for (int i = 0; i < total; ++i) {
            data.push_back(ofxIntersection2D::ObjectLine());
            data[i].set(tmpLineBeginPosList[i], tmpLineEndPosList[i]);
        }

        vector<ofVec2f> tmpPositions = getMultipleIntersectionsManagement(data);
        return tmpPositions;
    };

    //--------------------------------------------------------------
    inline ofVec2f getLineIntersection(ofVec2f p1_1, ofVec2f p1_2, ofVec2f p2_1, ofVec2f p2_2) {
        float dev = (p1_2.y - p1_1.y) * (p2_2.x - p2_1.x) - (p1_2.x - p1_1.x) * (p2_2.y - p2_1.y);

        float d1, d2;
        d1 = (p2_1.y * p2_2.x - p2_1.x * p2_2.y);
        d2 = (p1_1.y * p1_2.x - p1_1.x * p1_2.y);

        ofVec2f pos;
        pos.x = d1 * (p1_2.x - p1_1.x) - d2 * (p2_2.x - p2_1.x);
        pos.x /= dev;
        pos.y = d1 * (p1_2.y - p1_1.y) - d2 * (p2_2.y - p2_1.y);
        pos.y /= dev;

        return pos;
    };

   public:
    void clear() override;
    void addLine(ofVec2f &beginPosition, ofVec2f &endPosition) override;
    void update() override;

   private:
    vector<ofxIntersection2D::ObjectLine> dataLineList;

    vector<ofVec2f> lineBeginPosList;
    vector<ofVec2f> lineEndPosList;
};
}
#endif /* ofxIntersection2DCalculateLine_hpp */
