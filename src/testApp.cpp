#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    
    ofSetLogLevel(OF_LOG_VERBOSE);

    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    openNIDevice.addUserGenerator();
    openNIDevice.setMaxNumUsers(2);
    openNIDevice.start();

    openNIDevice.setUseMaskTextureAllUsers(true);
    openNIDevice.setUsePointCloudsAllUsers(true);
    openNIDevice.setPointCloudDrawSizeAllUsers(1); // size of each 'point' in the point cloud
    openNIDevice.setPointCloudResolutionAllUsers(1); // resolution of the mesh created for the point cloud eg., this will
      
//    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
//    font.loadFont("verdana.ttf", 60);
//    
//    beats.loadSound("sounds/synth.wav");
    
    ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	
	for (int i = 0; i < 200; i++){
		particle myParticle;
		myParticle.setInitialCondition(ofRandom(0,ofGetWidth()),ofRandom(0,ofGetHeight()),0,0);
		particles.push_back(myParticle);
	}
	
	bPressed = false;
	
	NF.setup();
	NF.scaleOfField = 0.01;
    time=0;
    p1_1_speed=0;
    p1_1_ballrad=0;
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
//    ofSoundUpdate();
    
    
	
	NF.setTime(ofGetElapsedTimef()*0.1);
	//NF.scaleOfField = ofMap(mouseX, 0,ofGetWidth(),0,0.01);
	
	// on every frame
	// we reset the forces
	// add in any forces on the particle
	// perfom damping and
	// then update
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].resetForce();
	}
	
	
	for (int i = 0; i < particles.size(); i++){
		for (int j = 0; j < i; j++){
			if (!bPressed){
				particles[i].addRepulsionForce(particles[j], 30,1.5);
			} else {
				particles[i].addRepulsionForce(particles[j], 30,0.3);
			}
		}
		
		if (bPressed){
			//particles[i].addAttractionForce(mouseX, mouseY, 2000,0.1);
			ofVec2f frcFromNoise = NF.getNoiseForPosition(particles[i].pos.x, particles[i].pos.y,0.32);
			particles[i].addForce(frcFromNoise.x, frcFromNoise.y);
		} else {
			particles[i].addAttractionForce(p2_left_hand.x, p2_left_hand.y, 1000,0.5);
            
		}
	}
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].addDampingForce();
		particles[i].update();
	}
    


}

