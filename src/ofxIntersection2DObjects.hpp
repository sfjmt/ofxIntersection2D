#ifndef ofxIntersection2DObjects_hpp
#define ofxIntersection2DObjects_hpp

#include "ofMain.h"

namespace ofxIntersection2D {
//==============================================================
//
// ofxIntersection2DObjects::IntersectionSimplyCircle
//
//==============================================================
class ObjectCircle {
   public:
    ObjectCircle(){};
    ~ObjectCircle(){};

    void set(ofVec2f position, double radius) {
        this->position = position;
        this->radius = radius;
    };

    ofVec2f position;
    double radius;

   private:
};

//==============================================================
//
// ofxIntersection2DObjects::IntersectionSimplyCircle
//
//==============================================================
class ObjectLine {
   public:
    ObjectLine(){};
    ~ObjectLine(){};

    void set(ofVec2f p1, ofVec2f p2) {
        this->position1 = p1;
        this->position2 = p2;
    };

    ofVec2f position1;
    ofVec2f position2;

   private:
};
}

#endif /* ofxIntersection2DObjects_hpp */
