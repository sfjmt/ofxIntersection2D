#ifndef BaseIntersection_hpp
#define BaseIntersection_hpp

#include "ofMain.h"
#include "ofxIntersection2DObjects.hpp"

namespace ofxIntersection2D {
class BaseIntersection : public ofThread {
   public:
    BaseIntersection(){};
    ~BaseIntersection() {
        // Stop thread
        stop();
        waitForThread(true);
    };

    inline int getIntersectionTotal() { return intersectionPositionList.size(); };
    inline vector<ofVec2f> getIntersections() { return intersectionPositionList; };

    virtual void clear(){};

    virtual void addCircle(ofVec2f &centralPosition, double &radius){};
    virtual void addLine(ofVec2f &beginPosition, ofVec2f &endPosition){};
    virtual void addPoint(ofVec2f &pt){};

    virtual void render(vector<ofVec2f> &centralPositionList, vector<double> &radiusList){};
    virtual void render(vector<ofxIntersection2D::ObjectCircle> &circleList){};

    virtual void render(vector<ofVec2f> &lineBeginPosList, vector<ofVec2f> &lineEndPosList){};
    virtual void render(vector<ofxIntersection2D::ObjectLine> &lineList){};

    virtual void render(vector<ofVec2f> &lineBeginPosList, vector<ofVec2f> &lineEndPosList, vector<ofVec2f> &centralPositionList, vector<double> &radiusList){};
    virtual void render(vector<ofxIntersection2D::ObjectLine> &lineList, vector<ofxIntersection2D::ObjectCircle> &circleList){};

    virtual void start() { startThread(); };
    virtual void stop() { stopThread(); };

    virtual void setup(){};
    virtual void update(){};
    virtual void updateInThread(){};

   protected:
    template <typename T>
    void clearArray(vector<T> &arr) {
        arr.clear();
    };

    vector<ofVec2f> intersectionPositionList;

   private:
    void threadedFunction() {
        while (isThreadRunning()) {
            //--------------------------------------------------------------
            // 1. lock
            //--------------------------------------------------------------
            if (lock()) {
                //--------------------------------------------------------------
                // 2. update
                //--------------------------------------------------------------
                updateInThread();

                //--------------------------------------------------------------
                // 3. unlock
                //--------------------------------------------------------------
                unlock();

                //--------------------------------------------------------------
                // 4. sleep
                //--------------------------------------------------------------
                sleep(0);
            }
        }
    };
};
}

#endif