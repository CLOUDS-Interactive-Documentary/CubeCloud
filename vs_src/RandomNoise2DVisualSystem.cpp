//
//  RandomNoise2DVisualSystem.cpp
//

#include "RandomNoise2DVisualSystem.h"

#include "CloudsRGBDVideoPlayer.h"
#ifdef AVF_PLAYER
#include "ofxAVFVideoPlayer.h"
#endif

void RandomNoise2DVisualSystem::selfSetup()
{
    height = ofGetHeight();
    width = ofGetWidth();
    halfHeight = height/2;
    halfWidth = width/2;
    numBuckets = width;
    buckets = new int[numBuckets];
    for (int i = 0; i < numBuckets; i++) {
        buckets[i] = 0;
    }
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
    delete buckets;
}

void RandomNoise2DVisualSystem::selfSetupSystemGui()
{
    sysGui->addLabel("NoiseBuilding");
    speed = 40;
    step_size = 10;
    bucket_width = 5;
    top = 400;
    total_width = width;
    sysGui->addSlider("speed", 1, 100, &speed);
    sysGui->addSlider("step_size", 1, 100, &step_size);
    sysGui->addSlider("bucket_width", 1, 100, &bucket_width);
    //don't set total_width greater than width, unless you increase numBuckets
    sysGui->addSlider("total_width", 1, width, &total_width);
    sysGui->addSlider("top", 100, height*2, &top);
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
    for (int i = 0; i < speed; i++) {
        int bucketIndex = (int)ofRandom(numBuckets);
        buckets[bucketIndex]+=step_size;
        if (buckets[bucketIndex] >= top){
            buckets[bucketIndex] -= top*2;
        }
    }
}

void RandomNoise2DVisualSystem::selfDraw()
{
    int currNumBuckets = total_width/bucket_width;
    for (int i = 0; i < currNumBuckets; i++) {
        int value = buckets[i];
        if (value > 0){
            ofRect(i*bucket_width, 0, bucket_width, value);
        } else if (value < 0){
            ofRect(i*bucket_width, top + value, bucket_width, -value);
        }
    }
//    long totalPixels = ofGetWidth() * ofGetHeight();
//    int stepSize = totalPixels/num_points;
//    for(int i = 0; i < totalPixels; i += stepSize){
//        ofSetColor(ofNoise(i, ofGetElapsedTimef())*255);
//        ofSetRectMode(OF_RECTMODE_CENTER);
//        ofRect(i%ofGetWidth()-ofGetWidth()/2, i/ofGetWidth()-ofGetWidth()/2, ofRandom(min_size, max_size), ofRandom(min_size, max_size));
//    }
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
    //ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
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