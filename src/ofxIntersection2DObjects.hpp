#ifndef ofxIntersection2DObjects_hpp
#define ofxIntersection2DObjects_hpp

#include "ofMain.h"

namespace ofxIntersection2D {
//==============================================================
//
// ofxIntersection2D::ofxIntersection2DObjects::ObjectCircle
//
//==============================================================
class ObjectCircle {
   public:
    ObjectCircle(){};
    ~ObjectCircle(){};

    void set(ofVec2f central, double radius) {
        this->central = central;
        this->radius = radius;
    };

    ofVec2f central;
    double radius;

   private:
};

//==============================================================
//
// ofxIntersection2D::ofxIntersection2DObjects::ObjectLine
//
//==============================================================
class ObjectLine {
   public:
    ObjectLine(){};
    ~ObjectLine(){};

    void set(ofVec2f p1, ofVec2f p2) {
        this->p1 = p1;
        this->p2 = p2;
    };

    ofVec2f p1;
    ofVec2f p2;

   private:
};
}

#endif /* ofxIntersection2DObjects_hpp */
