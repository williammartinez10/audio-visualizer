#pragma once

#include "ofMain.h"
#include "AudioVisualizer.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void drawMode1(vector<float> amplitudes);
		void drawMode2(vector<float> amplitudes);
		void drawMode3(vector<float> amplitudes);
		void drawMode4(vector<float> amplitudes);
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
	
	ofImage RecordingIndicator;
	ofImage ReplayingIndicator;
	ofImage UserGuide;
	ofImage disco;


	private:
    
		ofSoundPlayer sound;
		AudioVisualizer visualizer;
		
		bool playing = false;
		char mode = '1';
    
    float volume;
    vector <ofSoundPlayer> soundList;

    ofSoundPlayer beatSound;
    ofSoundPlayer badbunnySound;
    ofSoundPlayer babysharkSound;
    ofSoundPlayer rockSound;
    ofSoundPlayer donomarSound;
    
    ofSoundPlayer selectedSound;
    int soundIndex;
    
    vector <int> recordedKeys;
    vector <float> recordedTimes;
    
    bool recorded;
    bool replay;
    
    float currentTimeRecord;
    float currentTimeReplay;
    float passTime;
    
    int index;
    bool replayEvent;
    
    ofSoundPlayer firstSound;
    char firstMode;

};
