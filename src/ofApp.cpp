#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    volume = 0.5;
    soundIndex = 0;
    recorded = false;
    replay = false;
        
    ofSetBackgroundColor(36, 32,56); // Set background color
    
    // Images
    RecordingIndicator.load("Record.png");
    RecordingIndicator.resize(157,65);    
    ReplayingIndicator.load("Replay.png");
    ReplayingIndicator.resize(157,65);
    UserGuide.load("User_Guide.png");
    UserGuide.resize(258,90);
    disco.load("Picture1.jpg"); 


    // Songs
    beatSound.load("beat.wav");
    badbunnySound.load("badbunny.wav");
    babysharkSound.load("babyshark.wav");
    rockSound.load("rock-song.wav");
    donomarSound.load("donomar.wav");
    
    soundList.push_back(beatSound);
    soundList.push_back(badbunnySound);
    soundList.push_back(babysharkSound);
    soundList.push_back(rockSound);
    soundList.push_back(donomarSound);
    
    selectedSound = beatSound;
    selectedSound.setLoop(true); // Loop song
    selectedSound.setVolume(volume); // Set volume

    replayEvent = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */

    ofSoundUpdate(); // Updates all sound players
    selectedSound.setVolume(volume); // Update volume
    visualizer.updateAmplitudes(); // Update visualizer amplitudes

    passTime = ofGetElapsedTimef();
    
    if(replayEvent){
        if(passTime - currentTimeReplay > recordedTimes[index]){
            
            if(recordedKeys[index] == 49){
                mode = '1';
            }
            if(recordedKeys[index] == 50){
                mode = '2';
            }
            if(recordedKeys[index] == 51){
                mode = '3';
            }
            if(recordedKeys[index] == 52){
                mode = '4';
            }
            if(recordedKeys[index] == 115){ // Play "badbunny.wav"
                       selectedSound.stop();
                       selectedSound = badbunnySound;
                       if(playing){
                           selectedSound.setLoop(true);
                           selectedSound.play();
                       }
              }
            if(recordedKeys[index] == 100){ // Play "babyshark.wav"
                   selectedSound.stop();
                   selectedSound = babysharkSound;
                   if(playing){
                       selectedSound.setLoop(true);
                       selectedSound.play();
                   }
            }
        if(recordedKeys[index] == 102){ // Play "rock-song.wav"
                   selectedSound.stop();
                   selectedSound = rockSound;
                   if(playing){
                       selectedSound.setLoop(true);
                       selectedSound.play();
                   }
            }
        if(recordedKeys[index] == 103){ // Play "donomar.wav"
                   selectedSound.stop();
                   selectedSound = donomarSound;
                   if(playing){
                       selectedSound.setLoop(true);
                       selectedSound.play();
                   }
            }
        if(recordedKeys[index] == 61){  // Increase volume
                   if(playing){
                       volume += 0.1;
                       selectedSound.setVolume(volume);
                   }
        }
        if(recordedKeys[index] == 45){  // Decrease volume
                   if(playing){
                       volume -= 0.1;
                       selectedSound.setVolume(volume);
                   }
        }
        // if(recordedKeys[index] == 32){   // Skip song
        //            if(playing){
        //                selectedSound.stop();
        //                if(soundIndex < soundList.size() - 1){
        //                    soundIndex += 1;
        //                }else{
        //                    soundIndex = 0;
        //                }
        //                selectedSound = soundList[soundIndex];
        //                selectedSound.play();
        //            }
        // }
            
        index += 1;
            
        if(index > recordedKeys.size() - 1){
            replayEvent = false;
            ReplayingIndicator.clear();
        }
    }
}

}

//--------------------------------------------------------------
void ofApp::draw(){
    /* The update method is called multiple times per second
    It's in charge of drawing all figures and text on screen */
    if(!playing){
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth()/2 - 50, ofGetHeight()/2);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if(mode == '1'){
        ofSetBackgroundColor(20, 80, 120); // Set background color
        drawMode1(amplitudes);
    }else if(mode == '2'){
        ofSetBackgroundColor(40, 120, 40); // Set background color
        drawMode2(amplitudes);
    }else if(mode == '3'){
        ofSetBackgroundColor(140, 0, 120); // Set background color
        drawMode3(amplitudes);
    }else if(mode == '4'){
        ofSetBackgroundColor(120, 120, 0); // Set background color
        drawMode4(amplitudes);
    }

    if(playing && recorded){
        ofDrawBitmapString("Recording...", ofGetWidth()/2, ofGetHeight()/2);
        RecordingIndicator.draw(ofGetWidth() - (RecordingIndicator.getWidth() + 10),10);
    }

    if(replayEvent){
        ofDrawBitmapString("Replaying...", ofGetWidth()/2, ofGetHeight()/2);
        ReplayingIndicator.draw(ofGetWidth() - (ReplayingIndicator.getWidth() + 10),10);
    }
    

}
void ofApp::drawMode1(vector<float> amplitudes){
        ofFill(); // Drawn Shapes will be filled in with color
        ofSetColor(256); // This resets the color of the "brush" to white
        ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
        UserGuide.draw(ofGetWidth() /2 - (UserGuide.getWidth() /2), ofGetHeight() - (UserGuide.getHeight() + 5));

        ofSetColor(ofRandom(200), ofRandom(200), ofRandom(200)); // Sets the color of the rectangles to be random
        for (int i=0; i<64; i++){
            ofDrawRectangle(ofGetWidth() / 64 * i, ofGetHeight() - 100, ofGetWidth() / 64,  amplitudes[i]); // Creates 64 bars in visualizer
        }
}
void ofApp::drawMode2(vector<float> amplitudes){
        ofSetLineWidth(5); // Sets the line width
        ofNoFill(); // Only the outline of shapes will be drawn
        ofSetColor(256); // This resets the color of the "brush" to white
        ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
        UserGuide.draw(ofGetWidth() /2 - (UserGuide.getWidth() /2), ofGetHeight() - (UserGuide.getHeight() + 5));

        int bands = amplitudes.size();
        for(int i=0; i< bands; i++){
            ofSetColor((bands - i)*32 %256,18,144); // Color varies between frequencies
            ofDrawCircle(ofGetWidth()/2, ofGetHeight()/2, amplitudes[0]/(i +1));
        }
}

