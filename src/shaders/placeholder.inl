#pragma data_seg(".shader")
const char* fragment_frag =
 "#version 130\n"
 "uniform float iTime;\n"
 "uniform sampler2D img;\n"
 "void main(){\n"
 "gl_FragColor=vec4(1.0, sin(iTime), 0.0, 1.0);"
 "}";
