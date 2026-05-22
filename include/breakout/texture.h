#pragma once

typedef struct {
    unsigned int id;
} Texture;

Texture texture_load(const char *path);
void texture_unload(Texture texture);
void texture_bind(Texture texture);
void texture_unbind(void);