//--------------------------------------------------------------
void testApp::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    
	ofSetColor(255, 255, 255);
    
    ofPushMatrix();
   // ofTranslate(-640,0, 0);
    openNIDevice.drawDebug();
    ofPopMatrix();
    
    
    
    
    
    ofPushMatrix();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    numUsers = openNIDevice.getNumTrackedUsers();
    
    
    
    
    
    
    
    
    
    //if one player
    if(numUsers==1){
        
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(0);
        
     //  ofxOpenNIUser & user2 = openNIDevice.getTrackedUser(1);
        

//        ofSetColor(255, 255, 255);
//        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        
        
       // user.setUseMaskTexture(true);
        //bg.draw(-200, 0);
        
        //ofPixels & pix= user.getMaskPixels();
       // ofPixels & pix = user.getMaskPixels();
        //ofTexture & tex = user.getMaskTextureReference();
        //ofLog(tex);
        //ofLog(pix);
        //user.drawMask();
        //pix.mirror(true, true);
      // for(int x = 0; x < pix.get; x++){
        //    for(int y = 0; y < pix.getWidth(); y++){
        //pix.setChannel(1, c);
       // ofGLRenderer();
       // pix.setImageType(OF_IMAGE_COLOR);
        //user.drawMask();
       // pix.setColor(<#int index#>, <#const ofColor_<unsigned char> &color#>)
          //  }
       // }
    
        //pix.set(OF_PIXELS_BGRA);
        //pix.setColor(OF_PIXELS_BGRA&(255,0,0,1));
        //tex.draw(20, 30,800,600);
        
        //ofSetColor(0, 255, 0);
        //user.drawPointCloud();
        //ofMesh & mesh = user.getPointCloud();
        
        

       left_hand = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
       right_hand = user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
       left_foot = user.getJoint(JOINT_LEFT_FOOT).getProjectivePosition();
        right_foot =user.getJoint(JOINT_RIGHT_FOOT).getProjectivePosition();
        left_knee = user.getJoint(JOINT_LEFT_KNEE).getProjectivePosition();
        right_knee = user.getJoint(JOINT_RIGHT_KNEE).getProjectivePosition();
        left_elbow = user.getJoint(JOINT_LEFT_ELBOW).getProjectivePosition();
        right_elbow = user.getJoint(JOINT_RIGHT_ELBOW).getProjectivePosition();

        left_shoulder=user.getJoint(JOINT_LEFT_SHOULDER).getProjectivePosition();
        right_shoulder=user.getJoint(JOINT_RIGHT_SHOULDER).getProjectivePosition();
        head=user.getJoint(JOINT_HEAD).getProjectivePosition();
        

        if(time==10){
            prev_left_hand=user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
            prev_right_hand=user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
            prev_left_foot=user.getJoint(JOINT_LEFT_FOOT).getProjectivePosition();
            prev_right_foot=user.getJoint(JOINT_RIGHT_FOOT).getProjectivePosition();
            
            prev_left_shoulder=user.getJoint(JOINT_LEFT_SHOULDER).getProjectivePosition();
            prev_right_shoulder=user.getJoint(JOINT_RIGHT_SHOULDER).getProjectivePosition();
            
            time=0;
        }
        else{
            time++;
        }
        
        
        
        ofSetColor(255,0,0);
        
        
        
        for (int i = 0; i < particles.size(); i++){
            particles[i].draw();
        }
        
        ofSetColor(0,0,0);
        ofRect(10,10,230,20);
        ofSetColor(255,255,255);
        ofDrawBitmapString(ofToString(numUsers), 20, 23);

        float diff_left_hand=prev_left_hand.x-left_hand.x;
        float diff_right_hand=prev_right_hand.x-right_hand.x;
   
        //p1 1
        if(left_hand.x<left_shoulder.x && right_hand.x<left_shoulder.x && left_hand.y>right_shoulder.y && right_hand.y>right_shoulder.y && p1_1_isthrow==false){
            p1_1_issaving=true;
        }
        
        
        if(diff_left_hand<-100 ){
            p1_1_isthrow=true;
            p1_1_issaving=false;
            p1_1_speed=diff_left_hand;
        }
        if(diff_right_hand<-100 ){
            p1_1_isthrow=true;
            p1_1_issaving=false;
            p1_1_speed=diff_right_hand;
        }
        
        
        
        if(p1_1_issaving==true){
            p1_1_ballposx=left_hand.x;
            p1_1_ballposy=left_hand.y;
            if(p1_1_ballrad<100){
            p1_1_ballrad+=1;
            }
        }
        if(p1_1_isthrow==true){
            p1_1_ballposx-=p1_1_speed;
            p1_1_speed=p1_1_speed*0.95;
            if(p1_1_ballposx>640){
                p1_1_isthrow=false;
                p1_1_ballrad=0;
            }
            
            
        }
        
        if(p1_1_issaving==true || p1_1_isthrow==true){
            ofSetColor(0,255,0);
            ofRect(p1_1_ballposx,p1_1_ballposy,p1_1_ballrad,p1_1_ballrad);

        }
        
        
        
        
        float diff_left_foot=prev_left_foot.x-left_foot.x;
        float diff_right_foot=prev_right_foot.x-right_foot.x;
        
        //p1 2
        
        if(right_foot.y<right_knee.y  && diff_right_foot<0){
            //ofRect(20, 20, 90, 90);
            p1_2_isthrow=true;
            p1_2_ballposx=right_foot.x;
            p1_2_ballposy=right_foot.y;
            p1_2_speed=diff_right_foot;
        }
        
        if(p1_2_isthrow==true){
            ofSetColor(0,255,0);
            p1_2_ballposx=p1_2_ballposx-p1_2_speed;
            p1_2_speed=p1_2_speed*0.95;
            p1_2_ballrad=50;

            ofRect(p1_2_ballposx, p1_2_ballposy, p1_2_ballrad, p1_2_ballrad);
            if(p1_2_ballposx>640){
                p1_2_isthrow=false;
            }
        }
        
        
        //p1 b
        if(((head.y<right_hand.y && right_hand.y<right_shoulder.y && right_hand.x>head.x)||(head.y<left_hand.y  && left_hand.y<right_shoulder.y && left_hand.x>head.x)) && p1_1_isthrow==false && p1_2_isthrow==false){
            p1_block=true;
            ofSetColor(0, 255, 0);
            ofRect(right_elbow.x,right_hand.y,20,200);
            p1_1_issaving=false;
            p1_1_ballrad=0;

        }
        else{
            p1_block=false;
        }
            
       }
        
    
    
    
    
    
    
    
    