void ofApp::drawMode3(vector<float> amplitudes){
        ofSetColor(256); // This resets the color of the "brush" to white
        ofDrawBitmapString("Rectangle Width Visualizer", 0, 15);
        UserGuide.draw(ofGetWidth() /2 - (UserGuide.getWidth() /2), ofGetHeight() - (UserGuide.getHeight() + 5));
        
        ofSetColor(ofRandom(200), ofRandom(200), ofRandom(200));
        ofFill();
        for (int i = 0; i < 64; i++){
            ofDrawRectangle(ofGetWidth(), ofGetHeight() / 64 * i, amplitudes[i], ofGetHeight() / 64);
    }
}
void ofApp::drawMode4(vector<float> amplitudes){
        ofSetColor(256); // This resets the color of the "brush" to white
        ofDrawBitmapString("Custom Visualizer", 0, 15);
        UserGuide.draw(10, ofGetHeight() - 100);

        if (playing){
            ofFill();
            disco.draw(0, 0, ofGetWidth(), ofGetHeight());
            UserGuide.draw(10, ofGetHeight() - 100);

            for (int i = 0; i < 4; i++){
                ofEnableAlphaBlending();
                ofSetColor(50, 205, 50, 127);
                ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[i]);
            }

            ofTranslate(ofGetWidth()/2, ofGetHeight()/2 - 20);
            ofRotateDeg(60);

            for (int i=4; i<64; i++){
                ofSetColor(255,255,255);
                ofDrawRectangle(i, i * 8, 23, amplitudes[i]);
                ofRotateDeg(-30%360);
            }
        }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // This method is called automatically when any key is pressed
    switch(key){
        case 'p': // Play the music and visualizer
            if(playing){
                selectedSound.stop();
            }else{
                selectedSound.play();
            }
            playing = !playing;
            break;
        case '1':
            mode = '1';
            break;
        case '2':
            mode = '2';
            break;
        case '3':
            mode = '3';
            break;
        case '4':
            mode = '4';
            break;
        case 'a': // Pause the music and visualizer
            if (replayEvent){
                break;
            }
            if(playing){
                selectedSound.stop();
            }
            playing = !playing;
            break;
        case 's': // Play "badbunny.wav"
            selectedSound.stop();
            selectedSound = badbunnySound;
            if(playing){
                selectedSound.setLoop(true);
                selectedSound.play();
            }
            break;
        case 'd': // Play "babyshark.wav"
            selectedSound.stop();
            selectedSound = babysharkSound;
            if(playing){
                selectedSound.setLoop(true);
                selectedSound.play();
            }
            break;
        case 'f': // Play "rock-song.wav"
            selectedSound.stop();
            selectedSound = rockSound;
            if(playing){
                selectedSound.setLoop(true);
                selectedSound.play();
            }
            break;
        case 'g': // Play "donomar.wav"
            selectedSound.stop();
            selectedSound = donomarSound;
            if(playing){
                selectedSound.setLoop(true);
                selectedSound.play();
            }
            break;
        case '=':   // Increase volume
            if(playing){
                volume += 0.1;
                selectedSound.setVolume(volume);
            }
            break;
        case '-':   // Decrease volume
            if(playing){
                volume -= 0.1;
                selectedSound.setVolume(volume);
            }
            break;
        // case ' ':   // Skip song
        //     if(playing){
        //         selectedSound.stop();
        //         if(soundIndex < soundList.size() - 1){
        //             soundIndex += 1;
        //         }else{
        //             soundIndex = 0;
        //         }
        //         selectedSound = soundList[soundIndex];
        //         selectedSound.play();
        //     }
        //     selectedSound.setLoop(true);
        //     break;
        case 'r':  // Record
            if (recorded == true){
                recorded = false;
                break;
            }
            if(playing && recorded == false){
                RecordingIndicator.draw(ofGetWidth() - (RecordingIndicator.getWidth() + 10),10);
                firstSound = selectedSound;
                firstMode = mode;
                recordedTimes.clear();
                recordedKeys.clear();
                currentTimeRecord = ofGetElapsedTimef();
                recorded = true;
                break;
            }
        case 't': // Replay
            if (replay == true){
                selectedSound.stop();
                replay = false;
                replayEvent = false; 
                break;
            }

            if(playing && replay == false){
                ReplayingIndicator.draw(ofGetWidth() - (ReplayingIndicator.getWidth() + 10),10);
                currentTimeReplay = ofGetElapsedTimef();
                selectedSound.stop();
                selectedSound = firstSound;
                selectedSound.play();
                mode = firstMode;
                index = 0;
                replay = true;
                replayEvent = true;
                break;
                
            }

    }
    
    // Get recorded keys and times
    if(key != 'r' && playing && recorded){
        passTime = ofGetElapsedTimef() - currentTimeRecord;
        recordedKeys.push_back(key);
        recordedTimes.push_back(passTime);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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