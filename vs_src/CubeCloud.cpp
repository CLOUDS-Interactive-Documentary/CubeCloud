//
//  RandomNoise2DVisualSystem.cpp
//

#include "RandomNoise2DVisualSystem.h"
#include "ofGraphics.h"

#include "CloudsRGBDVideoPlayer.h"
#ifdef AVF_PLAYER
#include "ofxAVFVideoPlayer.h"
#endif

void RandomNoise2DVisualSystem::selfSetup()
{
    maxNumBucketsAcross = 100;
    totalNumBuckets = maxNumBucketsAcross*maxNumBucketsAcross;
    bucketWidth = 5;
    speed = 40;
    numBucketsAcross = maxNumBucketsAcross;
    buckets = new int[totalNumBuckets];
    for (int i = 0; i < totalNumBuckets; i++) {
        buckets[i] = 0;
    }
    myCustomCamera.lookAt(ofVec3f(maxNumBucketsAcross/2., maxNumBucketsAcross/2., maxNumBucketsAcross/2.));
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
    sysGui->addSlider("speed", 1, 1000, &speed);
    sysGui->addSlider("bucketWidth", 1, 100, &bucketWidth);
    sysGui->addSlider("numBucketsAcross", 1, maxNumBucketsAcross, &numBucketsAcross);
    //don't set total_width greater than width, unless you increase numBuckets
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
        int bucketIndex = (int)ofRandom(totalNumBuckets);
        buckets[bucketIndex]++;
        if (buckets[bucketIndex] >= numBucketsAcross){
            buckets[bucketIndex] -= numBucketsAcross*2;
        }
    }
}

void RandomNoise2DVisualSystem::selfDraw()
{
    ofSetColor(255,1);
    glDepthMask(false);
    for(int i = 0; i < numBucketsAcross; i++){
        for(int j = 0; j < numBucketsAcross; j++){
            int value = buckets[i*maxNumBucketsAcross+j];
            if (value != 0){
                ofPushMatrix();
                bool negative = value < 0;
                if (negative){value = -value;}
                ofScale(bucketWidth, bucketWidth, bucketWidth * value);
                //ofBox(i, j, value/2./bucketWidth, 1);
                float z = .5;
                if (negative){
                    //when value == 0, z = bucketWidth*numBucketsAcross
                    //when value == numBucketsAcross, z = .5
                    float top = numBucketsAcross*bucketWidth;
                    float bottom = top - bucketWidth*value;
                    z = (top - bottom)/2.+bottom;
                    z /= bucketWidth*value;
                }
                ofSetColor(255,ofMap(value, 0, numBucketsAcross, 1, 4));
                ofBox(i, j, z, 1);
                ofPopMatrix();
            }
        }
    }
}

void RandomNoise2DVisualSystem::selfDrawBackground()
{
    //2D version
//    int currNumBuckets = total_width/bucket_width;
//    for (int i = 0; i < currNumBuckets; i++) {
//        int value = buckets[i];
//        if (value > 0){
//            ofRect(i*bucket_width, 0, bucket_width, value);
//        } else if (value < 0){
//            ofRect(i*bucket_width, top + value, bucket_width, -value);
//        }
//    }
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