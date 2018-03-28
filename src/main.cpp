// custom build and feature flags
#ifdef DEBUG
	#define OPENGL_DEBUG        1
	#define FULLSCREEN          0
	#define DESPERATE           0
	#define BREAK_COMPATIBILITY 0
#else
	#define OPENGL_DEBUG        0
	#define FULLSCREEN          1
	#define DESPERATE           0
	#define BREAK_COMPATIBILITY 0
#endif

#define TWO_PASS    0
#define USE_MIPMAPS 0
#define USE_AUDIO   1
#define NO_UNIFORMS 0

#include "definitions.h"
#if OPENGL_DEBUG
	#include "debug.h"
#else
	#define CHECK_ERRORS() // TODO this should be defined inside debug.h
#endif

#define GLSL(version, shader)  "#version " #version "\n" #shader

#include "glext.h"
#pragma data_seg(".shader") 
const char *fragment_frag = R"END(
#version 130
#define SCREEN_X (1280/2)
#define SCREEN_Y (720/2)
uniform float iTime;
uniform sampler2D img;

float buildings, buildings2, sea, bust, intro, end;
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
    r = r * r * r * (r * (6.0 * r - 15.0) + 10.0);
    return mix(a, b, r);
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
    p.z -= pow(0.015*t, 4.0);
    
    float side = abs(sin(p.x*0.2)*sin(p.z*0.2));
    vec3 red = mix(vec3(1.0, 0.7, 0.1), vec3(0.05, 0.2, 0.9), sea);
    vec3 col = mix(red, vec3(0.1, 0.9, 0.9), side);
    //float thick = snoise(p.xz*4.0 + vec2(t*0.0,t*0.1))+snoise(p.yy*3.0);
    float thick = -0.05;
    float bt = 0.85*buildings;
    bt += ( 1.0*snoise(p.xz*(0.4))) ;
    bt += (p.y*0.02 - 0.2*snoise(p.yy*0.2+p.z));
    bt += cos(p.x*0.5);
    bt += 0.5*snoise(p.yz*10.0);
    
        
    thick += buildings*bt;
    
    thick += (1.0-buildings) * (snoise(p.xz*(2.0) + vec2(t*0.0,t*0.1))+snoise(p.yy*3.0));
    thick -= 0.0*sea;
    
    p.xy += 0.5*sin(p.zx*2.0+vec2(t*.5, t*.2))*sea;
    
    float flash = 0.0;//0.5*(1.0+sin(t + 0.2*snoise(p.xx)+0.2*snoise(p.yz)));
    float ofs = pow(thick*1.0 + sin(p.x+t*0.1)*0.1, 2.0) - 0.1*flash;
    vec3 p2=p;
    vec3 cluster = pMod3(p, vec3(0.4));
    
    vec3 small = col*vec3(3e-3) / (length(p) + ofs);
    small += max(0.,-sign(op.y))*vec3(0.004)*(1.0-sea);
    
    return small;
}

vec3 face(vec3 p, float t) {
    p.x -= 0.2;
    p.y -= 5.0;
    p.z -= 2.0;
    
    const float H=7.0;
    float a=0.0;
    for (float i=0.;i<1.0;i+=1./H) {
        float angle = (i)*2.*PI + t*0.5;
        float dist = 0.2;
        vec3 q = p + 1.0*vec3(dist*cos(angle*1.1), dist*sin(angle*1.0), 0.0);
        //vec3 q = p + vec3(0.0, 0.0, 0.0);
        a += 0.8e-2/pow(length(q) * H, 1.0);
    }

    return vec3(0.0, 0.5, 1.0)*a;
}

vec3 field(vec3 p, float t) {
    return mix(face(p,t), space(p, t), intro);
}


