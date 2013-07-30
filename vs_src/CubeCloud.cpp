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
    
    //create the box VBO
    //borrowed from ofBox
	float h = .5;
    ofVec3f vertices[] = {
        ofVec3f(+h,-h,+h), ofVec3f(+h,-h,-h), ofVec3f(+h,+h,-h), ofVec3f(+h,+h,+h),
        ofVec3f(+h,+h,+h), ofVec3f(+h,+h,-h), ofVec3f(-h,+h,-h), ofVec3f(-h,+h,+h),
        ofVec3f(+h,+h,+h), ofVec3f(-h,+h,+h), ofVec3f(-h,-h,+h), ofVec3f(+h,-h,+h),
        ofVec3f(-h,-h,+h), ofVec3f(-h,+h,+h), ofVec3f(-h,+h,-h), ofVec3f(-h,-h,-h),
        ofVec3f(-h,-h,+h), ofVec3f(-h,-h,-h), ofVec3f(+h,-h,-h), ofVec3f(+h,-h,+h),
        ofVec3f(-h,-h,-h), ofVec3f(-h,+h,-h), ofVec3f(+h,+h,-h), ofVec3f(+h,-h,-h)
    };
    vboBox.setVertexData(vertices,24,GL_DYNAMIC_DRAW);
    
    static ofVec3f normals[] = {
        ofVec3f(+1,0,0), ofVec3f(+1,0,0), ofVec3f(+1,0,0), ofVec3f(+1,0,0),
        ofVec3f(0,+1,0), ofVec3f(0,+1,0), ofVec3f(0,+1,0), ofVec3f(0,+1,0),
        ofVec3f(0,0,+1), ofVec3f(0,0,+1), ofVec3f(0,0,+1), ofVec3f(0,0,+1),
        ofVec3f(-1,0,0), ofVec3f(-1,0,0), ofVec3f(-1,0,0), ofVec3f(-1,0,0),
        ofVec3f(0,-1,0), ofVec3f(0,-1,0), ofVec3f(0,-1,0), ofVec3f(0,-1,0),
        ofVec3f(0,0,-1), ofVec3f(0,0,-1), ofVec3f(0,0,-1), ofVec3f(0,0,-1)
    };
    vboBox.setNormalData(normals,24,GL_DYNAMIC_DRAW);
    
    static ofVec2f tex[] = {
        ofVec2f(1,0), ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1),
        ofVec2f(1,1), ofVec2f(1,0), ofVec2f(0,0), ofVec2f(0,1),
        ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0), ofVec2f(0,0),
        ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0),
        ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0),
        ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0)
    };
    vboBox.setTexCoordData(tex,24,GL_DYNAMIC_DRAW);
    
    static ofIndexType indices[] = {
        0,1,2, // right top left
        0,2,3, // right bottom right
        4,5,6, // bottom top right
        4,6,7, // bottom bottom left
        8,9,10, // back bottom right
        8,10,11, // back top left
        12,13,14, // left bottom right
        12,14,15, // left top left
        16,17,18, // ... etc
        16,18,19,
        20,21,22,
        20,22,23
    };
    vboBox.setIndexData(indices,36,GL_DYNAMIC_DRAW);
    
    
//    ofVec3f vertices[8];
//    ofIndexType faces[12*3];
//    int vi = 0;
//    vertices[vi].x = -.5;vertices[vi].y = -.5;vertices[vi++].z = .5;
//    vertices[vi].x = .5;vertices[vi].y = -.5;vertices[vi++].z = .5;
//    vertices[vi].x = -.5;vertices[vi].y = .5;vertices[vi++].z = .5;
//    vertices[vi].x = .5;vertices[vi].y = .5;vertices[vi++].z = .5;
//    vertices[vi].x = -.5;vertices[vi].y = -.5;vertices[vi++].z = -.5;
//    vertices[vi].x = .5;vertices[vi].y = -.5;vertices[vi++].z = -.5;
//    vertices[vi].x = -.5;vertices[vi].y = .5;vertices[vi++].z = -.5;
//    vertices[vi].x = .5;vertices[vi].y = .5;vertices[vi++].z = -.5;
//    
//    int fi = 0;
//    //front
//    faces[fi++] = 0;faces[fi++] = 1; faces[fi++] = 2;
//    faces[fi++] = 2;faces[fi++] = 1; faces[fi++] = 3;
//    //back
//    faces[fi++] = 4;faces[fi++] = 6; faces[fi++] = 5;
//    faces[fi++] = 6;faces[fi++] = 5; faces[fi++] = 7;
//    //right
//    faces[fi++] = 1;faces[fi++] = 5; faces[fi++] = 3;
//    faces[fi++] = 3;faces[fi++] = 5; faces[fi++] = 7;
//    //left
//    faces[fi++] = 4;faces[fi++] = 0; faces[fi++] = 6;
//    faces[fi++] = 6;faces[fi++] = 0; faces[fi++] = 2;
//    //top
//    faces[fi++] = 2;faces[fi++] = 3; faces[fi++] = 6;
//    faces[fi++] = 6;faces[fi++] = 3; faces[fi++] = 7;
//    //bottom
//    faces[fi++] = 4;faces[fi++] = 5; faces[fi++] = 0;
//    faces[fi++] = 0;faces[fi++] = 5; faces[fi++] = 1;
//    
//    vboBox.setVertexData(vertices, 8, GL_DYNAMIC_DRAW);
//    vboBox.setIndexData(faces, 12*3, GL_DYNAMIC_DRAW);
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
    glDisable(GL_DEPTH_TEST);
    ofSetColor(255,1);
//    glEnable(GL_DEPTH_TEST);
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
                ofTranslate(i, j, z);
                //ofBox(i, j, z, 1);
                vboBox.drawElements(GL_TRIANGLES, 36);
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