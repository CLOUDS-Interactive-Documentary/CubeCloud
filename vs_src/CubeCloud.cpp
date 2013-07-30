//
//  CubeCloud.cpp
//

#include "CubeCloud.h"
#include "ofGraphics.h"

#include "CloudsRGBDVideoPlayer.h"
#ifdef AVF_PLAYER
#include "ofxAVFVideoPlayer.h"
#endif

void CubeCloud::selfSetup()
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

void CubeCloud::selfPresetLoaded(string presetPath){
	
}

void CubeCloud::selfBegin()
{
    
}

void CubeCloud::selfEnd()
{
    
}

void CubeCloud::selfExit()
{
    delete buckets;
}

void CubeCloud::selfSetupSystemGui()
{
    sysGui->addLabel("NoiseBuilding");
    sysGui->addSlider("speed", 1, 1000, &speed);
    sysGui->addSlider("bucketWidth", 1, 100, &bucketWidth);
    sysGui->addSlider("numBucketsAcross", 1, maxNumBucketsAcross, &numBucketsAcross);
    //don't set total_width greater than width, unless you increase numBuckets
}

void CubeCloud::selfSetupRenderGui()
{
    
}

void CubeCloud::guiSystemEvent(ofxUIEventArgs &e)
{
    
}

void CubeCloud::selfKeyPressed(ofKeyEventArgs & args){
    
}

void CubeCloud::selfUpdate()
{
    for (int i = 0; i < speed; i++) {
        int bucketIndex = (int)ofRandom(totalNumBuckets);
        buckets[bucketIndex]++;
        if (buckets[bucketIndex] >= numBucketsAcross){
            buckets[bucketIndex] -= numBucketsAcross*2;
        }
    }
}

void CubeCloud::selfDraw()
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

void CubeCloud::selfDrawBackground()
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

void CubeCloud::selfDrawDebug()
{
    
}

void CubeCloud::selfSceneTransformation()
{
}

void CubeCloud::selfKeyReleased(ofKeyEventArgs & args)
{
    
}

void CubeCloud::selfMouseDragged(ofMouseEventArgs& data)
{
    
}

void CubeCloud::selfMouseMoved(ofMouseEventArgs& data)
{
    
}

void CubeCloud::selfMousePressed(ofMouseEventArgs& data)
{
    
}

void CubeCloud::selfMouseReleased(ofMouseEventArgs& data)
{
    
}

void CubeCloud::selfSetupGui()
{
    
}

void CubeCloud::selfGuiEvent(ofxUIEventArgs &e)
{
    
}

void CubeCloud::guiRenderEvent(ofxUIEventArgs &e)
{
    
}