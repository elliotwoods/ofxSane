#include "testApp.h"

void testApp::setup(){
    ofSetFrameRate(60);
    scanner.setup();
    ofAddListener(scanner.lineEvent, this, &testApp::lineEvent);
    ofBackground(0, 0, 0);
    maxBufferSize = 32;
    white = NULL;
    lowPass = NULL;
}

void testApp::update(){
}

bool testApp::significantMinima(float a, float b, float c, float sig) {
    return (b + sig < a) && (b + sig < c);
}

void testApp::drawRgbPlot(unsigned char* data, int size, int offset, int width, int height) {
    glBegin(GL_LINE_STRIP);
    for(float x = 0; x < width; x++) {
        int i = (int) ofMap(x, 0, width, 0, size / 3);
        i = (i * 3) + offset;
        float y = ofMap(data[i], 0, 255, height, 0);
        glVertex2f(x, y);
    }
    glEnd();
}

void testApp::draw(){
ofSetColor(255, 255, 255);

    while(buffer.size() > maxBufferSize) {
        delete [] buffer.front();
        buffer.pop_front();
    }

    if(!buffer.empty()) {
        unsigned char* cur = buffer.front();
        int size = scanner.getBufferSize();
        float width = ofGetWidth();
        float height = ofGetHeight();

        // draw color components
        ofSetColor(255, 0, 0);
        drawRgbPlot(cur, size, 0, width, height);
        ofSetColor(0, 255, 0);
        drawRgbPlot(cur, size, 1, width, height);
        ofSetColor(0, 0, 255);
        drawRgbPlot(cur, size, 2, width, height);

        // draw buffer size
        ofSetColor(255, 255, 255);
        //ofLine(0, height / 2, ofMap(buffer.size(), 0, minBufferSize * 4, 0, width), height / 2);

        // average + normalize all channels
        if(lowPass == NULL) {
            white = new float[size / 3];
            lowPass = new float[size / 3];
        }
        for(int i = 0; i < size / 3; i++) {
            white[i] = cur[i * 3] + cur[i * 3 + 1] + cur[i * 3 + 2];
            white[i] /= 3. * 255.;
        }

        // low pass from left
        int lowPassSize = size / 3;
        float lowPassAmount = .005;
        float average;
        average = 1;
        for(int i = 0; i < lowPassSize; i++) {
            average = ofLerp(average, white[i], lowPassAmount);
            lowPass[i] = average;
        }
        // low pass from right
        average = 1;
        for(int i = lowPassSize - 1; i >= 0; i--) {
            average = ofLerp(average, white[i], lowPassAmount);
            lowPass[i] = (lowPass[i] + average) / 2;
        }

        // draw low passed data
        glBegin(GL_LINE_STRIP);
        for(int i = 0; i < lowPassSize; i++) {
            float x = ofMap(i, 0, lowPassSize, 0, width);
            float y = ofMap(lowPass[i], 0, 1, height, 0);
            glVertex2f(x, y);
        }
        glEnd();

        // draw local minima
        int dist = 128;
        for(int i = dist; i < lowPassSize - dist; i++) {
            if(significantMinima(lowPass[i - dist], lowPass[i], lowPass[i + dist], .001)) {
                float x = ofMap(i, 0, lowPassSize, 0, width);
                float y = ofMap(lowPass[i], 0, 1, height, 0);
                ofLine(x, y, x, height);
            }
        }

        delete [] buffer.front();
        buffer.pop_front();
    }

    if(ofGetFrameNum() % 60 == 0 && ofGetFrameRate() < 60)
        cout << "slow: " << ofGetFrameRate() << "fps" << endl;
}

void testApp::mousePressed(int x, int y, int button){
    scanner.scan();
}

void testApp::keyPressed(int key) {
    if(key == ' ')
        scanner.stop();
}

void testApp::lineEvent(lineEventArgs& event) {
    unsigned char* cur = new unsigned char[event.size];
    memcpy(cur, event.line, event.size);
    buffer.push_back(cur);
}
