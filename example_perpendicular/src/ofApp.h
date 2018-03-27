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

    int totalPoint;
    int totalIntersection;

    ofxIntersection2D::ObjectLine line;
    vector<ofVec2f> pointList;
    vector<ofVec2f> intersectionList;

    string caption();
};
