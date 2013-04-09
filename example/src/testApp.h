#pragma once

#include "ofMain.h"
#include "ofxSane.h"
#include <list>

class testApp : public ofBaseApp{
public:
    ~testApp() {
        scanner.stop();
        if(white != NULL)
            delete [] white;
        if(lowPass != NULL)
            delete [] lowPass;
        while(!buffer.empty()) {
            delete [] buffer.front();
            buffer.pop_front();
        }
    }

    void setup();
    void update();
    void draw();

    bool significantMinima(float a, float b, float c, float sig);
    void drawRgbPlot(unsigned char* data, int size, int offset, int width, int height);
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    void lineEvent(lineEventArgs& event);

    ofxSane scanner;
    list<unsigned char*> buffer;
    unsigned bufferDelay;
    float* white;
    float* lowPass;

    unsigned maxBufferSize;
};
