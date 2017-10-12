#pragma once

#include "ofMain.h"


struct Droplet{
	Droplet();
	Droplet(int x, int y, int r, bool g);

	ofPoint position;
	int radius;
	bool grow;
	int quad;
};

struct Thunder {
	Thunder();
	Thunder(int size);
	void loadClips(string t1, string t2, string t3, string t4);
	vector<ofSoundPlayer> all;
};

struct Rain {
	Rain();
	Rain(int size);
	void loadClips(string t1, string t2, string t3, string t4);
	vector<ofSoundPlayer> all;
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		vector<ofPoint> circles;
		vector<int> radii;
		vector<bool> grow;
		vector<Droplet> droplets;

		bool followLeader;
		
		Thunder thunderTypes;
		Rain rainTypes;
		ofSoundPlayer waterdrop;
};
