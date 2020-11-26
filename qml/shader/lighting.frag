#version 440
layout(std140, binding = 0) uniform buf {
    mat4 qt_Matrix;
    float qt_Opacity;
    float width;
    float height;
    float iTime;
    vec3 iResolution;
};
#define t iTime
#define r iResolution.xy
layout(location = 0) out vec4 fragColor;
void main() {
    vec3 c;
    float l,z=t;
    for(int i=0;i<3;i++) {
        vec2 uv,p=gl_FragCoord.xy/r/2;
        uv=p;
        p-=.5;
        p.x*=r.x/r.y;
        z+=.07;
        l=length(p);
        uv+=p/l*(sin(z)+1.)*abs(sin(l*9.-z*2.));
        c[i]=.01/length(abs(mod(uv,1.)-.5));
    }
    fragColor=vec4(c/l,t);
}