vec3 march(vec2 uv, float t) {
	vec3 c = vec3(1.0, 0.0, 0.0);
    vec3 origin = vec3(uv - vec2(0.5, 0.25), 1.0);
    origin.xy*=0.7;

    #define nice(x) smootherstep(0.0, 1.0, max(0.0, min(1.0, x)))
    
    float orbit = 1.0 - nice((t-40.0)*0.025);
    sea = nice((t-100.0)*0.05);
    buildings2 = 1.0-orbit; // TODO simplify?
    buildings = buildings2-sea;
	
    float back = nice((t-155.0)*0.1);
    end = nice((t-170.0)*0.1);
    sea -= back; //nice((t-150.0)*0.1);
    intro = nice((t-3.0)*0.05);
    intro -= back;
    
    bust = nice((t-30.0)*0.2);
    
    //intro
    float ryz = orbit*0.4 - 0.2 + buildings*0.15 + 0.5;
    float rxz = orbit*0.7 + sin(t*0.1)*0.1*sea + sea*0.1;
    
    ryz += buildings*(sin(t*0.1)*0.2-0.1);
   
    rxz += buildings*0.8;
    rxz += cos(t*0.1)*0.3*sea + 0.2*sea;
    ryz -= 0.4 + 0.4*sea + cos(t*0.1)*0.4*sea;
    float rxy = 0.5*sea;
    
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
    accum /= 1.0+buildings*0.4;
    float boost = pow(max(accum.x, max(accum.y, accum.z)), 2.0);
    return accum + vec3(boost);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	float t = iTime;
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy/vec2(SCREEN_X, SCREEN_Y);
    vec2 p = vec2(uv.x, uv.y * (float(SCREEN_Y)/SCREEN_X));

    // Time varying pixel color
    vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));
    
    vec2 movement = 1e-4*vec2(cos(t*.2), sin(t*.2));
    vec2 centr = vec2(0.5) + movement;
      
    vec2 zoomed_uv = (uv - centr)*1.0+vec2(0.5);
	//pR(zoomed_uv, 0.04);
    
    vec3 old = texture(img, zoomed_uv ).rgb;
    old = floor(old*255.)/255.0; // DEBUG simulate quantization
    old += 1.0/255. * rand(uv+vec2(t)) - 0.1/255.0;
    vec2 ncoord = p + vec2(sin(iTime*199.), sin(iTime*238.));
	float noise = snoise(8e2*ncoord);
    
    vec3 stars = pow(march(p, t), vec3(2.0));
    vec3 back = vec3(1.0,0.98,0.99)*old;
    float feedback = 0.98 - buildings * 0.03 - 0.5;
    
    vec3 new = feedback*back + 0.1*stars + 0.0*vec3(noise-0.5);
    new *= 1.0-end;
    new = clamp(new, vec3(0.0), vec3(1.0));
    
    gl_FragColor = vec4(new*2.0,1.0);
}
)END";
//#include "shaders/fragment.inl"
#if TWO_PASS
	#pragma data_seg(".shader") 
	#include "shaders/post.inl"
#endif

static float timeInTicks;

void WINAPI threadDummy(void* param) {
	/* for (int i = 0; i < 44100 * 2; i++) {
		Oidos_MusicBuffer[i].left = i * 9000;
		Oidos_MusicBuffer[i].right = i * 9990;
	} */
	Oidos_GenerateMusic();
	int a = 0;
	a += 1;
}

#include <cstdio>

