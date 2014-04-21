#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "particle.h"
#include "noiseField.h"
class testApp : public ofBaseApp{

public:
    
	void setup();
	void update();
	void draw();
    void exit();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
    

    
    void userEvent(ofxOpenNIUserEvent & event);

    const ofColor c = ofColor::yellow;
    
	ofxOpenNI openNIDevice;
    
    ofTrueTypeFont verdana;
    ofTrueTypeFont  font;
    

    ofVec3f left_hand, prev_left_hand;
    ofVec3f left_foot, prev_left_foot;
    ofVec3f right_foot, prev_right_foot;
    ofVec3f left_knee, prev_left_knee;
    ofVec3f right_knee, prev_right_knee;
    ofVec3f right_hand, prev_right_hand;
    ofVec3f left_elbow, prev_left_elbow;
    ofVec3f right_elbow, prev_right_elbow;
    ofVec3f right_shoulder, prev_right_shoulder;
    ofVec3f left_shoulder, prev_left_shoulder;

    ofVec3f head,prev_head;

    
    
    ofVec3f p2_left_hand, p2_prev_left_hand;
    ofVec3f p2_left_foot, p2_prev_left_foot;
    ofVec3f p2_right_foot, p2_prev_right_foot;
    ofVec3f p2_left_knee, p2_prev_left_knee;
    ofVec3f p2_right_knee, p2_prev_right_knee;
    ofVec3f p2_right_hand, p2_prev_right_hand;
    ofVec3f p2_left_elbow, p2_prev_left_elbow;
    ofVec3f p2_right_elbow, p2_prev_right_elbow;
    ofVec3f p2_right_shoulder, p2_prev_right_shoulder;
    ofVec3f p2_left_shoulder, p2_prev_left_shoulder;
    ofVec3f p2_head,p2_prev_head;
    
    

    int time=0;
    int time2=0;
    int count1_1=0;
    int count1_2=0;
    int count2_2=0;
    int count2_1=0;
    
    bool p1_win=false;
    bool p2_win=false;
    
    int p1_health;
    int p2_health;
    bool p1_is_hit;
    bool p2_is_hit;
    int p1_1_speed;
    bool p1_1_isthrow;
    bool p1_1_issaving;
    float p1_1_ballposx;
    float p1_1_ballposy;
    float p1_1_ballrad;
    
    bool p1_block;
    
    int p1_2_speed;
    bool p1_2_isthrow;
    float p1_2_ballposx;
    float p1_2_ballposy;
    float p1_2_ballrad;
    
    
    int p2_1_speed;
    bool p2_1_isthrow;
    bool p2_1_issaving;
    float p2_1_ballposx;
    float p2_1_ballposy;
    float p2_1_ballrad;
    
    bool p2_block;
    
    int p2_2_speed;
    bool p2_2_isthrow;
    float p2_2_ballposx;
    float p2_2_ballposy;
    float p2_2_ballrad;
    // let's make a vector of them
    vector <particle> particles;
	
    noiseField NF;
	
    bool bPressed;
	
    

    
    
    
    int numUsers;
    
        ofSoundPlayer  beats;
    

};

#endif
