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

const char *vertex_vert = R"END(
#version 130
varying vec3 pos;
void main()
{
	gl_Position = vec4(pos, 1.0);
}
)END";

#include "glext.h"
#pragma data_seg(".shader") 
const char *fragment_frag = R"END(
#version 130
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
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
	
	#if 1
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
	GLuint vertshader = glCreateShader(GL_VERTEX_SHADER); CHECK_ERRORS();
	PID_QUALIFIER int pid = glCreateProgram(); CHECK_ERRORS();


	int lens = 1;
	{
		glShaderSource(shader, 1, &fragment_frag, &lens); CHECK_ERRORS();
		glCompileShader(shader); CHECK_ERRORS();
		GLint compiled = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled); CHECK_ERRORS();
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled); CHECK_ERRORS();
	}
	char info[2048];
	((PFNGLGETSHADERINFOLOGPROC) wglGetProcAddress("glGetShaderInfoLog"))(shader, 2047, NULL, (char*)info);

	int vert_result = -1;
	{
		glShaderSource(vertshader, 1, &vertex_vert, &vert_result); CHECK_ERRORS();
		glCompileShader(vertshader); CHECK_ERRORS();
		GLint vert_compiled = GL_FALSE;
		glGetShaderiv(vertshader, GL_COMPILE_STATUS, &vert_compiled); CHECK_ERRORS();
		glGetShaderiv(vertshader, GL_COMPILE_STATUS, &vert_compiled); CHECK_ERRORS();
	}
	char vert_info[2048];
	((PFNGLGETSHADERINFOLOGPROC) wglGetProcAddress("glGetShaderInfoLog"))(vertshader, 2047, NULL, (char*)vert_info);

	glAttachShader(pid, shader); CHECK_ERRORS();
	glAttachShader(pid, vertshader); CHECK_ERRORS();
	glLinkProgram(pid);  CHECK_ERRORS();
	//glDetachShader(pid, shader); CHECK_ERRORS();
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

		/*
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
		*/
		

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
