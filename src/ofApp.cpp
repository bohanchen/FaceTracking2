#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    fftSmooth = new float [8192];
    for (int i = 0; i<8192; ++i) {
        fftSmooth[i] = 0;
    }
    bands = 64;
    music.load("music.mp3");
    
    camWidth=1280;
    camHeight = 960;
    
    mycam.setDeviceID(0);
    mycam.setDesiredFrameRate(30);
    mycam.initGrabber(camWidth, camHeight);
    
    //set up tracker
    ofSetVerticalSync(true);
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    tracker.setup();
    
    //set up random color
    //light red
    colors[0] = {183, 43, 13};
    //lgith yellow
    colors[1] = {247,197,46};
    //light blue
    colors[2] = {8,26,91};
    //light Grey
    colors[3] = {227,255,228};
}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(253, 255, 252);
    float * value = ofSoundGetSpectrum(bands);
    
    for (int i = 0; i<bands; i++) {
        fftSmooth[i] *=0.9f;
        
        if (fftSmooth[i]<value[i]){
            fftSmooth[i] = value[i];
        }
        
    }
    
    //update camera frame
    mycam.update();
    if(mycam.isFrameNew()) {
        tracker.update(toCv(mycam));
        position = tracker.getPosition();
        scale = tracker.getScale();
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    //random color
    int ran = ofRandom(4);
    
    ofPixels & pixels = mycam.getPixels();
    int camWidth = pixels.getWidth();
    int camHeight = pixels.getHeight();
    int nChannels = pixels.getNumChannels();

    ofSetLineWidth(2);
    int Jaw =tracker.getGesture(ofxFaceTracker::JAW_OPENNESS);
    
    //dynamic background
    if (Jaw >22) {
    
        ofSetColor(colors[ran]);
        //mycam.draw(0,0);
        //mycam.draw(0,0);
        for (int i = 4; i < camWidth; i+=8){
            for (int j = 4; j < camHeight; j+=8){
                unsigned char r = pixels[(j * 320 + i)*nChannels];
                float val = 1 - ((float)r / 255.0f);
                    ofDrawRectangle(i,
                                j,
                                ofRandom(20)*val,
                                ofRandom(10)*val);
            }//end of for j
        }//end of for i
    }
    

    /*try to use the eye openness but the accuracy is not good enough
    
    int left_eyeOpen =tracker.getGesture(ofxFaceTracker::LEFT_EYE_OPENNESS);
    int right_eyeOpen =tracker.getGesture(ofxFaceTracker::RIGHT_EYE_OPENNESS);
    
    //Testing for the condition
    cout<<Jaw<<endl;
    cout<<left_eyeOpen<<endl;
    */
    
    //Assign values for eye, nose, mouse, and face
    ofPolyline lefteye = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
    ofPolyline righteye = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE);
    
    ofPolyline left_eyebrow = tracker.getImageFeature(ofxFaceTracker::LEFT_EYEBROW);
    ofPolyline right_eyebrow = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYEBROW);
    
    ofPolyline mouse = tracker.getImageFeature(ofxFaceTracker::INNER_MOUTH);
    ofPolyline face = tracker.getImageFeature(ofxFaceTracker::FACE_OUTLINE);
    ofPolyline nose = tracker.getImageFeature(ofxFaceTracker::NOSE_BASE);
    
    //=====================================
    //static Face
    ofSetColor(247,197,46);//yellow
    ofDrawCircle(lefteye.getCentroid2D(),30);
    ofDrawRectangle(right_eyebrow.getCentroid2D(),40,-10);
    ofDrawRectangle(right_eyebrow.getCentroid2D(),-40,-10);
    
    ofSetColor(183,43,13);//red
    ofDrawRectangle(left_eyebrow.getCentroid2D(),-40,-10);
    ofDrawRectangle(left_eyebrow.getCentroid2D(),40,-10);
    ofDrawCircle(righteye.getCentroid2D(),30);
    
    ofSetColor(8, 26, 91);//blue
    ofDrawRectangle(nose.getCentroid2D(), -15,-10);
    ofDrawRectangle(nose.getCentroid2D(), 15,-10);
    ofDrawCircle(mouse.getCentroid2D(), 15);
    
    ofSetColor(0, 0, 0);
    ofDrawCircle(lefteye.getCentroid2D(),10);
    ofDrawCircle(righteye.getCentroid2D(),10);
    
    ofSetColor(255, 255, 255);
    ofDrawCircle(nose.getCentroid2D(), 5);
    //=====================================
    
    for (int i = 0; i < bands; ++i) {
        //Background
        ofSetColor(colors[0]);//
        
        ofDrawCircle(ofRandom(camWidth/3),
                        ofRandom(camHeight),
                        (fftSmooth[i]*10));
        ofDrawCircle(camWidth/4,
                        ofRandom(camHeight),
                        (fftSmooth[i]*10));
        ofDrawCircle(ofRandom(camWidth/5),
                        ofRandom(camHeight),
                        (fftSmooth[i]*10));
        
        ofSetColor(colors[2]);//
        ofDrawCircle(ofRandom(camWidth/6),
                        ofRandom(camHeight),
                        (fftSmooth[i]*10));
        
        ofDrawCircle(ofRandom(camWidth/2.5),
                        ofRandom(camHeight),
                        (fftSmooth[i]*10));
        ofDrawCircle(ofRandom(camWidth/9),
                        ofRandom(camHeight),
                        (fftSmooth[i]*10));
        
        ofSetColor(colors[1]);//
        ofDrawCircle(ofRandom(camWidth/1.5),
                        ofRandom(camHeight),
                        (fftSmooth[i]*10));
        ofDrawCircle(ofRandom(camWidth/1.2),
                        ofRandom(camHeight),
                        (fftSmooth[i]*10));
        //=====================================
        //Horizontal bar
        ofSetColor(colors[0]);//
        ofDrawCircle(ofRandom(camWidth),
                        ofRandom(camHeight/3),
                        (fftSmooth[i]*10));
        ofDrawCircle(ofRandom(camWidth),
                        ofRandom(camHeight/5),
                        (fftSmooth[i]*10));
        ofSetColor(colors[1]);//
        ofDrawCircle(ofRandom(camWidth),
                        ofRandom(camHeight/6),
                        (fftSmooth[i]*10));
        ofDrawCircle(ofRandom(camWidth),
                        ofRandom(camHeight/1.3),
                        (fftSmooth[i]*10));
        ofDrawCircle(ofRandom(camWidth),
                        ofRandom(camHeight/8),
                        (fftSmooth[i]*10));
        //=====================================
        
        //=====================================
        //Dynamic Face
        ofSetColor(247,197,46);//yellow
        ofDrawCircle(lefteye.getCentroid2D(),-(fftSmooth[i]*30));
        ofDrawRectangle(right_eyebrow.getCentroid2D(),-(fftSmooth[i]*50),-(fftSmooth[i]*20));
        ofDrawRectangle(right_eyebrow.getCentroid2D(),(fftSmooth[i]*50),-(fftSmooth[i]*20));
        
        ofSetColor(183,43,13);//red
        ofDrawCircle(righteye.getCentroid2D(),-(fftSmooth[i]*30));
        ofDrawRectangle(left_eyebrow.getCentroid2D(),-(fftSmooth[i]*50),-(fftSmooth[i]*20));
        ofDrawRectangle(left_eyebrow.getCentroid2D(),(fftSmooth[i]*50),-(fftSmooth[i]*20));
        
        ofSetColor(8,26,91);//blue
        ofDrawRectangle(nose.getCentroid2D(), -(fftSmooth[i]*20),-(fftSmooth[i]*20));
        ofDrawRectangle(nose.getCentroid2D(), (fftSmooth[i]*20),-(fftSmooth[i]*20));
        
        ofDrawCircle(mouse.getCentroid2D(), -(fftSmooth[i]*30));
        
    }
    
    
    ofSetColor(255,255,255);
    if (Jaw<22 ) {
        
        //Play music when mouse is open
        music.play();
    }
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("Open your mouth" ,20,800);
    ofDrawBitmapString("press 'n' for no fill effect" ,20,820);
    ofDrawBitmapString("press 'f' for fill effect " ,20,840);
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r') {
        tracker.reset();
    }
    if (key == 'n'){
        ofNoFill();
    }
    if (key == 'f'){
        ofFill();
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
