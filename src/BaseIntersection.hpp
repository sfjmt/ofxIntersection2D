#ifndef BaseIntersection_hpp
#define BaseIntersection_hpp

#include "ofMain.h"
#include "ofxIntersection2DObjects.hpp"

namespace ofxIntersection2D {
class BaseIntersection {
   public:
    BaseIntersection(){};
    ~BaseIntersection(){};

    inline int getIntersectionTotal() { return intersectionPositionList.size(); };
    inline vector<ofVec2f> getIntersections() { return intersectionPositionList; };

    virtual void clear(){};

    virtual void addCircle(ofVec2f &centralPosition, float &radius){};
    virtual void addLine(ofVec2f &beginPosition, ofVec2f &endPosition){};
    virtual void addPoint(ofVec2f &pt){};

    virtual void setUsingOutsidePoints(bool toggle) { toggleUsingOutsidePoints = toggle; };

    virtual void setup(){};
    virtual void update(){};

   protected:
    //--------------------------------------------------------------
    template <typename T>
    void clearArray(vector<T> &arr) {
        arr.clear();
    };

    //--------------------------------------------------------------
    inline bool isInWindow(ofVec2f v) {
        if ((v.x >= 0) && (v.x <= ofGetWindowWidth()) && (v.y >= 0) && (v.y <= ofGetWindowHeight())) {
            return true;
        } else {
            return false;
        }
    }

    //--------------------------------------------------------------
    inline bool isAlreadyInList(ofVec2f v, vector<ofVec2f> list) {
        int total = list.size();
        for (int i = 0; i < total; ++i) {
            if ((int)v.x == (int)list[i].x && (int)v.y == (int)list[i].y) {
                return true;
            }
        }
        return false;
    }

    vector<ofVec2f> intersectionPositionList;
    bool toggleUsingOutsidePoints = false;

   private:
};
}

#endif