#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //change the file names to match the desired ones
    videoFileName = "videoFileName.mov";
    soundFileName = "soundFileName.mp3";
    //loads the files into the readers
    sound.load(soundFileName);
    myPlayer.load(videoFileName);
    
    
    //sets how fast the cap of the audio levels decay (higher=faster decay, lower=slower decay)
    decay=0.98;
    
   
    fft = new float[128];
    for (int i=0; i < 128; i++){
        fft[i]=0;
    }
    
    //sets the amount of sections of audio are being read and how much the audio is averaged out
    bands = 64;
  

    //sets the sound to not permanently loop
    sound.setLoop(false);
    
 
 
    
    //IMAGE SETUP
    image.allocate(352,262, OF_IMAGE_COLOR);
    
    
    //Sets cam at slightly left of center
  cam.setPosition(176, 131, 300);
  
   
    
    
    //if true, displayed as a wireframe mesh, if false it is a 3D wall
   wires=true;
    
    
//Grid SETUP
    for(int i=1; i<nGrids; i++){
             grid[i].setup(i);
         }
   
  
    }


//--------------------------------------------------------------


void ofApp::update(){
   
    //if no sound is coming out the video feed will stop
    if(sound.isPlaying()==false){
        myPlayer.stop();
    }
    
    //loads in the next frame of the video to the player
    myPlayer.update();
    //updates the audio bands
    soundSpectrum = ofSoundGetSpectrum(bands);
    
    for(int i= 0; i<bands; i++){
        //causes the specific band of audio to decay and reduce
        fft[i]*=decay;
        //raises the audio band if the band is less than the current sound level for it
        if(fft[i] < soundSpectrum[i]){
            fft[i] = soundSpectrum[i];
        }
    }
 
    for(int i =1; i<(bands-1); i++){
        //calculates the frequency of the band
        freq=fft[i]*100;
    }
    
    //picks out the mid-low notes
    if(freq>0.5){
    truefreq=ofMap(freq, 0.5,3,0,255);
    }
    //picks out the extreme high notes and prevents it from going higher to prevent disruption of the audioreactivity
    if(freq>3){
        freq=3;
    }
    //picks out the high notes
    if(freq >= 1.5){
    freq=ofMap(freq, 1.5, 3, 0, 255);
    }
    //picks out the low notes
    if(freq < 1.5){
       freq=ofMap(freq, 0.0006, 1.5, 0, 255);
    }
   
   
 


    
    
    //changes how much the indices are amplified (up and down)
    amp=addition;
    
    //checks for a new frame in video player
    if(myPlayer.isFrameNew()){
            //creates an image from the video which is passed to the Gridd class update section
               image.setFromPixels(myPlayer.getPixels());
    }
               
   //i controls the y axis
               //image is the video info
               //Amplitude controls the z axis
               //Wires control whether a wireframe is displayed or its a solid mesh
    for(int i=1; i<nGrids; i++){
             grid[i].update(i, image, amp, freq, truefreq);
         }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
  
    
    //Sets up draw function
    ofBackground(0);
//    ofBackground(ofMap(freq, 0, 255, 0, 10), ofMap(freq, 0, 255, 0, 10), ofMap(freq, 0, 255, 0, 44.8));
    ofEnableDepthTest();
    cam.begin();
    

    for(int i=1; i<nGrids; i++){
    grid[i].draw(wires);
    }
    
    //ends draw functions
    cam.end();
   
    cam.draw();

 
 
   
    ofDisableDepthTest();
    
    
}

//--------------------------------------------------------------


void ofApp::keyPressed(int key){
    if (key == 'w'){
        addition+= 0.1;
    }
    if (key == 's'){
        addition-=0.1;
    }
    if (key == 'a'){
        wires=false;
    }
    if (key == 'd'){
           wires=true;
       }
    if (key == 'p'){
          sound.play();
           myPlayer.play();
    }
    }
    




