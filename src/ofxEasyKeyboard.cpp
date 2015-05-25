//
//  keyboard.cpp
//  easyMailKeyboard
//
//  Created by Enrico Becker on 26.04.15.
//
//

#include "keyboard.h"

keyboard::keyboard()
{
}

keyboard::~keyboard()
{
}



void keyboard::init(float px,float py,float wx, float wy,float spacerX, float spacerY)
{
    createFbos(wx, wy);
    defaultValue = "enter your email adress";
    ausF.loadFont("verdana.ttf", 18);
    keyF.loadFont("verdana.ttf", 14);
    position = ofVec2f(px,py);
    size = ofVec2f(wx,wy);
    ///konst
    primValues.clear();
    primValues.push_back("1234567890");
    primValues.push_back("QWERTYUIOP");
    primValues.push_back("ASDFGHJKL@");
    primValues.push_back("ZXCVBNM._-");
    secValues.clear();
    secValues.push_back("1234567890");
    secValues.push_back("qwertyuiop");
    secValues.push_back("asdfghjkl@");
    secValues.push_back("zxcvbnm._-");
    float xSpace = spacerX;
    float ySpace = spacerY;
    
    int yCount = primValues.size();
    k.clear();
    //eof konst
    for(int i = 0;i < yCount;i++)
    {
        int xCount = primValues[i].size();
        for (int j = 0; j < xCount; j++)
        {
            key *sK = new key();
            float x = px + ((wx + xSpace) * j);
            float y = py + ((wy + ySpace) * i);
            string v = ofToString(primValues[i][j]);
            string v2 = ofToString(secValues[i][j]);
            sK->setup(x,y,wx,wy,v,v2,&keyF,&selectButton,&deselectButton);
            //string s,ofRectangle a, ofTrueTypeFont *f,ofColor c
            ofAddListener(sK->keyRel, this, &keyboard::getKey);
            k.push_back(sK);
        }
    }
    //special key
    key *sK = new key();
    float x = px + ((wx + xSpace) * primValues[0].size());
    float y = py + ((wy + ySpace) * 0 * 1.08);
    float w = wx;
    float h = wy;
    string v = "DEL";
    string v2 = "DEL";
    sK->setup(x,y,w,h,v,v2,&keyF,&selectButton,&deselectButton);
    ofAddListener(sK->keyRel, this, &keyboard::getKey);
    k.push_back(sK);

    ausgabe = "";
    //noch die special keys
    //del
    cursor = false;
    counter = 0;
    maxCount = 120;
}

void keyboard::draw()
{
    counter++;
    float alpha = counter / float(maxCount);
    alpha = (sin(ofDegToRad(alpha * 360)) + 1) / 2;
    int off = 5;
    for (int i = 0; i < k.size(); i++)
    {
        k[i]->draw();
    }
    ofPushMatrix();
    if (ausgabe.size() == 0)
    {
        ofSetColor(150, 150, 150,255 * alpha);
        ausF.drawString(defaultValue, position.x, position.y - 50);
/*        if(cursor)
        {
            ofSetColor(150, 150, 150,255 * alpha);
            ofLine(position.x - off, position.y -45,position.x - off, position.y -72);
        }*/
    }
    else
    {
        ofSetColor(0, 0, 0);
        ausF.drawString(ausgabe, position.x, position.y - 50);
        ofRectangle r = ausF.getStringBoundingBox(ausgabe, position.x + off, position.y);
        if (cursor)
        {
            ofSetColor(0, 0, 0,255 * alpha);
            ofLine(r.getRight(), position.y -45,r.getRight(), position.y -72);
        }
    }
    ofPopMatrix();
    if (counter > maxCount) counter = 0;
}

void keyboard::activate()
{
    for (int i = 0; i < k.size(); i++)
    {
        k[i]->enable();
    }
}
void keyboard::deactivate()
{
    for (int i = 0; i < k.size(); i++)
    {
        k[i]->disable();
    }
}

void keyboard::createFbos(float w,float h)
{
    //active
    selectButton.allocate(w, h,GL_RGBA);
    selectButton.begin();
    ofClear(0, 0, 0);
    ofSetColor(200, 200, 200);
    ofFill();
    ofRectRounded(0,0,w,h, 5);
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofSetLineWidth(2);
    ofRectRounded(0,0,w,h, 5);
    ofSetLineWidth(1);
    selectButton.end();
    //inactive
    deselectButton.allocate(w, h,GL_RGBA);
    deselectButton.begin();
    ofClear(0, 0, 0);
    ofSetColor(255, 255, 255);
    ofFill();
    ofRectRounded(0,0,w,h, 5);
    ofSetColor(0, 0, 0);
    ofNoFill();
    ofSetLineWidth(2);
    ofRectRounded(0,0,w,h, 5);
    ofSetLineWidth(1);
    deselectButton.end();

}


string keyboard::getOutput()
{
    //eventuell noch ein validitätscheck
    if (verifyString(ausgabe)) return ausgabe;
    return "-1";
}

bool keyboard::verifyString(string & s)
{
    if (s.size() > 4)//mind 4 zeichen
    {
        bool hasAt = false;
        bool hasPoint = false;
        int endCounter = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[0] == '.') return false;  //no point in begin
            if (s[i] == '@') hasAt = true;
            if (s[i] == '.' && hasAt == true) hasPoint = true; endCounter = i;
        }
        if (!hasAt) return false;   //no at sign
        if (!hasPoint) return false;    //no point after at
        if ((s.size() - endCounter) < 1) return false;  //to short ending
        
        return true;
    }
}


void keyboard::getKey(string &e)
{
    cout << "key " << e << endl;
    if (e == "DEL")
    {
        if (ausgabe.size() > 0)
        {
            ausgabe.erase(ausgabe.size() - 1);
        }
    }
    else ausgabe.append(e);
}

void keyboard::enableCursor()
{
    cursor = true;
}

void keyboard::disableCursor()
{
    cursor = false;
}
