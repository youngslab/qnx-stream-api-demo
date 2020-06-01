

#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <screen/screen.h>
#include <iostream>
#include "helper.h"

const char *vertexShaderSource =
    "#version 300 es\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\n\0";

const char *fragmentShaderSource =
    "#version 300 es\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

int main() {
  std::cout << "producer\n";

  screen_context_t screen_ctx;
  screen_create_context(&screen_ctx, SCREEN_APPLICATION_CONTEXT);

  // create the producer's stream
  screen_stream_t stream_p;
  screen_create_stream(&stream_p, screen_ctx);

  // Set the appropriate properties
  int buffer_size[2] = {720, 720};
  screen_set_stream_property_iv(stream_p, SCREEN_PROPERTY_BUFFER_SIZE,
                                buffer_size);
  screen_set_stream_property_iv(stream_p, SCREEN_PROPERTY_FORMAT,
                                (const int[]){SCREEN_FORMAT_RGBX8888});
  screen_set_stream_property_iv(
      stream_p, SCREEN_PROPERTY_USAGE,
      (const int[]){SCREEN_USAGE_OPENGL_ES1 | SCREEN_USAGE_WRITE |
                    SCREEN_USAGE_NATIVE});

  // 3. create buffers for the stream
  screen_create_stream_buffers(stream_p, 2);

  // 4. permission
  std::cout << "producer) set stream permission.\n";
  int permissions;
  screen_get_stream_property_iv(stream_p, SCREEN_PROPERTY_PERMISSIONS,
                                &permissions);
  /* Allow processes in the same group to access the stream */
  permissions |= SCREEN_PERMISSION_IRGRP;
  screen_set_stream_property_iv(stream_p, SCREEN_PROPERTY_PERMISSIONS,
                                &permissions);

  std::cout << "producer) start init egl.\n";
  // EGL init
  EGLDisplay egl_disp;
  egl_disp = eglGetDisplay(EGL_DEFAULT_DISPLAY);
  eglInitialize(egl_disp, NULL, NULL);

  // egl config
  EGLConfig egl_config;
  EGLint egl_config_nr;
  EGLint attribute_list[] = {EGL_RED_SIZE,  8, EGL_GREEN_SIZE, 8,
                             EGL_BLUE_SIZE, 8, EGL_ALPHA_SIZE, 8,
                             EGL_NONE};

  eglChooseConfig(egl_disp, attribute_list, &egl_config, 1, &egl_config_nr);

  EGLContext egl_ctx;
  egl_ctx = eglCreateContext(egl_disp, egl_config, EGL_NO_CONTEXT, NULL);

  EGLSurface egl_surf;
  struct {
    EGLint render_buffer[2];
    EGLint none;
  } egl_surf_attr = {
      .render_buffer = {EGL_RENDER_BUFFER,
                        EGL_BACK_BUFFER}, /* Ask for double-buffering */
      .none = EGL_NONE                    /* End of list */
  };

  egl_surf = eglCreateWindowSurface(egl_disp, egl_config,
                                    (EGLNativeWindowType) nullptr,
                                    (EGLint *)&egl_surf_attr);

  eglMakeCurrent(egl_disp, egl_surf, egl_surf, egl_ctx);
  std::cout << "producer) make current.\n";

  // draw render buffer

  // Create and compile our GLSL program from the shaders
  int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  std::cout << "producer) load shader.\n";

  static const GLfloat g_vertex_buffer_data[] = {
      -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
  };
  // std::cout << "producer) vertex array.\n";
  // GLuint VertexArrayID;
  // glGenVertexArrays(1, &VertexArrayID);
  // glBindVertexArray(VertexArrayID);

  std::cout << "producer) vertex buffer.\n";
  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);

  while (1) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    std::cout << "producer) load data.\n";
    glUseProgram(shaderProgram);
    std::cout << "producer) load data.\n";
    glEnableVertexAttribArray(0);
    std::cout << "producer) load data.\n";
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    std::cout << "producer) load data.\n";
    glVertexAttribPointer(0, 3,
                          GL_FLOAT,  // 타입(type)
                          GL_FALSE,  // 정규화(normalized)?
                          0,         // 다음 요소 까지 간격(stride)
                          (void *)0  // 배열 버퍼의 오프셋(offset; 옮기는 값)
                          );
    glDrawArrays(GL_TRIANGLES, 0, 3);
    std::cout << "producer) load data.\n";
    glDisableVertexAttribArray(0);
    std::cout << "producer) load data.\n";

    //// STREAM 5. Render and Post.
    // screen_post_stream();
  }
}

