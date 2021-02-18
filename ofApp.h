#pragma once

#include "ofMain.h"
#include "Grid.hpp"
#include "ofxVideoRecorder.h"
#define nGrids 63

class ofApp : public ofBaseApp{
    
    //The concept is to convey video through a wire mesh and have the colors react to the height of the indice and the audio

    //Elements yet to be added: GUI control for the amplification of the z axis, GUI control to change the color of the tallest Vertexes
    
    public:
        void setup();
        void update();
        void draw();
    void keyPressed(int key);
    

 
    Gridclass grid[63];
    //camera
    ofCamera cam;
    //The video player and the image made by it
    ofxVideoRecorder vidRecorder;
    ofImage image, img;
    //determines if the video is displayed as a wireframe or a 3d wall
    bool wires;
    //controls the amplification of the height of the indices
    //freq and truefreq are frequencies chosen to control the colors
    float amp, addition, freq, decay, truefreq;
    
    //video player
    ofVideoPlayer myPlayer;
    
    //audio player
    ofSoundPlayer sound;
    
    //these are all used to assess different audio bands and later to find their frequencies
    float *fft;
    float *soundSpectrum;
    int bands;
    
    //file names
    string videoFileName, soundFileName;
  
    

 
        
};
