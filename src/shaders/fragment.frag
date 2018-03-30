#version 130
#define SCREEN_X (1280)
#define SCREEN_Y (720)
uniform float iTime;
uniform sampler2D img;

float buildings, buildings2, sea, seabrite, bust, intro, end, struckfinal, startmove, surface;
float zofs;
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


float sa, sb, sc, sd;
vec2 su;

float snoise(in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    sa = rand(i);
    sb = rand(i + vec2(1.0, 0.0));
    sc = rand(i + vec2(0.0, 1.0));
    sd = rand(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    su = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 corners
    return mix(sa, sb, su.x) +
            (sc - sa)* su.y * (1.0 - su.x) +
            (sd - sb) * su.x * su.y;
}

vec3 cc;

// Repeat in three dimensions
/*vec3 pMod3(inout vec3 p, vec3 size) {
	cc = floor((p + size*0.5)/size);
	p = mod(p + size*0.5, size) - size*0.5;
	return cc;
}*/

vec3 op, small;
float side, thick, bt, ofs;

vec3 space(vec3 p, float t) {
    op=p;
    p.y = abs(p.y - buildings*10.0);
	p.z += zofs;
	side = abs(sin(p.x*0.2)*sin(p.z*0.2));

    thick = -0.00;
    bt = 0.82*buildings;
    bt += ( 1.0*snoise(p.xz*(0.4))) ;
    bt += (p.y*0.02 - 0.2*snoise(p.yy*0.2+p.z));
    bt += cos(p.x*0.5);
    bt += 0.5*snoise(p.yz*10.0);
    
    thick += buildings*bt;
    
	//thick += -0.2 + 0.4*sea*snoise(p.yy*0.2);
	
	thick += 0.6*sin(p.y*0.3) *seabrite*abs(sin(t*0.06-1.0)); // TODO fix sync
    thick += (1.0-buildings) * (snoise(p.xz*(2.0) + vec2(t*0.0,t*0.1))+snoise(p.yy*3.0));
    thick += 0.3*sea - 0.35*seabrite;
	thick += 0.3*sign(-op.y+4.9)*struckfinal;
    //thick += sin(p.y/(1.0+p.y));
    
    //p.x += (sin(p.z+t*.5))*.5 * sea;
    //p.y += (sin(p.x+t*.4))*.5 * sea;
    p.xy += 0.5*sin(p.zx*2.0+vec2(t*.5, t*.2))*sea;
    
    ofs = pow(thick*1.0 + sin(p.x+t*0.1)*0.1, 2.0);
	
	/*vec3 pMod3(inout vec3 p, vec3 size) {
	cc = floor((p + size*0.5)/size);
	p = mod(p + size*0.5, size) - size*0.5;
	return cc;
	}*/
	//cc = floor((p + size*0.5)/size);
	vec3 size = vec3(0.4);
	p = mod(p + size*0.5, size) - size*0.5;
    //pMod3(p, vec3(0.4));

    
    small = mix(
		mix(vec3(1.0, 0.7, 0.1), vec3(0.3, 0.4, 0.6), sea), 
		vec3(0.1, 0.9, 0.9), side )*vec3(3e-3) / (length(p) + ofs);
    small += max(0.,-sign(op.y))*vec3(0.004)*(1.0-sea);
    
    return small;
}

float a, angle, dist, ii;

vec3 face(vec3 p, float t) {
    p.x -= 0.25 ;
    p.y -= 5.05;
    p.z -= 2.0;// - struckfinal*0.6 ;
    
    a=0.0;
    for (ii=0.;ii<1.0;ii+=1./7.0) {
        angle = (ii)*2.*PI + (t - end)*0.5;
		//float angle2 =(i)*2.*PI + PI*0.5;
        dist = 0.24 + sin(t*.5)*(0.05 + struckfinal*0.04) - 0.295*end;
        vec3 q = p + 1.0*vec3(
			dist*cos(angle*1.0) + 0.0,
			dist*sin(angle*1.0) ,
			0.0					);
        //vec3 q = p + vec3(0.0, 0.0, 0.0);
        a += 0.8e-2/pow(length(q) * 7.0, 1.0);
    }

    return vec3(0.0, 0.5, 1.0)*a;
}

vec3 field(vec3 p, float t) {
    //return mix(max(vec3(0.0), space(p, t)), face(p, t), bust);
    //return space(p, t) + face(p, t) * bust * 0.0;
    return mix(face(p,t), space(p, t), intro+struckfinal*0.1);
}

vec3 origin;
float rxy, ryz, rxz, orbit, back;
vec3 p, accum, d;
int iii;

vec3 march(vec2 uv, float t) {
    origin = vec3(uv - vec2(0.5, 0.25), 1.0);
    origin.xy*=0.7;
    
    #define ni(x) smootherstep(0.0, 1.0, max(0.0, min(1.0, x)))
    
    orbit = 1.0 - ni((t-50.0)*0.04);
    sea = ni((t-100.0)*0.05);
	seabrite = ni((t-113.0)*0.3);
    buildings2 = 1.0-orbit; // TODO simplify?
    buildings = buildings2-sea;
	startmove = ni((t-7.0)*0.045);
	surface = ni((t-140.0)*0.1);
	
    //float back = ni((t-142.0)*0.08);
    back = ni((t-159.0)*0.1); //147
    end = ni((t-185.0)*0.2);
    sea -= back; //ni((t-150.0)*0.1);
    intro = ni((t-8.0)*0.1);
    intro -= back;
	surface -= back*0.9;
	
	struckfinal = ni((t-175.0)*0.15);
    
    bust = ni((t-30.0)*0.2);
	
	zofs = t*0.5 + t*buildings2*0.5      - pow(0.015*t, 4.0) - startmove*6.0 - buildings*40.0;;
    
    //intro
    ryz = orbit*0.4 - 0.2 + buildings*0.15 + 0.5;
    rxz = orbit*0.7 + sin(t*0.1)*0.1*sea + sea*0.1;
    
    ryz += buildings*(sin(t*0.1)*0.2-0.1) + 0.1 * surface;
   
    rxz += buildings*0.8;
    rxz += cos(t*0.1)*0.3*sea  - 0.2*sea;
    ryz -= 0.4 + 0.4*sea + cos(t*0.1)*0.4*sea;
    rxy = -0.2*sea;
    
    pR(origin.xy, rxy * intro);
    pR(origin.yz, ryz * intro);
    pR(origin.xz, rxz * intro);
    
    vec3 dir = normalize(origin);
    
    origin.x += 0.25;
    origin.y += 5.0 - sea*7.0;
    
    p = origin;
    accum = vec3(0.);
    for (iii=0;iii<80;iii++) {
        d = field(p, t);
        accum += d;
            
    	p += dir * 1.0e-3 * max(0.005, 1.0/length(d));
    }
    
    accum *= mix(max(0., 1.0 - 0.1*sqrt(length(p-origin))), 1.0, buildings);
	accum *= 1.0 + surface*abs(sin(length(p-origin) * 0.1))*2.0*cos(p.y*0.6);
    accum /= 1.0+buildings*0.4;
    return accum + vec3(pow(max(accum.x, max(accum.y, accum.z)), 2.0)); // boost the saturated colors to white
}

float t;
vec2 uv, pu, movement, centr;
vec3 stars, bg, new;
float noise, feedback;

void main()
{
	t = iTime;
    // Normalized pixel coordinates (from 0 to 1)
    uv = gl_FragCoord.xy/vec2(SCREEN_X, SCREEN_Y);
    pu = vec2(uv.x, uv.y * (float(SCREEN_Y)/SCREEN_X));

    // Time varying pixel color
    vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
    
    movement = 1e-4*vec2(cos(t*.2), sin(t*.2));
    centr = vec2(0.5) + movement;

    
    vec3 old = texture(img, uv ).rgb;
    old += 1.0/255. * rand(uv+vec2(t)) - 0.1/255.0;
    vec2 ncoord = pu + vec2(sin(iTime*199.), sin(iTime*238.));
	noise = snoise(8e2*ncoord);
    
    stars = pow(march(pu, t), vec3(2.0));
    feedback = 0.96 - buildings * 0.2 - 0.5 + struckfinal*0.04;
    
    new = feedback*(mix(vec3(1.0,0.98,0.99), vec3(0.99, 0.95, 0.95), struckfinal)*old) + (0.2 + buildings*0.3)*stars + 0.0*vec3(noise-0.5);
	//vec3 new = back*0.4 + 0.05*stars;
    new *= 1.0-end-max(0.,3.0-t);
    new = clamp(new, vec3(0.0), vec3(1.0));
    //new = new*0.001 + vec3(uv.x, uv.y, 0.0);
    gl_FragColor = vec4(new*2.0,1.0);
    //gl_FragColor = vec4(uv.x, uv.y, 0.0, 1.0);
}
