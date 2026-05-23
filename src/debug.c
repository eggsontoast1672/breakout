#include "breakout/debug.h"

#include <assert.h>

#include "glad/glad.h"

#include "breakout/logging.h"

static const char *get_error_string(GLenum error) {
    switch (error) {
    case GL_INVALID_ENUM: return "invalid enum";
    case GL_INVALID_VALUE: return "invalid value";
    case GL_INVALID_OPERATION: return "invalid operation";
    case GL_INVALID_FRAMEBUFFER_OPERATION: return "invalid framebuffer operation";
    case GL_OUT_OF_MEMORY: return "out of memory";
    default: assert(0 && "unrecognized error value");
    }
}

void debug_report_errors(const char *file, unsigned int line) {
    while (1) {
        const GLenum error = glGetError();
        if (error != GL_NO_ERROR) {
            const char *const message = get_error_string(error);
            log_message(LOG_ERROR, "%s:%u: OpenGL error: %s\n", file, line, message);
        } else {
            break;
        }
    }
}
