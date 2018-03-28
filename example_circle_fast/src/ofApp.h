#pragma once

#include "ofMain.h"
#include "ofxIntersection2D.hpp"

class ofApp : public ofBaseApp {
   public:
    void setup();
    void update();
    void draw();

   private:
    ofxIntersection2D::BaseIntersection *intersection;

    int total;
    vector<ofVec2f> baseCircleCentralPosList;
    vector<ofxIntersection2D::ObjectCircle> circleList;
};
