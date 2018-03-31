const char *fragment_frag =
 "#version 130\n"
 "#define SCREEN_X (1280/2)\n"
 "#define SCREEN_Y (720/2)\n"
 "uniform float iTime;\n"
 "uniform sampler2D img;\n"
 "float v,f,y,s,m,x,z,c,r,e,n;\n"
 "const float i=3.14159;\n"
 "float t(in vec2 x)\n"
 "{\n"
   "return fract(sin(dot(x.xy,vec2(12.9898,78.233)))*43758.5);\n"
 "}\n"
 "void t(inout vec2 y,float x)\n"
 "{\n"
   "y=cos(x)*y+sin(x)*vec2(y.y,-y.x);\n"
 "}\n"
 "float smootherstep(float s,float f,float y)\n"
 "{\n"
   "return y=clamp(y,0.,1.),mix(s,f,y*y*y*(y*(6.*y-15.)+10.));\n"
 "}\n"
 "float l,g,S,u;\n"
 "vec2 a;\n"
 "float p(in vec2 x)\n"
 "{\n"
   "vec2 y=floor(x),f=fract(x);\n"
   "l=t(y);\n"
   "g=t(y+vec2(1.,0.));\n"
   "S=t(y+vec2(0.,1.));\n"
   "u=t(y+vec2(1.,1.));\n"
   "a=f*f*(3.-2.*f);\n"
   "return mix(l,g,a.x)+(S-l)*a.y*(1.-a.x)+(u-g)*a.x*a.y;\n"
 "}\n"
 "vec3 o;\n"
 "vec3 p(inout vec3 y,vec3 x)\n"
 "{\n"
   "return o=floor((y+x*.5)/x),y=mod(y+x*.5,x)-x*.5,o;\n"
 "}\n"
 "vec3 d,E;\n"
 "float Y,X,C,h;\n"
 "vec3 w(vec3 x,float f)\n"
 "{\n"
   "return d=x,x.y=abs(x.y-v*10.),x.z+=n,Y=abs(sin(x.x*.2)*sin(x.z*.2)),\n"
   "X=0.,C=.82*v,C+=p(x.xz*.4),C+=x.y*.02-.2*p(x.yy*.2+x.z),C+=cos(x.x*.5),C+=.5*p(x.yz*10.),X+=v*C,X+=.6*sin(x.y*.3)*s*abs(sin(f*.06-1.)),\n"
   "X+=(1.-v)*(p(x.xz*2.+vec2(0.,f*.1))+p(x.yy*3.)),X+=.3*y-.35*s,X+=.3*sign(-d.y+4.9)*c,\n"
   "\n"
   "x.xy+=.5*sin(x.zx*2.+vec2(f*.5,f*.2))*y,h=pow(X+sin(x.x+f*.1)*.1,2.),\n"
   "\n"
   "\n"
   "\n"
   "p(x,vec3(.4)),\n"
   "E=mix(mix(vec3(1.,.7,.1),vec3(.3,.4,.6),y),vec3(.1,.9,.9),Y)*vec3(.003)/(length(x)+h),\n"
   "E+=max(0.,-sign(d.y))*vec3(.004)*(1.-y),E;\n"
 "}\n"
 "float R,N,T,b;\n"
 "vec3 F(vec3 x,float y)\n"
 "{\n"
   "x.x-=.25;\n"
   "x.y-=5.05;\n"
   "x.z-=2.;\n"
   "R=0.;\n"
   "for(b=0.;b<1.;b+=1./7.)\n"
     "{\n"
       "N=b*2.*i+(y-z)*.5;\n"
       "T=.24+sin(y*.5)*(.05+c*.04)-.295*z;\n"
       "vec3 f=x+vec3(T*cos(N),T*sin(N),0.);\n"
       "R+=.008/pow(length(f)*7.,1.);\n"
     "}\n"
   "return vec3(0.,.5,1.)*R;\n"
 "}\n"
 "vec3 D(vec3 y,float f)\n"
 "{\n"
   "return mix(F(y,f),w(y,f),x+c*.1);\n"
 "}\n"
 "vec3 q;\n"
 "float Z,W,V,U,Q;\n"
 "vec3 P,O,M;\n"
 "int L;\n"
 "vec3 K(vec2 S,float ac)\n"
 "{\n"
   "q=vec3(S-vec2(.5,.25),1.);\n"
   "q.xy*=.7;\n"
   "\n#define ni(x)smootherstep(0.0,1.0,max(0.0,min(1.0,x)))\n\n"
   "U=1.-ni((ac-50.)*.04);\n"
   "y=ni((ac-100.)*.05);\n"
   "s=ni((ac-113.)*.3);\n"
   "f=1.-U;\n"
   "v=f-y;\n"
   "r=ni((ac-7.)*.045);\n"
   "e=ni((ac-140.)*.1);\n"
   "Q=ni((ac-159.)*.1);\n"
   "z=ni((ac-185.)*.2);\n"
   "y-=Q;\n"
   "x=ni((ac-8.)*.1);\n"
   "x-=Q;\n"
   "e-=Q*.9;\n"
   "c=ni((ac-175.)*.15);\n"
   "m=ni((ac-30.)*.2);\n"
   "n=ac*.5+ac*f*.5-pow(.015*ac,4.)-r*6.-v*40.;\n"
   "W=U*.4-.2+v*.15+.5;\n"
   "V=U*.7+sin(ac*.1)*.1*y+y*.1;\n"
   "W+=v*(sin(ac*.1)*.2-.1)+.1*e;\n"
   "V+=v*.8;\n"
   "V+=cos(ac*.1)*.3*y-.2*y;\n"
   "W-=.4+.4*y+cos(ac*.1)*.4*y;\n"
   "Z=-.2*y;\n"
   "t(q.xy,Z*x);\n"
   "t(q.yz,W*x);\n"
   "t(q.xz,V*x);\n"
   "vec3 j=normalize(q);\n"
   "q.x+=.25;\n"
   "q.y+=5.-y*7.;\n"
   "P=q;\n"
   "O=vec3(0.);\n"
   "for(L=0;L<80;L++)\n"
     "M=D(P,ac),O+=M,P+=j*.001*max(.005,1./length(M));\n"
   "O*=mix(max(0.,1.-.1*sqrt(length(P-q))),1.,v);\n"
   "O*=1.+e*abs(sin(length(P-q)*.1))*2.*cos(P.y*.6);\n"
   "O/=1.+v*.4;\n"
   "return O+vec3(pow(max(O.x,max(O.y,O.z)),2.));\n"
 "}\n"
 "float J;\n"
 "vec2 I,H,G,B;\n"
 "vec3 A,k,j;\n"
 "float ab,ac;\n"
 "void D()\n"
 "{\n"
   "J=iTime;\n"
   "I=gl_FragCoord.xy/vec2(SCREEN_X,SCREEN_Y);\n"
   "H=vec2(I.x,I.y*(float(SCREEN_Y)/SCREEN_X));\n"
   "vec3 y=.5+.5*cos(iTime+I.xyx+vec3(0,2,4));\n"
   "G=.0001*vec2(cos(J*.2),sin(J*.2));\n"
   "B=vec2(.5)+G;\n"
   "vec3 x=texture(img,I).xyz;\n"
   "x+=1./255.*t(I+vec2(J))-.1/255.;\n"
   "vec2 f=H+vec2(sin(iTime*199.),sin(iTime*238.));\n"
   "ab=p(800.*f);\n"
   "A=pow(K(H,J),vec3(2.));\n"
   "ac=.96-v*.2-.5+c*.04;\n"
   "j=ac*(mix(vec3(1.,.98,.99),vec3(.99,.95,.95),c)*x)+(.2+v*.3)*A;\n"
   "j*=1.-z-max(0.,3.-J);\n"
   "j=clamp(j,vec3(0.),vec3(1.));\n"
   "gl_FragColor=vec4(j*2.,1.);\n"
 "}";