//  if two player
    else if(numUsers==2){
        
        ofxOpenNIUser & user = openNIDevice.getTrackedUser(0);
        
        ofxOpenNIUser & user2 = openNIDevice.getTrackedUser(1);
        
        

        
        left_hand = user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
        right_hand = user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
        left_foot = user.getJoint(JOINT_LEFT_FOOT).getProjectivePosition();
        right_foot =user.getJoint(JOINT_RIGHT_FOOT).getProjectivePosition();
        left_knee = user.getJoint(JOINT_LEFT_KNEE).getProjectivePosition();
        right_knee = user.getJoint(JOINT_RIGHT_KNEE).getProjectivePosition();
        left_elbow = user.getJoint(JOINT_LEFT_ELBOW).getProjectivePosition();
        right_elbow = user.getJoint(JOINT_RIGHT_ELBOW).getProjectivePosition();

        left_shoulder=user.getJoint(JOINT_LEFT_SHOULDER).getProjectivePosition();
        right_shoulder=user.getJoint(JOINT_RIGHT_SHOULDER).getProjectivePosition();
        head=user.getJoint(JOINT_HEAD).getProjectivePosition();
        

        head=user.getJoint(JOINT_HEAD).getProjectivePosition();
        
        
        
                p2_left_hand = user2.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
                p2_right_hand = user2.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
                p2_left_foot = user2.getJoint(JOINT_LEFT_FOOT).getProjectivePosition();
                p2_right_foot =user2.getJoint(JOINT_RIGHT_FOOT).getProjectivePosition();
                p2_left_knee = user2.getJoint(JOINT_LEFT_KNEE).getProjectivePosition();
                p2_right_knee = user2.getJoint(JOINT_RIGHT_KNEE).getProjectivePosition();
                p2_left_elbow = user2.getJoint(JOINT_LEFT_ELBOW).getProjectivePosition();
        p2_right_elbow = user2.getJoint(JOINT_RIGHT_ELBOW).getProjectivePosition();

        p2_left_shoulder=user2.getJoint(JOINT_LEFT_SHOULDER).getProjectivePosition();
        p2_right_shoulder=user2.getJoint(JOINT_RIGHT_SHOULDER).getProjectivePosition();

                p2_head=user2.getJoint(JOINT_HEAD).getProjectivePosition();
        
        
        if(time==10){
            prev_left_hand=user.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
            prev_right_hand=user.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
            prev_left_foot=user.getJoint(JOINT_LEFT_FOOT).getProjectivePosition();
            prev_right_foot=user.getJoint(JOINT_RIGHT_FOOT).getProjectivePosition();
            prev_left_shoulder=user.getJoint(JOINT_LEFT_SHOULDER).getProjectivePosition();
            prev_right_shoulder=user.getJoint(JOINT_RIGHT_SHOULDER).getProjectivePosition();
            

            
                        p2_prev_left_hand=user2.getJoint(JOINT_LEFT_HAND).getProjectivePosition();
                        p2_prev_right_hand=user2.getJoint(JOINT_RIGHT_HAND).getProjectivePosition();
                        p2_prev_left_foot=user2.getJoint(JOINT_LEFT_FOOT).getProjectivePosition();
                        p2_prev_right_foot=user2.getJoint(JOINT_RIGHT_FOOT).getProjectivePosition();
            p2_prev_left_shoulder=user2.getJoint(JOINT_LEFT_SHOULDER).getProjectivePosition();
            p2_prev_right_shoulder=user2.getJoint(JOINT_RIGHT_SHOULDER).getProjectivePosition();
            

            time=0;
        }
        else{
            time++;
        }
        

        ofSetColor(255,0,0);
        
        
        
        for (int i = 0; i < particles.size(); i++){
            particles[i].draw();
        }
        
        ofSetColor(0,0,0);
        ofRect(10,10,230,20);
        ofSetColor(255,255,255);
        ofDrawBitmapString(ofToString(numUsers), 20, 23);

        
        
        
        
        
        
        if(head.x>p2_head.x){ //if p1 is on the right
        
        float diff_left_hand=prev_left_hand.x-left_hand.x;
        float diff_right_hand=prev_right_hand.x-right_hand.x;
        
        //p1 1
if(left_hand.x>right_shoulder.x && right_hand.x>right_shoulder.x && left_hand.y>right_shoulder.y && right_hand.y>right_shoulder.y && p1_1_isthrow==false){
            p1_1_issaving=true;
        }
        
        
        if(diff_left_hand>100 ){
            p1_1_isthrow=true;
            p1_1_issaving=false;
            p1_1_speed=diff_left_hand;
        }
        if(diff_right_hand>100 ){
            p1_1_isthrow=true;
            p1_1_issaving=false;
            p1_1_speed=diff_right_hand;
        }
        
        
        
        if(p1_1_issaving==true){
            p1_1_ballposx=left_hand.x;
            p1_1_ballposy=left_hand.y;
            if(p1_1_ballrad<100){
                p1_1_ballrad+=1;
            }
        }
        if(p1_1_isthrow==true){
            p1_1_ballposx-=p1_1_speed;
            p1_1_speed=p1_1_speed*0.95;
            if(p1_1_ballposx<0){
                p1_1_isthrow=false;
                p1_1_ballrad=0;
            }
            
            
        }
        
        if(p1_1_issaving==true || p1_1_isthrow==true){
            ofSetColor(0,255,0);
            ofRect(p1_1_ballposx,p1_1_ballposy,p1_1_ballrad,p1_1_ballrad);
            
        }
        
        
        
        
        float diff_left_foot=prev_left_foot.x-left_foot.x;
        float diff_right_foot=prev_right_foot.x-right_foot.x;
        
        //p1 2
        
        if(left_foot.y<left_knee.y  && diff_left_foot>0){
            //ofRect(20, 20, 90, 90);
            p1_2_isthrow=true;
            p1_2_ballposx=left_foot.x;
            p1_2_ballposy=left_foot.y;
            p1_2_speed=diff_left_foot;
        }
        
        if(p1_2_isthrow==true){
            ofSetColor(0,255,0);
            p1_2_ballposx=p1_2_ballposx-p1_2_speed;
            p1_2_speed=p1_2_speed*0.95;
            p1_2_ballrad=50;
            
            ofRect(p1_2_ballposx, p1_2_ballposy, p1_2_ballrad, p1_2_ballrad);
            if(p1_2_ballposx<0){
                p1_2_isthrow=false;
            }
        }
        
        
        //p1 b
            if(((head.y<right_hand.y && right_hand.y<right_shoulder.y && right_hand.x<head.x)||(head.y<left_hand.y  && left_hand.y<right_shoulder.y && left_hand.x<head.x)) && p1_1_isthrow==false && p1_2_isthrow==false){
                p1_block=true;
                ofSetColor(0, 255, 0);
                ofRect(left_elbow.x,left_hand.y,20,200);
                p1_1_issaving=false;
                p1_1_ballrad=0;


        }
        else{p1_block=false;}
        
            
            
            
            
            
            
            float p2_diff_left_hand=p2_prev_left_hand.x-p2_left_hand.x;
            float p2_diff_right_hand=p2_prev_right_hand.x-p2_right_hand.x;
            
            //p1 1
            if(p2_left_hand.x<p2_left_shoulder.x && p2_right_hand.x<p2_left_shoulder.x && p2_left_hand.y>p2_right_shoulder.y && p2_right_hand.y>p2_right_shoulder.y && p2_1_isthrow==false){
                p2_1_issaving=true;
            }
            
            
            if(p2_diff_left_hand<-100 ){
                p2_1_isthrow=true;
                p2_1_issaving=false;
                p2_1_speed=p2_diff_left_hand;
            }
            if(p2_diff_right_hand<-100 ){
                p2_1_isthrow=true;
                p2_1_issaving=false;
                p2_1_speed=p2_diff_right_hand;
            }
            
            
            
            if(p2_1_issaving==true){
                p2_1_ballposx=p2_left_hand.x;
                p2_1_ballposy=p2_left_hand.y;
                if(p2_1_ballrad<100){
                    p2_1_ballrad+=1;
                }
            }
            if(p2_1_isthrow==true){
                p2_1_ballposx-=p2_1_speed;
                p2_1_speed=p2_1_speed*0.95;
                if(p2_1_ballposx>640){
                    p2_1_isthrow=false;
                    p2_1_ballrad=0;
                }
                
                
            }
            
            if(p2_1_issaving==true || p2_1_isthrow==true){
                ofSetColor(255,255,0);
                ofRect(p2_1_ballposx,p2_1_ballposy,p2_1_ballrad,p2_1_ballrad);
                
            }
            
            
            
            
            float p2_diff_left_foot=p2_prev_left_foot.x-p2_left_foot.x;
            float p2_diff_right_foot=p2_prev_right_foot.x-p2_right_foot.x;
            
            //p1 2
            
            if(p2_right_foot.y<p2_right_knee.y  && p2_diff_right_foot<0){
                //ofRect(20, 20, 90, 90);
                p2_2_isthrow=true;
                p2_2_ballposx=p2_right_foot.x;
                p2_2_ballposy=p2_right_foot.y;
                p2_2_speed=p2_diff_right_foot;
            }
            
            if(p2_2_isthrow==true){
                ofSetColor(255,255,0);
                p2_2_ballposx=p2_2_ballposx-p2_2_speed;
                p2_2_speed=p2_2_speed*0.95;
                p2_2_ballrad=50;
                
                ofRect(p2_2_ballposx, p2_2_ballposy, p2_2_ballrad, p2_2_ballrad);
                if(p2_2_ballposx>640){
                    p2_2_isthrow=false;
                }
            }
            
            
            //p1 b
            if(((p2_head.y<p2_right_hand.y && p2_right_hand.y<p2_right_shoulder.y && p2_right_hand.x>p2_head.x)||(p2_head.y<p2_left_hand.y  && p2_left_hand.y<p2_right_shoulder.y && p2_left_hand.x>p2_head.x)) && p2_1_isthrow==false && p2_2_isthrow==false){
                p2_block=true;
                ofSetColor(255, 255, 0);
                ofRect(p2_right_elbow.x,p2_right_hand.y,20,200);
                p2_1_issaving=false;
                p2_1_ballrad=0;
                
            }
            else{
                p2_block=false;
            }
            
            
            
            
            
            
            
    }
        
        
        
        
        
        
        
        
        
        else if(head.x<p2_head.x){ //if p1 is on the left
            float diff_left_hand=prev_left_hand.x-left_hand.x;
            float diff_right_hand=prev_right_hand.x-right_hand.x;
            
            //p1 1
            if(left_hand.x<left_shoulder.x && right_hand.x<left_shoulder.x && left_hand.y>right_shoulder.y && right_hand.y>right_shoulder.y && p1_1_isthrow==false){
                p1_1_issaving=true;
            }
            
            
            if(diff_left_hand<-100 ){
                p1_1_isthrow=true;
                p1_1_issaving=false;
                p1_1_speed=diff_left_hand;
            }
            if(diff_right_hand<-100 ){
                p1_1_isthrow=true;
                p1_1_issaving=false;
                p1_1_speed=diff_right_hand;
            }
            
            
            
            if(p1_1_issaving==true){
                p1_1_ballposx=left_hand.x;
                p1_1_ballposy=left_hand.y;
                if(p1_1_ballrad<100){
                    p1_1_ballrad+=1;
                }
            }
            if(p1_1_isthrow==true){
                p1_1_ballposx-=p1_1_speed;
                p1_1_speed=p1_1_speed*0.95;
                if(p1_1_ballposx>640){
                    p1_1_isthrow=false;
                    p1_1_ballrad=0;
                }
                
                
            }
            
            if(p1_1_issaving==true || p1_1_isthrow==true){
                ofSetColor(0,255,0);
                ofRect(p1_1_ballposx,p1_1_ballposy,p1_1_ballrad,p1_1_ballrad);
                
            }
            
            
            
            
            float diff_left_foot=prev_left_foot.x-left_foot.x;
            float diff_right_foot=prev_right_foot.x-right_foot.x;
            
            //p1 2
            
            if(right_foot.y<right_knee.y  && diff_right_foot<0){
                //ofRect(20, 20, 90, 90);
                p1_2_isthrow=true;
                p1_2_ballposx=right_foot.x;
                p1_2_ballposy=right_foot.y;
                p1_2_speed=diff_right_foot;
            }
            
            if(p1_2_isthrow==true){
                ofSetColor(0,255,0);
                p1_2_ballposx=p1_2_ballposx-p1_2_speed;
                p1_2_speed=p1_2_speed*0.95;
                p1_2_ballrad=50;
                
                ofRect(p1_2_ballposx, p1_2_ballposy, p1_2_ballrad, p1_2_ballrad);
                if(p1_2_ballposx>640){
                    p1_2_isthrow=false;
                }
            }
            
            
            //p1 b
            if(((head.y<right_hand.y && right_hand.y<right_shoulder.y && right_hand.x>head.x)||(head.y<left_hand.y  && left_hand.y<right_shoulder.y && left_hand.x>head.x)) && p1_1_isthrow==false && p1_2_isthrow==false){
                p1_block=true;
                ofSetColor(0, 255, 0);
                ofRect(right_elbow.x,right_hand.y,20,200);
                p1_1_issaving=false;
                p1_1_ballrad=0;
                
            }
            else{
                p1_block=false;
            }
        }

    
    

           }
        }

        

    



//--------------------------------------------------------------
void testApp::userEvent(ofxOpenNIUserEvent & event){
    ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
}

//--------------------------------------------------------------
void testApp::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}
//--------------------------------------------------------------

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}