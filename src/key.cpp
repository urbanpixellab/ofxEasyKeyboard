//
//  key.cpp
//  easyMailKeyboard
//
//  Created by Enrico Becker on 26.04.15.
//
//

#include "key.h"

key::key()
{
    start = ofVec2f(0,0);
    end = ofVec2f(10,10);
    shift = false;
}

key::~key()
{
    if(bRegisteredEvents) {
        ofUnregisterMouseEvents(this); // disable litening to mous events.
        bRegisteredEvents = false;
    }
    delete selectFbo;
    delete deselectFbo;
}

void key::setup(float x, float y, float w, float h,string v,string v2,ofTrueTypeFont *f,ofFbo * select, ofFbo * deselect)
{
    start = ofVec2f(x,y);
    end = ofVec2f(w,h);
    primValue = ofToString(v);
    secValue = ofToString(v2);
    keyObj = f;
    kBox = keyObj->getStringBoundingBox(primValue, 0, 0);
    area = ofRectangle(x,y,w,h);
    kPos = ofVec2f((w - kBox.getWidth()) / 2,(h - kBox.getHeight()) / 2 + kBox.getHeight());
    bActive = false;
    fC = ofColor(255,255,255);
    bRegisteredEvents = false;
    if(!bRegisteredEvents) {
        ofRegisterMouseEvents(this); // this will enable our circle class to listen to the mouse events.
        bRegisteredEvents = true;
    }
    selectFbo = new ofFbo();
    selectFbo = select;
    deselectFbo = new ofFbo();
    deselectFbo = deselect;
}

void key::draw()
{
    ofSetColor(255, 255, 255);
    ofPushMatrix();
    ofTranslate(start.x,start.y);
    if (bActive) selectFbo->draw(0,0);
    else deselectFbo->draw(0,0);
/*    if (bActive) ofSetColor(255, 0, 0);
    else ofSetColor(255,255,255);
    //ofRect(0,0,end.x,end.y);
    ofNoFill();
    ofSetLineWidth(2);
    ofRectRounded(0,0,end.x,end.y, 5);*/
    ofSetColor(0,0,0);
    if (shift) keyObj->drawString(primValue,kPos.x,kPos.y);
    else keyObj->drawString(secValue,kPos.x,kPos.y);
    ofPopMatrix();
}


void key::mousePressed(ofMouseEventArgs & args)
{
    if (inside(args.x, args.y)) {
        string kV = "";
        if(shift) kV = primValue;
        else kV = secValue;
        ofNotifyEvent(keyRel,kV,this);
        bActive = true;
    }
}

void key::mouseReleased(ofMouseEventArgs & args)
{
    if (inside(args.x, args.y))
    {
        bActive = false;
    }
}

bool key::inside(float x, float y)
{
    return area.inside(x, y);
}

void key::shiften()
{
    shift = !shift;
}

void key::enable()
{
    ofRegisterMouseEvents(this); // this will enable our circle class to listen to the mouse events.
    bRegisteredEvents = true;
}

void key::disable()
{
    ofUnregisterMouseEvents(this); // disable litening to mous events.
    bRegisteredEvents = false;
}