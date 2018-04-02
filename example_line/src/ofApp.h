#pragma once

#include "ofMain.h"
#include "ofxIntersection2D.hpp"

class ofApp : public ofBaseApp {
   public:
    void setup();
    void update();
    void draw();

   private:
    string caption();

    ofxIntersection2D::BaseIntersection *intersection;

    int total;
    vector<ofVec2f> baseLineBeginPosList;
    vector<ofVec2f> baseLineEndPosList;
    vector<ofVec2f> lineBeginPosList;
    vector<ofVec2f> lineEndPosList;
};
