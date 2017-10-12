#include "ofApp.h"
//audio clips edited by me
//water drop http://soundbible.com/1139-Water-Drop-Low.html
//thunder 1 http://soundbible.com/2015-Thunder-Strike-1.html
//thunder 2 http://soundbible.com/2016-Thunder-Strike-2.html
//thunder 3 http://soundbible.com/2012-Thunder-Strike-3.html
//thunder 4 http://soundbible.com/1907-Thunder.html
//rumbly rain http://soundbible.com/1158-Rain.html
//rain w bird http://soundbible.com/2006-Bird-In-Rain.html
//staticy rain http://soundbible.com/2011-Rain-Background.html
//rainy rain http://soundbible.com/1999-Rain.html

#define MAX_RADIUS min(ofGetWidth()/2,ofGetHeight()/2)
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetCircleResolution(80);
	ofSetFrameRate(60);

	followLeader = false;

	//set up initial circle
	Droplet ogCircle(ofGetWidth() / 2, ofGetHeight() / 2, 100, true);
	droplets.push_back(ogCircle);

	//initialize ofSoundPlayer objs for structs
	Thunder tempT(4);
	thunderTypes = tempT;
	Rain tempR(4);
	rainTypes = tempR;

	//setMultiPlay for all sounds
	for (int i = 0; i < thunderTypes.all.size(); ++i) {
		thunderTypes.all[i].setMultiPlay(true);
	}

	for (int i = 0; i < thunderTypes.all.size(); ++i) {
		rainTypes.all[i].setMultiPlay(true);
	}

	waterdrop.setMultiPlay(true);


	//load unloaded sound clips(rain & thunder are loaded upon creation)
	waterdrop.loadSound("waterdropSoundFX.wav");
	rainTypes.loadClips("1rumblyrain.wav","2birdyrain.wav","3staticyrain.wav","4rainyrain.wav");
	thunderTypes.loadClips("thunder1.wav", "thunder2.wav", "thunder3.wav", "thunder4.wav");

	//play waterdrop upon entry for initial circle drawing
	waterdrop.play();
}

//--------------------------------------------------------------
void ofApp::update(){
	for (int i = 0; i < droplets.size();  ++i) {
		if (droplets[i].radius >= MAX_RADIUS) {
			droplets[i].grow = false;

			////determine if thunder will crack 
			if ((int)ofRandom(0, 101) >= 75) {  //.25 chance of thunderclap
				if (droplets[i].position.x < ofGetWidth() / 2) { //left side
					if (droplets[i].position.y > ofGetHeight() / 2) { //Q1, top left
						thunderTypes.all[(int)ofRandom(0, 2)].play(); //to pick bt rainTypes index 0/1
					}
					else { //Q4, bott left
						thunderTypes.all[(int)ofRandom(2, 4)].play(); //to pick bt rainTypes index 2/3
					}

				}
				else { //right side
					if (droplets[i].position.y > ofGetHeight() / 2) { //Q2, top right
						thunderTypes.all[(int)ofRandom(2, 4)].play(); //to pick bt rainTypes index 2/3
					}
					else { //Q4, bott right
						thunderTypes.all[(int)ofRandom(0, 2)].play(); //to pick bt rainTypes index 0/1
					}
				}
			}

		}
		if (followLeader) {
			if (i != 0) {
				if (droplets[i].radius > droplets[i - 1].radius) {
					droplets[i].grow = false;
				}
			}
		}

		if (droplets[i].radius < 2 && droplets[i].radius < 2) {
			droplets[i].grow = true;
			waterdrop.play();
		}

		if (droplets[i].grow) {
			droplets[i].radius += 1;
		} 
		if (!droplets[i].grow) {
			droplets[i].radius -= 1;
		}

	}
}
 
//--------------------------------------------------------------
void ofApp::draw() {
	ofSetBackgroundColor(ofColor::black);
	ofSetColor(255, 255, 255);
	ofNoFill();
	float avgRadii = 0;
	for (int i = 0; i < droplets.size(); ++i) {
		avgRadii += droplets[i].radius;
		ofDrawCircle(droplets[i].position, droplets[i].radius);

		//play rain clip based on spawn location
		if (!rainTypes.all[droplets[i].quad].isPlaying()) {
			rainTypes.all[droplets[i].quad].play();
		}
	}
	avgRadii = avgRadii / droplets.size();
	for(int i = 0; i < rainTypes.all.size(); ++i) {
		rainTypes.all[i].setVolume(avgRadii/MAX_RADIUS);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ' ') {
		followLeader = !followLeader;
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
	if (button == 0) {
		cout << x << " " << y << endl;
		Droplet newtemp(x,y, (int)ofRandom(1, 100), (int)ofRandom(0, 2));
		droplets.push_back(newtemp);
	}

	if (button == 1) {
		int numNewDrops = (int)ofRandom(2, 5);
		for (int i = 0; i < numNewDrops; ++i) {
			Droplet newtemp(x, y, (int)ofRandom(3, 200), (int)ofRandom(0, 2));
			droplets.push_back(newtemp);
		}
		// crack thunder if largest possible number of droplets created upon click
		if (numNewDrops == 4) {
			thunderTypes.all[(int)ofRandom(0, 4)].play();
		}
	}

	if (button == 2) {
		int numNewDrops = (int)ofRandom(5, 9);
		for (int i = 0; i < numNewDrops; ++i) {
			Droplet newtemp(x, y, (int)ofRandom(2, 300), (int)ofRandom(0, 2));
			droplets.push_back(newtemp);
		}
		// crack thunder if largest possible number of droplets created upon click
		if (numNewDrops == 8) {
			thunderTypes.all[(int)ofRandom(0, 4)].play();
		}
	}

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

Droplet::Droplet() { }
Droplet::Droplet(int x, int y, int r, bool g) {
	position = ofPoint(x, y);
	radius = r;
	grow = g;

	if (x < ofGetWidth() / 4) { //quad0
		quad = 0;
	}
	if (x >= ofGetWidth() / 4 && x < ofGetWidth() / 2) { //quad1
		quad = 1;
	}
	if (x >= ofGetWidth() / 2 && x < (ofGetWidth() / 4) * 3) { //quad2
		quad = 2;
	}
	if (x >= (ofGetWidth() / 4) * 3) { //quad3
		quad = 3;
	}
}

Thunder::Thunder(){ }
Thunder::Thunder(int size) {
	//put different thunder sounds into vector
	for (int i = 0; i < size; ++i) {
		ofSoundPlayer t;
		all.push_back(t);
	}
}
void Thunder::loadClips(string t1, string t2, string t3, string t4){
	//load sound for all ofSoundPlayer objs in vector
	all[0].loadSound(t1);
	all[1].loadSound(t2);
	all[2].loadSound(t3);
	all[3].loadSound(t4);
}
Rain::Rain() { }
Rain::Rain(int size) {
	//put different thunder sounds into vector
	for (int i = 0; i < size; ++i) {
		ofSoundPlayer t;
		all.push_back(t);
	}
}
void Rain::loadClips(string t1, string t2, string t3, string t4) {
	//load sound for all ofSoundPlayer objs in vector
	all[0].loadSound(t1);
	all[1].loadSound(t2);
	all[2].loadSound(t3);
	all[3].loadSound(t4);

}