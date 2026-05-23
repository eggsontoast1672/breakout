#include "breakout/render.h"
#include "breakout/texture.h"
#include "breakout/window.h"

#include "glad/glad.h"

int main(void) {
    window_init_system();

    const Window window = window_create(800, 600, "Breakout");
    const Renderer renderer = renderer_init();
    const Texture awesomeface = texture_load("assets/textures/awesomeface.png");
    const Rect rect = {100.0f, 100.0f, 100.0f, 100.0f};

    while (!window_should_close(window)) {
        window_clear();
        renderer_draw_sprite(renderer, awesomeface, rect);
        window_swap_buffers(window);
        window_poll_events();
    }

    window_shutdown_system();
}
