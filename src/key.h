//
//  key.h
//  easyMailKeyboard
//
//  Created by Enrico Becker on 26.04.15.
//
//

#ifndef __easyMailKeyboard__key__
#define __easyMailKeyboard__key__

#include <stdio.h>
#include "ofMain.h"

class key
{
public:
    key();
    ~key();
    void setup(float x, float y, float w, float h,string v,string v2,ofTrueTypeFont *f);
    void draw();

    ofEvent<string> keyRel;
    
    void mouseMoved(ofMouseEventArgs & args){}
    void mouseDragged(ofMouseEventArgs & args){}
    void mousePressed(ofMouseEventArgs & args);
    void mouseReleased(ofMouseEventArgs & args);

    
    //this function checks if the passed arguments are inside the circle.
    bool inside(float _x, float _y );
    
    void enable();
    void disable();
    
    void shiften();
    
private:
    string primValue;
    string secValue;
    ofTrueTypeFont *keyObj;
    ofColor fC;
    bool bRegisteredEvents;
    bool bActive;
    ofVec2f start;
    ofVec2f end;
    ofRectangle kBox;
    ofVec2f kPos;
    ofRectangle area;
    
    bool shift;
};

#endif /* defined(__easyMailKeyboard__key__) */
