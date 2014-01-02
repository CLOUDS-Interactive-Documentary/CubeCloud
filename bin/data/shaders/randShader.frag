#version 110

const float MIN_AMT = 1./400.;

uniform sampler2DRect inputTex;
uniform float i;
uniform int sel[200];
uniform int type;
uniform float cutoff;
uniform float multiplier;

float rand(vec2 n)
{
    return 0.5 + 0.5 *
    fract(sin(dot(n.xy, vec2(12.9898, 78.233)))* 43758.5453);
}

vec4 inc(vec4 curr){
    bool bInc = false;
    int index = int(floor(gl_FragCoord.y)*100.+floor(gl_FragCoord.x));
    if (type == 0){//randomness is controlled by OF
        for (int j = 0; j < 5; j++){
            if (index == sel[j]){
                bInc = true;
                break;
            } else if (sel[j] == -1){
                break;
            }
        }
    } else if (type == 1){
        float fInc = rand(vec2(i, gl_FragCoord.x+gl_FragCoord.y/100.));//one half is slightly heavier than other
        bInc = (fInc > cutoff);
    } else if (type == 2){
        float fInc = rand(vec2(gl_FragCoord.y, rand(vec2(i, gl_FragCoord.x))));//gives stripes
        bInc = (fInc > cutoff);
    } else if (type == 3){
        bInc = floor(float(index)/1000.) == float(index)/1000.;//useful for testing
    } else if (type == 4){
        bInc = (rand(gl_FragCoord.xy) > .9);//useful for testing GL_NEAREST
    } else if (type == 5){
        float fInc = rand(vec2(i, gl_FragCoord.x/2.+gl_FragCoord.y/200.));//still has 'sections', but seems better
        bInc = (fInc > cutoff);
    }
    
    if (!bInc){
        return curr;
    } else {
        for(int j = 2; j >= 0; j--){
            if (curr[j] < 1.){
                curr[j] += MIN_AMT*multiplier;
                return curr;
            }
        }
    }
    return vec4(0.,0.,0.,0.);
}

void main()
{
    float windowWidth = 100.;
    float windowHeight = 100.;
    
    //the actual random implementation
    //float newR = texture2DRect(inputTex, gl_FragCoord.xy).r + (rand(vec2(i, gl_FragCoord.x+gl_FragCoord.y/100.))>.99 ? .01 : 0.);
    
    //for testing GL_NEAREST
    //float newR = texture2DRect(inputTex, gl_FragCoord.xy).r+(rand(gl_FragCoord.xy)>.9 ? minAmt : 0.);
    
    gl_FragColor = inc(texture2DRect(inputTex, gl_FragCoord.xy));// vec4((newR > 1. ? 0. : newR), 0., 0., 1.);
//    vec4 texel0 = texture(tex0, texCoordVarying);
//    vec4 texel1 = texture(imageMask, texCoordVarying);
//    // first three values are the rgb, fourth is the alpha
//    outputColor = vec4(texel0.rgb, texel0.a * texel1.a);
}