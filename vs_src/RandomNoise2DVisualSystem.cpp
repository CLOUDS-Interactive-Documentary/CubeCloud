//
//  RandomNoise2DVisualSystem.cpp
//

#include "RandomNoise2DVisualSystem.h"

#include "CloudsRGBDCombinedRenderer.h"
#ifdef AVF_PLAYER
#include "ofxAVFVideoPlayer.h"
#endif

void RandomNoise2DVisualSystem::selfSetup()
{
    
}

void RandomNoise2DVisualSystem::selfPresetLoaded(string presetPath){
	
}

void RandomNoise2DVisualSystem::selfBegin()
{
    
}

void RandomNoise2DVisualSystem::selfEnd()
{
    
}

void RandomNoise2DVisualSystem::selfExit()
{
    
}

void RandomNoise2DVisualSystem::selfSetupSystemGui()
{
    sysGui->addLabel("Crazy");
    num_points = 1000;
    max_size = 5;
    min_size = 0;
    sysGui->addSlider("num_points", 1, 5000, &num_points);
    sysGui->addSlider("max_size", 0.1, 100.0, &max_size);
    sysGui->addSlider("min_size", 0.0, max_size, &min_size);
}

void RandomNoise2DVisualSystem::selfSetupRenderGui()
{
    
}

void RandomNoise2DVisualSystem::guiSystemEvent(ofxUIEventArgs &e)
{
    
}

void RandomNoise2DVisualSystem::selfKeyPressed(ofKeyEventArgs & args){
    
}

void RandomNoise2DVisualSystem::selfUpdate()
{
    
}

void RandomNoise2DVisualSystem::selfDraw()
{
    long totalPixels = ofGetWidth() * ofGetHeight();
    int stepSize = totalPixels/num_points;
    for(int i = 0; i < totalPixels; i += stepSize){
        ofSetColor(ofNoise(i, ofGetElapsedTimef())*255);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofRect(i%ofGetWidth()-ofGetWidth()/2, i/ofGetWidth()-ofGetWidth()/2, ofRandom(min_size, max_size), ofRandom(min_size, max_size));
    }
//    for (int y = -ofGetHeight()/2; y < ofGetHeight()/2; y++){
//        for(int x = -ofGetWidth()/2; x < ofGetWidth()/2; x++){
//            ofSetColor((x+y)%255, 255);
//            ofRect(x, y, 1, 1);
//        }
//    }
//    for(int i = 0; i < num_points; i++){
//        ofSetColor(ofRandom(255));
//        ofCircle(ofRandom(ofGetWidth())-ofGetWidth()/2, ofRandom(ofGetHeight())-ofGetHeight()/2, ofRandom(min_size, max_size));
//    }
}

void RandomNoise2DVisualSystem::selfDrawBackground()
{
    
}

void RandomNoise2DVisualSystem::selfDrawDebug()
{
    
}

void RandomNoise2DVisualSystem::selfSceneTransformation()
{
    
}

void RandomNoise2DVisualSystem::selfKeyReleased(ofKeyEventArgs & args)
{
    
}

void RandomNoise2DVisualSystem::selfMouseDragged(ofMouseEventArgs& data)
{
    
}

void RandomNoise2DVisualSystem::selfMouseMoved(ofMouseEventArgs& data)
{
    
}

void RandomNoise2DVisualSystem::selfMousePressed(ofMouseEventArgs& data)
{
    
}

void RandomNoise2DVisualSystem::selfMouseReleased(ofMouseEventArgs& data)
{
    
}

void RandomNoise2DVisualSystem::selfSetupGui()
{
    
}

void RandomNoise2DVisualSystem::selfGuiEvent(ofxUIEventArgs &e)
{
    
}

void RandomNoise2DVisualSystem::guiRenderEvent(ofxUIEventArgs &e)
{
    
}