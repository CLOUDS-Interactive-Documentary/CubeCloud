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
    
    boxShader.load(getVisualSystemDataPath() + "shaders/boxShader");
    randShader.load(getVisualSystemDataPath() + "shaders/randShader");
    //problem with GL_LUMINANCE http://forum.openframeworks.cc/t/offbo-supported-colour-modes/10136
    ofFbo::Settings fboSettings;
    fboSettings.height = maxNumBucketsAcross;
    fboSettings.width = maxNumBucketsAcross;
    fboSettings.maxFilter = GL_NEAREST;
    fboSettings.minFilter = GL_NEAREST;
    fboSettings.wrapModeHorizontal = GL_REPEAT;
    fboSettings.wrapModeVertical = GL_REPEAT;
    fboSettings.internalformat = GL_RGB;//GL_LUMINANCE32F_ARB
    fboSettings.numSamples = 0;
    
    //FROM ofFbo.allocate:
#ifdef TARGET_OPENGLES
	fboSettings.useDepth		= false;
	fboSettings.useStencil		= false;
	//we do this as the fbo and the settings object it contains could be created before the user had the chance to disable or enable arb rect.
    fboSettings.textureTarget	= GL_TEXTURE_2D;
#else
	fboSettings.useDepth		= true;
	fboSettings.useStencil		= true;
	//we do this as the fbo and the settings object it contains could be created before the user had the chance to disable or enable arb rect.
    fboSettings.textureTarget	= ofGetUsingArbTex() ? GL_TEXTURE_RECTANGLE_ARB : GL_TEXTURE_2D;
#endif
    //END FROM
    
    lookupA.allocate(fboSettings);
    lookupB.allocate(fboSettings);
    flip = true;
    
    myCustomCamera.lookAt(ofVec3f(maxNumBucketsAcross/2., maxNumBucketsAcross/2., maxNumBucketsAcross/2.));
    
    //create the box VBO
    //borrowed from ofBox
	float h = .4999;
    //fuck it, brute force...
    ofVec3f vertices[24*10000];
    for(int i = 0, j = 0, k = .5, m = .5; i < 10000; i++, k+=1){
        if (k >= 100){m+=1; k = .5;}
        vertices[j++] = ofVec3f(k+h,m-h,+h); vertices[j++] = ofVec3f(k+h,m-h,-h); vertices[j++] = ofVec3f(k+h,m+h,-h); vertices[j++] = ofVec3f(k+h,m+h,+h);
        vertices[j++] = ofVec3f(k+h,m+h,+h); vertices[j++] = ofVec3f(k+h,m+h,-h); vertices[j++] = ofVec3f(k-h,m+h,-h); vertices[j++] = ofVec3f(k-h,m+h,+h);
        vertices[j++] = ofVec3f(k+h,m+h,+h); vertices[j++] = ofVec3f(k-h,m+h,+h); vertices[j++] = ofVec3f(k-h,m-h,+h); vertices[j++] = ofVec3f(k+h,m-h,+h);
        vertices[j++] = ofVec3f(k-h,m-h,+h); vertices[j++] = ofVec3f(k-h,m+h,+h); vertices[j++] = ofVec3f(k-h,m+h,-h); vertices[j++] = ofVec3f(k-h,m-h,-h);
        vertices[j++] = ofVec3f(k-h,m-h,+h); vertices[j++] = ofVec3f(k-h,m-h,-h); vertices[j++] = ofVec3f(k+h,m-h,-h); vertices[j++] = ofVec3f(k+h,m-h,+h);
        vertices[j++] = ofVec3f(k-h,m-h,-h); vertices[j++] = ofVec3f(k-h,m+h,-h); vertices[j++] = ofVec3f(k+h,m+h,-h); vertices[j++] = ofVec3f(k+h,m-h,-h);
    }
    vboBox.setVertexData(vertices,24*10000,GL_DYNAMIC_DRAW);
//    ofVec3f vertices[] = {
//        ofVec3f(+h,-h,+h), ofVec3f(+h,-h,-h), ofVec3f(+h,+h,-h), ofVec3f(+h,+h,+h),
//        ofVec3f(+h,+h,+h), ofVec3f(+h,+h,-h), ofVec3f(-h,+h,-h), ofVec3f(-h,+h,+h),
//        ofVec3f(+h,+h,+h), ofVec3f(-h,+h,+h), ofVec3f(-h,-h,+h), ofVec3f(+h,-h,+h),
//        ofVec3f(-h,-h,+h), ofVec3f(-h,+h,+h), ofVec3f(-h,+h,-h), ofVec3f(-h,-h,-h),
//        ofVec3f(-h,-h,+h), ofVec3f(-h,-h,-h), ofVec3f(+h,-h,-h), ofVec3f(+h,-h,+h),
//        ofVec3f(-h,-h,-h), ofVec3f(-h,+h,-h), ofVec3f(+h,+h,-h), ofVec3f(+h,-h,-h)
//    };
//    vboBox.setVertexData(vertices,24,GL_DYNAMIC_DRAW);
    
    //don't need normals unless we do lighting?
