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
#endif

#define GLSL(version, shader)  "#version " #version "\n" #shader

#include "glext.h"
#pragma data_seg(".shader") 
const char *fragment_frag = R"END(
#version 430
#define SCREEN_X (1280/2)
#define SCREEN_Y (720/2)
layout(location=0)uniform int ti;
layout(location=1)uniform sampler2D img;
//float t,l,v,f,z,i=0,m=2,n=.3,r=0;
float t;

/*
vec3 func(vec2 pos) {
	float d = length(pos - vec2(1.0) + 0.5*vec2(cos(t), sin(t*2.0)));
	if (d < 0.1) return vec3(1.0);
	return vec3(0.0);
}
*/


float rand(in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

void pR(inout vec2 p, float a) {
	p = cos(a)*p + sin(a)*vec2(p.y, -p.x);
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

vec3 field(vec3 p, float t) {
    p.z += t*2.0;
    //vec3 col = abs(sin(p));
    vec3 col = vec3(1.0, 0.5, 0.0);
    float ofs = pow(snoise(p.xz), 2.0);
	vec3 cluster = pMod3(p, vec3(1.0));
    return col*vec3(2e-3)/(length(p) + ofs);
}

vec3 march(vec2 uv, float t) {
	vec3 c = vec3(1.0, 0.0, 0.0);
    vec3 origin = vec3(uv - vec2(0.5, 0.25), 1.0);
    origin.y += 0.1;
    pR(origin.xy, t*0.2);
    pR(origin.xz, t*0.2);
    vec3 dir = normalize(origin);
    vec3 p = origin;
    //p.xy += 0.4*vec2(cos(t), sin(t));
    vec3 accum = vec3(0.);
    for (int i=0;i<50;i++) {
        vec3 d = field(p, t);
        accum += d;
            
        
    	p += dir * 1e-3 * 1.0/length(d);
    }
    
    float boost = pow(max(accum.x, max(accum.y, accum.z)), 2.0);
    return accum + vec3(boost);
}

void main()
{
    float t = ti/44100.;
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy/vec2(SCREEN_X, SCREEN_Y);
    vec2 p = vec2(uv.x, uv.y * (float(SCREEN_Y)/SCREEN_X));

    vec2 ncoord = p + vec2(sin(t*199.), sin(t*238.));
    
    vec3 new = pow(march(p, t), vec3(2.0));
    new = clamp(new, vec3(0.0), vec3(1.0));
	new += texture(img, uv * 0.5).rgb*0.90 - 1.0/255.0;
    
    // Output to screen
    gl_FragColor = vec4(new,1.0);
}

/*
void main()
{
	t=ti/44100.;
	vec2 fc = gl_FragCoord.xy/vec2(SCREEN_X, SCREEN_Y);
	vec3 c = func(fc) + texture(img, fc * 0.5).rgb*0.90 - 1.0/255.0;
	gl_FragColor=vec4(c, 1.0);
	};	
*/
)END";
//#include "shaders/fragment.inl"
#if TWO_PASS
	#pragma data_seg(".shader") 
	#include "shaders/post.inl"
#endif

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
	
	PID_QUALIFIER int pid = ((PFNGLCREATESHADERPROGRAMVPROC)wglGetProcAddress("glCreateShaderProgramv"))(GL_FRAGMENT_SHADER, 1, &fragment_frag);
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
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)_4klang_render, lpSoundBuffer, 0, 0);
			waveOutOpen(&hWaveOut, WAVE_MAPPER, &WaveFMT, NULL, 0, CALLBACK_NULL);
			waveOutPrepareHeader(hWaveOut, &WaveHDR, sizeof(WaveHDR));
			waveOutWrite(hWaveOut, &WaveHDR, sizeof(WaveHDR));
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

		// render with the primary shader
		((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram"))(pid);
		CHECK_ERRORS();

		glBindTexture(GL_TEXTURE_2D, 1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		((PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture"))(GL_TEXTURE0);
		CHECK_ERRORS();
		((PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i"))(1, 0);
		CHECK_ERRORS();
		// copy GL_BACK -> GL_TEXTURE_2D
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, XRES, YRES, 0);
		CHECK_ERRORS();
		

		#ifndef EDITOR_CONTROLS
			// if you don't have an audio system figure some other way to pass time to your shader
			#if USE_AUDIO
				waveOutGetPosition(hWaveOut, &MMTime, sizeof(MMTIME));
				// it is possible to upload your vars as vertex color attribute (gl_Color) to save one function import
				#if NO_UNIFORMS
					glColor3ui(MMTime.u.sample, 0, 0);
				#else
					// remember to divide your shader time variable with the SAMPLE_RATE (44100 with 4klang)
					((PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i"))(0, MMTime.u.sample);
				#endif
			#endif
		#else
		#if TWO_PASS
			refreshShaders(pid, pi2);
	#endif
			position = track.getTime();
			((PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i"))(0, ((int)(position*44100.0)));
		#endif
		glRects(-1, -1, 1, 1);

		// render "post process" using the opengl backbuffer
		#if TWO_PASS
			glBindTexture(GL_TEXTURE_2D, 1);
			#if USE_MIPMAPS
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, XRES, YRES, 0);
				((PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap"))(GL_TEXTURE_2D);
			#else
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				// copies from GL_BACK (double buffering is enabled) to currently bound image
				glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 0, 0, XRES, YRES, 0);
			#endif
			((PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture"))(GL_TEXTURE0);
			((PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram"))(pi2);
			((PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i"))(0, 0);
			glRects(-1, -1, 1, 1);
		#endif

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
	} while(!GetAsyncKeyState(VK_ESCAPE)
		#if USE_AUDIO
			&& MMTime.u.sample < MAX_SAMPLES
		#endif
	);

	ExitProcess(0);
}
