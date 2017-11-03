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
    
    ofSetVerticalSync(true);
    ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
    tracker.setup();
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
    //Background
    ofSetColor(0, 0, 0);
    //Vertical bar
    
    //Horizontal bar
    

    //mycam.draw(0,0);
    //tracker.draw();
    ofSetLineWidth(2);
    int Jaw =tracker.getGesture(ofxFaceTracker::JAW_OPENNESS);
    
    
    //try to use the eye openness but the accuracy is not good enough
    int left_eyeOpen =tracker.getGesture(ofxFaceTracker::LEFT_EYE_OPENNESS);
    int right_eyeOpen =tracker.getGesture(ofxFaceTracker::RIGHT_EYE_OPENNESS);
    
    //cout<<Jaw<<endl;
    cout<<left_eyeOpen<<endl;
    
    //Assign values for eye, nose, mouse, and face
    ofPolyline lefteye = tracker.getImageFeature(ofxFaceTracker::LEFT_EYE);
    ofPolyline righteye = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYE);
    
    ofPolyline left_eyebrow = tracker.getImageFeature(ofxFaceTracker::LEFT_EYEBROW);
    ofPolyline right_eyebrow = tracker.getImageFeature(ofxFaceTracker::RIGHT_EYEBROW);
    
    ofPolyline mouse = tracker.getImageFeature(ofxFaceTracker::INNER_MOUTH);
    ofPolyline face = tracker.getImageFeature(ofxFaceTracker::FACE_OUTLINE);
    ofPolyline nose = tracker.getImageFeature(ofxFaceTracker::NOSE_BASE);

    
    
    
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
    
    
    for (int i = 0; i < bands; ++i) {
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
        
        
        ofSetColor(217, 220, 214);
        ofDrawRectangle(ofGetWindowWidth()/3,
                        ofGetWindowHeight(),
                        (fftSmooth[i]*10),
                        -ofGetWindowHeight());
        ofDrawRectangle(ofGetWindowWidth()/4,
                        ofGetWindowHeight(),
                        (fftSmooth[i]*10),
                        -ofGetWindowHeight());
        ofDrawRectangle(ofGetWindowWidth()/5,
                        ofGetWindowHeight(),
                        (fftSmooth[i]*10),
                        -ofGetWindowHeight());
        ofDrawRectangle(ofGetWindowWidth()/6,
                        ofGetWindowHeight(),
                        (fftSmooth[i]*10),
                        -ofGetWindowHeight());
        ofDrawRectangle(ofGetWindowWidth()/2.5,
                        ofGetWindowHeight(),
                        (fftSmooth[i]*10),
                        -ofGetWindowHeight());
        ofDrawRectangle(ofGetWindowWidth()/9,
                        ofGetWindowHeight(),
                        (fftSmooth[i]*10),
                        -ofGetWindowHeight());
        ofDrawRectangle(ofGetWindowWidth()/1.5,
                        ofGetWindowHeight(),
                        (fftSmooth[i]*10),
                        -ofGetWindowHeight());
        ofDrawRectangle(ofGetWindowWidth()/1.2,
                        ofGetWindowHeight(),
                        (fftSmooth[i]*10),
                        -ofGetWindowHeight());
        
        //Horizontal bar
        ofDrawRectangle(ofGetWindowWidth(),
                        ofGetWindowHeight()/3,
                        -ofGetWindowWidth(),
                        (fftSmooth[i]*10));
        ofDrawRectangle(ofGetWindowWidth(),
                        ofGetWindowHeight()/5,
                        -ofGetWindowWidth(),
                        (fftSmooth[i]*10));
        ofDrawRectangle(ofGetWindowWidth(),
                        ofGetWindowHeight()/6,
                        -ofGetWindowWidth(),
                        (fftSmooth[i]*10));
        ofDrawRectangle(ofGetWindowWidth(),
                        ofGetWindowHeight()/1.3,
                        -ofGetWindowWidth(),
                        (fftSmooth[i]*10));
        ofDrawRectangle(ofGetWindowWidth(),
                        ofGetWindowHeight()/8,
                        -ofGetWindowWidth(),
                        (fftSmooth[i]*10));
    }
    
    ofSetColor(255,255,255);
    if (Jaw<22 ) {
        //Play music when mouse is open
        music.play();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'r') {
        tracker.reset();
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
