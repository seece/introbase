#version 130
#define SCREEN_X (1280/2)
#define SCREEN_Y (720/2)
uniform float iTime;
uniform sampler2D img;

float buildings, buildings2, sea, seabrite, bust, intro, end, struckfinal, startmove, surface;
const float PI=3.1415926536;

float rand(in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

void pR(inout vec2 p, float a) {
	p = cos(a)*p + sin(a)*vec2(p.y, -p.x);
}

float smootherstep(float a, float b, float r) {
    r = clamp(r, 0.0, 1.0);
    return mix(a, b, r * r * r * (r * (6.0 * r - 15.0) + 10.0));
}

float snoise(in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = rand(i);
    float b = rand(i + vec2(1.0, 0.0));
    float c = rand(i + vec2(0.0, 1.0));
    float d = rand(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners porcentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

// Repeat in three dimensions
vec3 pMod3(inout vec3 p, vec3 size) {
	vec3 c = floor((p + size*0.5)/size);
	p = mod(p + size*0.5, size) - size*0.5;
	return c;
}

vec3 space(vec3 p, float t) {
    vec3 op=p;
    p.y = abs(p.y - buildings*10.0);
    p.z += t*0.5 + t*buildings2*0.5;
    p.z -= pow(0.015*t, 4.0) + startmove*6.0 + buildings*40.0;
    //p.x += sin(t*0.05)*buildings2*16.0;
    
    //p.y = abs(p.y-10.0);
    //vec3 col = abs(sin(p));
    //vec3 col = vec3(1.0, 0.5, 0.0);
    float side = abs(sin(p.x*0.2)*sin(p.z*0.2));
    vec3 red = mix(vec3(1.0, 0.7, 0.1), vec3(0.2, 0.3, 0.9), sea);
    vec3 col = mix(red, vec3(0.1, 0.9, 0.9), side);
    //float thick = snoise(p.xz*4.0 + vec2(t*0.0,t*0.1))+snoise(p.yy*3.0);
    float thick = -0.00;
    float bt = 0.82*buildings;
    bt += ( 1.0*snoise(p.xz*(0.4))) ;
    bt += (p.y*0.02 - 0.2*snoise(p.yy*0.2+p.z));
    bt += cos(p.x*0.5);
    bt += 0.5*snoise(p.yz*10.0);
    
        
    thick += buildings*bt;
    
	//thick += -0.2 + 0.4*sea*snoise(p.yy*0.2);
	
	thick += 0.5*sin(p.y*0.3)*seabrite*abs(sin(t*0.07+1.0)); // TODO fix sync
    thick += (1.0-buildings) * (snoise(p.xz*(2.0) + vec2(t*0.0,t*0.1))+snoise(p.yy*3.0));
    thick += 0.3*sea - 0.3*seabrite;
	thick += 0.3*sign(-op.y+4.9)*struckfinal;
    //thick += sin(p.y/(1.0+p.y));
    
    //p.x += (sin(p.z+t*.5))*.5 * sea;
    //p.y += (sin(p.x+t*.4))*.5 * sea;
    p.xy += 0.5*sin(p.zx*2.0+vec2(t*.5, t*.2))*sea;
    
    float flash = 0.0;//0.5*(1.0+sin(t + 0.2*snoise(p.xx)+0.2*snoise(p.yz)));
    float ofs = pow(thick*1.0 + sin(p.x+t*0.1)*0.1, 2.0) - 0.1*flash;
    vec3 p2=p;
	//vec3 cluster = pMod3(p, vec3(0.5 - 0.3*buildings));
    vec3 cluster = pMod3(p, vec3(0.4));
    
    //vec3 cluster2 = pMod3(p2, vec3(8.0));
    
    vec3 small = col*vec3(3e-3) / (length(p) + ofs);
    //vec3 big = col*vec3(pow(2e-2 / ((length(p2) + ofs)), 1.1));
    //small += max(0.,-sign(op.y))*vec3(0.004)*vec3(1.0, 0.3, 0.1);
    small += max(0.,-sign(op.y))*vec3(0.004)*(1.0-sea);
    //small *= 1.0 + max(0., sign(p.y));
    
    return small;
}

vec3 face(vec3 p, float t) {
    p.x -= 0.25 ;
    p.y -= 5.05;
    p.z -= 2.0;// - struckfinal*0.6 ;
    
    const float H=7.0;
    float a=0.0;
    for (float i=0.;i<1.0;i+=1./H) {
        float angle = (i)*2.*PI + (t - end)*0.5;
		//float angle2 =(i)*2.*PI + PI*0.5;
        float dist = 0.24 + sin(t*.5)*(0.05 + struckfinal*0.04) - 0.295*end;
        vec3 q = p + 1.0*vec3(
			dist*cos(angle*1.0) + 0.0,
			dist*sin(angle*1.0) ,
			0.0					);
        //vec3 q = p + vec3(0.0, 0.0, 0.0);
        a += 0.8e-2/pow(length(q) * H, 1.0);
    }

    return vec3(0.0, 0.5, 1.0)*a;
}

vec3 field(vec3 p, float t) {
    //return mix(max(vec3(0.0), space(p, t)), face(p, t), bust);
    //return space(p, t) + face(p, t) * bust * 0.0;
    return mix(face(p,t), space(p, t), intro+struckfinal*0.1);
}


vec3 march(vec2 uv, float t) {
	vec3 c = vec3(1.0, 0.0, 0.0);
    vec3 origin = vec3(uv - vec2(0.5, 0.25), 1.0);
    origin.xy*=0.7;

    
    #define nice(x) smootherstep(0.0, 1.0, max(0.0, min(1.0, x)))
    
    float orbit = 1.0 - nice((t-50.0)*0.04);
    sea = nice((t-100.0)*0.05);
	seabrite = nice((t-113.0)*0.3);
    buildings2 = 1.0-orbit; // TODO simplify?
    buildings = buildings2-sea;
	startmove = nice((t-7.0)*0.045);
	surface = nice((t-140.0)*0.1);
	
    //float back = nice((t-142.0)*0.08);
    float back = nice((t-159.0)*0.1); //147
    end = nice((t-185.0)*0.2);
    sea -= back; //nice((t-150.0)*0.1);
    intro = nice((t-8.0)*0.1);
    intro -= back;
	surface -= back*0.9;
	
	struckfinal = nice((t-175.0)*0.15);
    
    bust = nice((t-30.0)*0.2);
    
    //intro
    float ryz = orbit*0.4 - 0.2 + buildings*0.15 + 0.5;
    float rxz = orbit*0.7 + sin(t*0.1)*0.1*sea + sea*0.1;
    
    ryz += buildings*(sin(t*0.1)*0.2-0.1) + 0.1 * surface;
   
    rxz += buildings*0.8;
    rxz += cos(t*0.1)*0.3*sea  - 0.2*sea;
    ryz -= 0.4 + 0.4*sea + cos(t*0.1)*0.4*sea;
    float rxy = -0.2*sea;
    
    pR(origin.xy, rxy * intro);
    pR(origin.yz, ryz * intro);
    pR(origin.xz, rxz * intro);
    
    vec3 dir = normalize(origin);
    
    origin.x += 0.25;
    origin.y += 5.0 - sea*7.0;
    
    vec3 p = origin;
    vec3 accum = vec3(0.);
    for (int i=0;i<80;i++) {
        vec3 d = field(p, t);
        accum += d;
            
    	p += dir * 1.0e-3 * max(0.005, 1.0/length(d));
    }
    
    accum *= mix(max(0., 1.0 - 0.1*sqrt(length(p-origin))), 1.0, buildings);
	accum *= 1.0 + surface*abs(sin(length(p-origin) * 0.1))*2.0*cos(p.y*0.6);
    accum /= 1.0+buildings*0.4;
    float boost = pow(max(accum.x, max(accum.y, accum.z)), 2.0);
    return accum + vec3(boost);
}

void main()
{
	float t = iTime;
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy/vec2(SCREEN_X, SCREEN_Y);
    vec2 p = vec2(uv.x, uv.y * (float(SCREEN_Y)/SCREEN_X));

    // Time varying pixel color
    vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
    
    vec2 movement = 1e-4*vec2(cos(t*.2), sin(t*.2));
    vec2 centr = vec2(0.5) + movement;

    
    vec3 old = texture(img, uv ).rgb;
    old += 1.0/255. * rand(uv+vec2(t)) - 0.1/255.0;
    vec2 ncoord = p + vec2(sin(iTime*199.), sin(iTime*238.));
	float noise = snoise(8e2*ncoord);
    
    vec3 stars = pow(march(p, t), vec3(2.0));
    vec3 back = mix(vec3(1.0,0.98,0.99), vec3(0.99, 0.95, 0.95), struckfinal)*old;
    float feedback = 0.96 - buildings * 0.2 - 0.5 + struckfinal*0.04;
    
    vec3 new = feedback*back + (0.2 + buildings*0.3)*stars + 0.0*vec3(noise-0.5);
	//vec3 new = back*0.4 + 0.05*stars;
    new *= 1.0-end-max(0.,3.0-t);
    new = clamp(new, vec3(0.0), vec3(1.0));
    //new = new*0.001 + vec3(uv.x, uv.y, 0.0);
    gl_FragColor = vec4(new*2.0,1.0);
    //gl_FragColor = vec4(uv.x, uv.y, 0.0, 1.0);
}