#ifndef EDITOR_CONTROLS
void entrypoint(void)
#else
#include "song.h"
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#endif
{
	// initialize window
	#if FULLSCREEN
		ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN);
		ShowCursor(0);
		const HDC hDC = GetDC(CreateWindow((LPCSTR)0xC018, 0, WS_POPUP | WS_VISIBLE, 0, 0, XRES, YRES, 0, 0, 0, 0));
	#else
		#ifdef EDITOR_CONTROLS
			HWND window = CreateWindow("static", 0, WS_POPUP | WS_VISIBLE, 0, 0, XRES, YRES, 0, 0, 0, 0);
			HDC hDC = GetDC(window);
		#else
			HDC hDC = GetDC(CreateWindow("static", 0, WS_POPUP | WS_VISIBLE, 0, 0, XRES, YRES, 0, 0, 0, 0));
		#endif
	#endif	

	// initalize opengl
	SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd);
	wglMakeCurrent(hDC, wglCreateContext(hDC));
	
	#if 0
	PID_QUALIFIER int pid = ((PFNGLCREATESHADERPROGRAMVPROC)wglGetProcAddress("glCreateShaderProgramv"))(GL_FRAGMENT_SHADER, 1, &fragment_frag);
	#else
	#define glCreateShader ((PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader"))
	#define glShaderSource ((PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource"))
	#define glCompileShader ((PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader"))
	#define glCreateProgram ((PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram"))
	#define glAttachShader ((PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader"))
	#define glLinkProgram ((PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram"))
	#define glDetachShader ((PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader"))
	#define glDeleteShader ((PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader"))
	#define glGetShaderiv ((PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv"))
	GLuint shader = glCreateShader(GL_FRAGMENT_SHADER); CHECK_ERRORS();
	PID_QUALIFIER int pid = glCreateProgram(); CHECK_ERRORS();
	int lens = 1;
	glShaderSource(shader, NULL, &fragment_frag, &lens); CHECK_ERRORS();
	glCompileShader(shader); CHECK_ERRORS();
	GLint compiled = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled); CHECK_ERRORS();
	char info[2048];
	((PFNGLGETSHADERINFOLOGPROC) wglGetProcAddress("glGetShaderInfoLog"))(shader, 2047, NULL, (char*)info);

	glAttachShader(pid, shader); CHECK_ERRORS();
	glLinkProgram(pid);  CHECK_ERRORS();
	glDetachShader(pid, shader); CHECK_ERRORS();
	GLint linked = -1;
	((PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv"))(pid, GL_LINK_STATUS, &linked);
	char info2[2048];
	((PFNGLGETPROGRAMINFOLOGPROC) wglGetProcAddress("glGetProgramInfoLog"))(pid, 2047, NULL, (char*)info2);
	#endif

	#if TWO_PASS
		PID_QUALIFIER int pi2 = ((PFNGLCREATESHADERPROGRAMVPROC)wglGetProcAddress("glCreateShaderProgramv"))(GL_FRAGMENT_SHADER, 1, &post_frag);
	#endif

	#if OPENGL_DEBUG
		shaderDebug(fragment_frag, FAIL_KILL);
		#if TWO_PASS
			shaderDebug(post_frag, FAIL_KILL);
		#endif
	#endif
	CHECK_ERRORS();

	// initialize sound
	#ifndef EDITOR_CONTROLS
		#if USE_AUDIO
			Oidos_FillRandomData();
			sample before = Oidos_MusicBuffer[20*44100];
			HANDLE result = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)threadDummy, 0, 0, 0);

			//Oidos_GenerateMusic();
			//Sleep(30000);

			//Oidos_StartMusic();

			//sample after = Oidos_MusicBuffer[20*44100];
			// FILE* fp = fopen("file.raw", "rw");
			// fwrite(Oidos_MusicBuffer, sizeof(sample), 44100 * 30, fp);
			// fclose(fp);

			//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)_4klang_render, lpSoundBuffer, 0, 0);
			//waveOutOpen(&hWaveOut, WAVE_MAPPER, &WaveFMT, NULL, 0, CALLBACK_NULL);
			//waveOutPrepareHeader(hWaveOut, &WaveHDR, sizeof(WaveHDR));
			//waveOutWrite(hWaveOut, &WaveHDR, sizeof(WaveHDR));
		#endif
	#else
		long double position = 0.0;
		song track(L"audio.wav");
		track.play();
		start = timeGetTime();
	#endif

	// main loop
	do
	{
		#if !(DESPERATE)
			// do minimal message handling so windows doesn't kill your application
			// not always strictly necessary but increases compatibility a lot
			MSG msg;
			PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
		#endif

			{
				GLint result = -1;
				((PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv"))(pid, GL_ATTACHED_SHADERS, &result);
				char info[2048];
				((PFNGLGETPROGRAMINFOLOGPROC) wglGetProcAddress("glGetProgramInfoLog"))(pid, 2047, NULL, (char*)info);
				info[2047] = '\0';
			}

		// render with the primary shader
		((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram"))(pid);
		CHECK_ERRORS();

		glBindTexture(GL_TEXTURE_2D, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		((PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture"))(GL_TEXTURE0);
		CHECK_ERRORS();

		const GLuint imgLoc = ((PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation"))(pid, "img");
		((PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i"))(imgLoc, 0);
		CHECK_ERRORS();
		// copy GL_BACK -> GL_TEXTURE_2D
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, XRES, YRES, 0);
		CHECK_ERRORS();
		

		#ifndef EDITOR_CONTROLS
			// if you don't have an audio system figure some other way to pass time to your shader
			#if USE_AUDIO
				//waveOutGetPosition(hWaveOut, &MMTime, sizeof(MMTIME));
				timeInTicks = Oidos_GetPosition(); 
				// it is possible to upload your vars as vertex color attribute (gl_Color) to save one function import
				#if NO_UNIFORMS
					#error not implemented
					//glColor3ui(MMTime.u.sample, 0, 0);
				#else
					const GLuint timeLoc = 
						((PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation"))(pid, "iTime");
					((PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f"))(timeLoc, timeInTicks/Oidos_TicksPerSecond);
				#endif
			#endif
		#else
			position = track.getTime();
			((PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i"))(0, ((int)(position*44100.0)));
		#endif
		glRects(-1, -1, 1, 1);

		SwapBuffers(hDC);

		// pausing and seeking enabled in debug mode
		#ifdef EDITOR_CONTROLS
			if(GetAsyncKeyState(VK_MENU))
			{
				double seek = 0.0;
				if(GetAsyncKeyState(VK_DOWN)) track.pause();
				if(GetAsyncKeyState(VK_UP))   track.play();
				if(GetAsyncKeyState(VK_RIGHT) && !GetAsyncKeyState(VK_SHIFT)) seek += 1.0;
				if(GetAsyncKeyState(VK_LEFT)  && !GetAsyncKeyState(VK_SHIFT)) seek -= 1.0;
				if(GetAsyncKeyState(VK_RIGHT) && GetAsyncKeyState(VK_SHIFT))  seek += 0.1;
				if(GetAsyncKeyState(VK_LEFT)  && GetAsyncKeyState(VK_SHIFT))  seek -= 0.1;
				if(position+seek != position)
				{
					position += seek;
					track.seek(position);
				}
			}
		#endif
	} while (!GetAsyncKeyState(VK_ESCAPE)
		#if USE_AUDIO
		//&& MMTime.u.sample < MAX_SAMPLES
		//&& timeInTicks < Oidos_MusicLength
		#endif
	);

	ExitProcess(0);
}
