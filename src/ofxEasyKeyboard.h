//
//  keyboard.h
//  easyMailKeyboard
//
//  Created by Enrico Becker on 26.04.15.
//
//

#ifndef __easyMailKeyboard__keyboard__
#define __easyMailKeyboard__keyboard__

#include <stdio.h>
#include "ofMain.h"
#include "key.h"


class keyboard
{
public:
    keyboard();
    ~keyboard();
    
    void init(float px,float py,float width, float height, float spaceX, float spaceY);
    void draw();
    void getKey(string &e);
    
    void activate();
    void deactivate();
    
    void enableCursor();
    void disableCursor();
    
    string getOutput();
    bool verifyString(string &s);
    
    void createFbos(float width,float height);

private:
    ofVec2f position;
    ofVec2f size;
    vector<string> primValues;
    vector<string> secValues;
    vector<key*> k;
    string ausgabe;
    ofTrueTypeFont ausF;
    ofTrueTypeFont keyF;
    string defaultValue;
    unsigned int counter;
    unsigned int maxCount;
    bool cursor;
    ofFbo selectButton;
    ofFbo deselectButton;
};

#endif /* defined(__easyMailKeyboard__keyboard__) */