//    static ofVec3f normals[] = {
//        ofVec3f(+1,0,0), ofVec3f(+1,0,0), ofVec3f(+1,0,0), ofVec3f(+1,0,0),
//        ofVec3f(0,+1,0), ofVec3f(0,+1,0), ofVec3f(0,+1,0), ofVec3f(0,+1,0),
//        ofVec3f(0,0,+1), ofVec3f(0,0,+1), ofVec3f(0,0,+1), ofVec3f(0,0,+1),
//        ofVec3f(-1,0,0), ofVec3f(-1,0,0), ofVec3f(-1,0,0), ofVec3f(-1,0,0),
//        ofVec3f(0,-1,0), ofVec3f(0,-1,0), ofVec3f(0,-1,0), ofVec3f(0,-1,0),
//        ofVec3f(0,0,-1), ofVec3f(0,0,-1), ofVec3f(0,0,-1), ofVec3f(0,0,-1)
//    };
//    vboBox.setNormalData(normals,24,GL_DYNAMIC_DRAW);
    
    //don't need texture coords unless we want to texture it?
//    static ofVec2f tex[] = {
//        ofVec2f(1,0), ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1),
//        ofVec2f(1,1), ofVec2f(1,0), ofVec2f(0,0), ofVec2f(0,1),
//        ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0), ofVec2f(0,0),
//        ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0),
//        ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0),
//        ofVec2f(0,0), ofVec2f(0,1), ofVec2f(1,1), ofVec2f(1,0)
//    };
//    vboBox.setTexCoordData(tex,24,GL_DYNAMIC_DRAW);
    
    static ofIndexType indices[36*10000];
    for(int i = 0, j = 0, k = 0; i < 10000; i++, k+=24){
        indices[j++] = 0+k; indices[j++] = 1+k; indices[j++] = 2+k;
        indices[j++] = 0+k; indices[j++] = 2+k; indices[j++] = 3+k;
        indices[j++] = 4+k; indices[j++] = 5+k; indices[j++] = 6+k;
        indices[j++] = 4+k; indices[j++] = 6+k; indices[j++] = 7+k;
        indices[j++] = 8+k; indices[j++] = 9+k; indices[j++] = 10+k;
        indices[j++] = 8+k; indices[j++] = 10+k; indices[j++] = 11+k;
        indices[j++] = 12+k; indices[j++] = 13+k; indices[j++] = 14+k;
        indices[j++] = 12+k; indices[j++] = 14+k; indices[j++] = 15+k;
        indices[j++] = 16+k; indices[j++] = 17+k; indices[j++] = 18+k;
        indices[j++] = 16+k; indices[j++] = 18+k; indices[j++] = 19+k;
        indices[j++] = 20+k; indices[j++] = 21+k; indices[j++] = 22+k;
        indices[j++] = 20+k; indices[j++] = 22+k; indices[j++] = 23+k;
    }
    vboBox.setIndexData(indices,36*10000,GL_DYNAMIC_DRAW);
//    static ofIndexType indices[] = {
//        0,1,2, // right top left
//        0,2,3, // right bottom right
//        4,5,6, // bottom top right
//        4,6,7, // bottom bottom left
//        8,9,10, // back bottom right
//        8,10,11, // back top left
//        12,13,14, // left bottom right
//        12,14,15, // left top left
//        16,17,18, // ... etc
//        16,18,19,
//        20,21,22,
//        20,22,23
//    };
//    vboBox.setIndexData(indices,36,GL_DYNAMIC_DRAW);
    
    
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
    lookupA.begin();
    ofClear(0, 0, 0, 0);
    lookupA.end();  
    
    lookupB.begin();
    ofClear(0, 0, 0, 0);
    lookupB.end();
}

void CubeCloud::selfEnd()
{
    
}

void CubeCloud::selfExit()
{
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
    ofFbo* from;
    ofFbo* to;
    randShader.begin();
    if (flip){
        from = &lookupA;
        to = &lookupB;
    } else {//flop
        from = &lookupB;
        to = &lookupA;
    }
    
//    from->getTextureReference().bind();
    randShader.setUniformTexture("inputTex", from->getTextureReference(), 1);
    randShader.setUniform1f("i", ofRandomf());
    int sel[] = {55,10, 999, 8493, 2304};
    randShader.setUniform1iv("sel", sel, 5);
    to->begin();
    
    //TODO: stuff
    ofClear(0, 0, 0, 0);
    //ofSetColor(0, 0, 0, 0);
    ofRect(0, 0, to->getWidth(), to->getHeight());
    
    from->getTextureReference().unbind();
    to->end();
    randShader.end();
    
    flip = !flip;
}

void CubeCloud::selfDraw()
{
	boxShader.begin();
    boxShader.setUniformTexture("lookup", (flip ? lookupB : lookupA).getTextureReference(), 1);
    glDisable(GL_DEPTH_TEST);
    //ofSetColor(255,1);
    vboBox.drawElements(GL_TRIANGLES, 36*10000);
	boxShader.end();
}

void CubeCloud::selfDrawBackground()
{
    ofFbo* from;
    ofFbo* to;
    if (flip){
        to = &lookupB;
    } else {//flop
        to = &lookupA;
    }
    
    to->draw(0, 0);

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