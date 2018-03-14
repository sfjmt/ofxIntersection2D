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

    virtual void add(ofVec2f &centralPosition, double &radius){};  // for circle object
    virtual void add(ofVec2f &p1, ofVec2f &p2){};                  // for line object

    virtual void render(vector<ofVec2f> &centralPositionList, vector<double> &radiusList){};  // for circle object
    virtual void render(vector<ofVec2f> &list1, vector<ofVec2f> &list2){};                    // for line object

    virtual void start() { startThread(); };
    virtual void stop() { stopThread(); };

    virtual void setup(){};
    virtual void update(){};
    virtual void updateInThread(){};

   protected:
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