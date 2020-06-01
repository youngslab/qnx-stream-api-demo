

#include <screen/screen.h>
#include <iostream>

int main() {
  screen_context_t screen_ctx;
  auto rc = screen_create_context(&screen_ctx, 0);

  screen_window_t screen_win;
  rc = screen_create_window(&screen_win, screen_ctx);

  screen_set_window_property_iv(
      screen_win, SCREEN_PROPERTY_USAGE,
      (const int[]){SCREEN_USAGE_OPENGL_ES2 | SCREEN_USAGE_WRITE |
                    SCREEN_USAGE_NATIVE});

  int buffer_size[2] = {720, 720};
  screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_BUFFER_SIZE,
                                buffer_size);

  screen_set_window_property_iv(screen_win, SCREEN_PROPERTY_FORMAT,
                                (const int[]){SCREEN_FORMAT_RGBA8888});
  int nbuffers = 2;
  screen_create_window_buffers(screen_win, nbuffers);

  while (1) {
    screen_buffer_t wbuffer = nullptr;
    screen_get_window_property_pv(  // buffers property
        /* A handle to the buffer or buffers available for rendering. */
        screen_win, SCREEN_PROPERTY_RENDER_BUFFERS, (void **)&wbuffer);

    void *pointer;
    screen_get_buffer_property_pv(wbuffer, SCREEN_PROPERTY_POINTER, &pointer);

    for (int i = 0; i < 720; i++) {
      for (int j = 0; j < 720; j++) {
        ((char *)pointer)[(i * 720 + j) * 4 + 2] += 5;
      }
    }

    screen_post_window(screen_win, wbuffer, 0, nullptr, 0);
  }
}
