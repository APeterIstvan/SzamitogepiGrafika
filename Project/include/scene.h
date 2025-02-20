#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "car.h"
#include "texture.h"

#include <SDL2/SDL.h>

#include <obj/model.h>

#define ROAD_NUMBERS 1
#define BARRIER_NUMBERS 29

typedef struct Bridge {
    Model model;
    GLuint texture;
    vec3 position;
} Bridge;

typedef struct Barrier {
    GLuint texture;
    vec3 position;
    float minus_size;
    float plus_size;
} Barrier;

typedef struct Skull {
    Model model;
    GLuint texture;
    vec3 position;
} Skull;

typedef struct Light {
    float ambient[4];
    float diffuse[4];
    float specular[4];
    float speed;
} Light;

typedef struct Water {
    Model model;
    GLuint texture;
    vec3 position;
    bool motion_up;
} Water;

typedef struct Scene {
    Water water;

    Model road;
    Bridge bridge[ROAD_NUMBERS];
    Model bridge_model;
    GLuint bridge_texture;

    Barrier barrier[BARRIER_NUMBERS];
    Model barrier_model;

    Skull skull;
    Material skull_material;

    Light light;

    Material material;

    Model mountain_model;
    GLuint mountain_texture;

    Car car;
    SDL_AudioDeviceID crash_sound;

    GLuint skybox_texture;
    bool fog_state;
    float fog_speed;
    bool help_panel_state;
    GLuint help_panel_texture;
    double uptime;

    GLuint skullList;
    GLuint bridgeList;
    GLuint barrierList;
    GLuint waterList;
    GLuint mountainList;

    SDL_AudioSpec wav_spec;
    Uint32 wav_length;
    Uint8 *wav_buffer;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene *scene);

/**
 * Initialize the objects.
 */
void init_objects(Scene *scene);

/**
 * Initialize the textures.
 */
void init_textures(Scene *scene);

/**
 * Initialize the display lists.
 */
void init_display_lists(Scene *scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(const Scene *scene);

/**
 * Initialize the bridges.
 */
void init_bridges(Scene *scene);

/**
 * Initialize the obstacles.
 */
void init_obstacles(Scene *scene);

/**
 * Initialize the materials of the scene.
 */
void init_material_scene(Scene *scene);

/**
 * Initialize the materials of the skull.
 */
void init_material_skull(Scene *scene);

/**
 * Initialize the water.
 */
void init_water(Scene *scene);

/**
 * Initialize the light.
 */
void init_light(Scene *scene);

/**
 * Initialize the audio.
 */
void init_audio(Scene *scene);

/**
 * Initialize the fog.
 */
void init_fog(Scene *scene);

/**
 * Set the current material.
 */
void set_material(const Material *material);

/**
 * Update the scene.
 */
void update_scene(Scene *scene, Camera *camera, Car *car, double time);

/**
 * Collision detection for the road.
 */
void road_collision_detection(Car *car, Camera *camera);

/**
 * Collision detection for certain obstacles.
 */
void obstacle_collision_detection(Scene *scene, Car *car, double time);

void finish_line(Scene *scene, Car *car, Camera *camera);

void water_motion(Scene *scene, double time);

/**
 *
 * Render the scene objects.
 */
void render_scene(const Scene *scene);

void render_barrier(const Scene *scene);

void render_skull(const Scene *scene);

void render_water(const Scene *scene);

void render_road(const Scene *scene);

void render_init_bridge(const Scene *scene);

void render_mountain(const Scene *scene);

void draw_help_panel(GLuint help_panel);

void load_skybox();

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

void set_light_speed(Scene *scene, float speed);

void set_fog_speed(Scene *scene, float speed);

void set_fog_state(Scene *scene, bool state);

void display_help_panel(Scene *scene, bool state);

#endif /* SCENE_H */
