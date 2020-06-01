const char *vtx_shdr_src =
"// gears.vs\n"
"//\n"
"// Emulates a fixed-function pipeline with:\n"
"//  GL_ALPHA_TEST is disabled by default\n"
"//  GL_BLEND is disabled by default\n"
"//  GL_CLIP_PLANEi is disabled\n"
"//  GL_LIGHTING and GL_LIGHT0 enabled\n"
"//  GL_FOG disabled\n"
"//  GL_TEXTURE_xx disabled\n"
"//  GL_TEXTURE_GEN_x disabled\n"
"//\n"
"//  GL_LIGHT_MODEL_AMBIENT is never set -> default value is (0.2, 0.2, 0.2, 1.0)\n"
"//\n"
"//  GL_LIGHT0 position is (5, 5, 10, 0)\n"
"//  GL_LIGHT0 ambient is never set -> default value is (0, 0, 0, 1)\n"
"//  GL_LIGHT0 diffuse is never set -> default value is (1, 1, 1, 1)\n"
"//  GL_LIGHT0 specular is never set -> default value is (1, 1, 1, 1)\n"
"//\n"
"//  GL_AMBIENT and GL_DIFFUSE are (red/green/blue)\n"
"//  GL_SPECULAR is never set -> default value is (0, 0, 0, 1)\n"
"//  GL_EMISSION is never set -> default value is (0, 0, 0, 1)\n"
"//  GL_SHININESS is never set -> default value is 0\n"
"//\n"
"//  ES 2.0 only supports generic vertex attributes as per spec para 2.6\n"
"//\n"
"//  Combining material with light settings gives us directional diffuse with\n"
"//  ambient from light model.\n"
"//\n"
"//  Since alpha test and blend are both disabled, there is no need to keep track\n"
"//  of the alpha component when shading. This saves the interpolation of one\n"
"//  float between vertices and brings the performance back to the level of the\n"
"//  'fixed function pipeline' when the window is maximized.\n"
"//\n"
"//  App is responsible for normalizing LightPosition.\n"
"\n"
"// should be set to gl_ProjectionMatrix * gl_ModelViewMatrix\n"
"uniform mat4 ModelViewProjectionMatrix;\n"
"\n"
"// should be same as mat3(gl_ModelViewMatrix) because gl_ModelViewMatrix is orthogonal\n"
"uniform mat3 NormalMatrix;\n"
"\n"
"// should be set to 'normalize(5.0, 5.0, 10.0)'\n"
"uniform vec3 LightPosition;\n"
"\n"
"// should be set to AmbientDiffuse * vec4(0.2, 0.2, 0.2, 1.0)\n"
"uniform vec3 LightModelProduct;\n"
"\n"
"// will be set to red/green/blue\n"
"uniform vec3 AmbientDiffuse;\n"
"\n"
"// user defined attribute to replace gl_Vertex\n"
"attribute vec4 Vertex;\n"
"\n"
"// user defined attribute to replace gl_Normal\n"
"attribute vec3 Normal;\n"
"\n"
"// interpolate per-vertex lighting\n"
"varying vec3 Color;\n"
"\n"
"void main(void)\n"
"{\n"
"  // transform the vertex and normal in eye space\n"
"  gl_Position = ModelViewProjectionMatrix * Vertex;\n"
"  vec3 NormEye = normalize(NormalMatrix * Normal);\n"
"\n"
"  // do one directional light (diffuse only); no need to clamp for this example\n"
"  Color = LightModelProduct + AmbientDiffuse * max(0.0, dot(NormEye, LightPosition));\n"
"}\n";
