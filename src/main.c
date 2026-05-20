#include "breakout/window.h"

int main(void) {
    window_init_system();

    const Window window = window_create(800, 600, "Breakout");

    while (!window_should_close(window)) {
        window_clear();
        window_swap_buffers(window);
        window_poll_events();
    }

    window_shutdown_system();
}
