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

    int totalCircle;
    int totalLine;

    vector<ofxIntersection2D::ObjectCircle> circleList;
    vector<ofxIntersection2D::ObjectLine> lineList;
    vector<ofVec2f> intersectionList;

    string caption();
};
