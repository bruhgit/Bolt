#ifndef BOLT_H
#define BOLT_H

#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <miniaudio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#ifndef PI
#define PI 3.14159265358979323846
#endif

// ---------------------------------------------------------
// BOLT ENGINE - MACROS & API
// ---------------------------------------------------------
#ifdef BOLT_STATIC
#define BOLT_API static
#else
#define BOLT_API extern
#endif

// ---------------------------------------------------------
// BOLT ENGINE - TİPLER VE YAPILAR
// ---------------------------------------------------------

// SDL Türlerini Gizleme (Abstraction)
typedef SDL_Texture BoltImage;
typedef TTF_Font BoltFont;
typedef SDL_Scancode BoltKey;
typedef SDL_GamepadButton BoltGamepadButton;
typedef SDL_GamepadAxis BoltGamepadAxis;
typedef SDL_BlendMode BoltBlendMode;
typedef SDL_Vertex BoltVertex;
typedef SDL_FRect BoltRect;
typedef SDL_FPoint BoltPoint;
typedef SDL_FlipMode BoltFlipMode;

// Tuş Sabitleri
#define BOLT_KEY_A SDL_SCANCODE_A
#define BOLT_KEY_B SDL_SCANCODE_B
#define BOLT_KEY_C SDL_SCANCODE_C
#define BOLT_KEY_D SDL_SCANCODE_D
#define BOLT_KEY_E SDL_SCANCODE_E
#define BOLT_KEY_F SDL_SCANCODE_F
#define BOLT_KEY_G SDL_SCANCODE_G
#define BOLT_KEY_H SDL_SCANCODE_H
#define BOLT_KEY_I SDL_SCANCODE_I
#define BOLT_KEY_J SDL_SCANCODE_J
#define BOLT_KEY_K SDL_SCANCODE_K
#define BOLT_KEY_L SDL_SCANCODE_L
#define BOLT_KEY_M SDL_SCANCODE_M
#define BOLT_KEY_N SDL_SCANCODE_N
#define BOLT_KEY_O SDL_SCANCODE_O
#define BOLT_KEY_P SDL_SCANCODE_P
#define BOLT_KEY_Q SDL_SCANCODE_Q
#define BOLT_KEY_R SDL_SCANCODE_R
#define BOLT_KEY_S SDL_SCANCODE_S
#define BOLT_KEY_T SDL_SCANCODE_T
#define BOLT_KEY_U SDL_SCANCODE_U
#define BOLT_KEY_V SDL_SCANCODE_V
#define BOLT_KEY_W SDL_SCANCODE_W
#define BOLT_KEY_X SDL_SCANCODE_X
#define BOLT_KEY_Y SDL_SCANCODE_Y
#define BOLT_KEY_Z SDL_SCANCODE_Z
#define BOLT_KEY_1 SDL_SCANCODE_1
#define BOLT_KEY_2 SDL_SCANCODE_2
#define BOLT_KEY_3 SDL_SCANCODE_3
#define BOLT_KEY_4 SDL_SCANCODE_4
#define BOLT_KEY_5 SDL_SCANCODE_5
#define BOLT_KEY_6 SDL_SCANCODE_6
#define BOLT_KEY_7 SDL_SCANCODE_7
#define BOLT_KEY_8 SDL_SCANCODE_8
#define BOLT_KEY_9 SDL_SCANCODE_9
#define BOLT_KEY_0 SDL_SCANCODE_0
#define BOLT_KEY_SPACE SDL_SCANCODE_SPACE
#define BOLT_KEY_LCTRL SDL_SCANCODE_LCTRL
#define BOLT_KEY_ESCAPE SDL_SCANCODE_ESCAPE
#define BOLT_KEY_RETURN SDL_SCANCODE_RETURN
#define BOLT_KEY_UP SDL_SCANCODE_UP
#define BOLT_KEY_DOWN SDL_SCANCODE_DOWN
#define BOLT_KEY_LEFT SDL_SCANCODE_LEFT
#define BOLT_KEY_RIGHT SDL_SCANCODE_RIGHT

#define BOLT_FLIP_NONE SDL_FLIP_NONE
#define BOLT_FLIP_HORIZONTAL SDL_FLIP_HORIZONTAL
#define BOLT_FLIP_VERTICAL SDL_FLIP_VERTICAL

#define BOLT_BLENDMODE_NONE SDL_BLENDMODE_NONE
#define BOLT_BLENDMODE_BLEND SDL_BLENDMODE_BLEND
#define BOLT_BLENDMODE_ADD SDL_BLENDMODE_ADD
#define BOLT_BLENDMODE_MOD SDL_BLENDMODE_MOD

typedef struct {
    uint64_t last_time;
    uint64_t current_time;
    double delta_time; 
    float fps;
} BoltClock;

typedef struct {
    float x, y;
    float vx, vy;
    float life;
    float max_life;
    int r, g, b;
    bool active;
} BoltParticle;

typedef struct {
    BoltImage* sheet;
    int kare_sayisi;
    int su_anki_kare;
    float anim_hizi; 
    float zaman_sayaci;
} BoltSprite;

typedef enum { 
    BOLT_ANCHOR_TOP_LEFT, 
    BOLT_ANCHOR_CENTER, 
    BOLT_ANCHOR_BOTTOM_RIGHT 
} BoltAnchor;

typedef struct {
    float x, y, z;
} BoltVec3;

typedef struct {
    float x, y;
    float zoom;
} BoltCamera2D;

typedef struct {
    BoltVec3 position;
    float yaw;
    float pitch;
} BoltCamera3D;

typedef struct {
    Uint8 r, g, b, a;
} BoltColor;

// Renk Sabitleri
static const BoltColor BOLT_WHITE  = { 255, 255, 255, 255 };
static const BoltColor BOLT_BLACK  = { 0, 0, 0, 255 };
static const BoltColor BOLT_RED    = { 255, 0, 0, 255 };
static const BoltColor BOLT_GREEN  = { 0, 255, 0, 255 };
static const BoltColor BOLT_BLUE   = { 0, 0, 255, 255 };
static const BoltColor BOLT_YELLOW = { 255, 255, 0, 255 };

// Ses tipleri (miniaudio)
typedef ma_sound BoltSound;
typedef ma_sound BoltMusic;

// Fare İmleci Tipleri
typedef enum {
    BOLT_CURSOR_DEFAULT = 0,
    BOLT_CURSOR_TEXT,
    BOLT_CURSOR_WAIT,
    BOLT_CURSOR_CROSSHAIR,
    BOLT_CURSOR_PROGRESS,
    BOLT_CURSOR_HAND,
    BOLT_CURSOR_NOT_ALLOWED
} BoltCursorType;

// Global Değişken Erişimleri
BOLT_API SDL_Window* bolt_window;
BOLT_API SDL_Renderer* bolt_renderer;
BOLT_API BoltClock bolt_clock;

// 1. BAŞLATMA VE PENCERE AYARLARI
BOLT_API void bolt_init(const char* baslik, int genislik, int yukseklik);
BOLT_API void bolt_quit(void);
BOLT_API bool bolt_should_close(void);
BOLT_API void bolt_update(void); // update_events ve update_clock'u otomatik yapar
BOLT_API void bolt_update_events(void);
BOLT_API void bolt_update_clock(void);
BOLT_API void bolt_set_canvas_color(int r, int g, int b);
BOLT_API void bolt_clear_background(BoltColor color);
BOLT_API void bolt_present(void);

// Zaman (Time / FPS)
BOLT_API float bolt_get_fps(void);
BOLT_API float bolt_get_delta_time(void);
BOLT_API float bolt_get_time(void);

// Pencere ve Monitör Yönetimi
BOLT_API void bolt_set_fullscreen(bool fullscreen);
BOLT_API void bolt_set_window_title(const char* title);
BOLT_API int bolt_get_window_width(void);
BOLT_API int bolt_get_window_height(void);
BOLT_API int bolt_get_monitor_width(void);
BOLT_API int bolt_get_monitor_height(void);

// Fare (Cursor) Yönetimi
BOLT_API void bolt_hide_cursor(void);
BOLT_API void bolt_show_cursor(void);
BOLT_API void bolt_lock_cursor(bool lock);
BOLT_API void bolt_set_cursor_type(BoltCursorType type);

// 2. GİRDİ (INPUT) SİSTEMİ
BOLT_API void bolt_update_input(void); 
BOLT_API bool bolt_get_key(BoltKey key);
BOLT_API bool bolt_is_key_pressed(BoltKey key);
BOLT_API bool bolt_is_key_released(BoltKey key);
BOLT_API void bolt_start_text_input(void);
BOLT_API void bolt_stop_text_input(void);
BOLT_API const char* bolt_get_text_input(void);
BOLT_API void bolt_clear_text_input(void);
BOLT_API bool bolt_get_mouse_button(int button);
BOLT_API bool bolt_is_mouse_pressed(int button);
BOLT_API bool bolt_is_mouse_released(int button);
BOLT_API float bolt_get_mouse_x(void);
BOLT_API float bolt_get_mouse_y(void);
BOLT_API float bolt_get_mouse_delta_x(void);
BOLT_API float bolt_get_mouse_delta_y(void);
BOLT_API float bolt_get_mouse_wheel_x(void);
BOLT_API float bolt_get_mouse_wheel_y(void);

// Gamepad (Kontrolcü) Sistemi
BOLT_API bool bolt_is_gamepad_connected(int index);
BOLT_API bool bolt_get_gamepad_button(int index, BoltGamepadButton button);
BOLT_API float bolt_get_gamepad_axis(int index, BoltGamepadAxis axis);

// 3. FİZİK VE ÇARPIŞMA (COLLISION) SİSTEMİ
BOLT_API bool bolt_check_collision_rect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
BOLT_API bool bolt_check_collision_circle(float x1, float y1, float r1, float x2, float y2, float r2);

// 4. PARÇACIK (PARTICLE) SİSTEMİ
BOLT_API void bolt_emit_particle(float x, float y, float vx, float vy, float life, int r, int g, int b);
BOLT_API void bolt_update_and_draw_particles(void);

// 5. TEMEL ÇİZİM VE GEOMETRİ
BOLT_API void bolt_draw_color(BoltColor color);
BOLT_API void bolt_draw_pixel(float x, float y, int r, int g, int b);
BOLT_API void bolt_draw_line(float x1, float y1, float x2, float y2, int r, int g, int b);
BOLT_API void bolt_draw_rect(float x, float y, float w, float h, int r, int g, int b);
BOLT_API void bolt_draw_rect_filled(float x, float y, float w, float h, int r, int g, int b);
BOLT_API void bolt_draw_circle(float x, float y, float radius, int r, int g, int b);
BOLT_API void bolt_draw_circle_filled(float x, float y, float radius, int r, int g, int b);

// 6. MULTİMEDYA VE RENDER TARGET
BOLT_API BoltImage* bolt_load_image(const char* yol);
BOLT_API void bolt_get_image_size(BoltImage* tex, float* w, float* h);
BOLT_API void bolt_draw_image(BoltImage* tex, float x, float y, float w, float h);
BOLT_API void bolt_draw_image_rec(BoltImage* tex, BoltRect src, BoltRect dst);
BOLT_API void bolt_draw_image_ex(BoltImage* tex, float x, float y, float w, float h, float angle, BoltPoint* center, BoltFlipMode flip);
BOLT_API BoltImage* bolt_load_image_from_buffer(const void* buffer, size_t size);

BOLT_API BoltImage* bolt_create_render_target(int w, int h);
BOLT_API void bolt_set_render_target(BoltImage* target);
BOLT_API void bolt_reset_render_target(void);
BOLT_API BoltColor bolt_read_pixel(float x, float y);

// 7. ANİMASYON VE HAREKET MANTIĞI
BOLT_API void bolt_move_logic(float* pos, float hedef_hiz);
BOLT_API void bolt_draw_sprite_anim(BoltSprite* sprite, float x, float y, float w, float h);

// 8. METİN VE UI
BOLT_API BoltFont* bolt_load_font(const char* yol, int boyut);
BOLT_API void bolt_draw_text(BoltFont* font, const char* metin, float x, float y, int r, int g, int b, BoltAnchor anchor);
BOLT_API bool bolt_gui_button(float x, float y, float w, float h, const char* text);

// 8.5 2D KAMERA SİSTEMİ
BOLT_API void bolt_begin_2d(BoltCamera2D cam);
BOLT_API void bolt_end_2d(void);

// 9. 3D ÇİZİM SİSTEMİ
BOLT_API BoltCamera3D bolt_camera_3d;
BOLT_API void bolt_draw_cube(float x, float y, float z, float size, int r, int g, int b);
BOLT_API void bolt_draw_cube_textured(BoltImage* tex, float x, float y, float z, float size);
BOLT_API void bolt_draw_plane_textured(BoltImage* tex, float x, float y, float z, float w, float d);
BOLT_API void bolt_draw_pyramid(float x, float y, float z, float size, int r, int g, int b);
BOLT_API void bolt_draw_sphere(float x, float y, float z, float radius, int segments, int r, int g, int b);

// 10. SES VE MÜZİK SİSTEMİ
BOLT_API BoltSound* bolt_load_sound(const char* yol);
BOLT_API void bolt_play_sound(BoltSound* sound);
BOLT_API void bolt_set_sound_volume(BoltSound* sound, int volume);
BOLT_API void bolt_set_sound_pitch(BoltSound* sound, float pitch);

BOLT_API BoltMusic* bolt_load_music(const char* yol);
BOLT_API void bolt_play_music(BoltMusic* music, bool loop);
BOLT_API void bolt_stop_music(void);
BOLT_API void bolt_set_music_volume(int volume);

// 11. MATEMATİK, İŞLETİM SİSTEMİ VE DOSYA (FILE I/O) ARAÇLARI
BOLT_API float bolt_lerp(float a, float b, float t);
BOLT_API float bolt_distance_2d(float x1, float y1, float x2, float y2);
BOLT_API float bolt_distance_3d(BoltVec3 v1, BoltVec3 v2);
BOLT_API float bolt_angle_2d(float x1, float y1, float x2, float y2);
BOLT_API int bolt_random_int(int min, int max);
BOLT_API float bolt_random_float(float min, float max);

BOLT_API int bolt_get_system_ram(void);
BOLT_API int bolt_get_cpu_count(void);
BOLT_API bool bolt_is_dark_mode(void);

BOLT_API void bolt_set_window_icon(const char* filepath);
BOLT_API void bolt_show_message_box(const char* title, const char* message);
BOLT_API void bolt_set_clipboard_text(const char* text);
BOLT_API const char* bolt_get_clipboard_text(void);

BOLT_API bool bolt_save_text(const char* filepath, const char* content);
BOLT_API char* bolt_load_text(const char* filepath);

// SDL3 Dosya Seçici (File Dialog)
BOLT_API void bolt_open_file_dialog(void);
BOLT_API bool bolt_is_dialog_ready(void);
BOLT_API const char* bolt_get_dialog_result(void);

// 12. GELİŞMİŞ RENDER KONTROLLERİ
BOLT_API void bolt_set_render_viewport(float x, float y, float w, float h);
BOLT_API void bolt_reset_render_viewport(void);
BOLT_API void bolt_set_render_clip(float x, float y, float w, float h);
BOLT_API void bolt_reset_render_clip(void);
BOLT_API void bolt_set_render_scale(float scale_x, float scale_y);
BOLT_API void bolt_set_blend_mode(BoltBlendMode mode);
BOLT_API void bolt_set_texture_blend_mode(BoltImage* tex, BoltBlendMode mode);
BOLT_API void bolt_set_texture_color_mod(BoltImage* tex, int r, int g, int b);
BOLT_API void bolt_set_texture_alpha_mod(BoltImage* tex, int a);
BOLT_API void bolt_draw_geometry(BoltImage* tex, const BoltVertex* vertices, int num_vertices, const int* indices, int num_indices);

// 13. LOG SİSTEMİ
typedef enum { BOLT_LOG_INFO=0, BOLT_LOG_WARN, BOLT_LOG_ERROR, BOLT_LOG_DEBUG } BoltLogLevel;
BOLT_API void bolt_log(BoltLogLevel level, const char* fmt, ...);
BOLT_API void bolt_log_set_file(const char* filepath);

// 14. GELİŞmİŞ GUI WİDGET’LARI
// -- Slider (Kaıdırma Çubuğu)
typedef struct {
    float x, y, w, h;
    float value;      // 0.0 - 1.0 arasi
    float min, max;
    bool dragging;
} BoltSlider;

// -- Checkbox (İşaret Kutusu)
typedef struct {
    float x, y, size;
    bool checked;
} BoltCheckbox;

// -- TextBox (Metin Kutusu)
typedef struct {
    float x, y, w, h;
    bool active;
    char text[512];
} BoltTextBox;

BOLT_API void bolt_slider_init(BoltSlider* s, float x, float y, float w, float h, float min, float max, float value);
BOLT_API bool bolt_slider_draw(BoltSlider* s); // Returns true if value changed
BOLT_API void bolt_checkbox_init(BoltCheckbox* c, float x, float y, float size, bool checked);
BOLT_API bool bolt_checkbox_draw(BoltCheckbox* c); // Returns toggled state
BOLT_API void bolt_textbox_init(BoltTextBox* t, float x, float y, float w, float h);
BOLT_API void bolt_textbox_draw(BoltTextBox* t, BoltFont* font);

// 15. RENK EFEKTLERİ (GRADIENT vb.)
BOLT_API void bolt_draw_gradient_rect(float x, float y, float w, float h, BoltColor c1, BoltColor c2, bool horizontal);
BOLT_API void bolt_draw_rounded_rect(float x, float y, float w, float h, float radius, int r, int g, int b);
BOLT_API void bolt_draw_rounded_rect_filled(float x, float y, float w, float h, float radius, int r, int g, int b);

// 16. 3D IŞIKLANDIRMA (DİREKTIONAL LİGHT)
typedef struct {
    BoltVec3 direction; // Işık yönü (normalize edilmiş)
    int r, g, b;        // Işık rengi
    float intensity;    // 0.0 - 1.0
    float ambient;      // Ortam aydınlığı 0.0-1.0
} BoltLight3D;

BOLT_API BoltLight3D bolt_light_3d; // Global 3D ışık
BOLT_API void bolt_draw_cube_lit(float x, float y, float z, float size, int r, int g, int b);

// 17. OBJ MODEL YÜKLEYİCİ
typedef struct {
    float* vertices;  // x,y,z gruplar halinde
    float* texcoords; // u,v gruplar halinde
    float* normals;   // nx,ny,nz gruplar halinde
    int*   indices;
    int vertex_count;
    int index_count;
} BoltModel3D;

BOLT_API BoltModel3D* bolt_load_model(const char* obj_filepath);
BOLT_API void bolt_draw_model(BoltModel3D* model, float x, float y, float z, float scale, int r, int g, int b);

// ============================================================
// 18. SAHNE YÖNETİMİ (Scene Management)
// ============================================================
typedef struct {
    const char* name;
    void (*on_enter)(void);   // Sahneye girilince bir kez çağrılır
    void (*on_update)(void);  // Her karede çağrılır
    void (*on_draw)(void);    // Her karede çizim için çağrılır
    void (*on_exit)(void);    // Sahneden çıkılınca bir kez çağrılır
} BoltScene;

BOLT_API void bolt_scene_register(BoltScene scene);
BOLT_API void bolt_scene_change(const char* name);
BOLT_API void bolt_scene_update(void);  // Aktif sahneyi update+draw eder
BOLT_API const char* bolt_scene_current_name(void);

// ============================================================
// 19. BASİT FİZİK MOTORU (Simple 2D Physics)
// ============================================================
typedef struct {
    float x, y;           // Pozisyon
    float vx, vy;         // Hız (velocity)
    float ax, ay;         // İvme (acceleration)
    float mass;           // Kütle
    float restitution;    // Esneklik (0=hiç zıplama, 1=tam zıplama)
    float friction;       // Sürtünme (0-1)
    float w, h;           // Boyut (AABB çarpışma için)
    bool  grounded;       // Yerde mi?
    bool  active;
} BoltBody;

BOLT_API void bolt_body_init(BoltBody* body, float x, float y, float w, float h, float mass);
BOLT_API void bolt_body_apply_force(BoltBody* body, float fx, float fy);
BOLT_API void bolt_body_apply_impulse(BoltBody* body, float ix, float iy);
BOLT_API void bolt_body_update(BoltBody* body, float gravity, float dt);
BOLT_API bool bolt_body_collide_rect(BoltBody* a, BoltBody* b);   // AABB çarpışma + tepki
BOLT_API void bolt_body_set_velocity(BoltBody* body, float vx, float vy);
BOLT_API void bolt_body_stop(BoltBody* body);

// ============================================================
// 20. POST-PROCESSING EFEKTLERİ
// ============================================================
BOLT_API void bolt_fx_vignette(float strength);       // Köşe kararması
BOLT_API void bolt_fx_crt(float scanline_alpha);      // Eski tüplü TV efekti
BOLT_API void bolt_fx_flash(int r, int g, int b, float alpha); // Ekran flaşı (hasar vb.)
BOLT_API void bolt_fx_fade_to_black(float alpha);     // Siyaha geçiş (0.0=şeffaf, 1.0=tam siyah)

// ============================================================
// 21. GAMEPAD TİTREŞİM (Haptic Rumble)
// ============================================================
BOLT_API void bolt_gamepad_rumble(int index, float low_freq, float high_freq, Uint32 duration_ms);

#endif // BOLT_H

// ---------------------------------------------------------
// IMPLEMENTATION - Include this in ONE C file via #define BOLT_IMPLEMENTATION
// ---------------------------------------------------------
#ifdef BOLT_IMPLEMENTATION

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

SDL_Window* bolt_window = NULL;
SDL_Renderer* bolt_renderer = NULL;
BoltClock bolt_clock = {0};
BoltCamera3D bolt_camera_3d = { {0, 0, 0}, 0, 0 };

static const bool* bolt_keyboard_state = NULL;
static Uint8 bolt_prev_keyboard_state[512] = {0};
static int bolt_numkeys = 0;
static bool bolt_quit_flag = false;
static char bolt_text_input_buffer[512] = {0};
static bool bolt_text_input_active = false;
static Uint32 bolt_mouse_state = 0;
static Uint32 bolt_prev_mouse_state = 0;
static float bolt_mouse_x = 0;
static float bolt_mouse_y = 0;
static float bolt_mouse_delta_x = 0;
static float bolt_mouse_delta_y = 0;
static float bolt_mouse_wheel_x = 0;
static float bolt_mouse_wheel_y = 0;
static int bolt_window_width = 800;
static int bolt_window_height = 600;

static ma_engine bolt_audio_engine;
static bool bolt_audio_initialized = false;

static SDL_Gamepad* bolt_gamepads[4] = {NULL};

#define BOLT_MAX_PARTICLES 1000
static BoltParticle particles[BOLT_MAX_PARTICLES] = {0};

// OTOMATİK BELLEK YÖNETİMİ (Garbage Collector)
#define BOLT_MAX_ASSETS 2048
static BoltImage* bolt_managed_images[BOLT_MAX_ASSETS] = {0};
static BoltFont*  bolt_managed_fonts[BOLT_MAX_ASSETS] = {0};
static BoltSound* bolt_managed_sounds[BOLT_MAX_ASSETS] = {0};
static BoltMusic* bolt_managed_music[BOLT_MAX_ASSETS] = {0};
static int bolt_image_count = 0;
static int bolt_font_count = 0;
static int bolt_sound_count = 0;
static int bolt_music_count = 0;

// 2D KAMERA STATE
static BoltCamera2D bolt_current_cam2d = {0, 0, 1.0f};
static bool bolt_cam2d_active = false;

static inline void bolt_apply_2d(float* x, float* y) {
    if (bolt_cam2d_active) {
        *x = (*x - bolt_current_cam2d.x) * bolt_current_cam2d.zoom + (bolt_window_width / 2.0f);
        *y = (*y - bolt_current_cam2d.y) * bolt_current_cam2d.zoom + (bolt_window_height / 2.0f);
    }
}
static inline void bolt_apply_2d_size(float* w, float* h) {
    if (bolt_cam2d_active) {
        *w *= bolt_current_cam2d.zoom;
        *h *= bolt_current_cam2d.zoom;
    }
}

static void bolt_track_image(BoltImage* img) {
    if (img && bolt_image_count < BOLT_MAX_ASSETS) bolt_managed_images[bolt_image_count++] = img;
}
static void bolt_track_font(BoltFont* font) {
    if (font && bolt_font_count < BOLT_MAX_ASSETS) bolt_managed_fonts[bolt_font_count++] = font;
}
static void bolt_track_sound(BoltSound* sound) {
    if (sound && bolt_sound_count < BOLT_MAX_ASSETS) bolt_managed_sounds[bolt_sound_count++] = sound;
}
static void bolt_track_music(BoltMusic* music) {
    if (music && bolt_music_count < BOLT_MAX_ASSETS) bolt_managed_music[bolt_music_count++] = music;
}

void bolt_init(const char* baslik, int genislik, int yukseklik) {
    srand((unsigned int)time(NULL));

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_GAMEPAD)) {
        SDL_Log("HATA: SDL3 Baslatilamadi: %s", SDL_GetError());
        exit(1);
    }
    
    if (!TTF_Init()) {
        SDL_Log("HATA: SDL3_ttf Baslatilamadi: %s", SDL_GetError());
        exit(1);
    }
    
    bolt_window_width = genislik;
    bolt_window_height = yukseklik;

    if (!SDL_CreateWindowAndRenderer(baslik, genislik, yukseklik, 0, &bolt_window, &bolt_renderer)) {
        SDL_Log("HATA: Pencere veya Renderer olusturulamadi: %s", SDL_GetError());
        exit(1);
    }
    
    // Ses sistemini başlat (miniaudio)
    if (ma_engine_init(NULL, &bolt_audio_engine) == MA_SUCCESS) {
        bolt_audio_initialized = true;
    } else {
        SDL_Log("UYARI: Ses cihazi baslatilamadi (Miniaudio).");
    }

    SDL_SetRenderVSync(bolt_renderer, 1);
    SDL_SetRenderDrawBlendMode(bolt_renderer, SDL_BLENDMODE_BLEND);
    
    // Program kapandığında bolt_quit fonksiyonunu otomatik çağır
    atexit(bolt_quit);
}

void bolt_quit(void) {
    // 1. Önce kullanıcının yüklediği tüm assetleri (resim, ses, font) otomatik temizle
    for (int i = 0; i < bolt_image_count; i++) {
        if (bolt_managed_images[i]) SDL_DestroyTexture(bolt_managed_images[i]);
    }
    for (int i = 0; i < bolt_font_count; i++) {
        if (bolt_managed_fonts[i]) TTF_CloseFont(bolt_managed_fonts[i]);
    }
    for (int i = 0; i < bolt_sound_count; i++) {
        if (bolt_managed_sounds[i]) {
            ma_sound_uninit(bolt_managed_sounds[i]);
            free(bolt_managed_sounds[i]);
        }
    }
    for (int i = 0; i < bolt_music_count; i++) {
        if (bolt_managed_music[i]) {
            ma_sound_uninit(bolt_managed_music[i]);
            free(bolt_managed_music[i]);
        }
    }

    // 2. Motorun kendi bileşenlerini temizle
    if (bolt_audio_initialized) {
        ma_engine_uninit(&bolt_audio_engine);
        bolt_audio_initialized = false;
    }
    if (bolt_renderer) {
        SDL_DestroyRenderer(bolt_renderer);
        bolt_renderer = NULL;
    }
    if (bolt_window) {
        SDL_DestroyWindow(bolt_window);
        bolt_window = NULL;
    }
    TTF_Quit();
    SDL_Quit();
}

void bolt_update(void) {
    bolt_update_clock();
    bolt_update_events();
}

void bolt_update_clock(void) {
    bolt_clock.last_time = bolt_clock.current_time;
    bolt_clock.current_time = SDL_GetTicksNS(); 
    
    if (bolt_clock.last_time > 0) {
        bolt_clock.delta_time = (double)(bolt_clock.current_time - bolt_clock.last_time) / 1000000000.0;
        if (bolt_clock.delta_time > 0.1) {
            bolt_clock.delta_time = 0.016; 
        }
        if (bolt_clock.delta_time > 0) {
            bolt_clock.fps = (float)(1.0 / bolt_clock.delta_time);
        }
    } else {
        bolt_clock.delta_time = 0.016;
    }
}

float bolt_get_fps(void) {
    return bolt_clock.fps;
}

float bolt_get_delta_time(void) {
    return (float)bolt_clock.delta_time;
}

float bolt_get_time(void) {
    return (float)(SDL_GetTicksNS() / 1000000000.0);
}

void bolt_set_canvas_color(int r, int g, int b) {
    SDL_SetRenderDrawColor(bolt_renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    SDL_RenderClear(bolt_renderer);
}

void bolt_clear_background(BoltColor color) {
    SDL_SetRenderDrawColor(bolt_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(bolt_renderer);
}

void bolt_present(void) {
    SDL_RenderPresent(bolt_renderer);
}

bool bolt_should_close(void) {
    return bolt_quit_flag;
}

void bolt_update_events(void) {
    if (bolt_keyboard_state && bolt_numkeys > 0) {
        int copy_size = bolt_numkeys < 512 ? bolt_numkeys : 512;
        memcpy(bolt_prev_keyboard_state, bolt_keyboard_state, copy_size);
    }
    
    bolt_mouse_wheel_x = 0;
    bolt_mouse_wheel_y = 0;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_QUIT) {
            bolt_quit_flag = true;
        }
        else if (event.type == SDL_EVENT_MOUSE_WHEEL) {
            bolt_mouse_wheel_x = event.wheel.x;
            bolt_mouse_wheel_y = event.wheel.y;
        }
        else if (event.type == SDL_EVENT_GAMEPAD_ADDED) {
            for (int i = 0; i < 4; i++) {
                if (!bolt_gamepads[i]) {
                    bolt_gamepads[i] = SDL_OpenGamepad(event.gdevice.which);
                    break;
                }
            }
        }
        else if (event.type == SDL_EVENT_GAMEPAD_REMOVED) {
            for (int i = 0; i < 4; i++) {
                if (bolt_gamepads[i] && SDL_GetGamepadID(bolt_gamepads[i]) == event.gdevice.which) {
                    SDL_CloseGamepad(bolt_gamepads[i]);
                    bolt_gamepads[i] = NULL;
                    break;
                }
            }
        }
        else if (bolt_text_input_active) {
            if (event.type == SDL_EVENT_TEXT_INPUT) {
                strncat(bolt_text_input_buffer, event.text.text, sizeof(bolt_text_input_buffer) - strlen(bolt_text_input_buffer) - 1);
            }
            else if (event.type == SDL_EVENT_KEY_DOWN) {
                if (event.key.key == SDLK_BACKSPACE && strlen(bolt_text_input_buffer) > 0) {
                    bolt_text_input_buffer[strlen(bolt_text_input_buffer)-1] = '\0';
                }
            }
        }
    }

    bolt_keyboard_state = SDL_GetKeyboardState(&bolt_numkeys);
    bolt_prev_mouse_state = bolt_mouse_state;
    bolt_mouse_state = SDL_GetMouseState(&bolt_mouse_x, &bolt_mouse_y);
    
    float mx, my;
    SDL_GetRelativeMouseState(&mx, &my);
    bolt_mouse_delta_x = mx;
    bolt_mouse_delta_y = my;
}

void bolt_update_input(void) {
    bolt_update_events();
}

bool bolt_get_key(SDL_Scancode key) {
    if (!bolt_keyboard_state) return false;
    return bolt_keyboard_state[key];
}

bool bolt_is_key_pressed(SDL_Scancode key) {
    if (!bolt_keyboard_state || key >= 512) return false;
    return (bolt_keyboard_state[key] && !bolt_prev_keyboard_state[key]);
}

bool bolt_is_key_released(SDL_Scancode key) {
    if (!bolt_keyboard_state || key >= 512) return false;
    return (!bolt_keyboard_state[key] && bolt_prev_keyboard_state[key]);
}

bool bolt_get_mouse_button(int button) {
    return (bolt_mouse_state & SDL_BUTTON_MASK(button)) != 0;
}

bool bolt_is_mouse_pressed(int button) {
    return ((bolt_mouse_state & SDL_BUTTON_MASK(button)) != 0) && ((bolt_prev_mouse_state & SDL_BUTTON_MASK(button)) == 0);
}

bool bolt_is_mouse_released(int button) {
    return ((bolt_mouse_state & SDL_BUTTON_MASK(button)) == 0) && ((bolt_prev_mouse_state & SDL_BUTTON_MASK(button)) != 0);
}

float bolt_get_mouse_x(void) { return bolt_mouse_x; }
float bolt_get_mouse_y(void) { return bolt_mouse_y; }
float bolt_get_mouse_delta_x(void) { return bolt_mouse_delta_x; }
float bolt_get_mouse_delta_y(void) { return bolt_mouse_delta_y; }
float bolt_get_mouse_wheel_x(void) { return bolt_mouse_wheel_x; }
float bolt_get_mouse_wheel_y(void) { return bolt_mouse_wheel_y; }

void bolt_start_text_input(void) {
    bolt_text_input_active = true;
    SDL_StartTextInput(bolt_window);
}

void bolt_stop_text_input(void) {
    bolt_text_input_active = false;
    SDL_StopTextInput(bolt_window);
}

const char* bolt_get_text_input(void) {
    return bolt_text_input_buffer;
}

void bolt_clear_text_input(void) {
    bolt_text_input_buffer[0] = '\0';
}

bool bolt_is_gamepad_connected(int index) {
    if (index < 0 || index >= 4) return false;
    return bolt_gamepads[index] != NULL;
}

bool bolt_get_gamepad_button(int index, SDL_GamepadButton button) {
    if (index < 0 || index >= 4 || !bolt_gamepads[index]) return false;
    return SDL_GetGamepadButton(bolt_gamepads[index], button);
}

float bolt_get_gamepad_axis(int index, SDL_GamepadAxis axis) {
    if (index < 0 || index >= 4 || !bolt_gamepads[index]) return 0.0f;
    Sint16 val = SDL_GetGamepadAxis(bolt_gamepads[index], axis);
    return (float)val / 32767.0f;
}

bool bolt_check_collision_rect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
    return (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2);
}

bool bolt_check_collision_circle(float x1, float y1, float r1, float x2, float y2, float r2) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    float mesafe = SDL_sqrtf(dx * dx + dy * dy);
    return mesafe < (r1 + r2);
}

void bolt_emit_particle(float x, float y, float vx, float vy, float life, int r, int g, int b) {
    for (int i = 0; i < BOLT_MAX_PARTICLES; i++) {
        if (!particles[i].active) {
            particles[i].x = x;
            particles[i].y = y;
            particles[i].vx = vx;
            particles[i].vy = vy;
            particles[i].life = life;
            particles[i].max_life = life;
            particles[i].r = r;
            particles[i].g = g;
            particles[i].b = b;
            particles[i].active = true;
            break;
        }
    }
}

void bolt_update_and_draw_particles(void) {
    for (int i = 0; i < BOLT_MAX_PARTICLES; i++) {
        if (particles[i].active) {
            particles[i].x += particles[i].vx * (float)bolt_clock.delta_time;
            particles[i].y += particles[i].vy * (float)bolt_clock.delta_time;
            particles[i].life -= (float)bolt_clock.delta_time;
            
            if (particles[i].life <= 0) {
                particles[i].active = false;
            } else {
                float alpha_ratio = particles[i].life / particles[i].max_life;
                SDL_SetRenderDrawColor(bolt_renderer, (Uint8)particles[i].r, (Uint8)particles[i].g, (Uint8)particles[i].b, (Uint8)(255 * alpha_ratio));
                SDL_FRect p_rect = { particles[i].x, particles[i].y, 4.0f, 4.0f };
                SDL_RenderFillRect(bolt_renderer, &p_rect);
            }
        }
    }
}

void bolt_draw_color(BoltColor color) {
    SDL_SetRenderDrawColor(bolt_renderer, color.r, color.g, color.b, color.a);
}

void bolt_draw_pixel(float x, float y, int r, int g, int b) {
    bolt_apply_2d(&x, &y);
    SDL_SetRenderDrawColor(bolt_renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    SDL_RenderPoint(bolt_renderer, x, y);
}

void bolt_draw_line(float x1, float y1, float x2, float y2, int r, int g, int b) {
    bolt_apply_2d(&x1, &y1);
    bolt_apply_2d(&x2, &y2);
    SDL_SetRenderDrawColor(bolt_renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    SDL_RenderLine(bolt_renderer, x1, y1, x2, y2);
}

void bolt_draw_rect(float x, float y, float w, float h, int r, int g, int b) {
    bolt_apply_2d(&x, &y);
    bolt_apply_2d_size(&w, &h);
    SDL_FRect rect = { x, y, w, h };
    SDL_SetRenderDrawColor(bolt_renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    SDL_RenderRect(bolt_renderer, &rect);
}

void bolt_draw_rect_filled(float x, float y, float w, float h, int r, int g, int b) {
    bolt_apply_2d(&x, &y);
    bolt_apply_2d_size(&w, &h);
    SDL_FRect rect = { x, y, w, h };
    SDL_SetRenderDrawColor(bolt_renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    SDL_RenderFillRect(bolt_renderer, &rect);
}

void bolt_draw_circle(float x, float y, float radius, int r, int g, int b) {
    bolt_apply_2d(&x, &y);
    if (bolt_cam2d_active) radius *= bolt_current_cam2d.zoom;
    SDL_SetRenderDrawColor(bolt_renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    float offsetx, offsety, d;
    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    while (offsety >= offsetx) {
        SDL_RenderPoint(bolt_renderer, x + offsetx, y + offsety);
        SDL_RenderPoint(bolt_renderer, x + offsety, y + offsetx);
        SDL_RenderPoint(bolt_renderer, x - offsetx, y + offsety);
        SDL_RenderPoint(bolt_renderer, x - offsety, y + offsetx);
        SDL_RenderPoint(bolt_renderer, x + offsetx, y - offsety);
        SDL_RenderPoint(bolt_renderer, x + offsety, y - offsetx);
        SDL_RenderPoint(bolt_renderer, x - offsetx, y - offsety);
        SDL_RenderPoint(bolt_renderer, x - offsety, y - offsetx);
        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        } else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

void bolt_draw_circle_filled(float x, float y, float radius, int r, int g, int b) {
    bolt_apply_2d(&x, &y);
    if (bolt_cam2d_active) radius *= bolt_current_cam2d.zoom;
    SDL_SetRenderDrawColor(bolt_renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    for (float w = 0; w <= radius * 2; w++) {
        for (float h = 0; h <= radius * 2; h++) {
            float dx = radius - w;
            float dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderPoint(bolt_renderer, x - dx, y - dy);
            }
        }
    }
}

BoltImage* bolt_load_image(const char* yol) {
    SDL_Surface* surface = SDL_LoadPNG(yol);
    if (surface == NULL) {
        surface = IMG_Load(yol);
        if (surface == NULL) {
            SDL_Log("HATA: [%s] yuklenemedi! Sebep: %s", yol, SDL_GetError());
            return NULL;
        }
    }
    BoltImage* texture = SDL_CreateTextureFromSurface(bolt_renderer, surface);
    SDL_DestroySurface(surface);
    if (texture) bolt_track_image(texture);
    return texture;
}

void bolt_get_image_size(SDL_Texture* tex, float* w, float* h) {
    if (!tex) {
        if (w) *w = 0;
        if (h) *h = 0;
        return;
    }
    SDL_GetTextureSize(tex, w, h);
}

void bolt_draw_image(BoltImage* tex, float x, float y, float w, float h) {
    if (!tex) return;
    bolt_apply_2d(&x, &y);
    bolt_apply_2d_size(&w, &h);
    SDL_FRect hedef = { x, y, w, h };
    SDL_RenderTexture(bolt_renderer, tex, NULL, &hedef);
}

void bolt_draw_image_rec(BoltImage* tex, BoltRect src, BoltRect dst) {
    if (!tex) return;
    bolt_apply_2d(&dst.x, &dst.y);
    bolt_apply_2d_size(&dst.w, &dst.h);
    SDL_RenderTexture(bolt_renderer, tex, &src, &dst);
}

void bolt_draw_image_ex(BoltImage* tex, float x, float y, float w, float h, float angle, BoltPoint* center, BoltFlipMode flip) {
    if (!tex) return;
    bolt_apply_2d(&x, &y);
    bolt_apply_2d_size(&w, &h);
    
    BoltPoint local_center;
    if (center) {
        local_center = *center;
        bolt_apply_2d_size(&local_center.x, &local_center.y);
        center = &local_center;
    }
    
    SDL_FRect dst = { x, y, w, h };
    SDL_RenderTextureRotated(bolt_renderer, tex, NULL, &dst, angle, center, flip);
}

BoltImage* bolt_create_render_target(int w, int h) {
    BoltImage* tex = SDL_CreateTexture(bolt_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
    if (tex) bolt_track_image(tex);
    return tex;
}

void bolt_set_render_target(SDL_Texture* target) {
    SDL_SetRenderTarget(bolt_renderer, target);
}

void bolt_reset_render_target(void) {
    SDL_SetRenderTarget(bolt_renderer, NULL);
}

BoltColor bolt_read_pixel(float x, float y) {
    BoltColor c = {0, 0, 0, 255};
    SDL_Rect rect = { (int)x, (int)y, 1, 1 };
    SDL_Surface* surface = SDL_RenderReadPixels(bolt_renderer, &rect);
    if (surface) {
        SDL_ReadSurfacePixel(surface, 0, 0, &c.r, &c.g, &c.b, &c.a);
        SDL_DestroySurface(surface);
    }
    return c;
}

BoltImage* bolt_load_image_from_buffer(const void* buffer, size_t size) {
    if (!buffer || size == 0) return NULL;
    SDL_IOStream* stream = SDL_IOFromConstMem(buffer, size);
    if (!stream) return NULL;
    BoltImage* img = IMG_LoadTexture_IO(bolt_renderer, stream, true);
    if (img) bolt_track_image(img);
    return img;
}

void bolt_move_logic(float* pos, float hedef_hiz) {
    *pos += (float)(hedef_hiz * bolt_clock.delta_time);
}

void bolt_draw_sprite_anim(BoltSprite* sprite, float x, float y, float w, float h) {
    if (!sprite || !sprite->sheet || sprite->kare_sayisi <= 0) return;
    sprite->zaman_sayaci += (float)bolt_clock.delta_time;
    if (sprite->zaman_sayaci >= (1.0f / sprite->anim_hizi)) {
        sprite->su_anki_kare = (sprite->su_anki_kare + 1) % sprite->kare_sayisi;
        sprite->zaman_sayaci = 0;
    }
    float tex_w, tex_h;
    SDL_GetTextureSize(sprite->sheet, &tex_w, &tex_h);
    float kare_genislik = tex_w / sprite->kare_sayisi;
    SDL_FRect src_rect = { sprite->su_anki_kare * kare_genislik, 0, kare_genislik, tex_h };
    SDL_FRect dst_rect = { x, y, w, h };
    SDL_RenderTexture(bolt_renderer, sprite->sheet, &src_rect, &dst_rect);
}

BoltFont* bolt_load_font(const char* yol, int boyut) {
    BoltFont* font = TTF_OpenFont(yol, (float)boyut);
    if (!font) {
        SDL_Log("HATA: [%s] fontu yuklenemedi! %s", yol, SDL_GetError());
    } else {
        bolt_track_font(font);
    }
    return font;
}

void bolt_draw_text(BoltFont* font, const char* metin, float x, float y, int r, int g, int b, BoltAnchor anchor) {
    if (!font || !metin) return;
    bolt_apply_2d(&x, &y);
    SDL_Color renk = {(Uint8)r, (Uint8)g, (Uint8)b, 255};
    SDL_Surface* surface = TTF_RenderText_Blended(font, metin, 0, renk);
    if (!surface) return;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(bolt_renderer, surface);
    float w = (float)surface->w;
    float h = (float)surface->h;
    if (anchor == BOLT_ANCHOR_CENTER) { x -= w/2; y -= h/2; }
    else if (anchor == BOLT_ANCHOR_BOTTOM_RIGHT) { x -= w; y -= h; }
    SDL_FRect hedef = { x, y, w, h };
    SDL_RenderTexture(bolt_renderer, texture, NULL, &hedef);
    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

BoltVec3 bolt_transform_3d(BoltVec3 p) {
    float tx = p.x - bolt_camera_3d.position.x;
    float ty = p.y - bolt_camera_3d.position.y;
    float tz = p.z - bolt_camera_3d.position.z;

    float cos_yaw = cosf(bolt_camera_3d.yaw);
    float sin_yaw = sinf(bolt_camera_3d.yaw);
    float rx = tx * cos_yaw - tz * sin_yaw;
    float rz = tx * sin_yaw + tz * cos_yaw;

    float cos_pitch = cosf(bolt_camera_3d.pitch);
    float sin_pitch = sinf(bolt_camera_3d.pitch);
    float ry = ty * cos_pitch - rz * sin_pitch;
    float final_z = ty * sin_pitch + rz * cos_pitch;

    return (BoltVec3){rx, ry, final_z};
}

SDL_FPoint bolt_project_transformed(BoltVec3 tp) {
    float factor = 600.0f / tp.z;
    SDL_FPoint p2d;
    p2d.x = tp.x * factor + (bolt_window_width / 2.0f);
    p2d.y = -tp.y * factor + (bolt_window_height / 2.0f);
    return p2d;
}

void bolt_draw_line_3d(BoltVec3 p1, BoltVec3 p2) {
    BoltVec3 tp1 = bolt_transform_3d(p1);
    BoltVec3 tp2 = bolt_transform_3d(p2);
    
    if (tp1.z < 0.1f && tp2.z < 0.1f) return; // Behind camera
    
    // Clipping against near plane Z=0.1
    if (tp1.z < 0.1f) {
        float t = (0.1f - tp1.z) / (tp2.z - tp1.z);
        tp1.x = tp1.x + t * (tp2.x - tp1.x);
        tp1.y = tp1.y + t * (tp2.y - tp1.y);
        tp1.z = 0.1f;
    } else if (tp2.z < 0.1f) {
        float t = (0.1f - tp2.z) / (tp1.z - tp2.z);
        tp2.x = tp2.x + t * (tp1.x - tp2.x);
        tp2.y = tp2.y + t * (tp1.y - tp2.y);
        tp2.z = 0.1f;
    }
    
    SDL_FPoint s1 = bolt_project_transformed(tp1);
    SDL_FPoint s2 = bolt_project_transformed(tp2);
    SDL_RenderLine(bolt_renderer, s1.x, s1.y, s2.x, s2.y);
}

void bolt_draw_cube(float x, float y, float z, float size, int r, int g, int b) {
    BoltVec3 v[8] = {
        {x-size, y-size, z-size}, {x+size, y-size, z-size},
        {x+size, y+size, z-size}, {x-size, y+size, z-size},
        {x-size, y-size, z+size}, {x+size, y-size, z+size},
        {x+size, y+size, z+size}, {x-size, y+size, z+size}
    };
    SDL_SetRenderDrawColor(bolt_renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    for(int i=0; i<4; i++) {
        bolt_draw_line_3d(v[i], v[(i+1)%4]);
        bolt_draw_line_3d(v[i+4], v[((i+1)%4)+4]);
        bolt_draw_line_3d(v[i], v[i+4]);
    }
}

void bolt_draw_cube_textured(SDL_Texture* tex, float x, float y, float z, float size) {
    if (!tex) return;
    BoltVec3 v[8] = {
        {x-size, y-size, z-size}, {x+size, y-size, z-size},
        {x+size, y+size, z-size}, {x-size, y+size, z-size},
        {x-size, y-size, z+size}, {x+size, y-size, z+size},
        {x+size, y+size, z+size}, {x-size, y+size, z+size}
    };
    int faces[6][4] = { {0,1,2,3}, {1,5,6,2}, {5,4,7,6}, {4,0,3,7}, {4,5,1,0}, {3,2,6,7} };
    
    typedef struct { int idx; float avg_z; BoltVec3 tv[4]; } FaceData;
    FaceData fd[6];
    
    for (int i=0; i<6; i++) {
        fd[i].idx = i;
        float z_sum = 0;
        for (int j=0; j<4; j++) {
            fd[i].tv[j] = bolt_transform_3d(v[faces[i][j]]);
            z_sum += fd[i].tv[j].z;
        }
        fd[i].avg_z = z_sum / 4.0f;
    }
    
    for (int i=0; i<5; i++) {
        for (int j=i+1; j<6; j++) {
            if (fd[i].avg_z < fd[j].avg_z) {
                FaceData temp = fd[i]; fd[i] = fd[j]; fd[j] = temp;
            }
        }
    }
    
    for (int i=0; i<6; i++) {
        if (fd[i].tv[0].z < 0.1f || fd[i].tv[1].z < 0.1f || fd[i].tv[2].z < 0.1f || fd[i].tv[3].z < 0.1f) continue;
        
        SDL_FPoint p[4];
        for (int j=0; j<4; j++) p[j] = bolt_project_transformed(fd[i].tv[j]);
        
        SDL_Vertex vertices[4];
        for(int j=0; j<4; j++) {
            vertices[j].position = p[j];
            vertices[j].color = (SDL_FColor){1.0f, 1.0f, 1.0f, 1.0f};
        }
        vertices[0].tex_coord = (SDL_FPoint){0.0f, 0.0f};
        vertices[1].tex_coord = (SDL_FPoint){1.0f, 0.0f};
        vertices[2].tex_coord = (SDL_FPoint){1.0f, 1.0f};
        vertices[3].tex_coord = (SDL_FPoint){0.0f, 1.0f};
        
        int indices[6] = {0, 1, 2, 0, 2, 3};
        bolt_draw_geometry(tex, vertices, 4, indices, 6);
    }
}

void bolt_draw_plane_textured(SDL_Texture* tex, float x, float y, float z, float w, float d) {
    if (!tex) return;
    BoltVec3 v[4] = { {x-w, y, z-d}, {x+w, y, z-d}, {x+w, y, z+d}, {x-w, y, z+d} };
    BoltVec3 tv[4];
    for(int i=0; i<4; i++) tv[i] = bolt_transform_3d(v[i]);
    
    if (tv[0].z < 0.1f || tv[1].z < 0.1f || tv[2].z < 0.1f || tv[3].z < 0.1f) return;
    
    SDL_FPoint p[4];
    for (int j=0; j<4; j++) p[j] = bolt_project_transformed(tv[j]);
    
    SDL_Vertex vertices[4];
    for(int j=0; j<4; j++) {
        vertices[j].position = p[j];
        vertices[j].color = (SDL_FColor){1.0f, 1.0f, 1.0f, 1.0f};
    }
    vertices[0].tex_coord = (SDL_FPoint){0.0f, 0.0f};
    vertices[1].tex_coord = (SDL_FPoint){1.0f, 0.0f};
    vertices[2].tex_coord = (SDL_FPoint){1.0f, 1.0f};
    vertices[3].tex_coord = (SDL_FPoint){0.0f, 1.0f};
    
    int indices[6] = {0, 1, 2, 0, 2, 3};
    bolt_draw_geometry(tex, vertices, 4, indices, 6);
}

void bolt_draw_pyramid(float x, float y, float z, float size, int r, int g, int b) {
    BoltVec3 v[5] = {
        {x, y + size, z},               
        {x - size, y - size, z - size}, 
        {x + size, y - size, z - size}, 
        {x + size, y - size, z + size}, 
        {x - size, y - size, z + size}  
    };
    SDL_SetRenderDrawColor(bolt_renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    for(int i=1; i<=4; i++) {
        int next = (i == 4) ? 1 : i + 1;
        bolt_draw_line_3d(v[i], v[next]);
        bolt_draw_line_3d(v[0], v[i]);
    }
}

void bolt_draw_sphere(float x, float y, float z, float radius, int segments, int r, int g, int b) {
    SDL_SetRenderDrawColor(bolt_renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    for (int i = 0; i <= segments; i++) {
        float lat0 = PI * (-0.5f + (float)(i - 1) / segments);
        float z0 = sinf(lat0);
        float zr0 = cosf(lat0);
        float lat1 = PI * (-0.5f + (float)i / segments);
        float z1 = sinf(lat1);
        float zr1 = cosf(lat1);
        for (int j = 0; j <= segments; j++) {
            float lng = 2 * PI * (float)(j - 1) / segments;
            float x0 = cosf(lng);
            float y0 = sinf(lng);
            BoltVec3 v1 = { x + x0 * zr0 * radius, y + y0 * zr0 * radius, z + z0 * radius };
            BoltVec3 v2 = { x + x0 * zr1 * radius, y + y0 * zr1 * radius, z + z1 * radius };
            bolt_draw_line_3d(v1, v2);

            float lng_next = 2 * PI * (float)(j) / segments;
            float x1 = cosf(lng_next);
            float y1_h = sinf(lng_next);
            BoltVec3 v3 = { x + x1 * zr0 * radius, y + y1_h * zr0 * radius, z + z0 * radius };
            bolt_draw_line_3d(v1, v3);
        }
    }
}

BoltSound* bolt_load_sound(const char* yol) {
    if (!bolt_audio_initialized) return NULL;
    BoltSound* sound = (BoltSound*)malloc(sizeof(BoltSound));
    if (ma_sound_init_from_file(&bolt_audio_engine, yol, 0, NULL, NULL, sound) != MA_SUCCESS) {
        SDL_Log("HATA: [%s] sesi yuklenemedi!", yol);
        free(sound);
        return NULL;
    }
    bolt_track_sound(sound);
    return sound;
}

void bolt_play_sound(BoltSound* sound) {
    if (sound && bolt_audio_initialized) {
        ma_sound_start(sound);
    }
}

void bolt_set_sound_volume(BoltSound* sound, int volume) {
    if (sound && bolt_audio_initialized) {
        ma_sound_set_volume(sound, volume / 128.0f);
    }
}

void bolt_set_sound_pitch(BoltSound* sound, float pitch) {
    if (sound && bolt_audio_initialized) {
        ma_sound_set_pitch(sound, pitch);
    }
}

BoltMusic* bolt_load_music(const char* yol) {
    if (!bolt_audio_initialized) return NULL;
    BoltMusic* music = (BoltMusic*)malloc(sizeof(BoltMusic));
    // Load as stream for music
    if (ma_sound_init_from_file(&bolt_audio_engine, yol, MA_SOUND_FLAG_STREAM, NULL, NULL, music) != MA_SUCCESS) {
        SDL_Log("HATA: [%s] muzigi yuklenemedi!", yol);
        free(music);
        return NULL;
    }
    bolt_track_music(music);
    return music;
}

void bolt_play_music(BoltMusic* music, bool loop) {
    if (music && bolt_audio_initialized) {
        ma_sound_set_looping(music, loop ? MA_TRUE : MA_FALSE);
        ma_sound_start(music);
    }
}

void bolt_stop_music(void) {
    for (int i=0; i<bolt_music_count; i++) {
        if (bolt_managed_music[i]) ma_sound_stop(bolt_managed_music[i]);
    }
}

void bolt_set_music_volume(int volume) {
    for (int i=0; i<bolt_music_count; i++) {
        if (bolt_managed_music[i]) ma_sound_set_volume(bolt_managed_music[i], volume / 100.0f);
    }
}

int bolt_random_int(int min, int max) {
    if (min >= max) return min;
    return min + (rand() % (max - min + 1));
}

float bolt_random_float(float min, float max) {
    if (min >= max) return min;
    float scale = rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}

float bolt_lerp(float a, float b, float t) {
    return a + t * (b - a);
}

float bolt_distance_2d(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return SDL_sqrtf(dx*dx + dy*dy);
}

float bolt_distance_3d(BoltVec3 v1, BoltVec3 v2) {
    float dx = v2.x - v1.x;
    float dy = v2.y - v1.y;
    float dz = v2.z - v1.z;
    return SDL_sqrtf(dx*dx + dy*dy + dz*dz);
}

float bolt_angle_2d(float x1, float y1, float x2, float y2) {
    float angle = SDL_atan2f(y2 - y1, x2 - x1) * (180.0f / PI);
    if (angle < 0) angle += 360.0f;
    return angle;
}

void bolt_set_window_icon(const char* filepath) {
    SDL_Surface* surface = SDL_LoadPNG(filepath);
    if (!surface) surface = IMG_Load(filepath);
    if (surface) {
        SDL_SetWindowIcon(bolt_window, surface);
        SDL_DestroySurface(surface);
    } else {
        SDL_Log("HATA: Ikon yuklenemedi: %s", filepath);
    }
}

void bolt_show_message_box(const char* title, const char* message) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, message, bolt_window);
}

void bolt_set_clipboard_text(const char* text) {
    SDL_SetClipboardText(text);
}

const char* bolt_get_clipboard_text(void) {
    return SDL_GetClipboardText();
}

bool bolt_save_text(const char* filepath, const char* content) {
    if (!filepath || !content) return false;
    SDL_IOStream* file = SDL_IOFromFile(filepath, "w");
    if (!file) return false;
    SDL_WriteIO(file, content, strlen(content));
    SDL_CloseIO(file);
    return true;
}

char* bolt_load_text(const char* filepath) {
    if (!filepath) return NULL;
    SDL_IOStream* file = SDL_IOFromFile(filepath, "r");
    if (!file) return NULL;
    size_t size = (size_t)SDL_GetIOSize(file);
    char* buffer = (char*)malloc(size + 1);
    SDL_ReadIO(file, buffer, size);
    buffer[size] = '\0';
    SDL_CloseIO(file);
    return buffer;
}

bool bolt_gui_button(float x, float y, float w, float h, const char* text) {
    float mx = bolt_get_mouse_x();
    float my = bolt_get_mouse_y();
    bool is_hover = (mx >= x && mx <= x + w && my >= y && my <= y + h);
    bool is_pressed = is_hover && bolt_get_mouse_button(1);
    
    if (is_pressed) {
        bolt_draw_rect_filled(x, y, w, h, 100, 100, 100);
    } else if (is_hover) {
        bolt_draw_rect_filled(x, y, w, h, 150, 150, 150);
    } else {
        bolt_draw_rect_filled(x, y, w, h, 200, 200, 200);
    }
    bolt_draw_rect(x, y, w, h, 50, 50, 50);
    
    BoltFont* font = bolt_font_count > 0 ? bolt_managed_fonts[0] : NULL;
    if (font && text) {
        bolt_draw_text(font, text, x + w/2, y + h/2, 255, 255, 255, BOLT_ANCHOR_CENTER);
    }
    
    return is_hover && bolt_is_mouse_pressed(1);
}

void bolt_begin_2d(BoltCamera2D cam) {
    bolt_current_cam2d = cam;
    bolt_cam2d_active = true;
}

void bolt_end_2d(void) {
    bolt_cam2d_active = false;
}

void bolt_set_fullscreen(bool fullscreen) {
    SDL_SetWindowFullscreen(bolt_window, fullscreen);
}

void bolt_set_window_title(const char* title) {
    SDL_SetWindowTitle(bolt_window, title);
}

int bolt_get_window_width(void) {
    int w, h;
    SDL_GetWindowSize(bolt_window, &w, &h);
    return w;
}

int bolt_get_window_height(void) {
    int w, h;
    SDL_GetWindowSize(bolt_window, &w, &h);
    return h;
}

// ---------------------------------------------------------
// 12. GELİŞMİŞ RENDER KONTROLLERİ (İMPLEMENTASYON)
// ---------------------------------------------------------

void bolt_set_render_viewport(float x, float y, float w, float h) {
    SDL_Rect rect = { (int)x, (int)y, (int)w, (int)h };
    SDL_SetRenderViewport(bolt_renderer, &rect);
}

void bolt_reset_render_viewport(void) {
    SDL_SetRenderViewport(bolt_renderer, NULL);
}

void bolt_set_render_clip(float x, float y, float w, float h) {
    SDL_Rect rect = { (int)x, (int)y, (int)w, (int)h };
    SDL_SetRenderClipRect(bolt_renderer, &rect);
}

void bolt_reset_render_clip(void) {
    SDL_SetRenderClipRect(bolt_renderer, NULL);
}

void bolt_set_render_scale(float scale_x, float scale_y) {
    SDL_SetRenderScale(bolt_renderer, scale_x, scale_y);
}

void bolt_set_blend_mode(SDL_BlendMode mode) {
    SDL_SetRenderDrawBlendMode(bolt_renderer, mode);
}

void bolt_set_texture_blend_mode(SDL_Texture* tex, SDL_BlendMode mode) {
    if (tex) SDL_SetTextureBlendMode(tex, mode);
}

void bolt_set_texture_color_mod(SDL_Texture* tex, int r, int g, int b) {
    if (tex) SDL_SetTextureColorMod(tex, (Uint8)r, (Uint8)g, (Uint8)b);
}

void bolt_set_texture_alpha_mod(SDL_Texture* tex, int a) {
    if (tex) SDL_SetTextureAlphaMod(tex, (Uint8)a);
}

void bolt_draw_geometry(SDL_Texture* tex, const SDL_Vertex* vertices, int num_vertices, const int* indices, int num_indices) {
    SDL_RenderGeometry(bolt_renderer, tex, vertices, num_vertices, indices, num_indices);
}

// ---------------------------------------------------------
// 13. SİSTEM, MONİTÖR, FARE VE DİYALOGLAR (YENİ EKLENENLER)
// ---------------------------------------------------------

int bolt_get_monitor_width(void) {
    const SDL_DisplayMode* mode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
    return mode ? mode->w : 0;
}

int bolt_get_monitor_height(void) {
    const SDL_DisplayMode* mode = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());
    return mode ? mode->h : 0;
}

void bolt_hide_cursor(void) { SDL_HideCursor(); }
void bolt_show_cursor(void) { SDL_ShowCursor(); }
void bolt_lock_cursor(bool lock) { SDL_SetWindowRelativeMouseMode(bolt_window, lock); }

void bolt_set_cursor_type(BoltCursorType type) {
    SDL_SystemCursor sdl_type = SDL_SYSTEM_CURSOR_DEFAULT;
    switch(type) {
        case BOLT_CURSOR_TEXT: sdl_type = SDL_SYSTEM_CURSOR_TEXT; break;
        case BOLT_CURSOR_WAIT: sdl_type = SDL_SYSTEM_CURSOR_WAIT; break;
        case BOLT_CURSOR_CROSSHAIR: sdl_type = SDL_SYSTEM_CURSOR_CROSSHAIR; break;
        case BOLT_CURSOR_PROGRESS: sdl_type = SDL_SYSTEM_CURSOR_PROGRESS; break;
        case BOLT_CURSOR_HAND: sdl_type = SDL_SYSTEM_CURSOR_POINTER; break;
        case BOLT_CURSOR_NOT_ALLOWED: sdl_type = SDL_SYSTEM_CURSOR_NOT_ALLOWED; break;
        default: break;
    }
    SDL_Cursor* cursor = SDL_CreateSystemCursor(sdl_type);
    SDL_SetCursor(cursor);
}

int bolt_get_system_ram(void) { return SDL_GetSystemRAM(); }
int bolt_get_cpu_count(void) { return SDL_GetNumLogicalCPUCores(); }
bool bolt_is_dark_mode(void) { return SDL_GetSystemTheme() == SDL_SYSTEM_THEME_DARK; }

// Dosya Seçici Diyaloğu
static char bolt_dialog_result_buffer[1024] = {0};
static bool bolt_dialog_finished = false;

static void SDLCALL bolt_dialog_callback(void *userdata, const char * const *filelist, int filter) {
    if (filelist && filelist[0]) {
        strncpy(bolt_dialog_result_buffer, filelist[0], sizeof(bolt_dialog_result_buffer)-1);
    } else {
        bolt_dialog_result_buffer[0] = '\0';
    }
    bolt_dialog_finished = true;
}

void bolt_open_file_dialog(void) {
    bolt_dialog_finished = false;
    bolt_dialog_result_buffer[0] = '\0';
    SDL_ShowOpenFileDialog(bolt_dialog_callback, NULL, bolt_window, NULL, 0, NULL, false);
}

bool bolt_is_dialog_ready(void) {
    return bolt_dialog_finished;
}


const char* bolt_get_dialog_result(void) {
    return bolt_dialog_result_buffer;
}

// =============================================================
// 13. LOG SİSTEMİ
// =============================================================
#include <stdio.h>
#include <stdarg.h>

static FILE* bolt_log_file = NULL;

void bolt_log_set_file(const char* filepath) {
    if (bolt_log_file) fclose(bolt_log_file);
    bolt_log_file = fopen(filepath, "a");
}

void bolt_log(BoltLogLevel level, const char* fmt, ...) {
    const char* level_strs[] = { "[INFO]", "[WARN]", "[ERROR]", "[DEBUG]" };
    const char* level_colors[] = { "", "", "", "" }; // SDL_Log handles color on some platforms
    char buf[2048];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    SDL_Log("%s %s", level_strs[level], buf);

    if (bolt_log_file) {
        fprintf(bolt_log_file, "%s %s\n", level_strs[level], buf);
        fflush(bolt_log_file);
    }
}

// =============================================================
// 14. GELİŞMİŞ GUI WİDGET'LARI
// =============================================================

void bolt_slider_init(BoltSlider* s, float x, float y, float w, float h, float min, float max, float value) {
    if (!s) return;
    s->x = x; s->y = y; s->w = w; s->h = h;
    s->min = min; s->max = max;
    s->value = value; s->dragging = false;
}

bool bolt_slider_draw(BoltSlider* s) {
    if (!s) return false;
    float old_value = s->value;
    float mx = bolt_get_mouse_x(), my = bolt_get_mouse_y();

    if (bolt_is_mouse_pressed(1) && mx >= s->x && mx <= s->x + s->w && my >= s->y && my <= s->y + s->h)
        s->dragging = true;
    if (!bolt_get_mouse_button(1)) s->dragging = false;
    if (s->dragging) {
        float t = (mx - s->x) / s->w;
        if (t < 0) t = 0; if (t > 1) t = 1;
        s->value = s->min + t * (s->max - s->min);
    }

    // Arka plan (track)
    bolt_draw_rect_filled(s->x, s->y + s->h * 0.35f, s->w, s->h * 0.3f, 80, 80, 80);
    // Aktif kisim
    float filled = (s->value - s->min) / (s->max - s->min) * s->w;
    bolt_draw_rect_filled(s->x, s->y + s->h * 0.35f, filled, s->h * 0.3f, 100, 180, 255);
    // Handle (daire/tutacak)
    bolt_draw_circle_filled(s->x + filled, s->y + s->h * 0.5f, s->h * 0.45f, 220, 220, 220);
    bolt_draw_circle(s->x + filled, s->y + s->h * 0.5f, s->h * 0.45f, 100, 180, 255);

    return s->value != old_value;
}

void bolt_checkbox_init(BoltCheckbox* c, float x, float y, float size, bool checked) {
    if (!c) return;
    c->x = x; c->y = y; c->size = size; c->checked = checked;
}

bool bolt_checkbox_draw(BoltCheckbox* c) {
    if (!c) return false;
    float mx = bolt_get_mouse_x(), my = bolt_get_mouse_y();
    bool hov = (mx >= c->x && mx <= c->x + c->size && my >= c->y && my <= c->y + c->size);

    if (hov && bolt_is_mouse_pressed(1)) c->checked = !c->checked;

    // Kutu
    bolt_draw_rect_filled(c->x, c->y, c->size, c->size, hov ? 220 : 200, hov ? 220 : 200, hov ? 220 : 200);
    bolt_draw_rect(c->x, c->y, c->size, c->size, 60, 60, 60);

    // Tik işareti
    if (c->checked) {
        float p = c->size * 0.2f;
        bolt_draw_line(c->x + p, c->y + c->size * 0.5f,
                       c->x + c->size * 0.45f, c->y + c->size - p, 30, 160, 60);
        bolt_draw_line(c->x + c->size * 0.45f, c->y + c->size - p,
                       c->x + c->size - p, c->y + p, 30, 160, 60);
    }
    return c->checked;
}

void bolt_textbox_init(BoltTextBox* t, float x, float y, float w, float h) {
    if (!t) return;
    t->x = x; t->y = y; t->w = w; t->h = h;
    t->active = false; t->text[0] = '\0';
}

void bolt_textbox_draw(BoltTextBox* t, BoltFont* font) {
    if (!t) return;
    float mx = bolt_get_mouse_x(), my = bolt_get_mouse_y();
    if (bolt_is_mouse_pressed(1)) {
        t->active = (mx >= t->x && mx <= t->x + t->w && my >= t->y && my <= t->y + t->h);
        if (t->active) bolt_start_text_input();
        else bolt_stop_text_input();
    }

    // Kutu
    bolt_draw_rect_filled(t->x, t->y, t->w, t->h, 250, 250, 250);
    bolt_draw_rect(t->x, t->y, t->w, t->h, t->active ? 100 : 150, t->active ? 180 : 150, t->active ? 255 : 150);

    // Gelen metin varsa biriktir
    if (t->active) {
        const char* inp = bolt_get_text_input();
        if (inp && inp[0] != '\0') {
            strncat(t->text, inp, sizeof(t->text) - strlen(t->text) - 1);
            bolt_clear_text_input();
        }
        // Backspace
        if (bolt_is_key_pressed(SDLK_BACKSPACE - 8)) { // SDL_SCANCODE_BACKSPACE = 42
            size_t len = strlen(t->text);
            if (len > 0) t->text[len - 1] = '\0';
        }
    }

    if (font) {
        char display[514];
        snprintf(display, sizeof(display), "%s%s", t->text, t->active ? "|" : "");
        bolt_draw_text(font, display, t->x + 5, t->y + t->h * 0.5f - 1, 30, 30, 30, BOLT_ANCHOR_TOP_LEFT);
    }
}

// =============================================================
// 15. RENK EFEKTLERİ
// =============================================================

void bolt_draw_gradient_rect(float x, float y, float w, float h, BoltColor c1, BoltColor c2, bool horizontal) {
    if (horizontal) {
        for (float i = 0; i < w; i++) {
            float t = i / w;
            int cr = (int)(c1.r + t * (c2.r - c1.r));
            int cg = (int)(c1.g + t * (c2.g - c1.g));
            int cb = (int)(c1.b + t * (c2.b - c1.b));
            int ca = (int)(c1.a + t * (c2.a - c1.a));
            SDL_SetRenderDrawColor(bolt_renderer, (Uint8)cr, (Uint8)cg, (Uint8)cb, (Uint8)ca);
            SDL_FRect line = { x + i, y, 1, h };
            SDL_RenderFillRect(bolt_renderer, &line);
        }
    } else {
        for (float i = 0; i < h; i++) {
            float t = i / h;
            int cr = (int)(c1.r + t * (c2.r - c1.r));
            int cg = (int)(c1.g + t * (c2.g - c1.g));
            int cb = (int)(c1.b + t * (c2.b - c1.b));
            int ca = (int)(c1.a + t * (c2.a - c1.a));
            SDL_SetRenderDrawColor(bolt_renderer, (Uint8)cr, (Uint8)cg, (Uint8)cb, (Uint8)ca);
            SDL_FRect line = { x, y + i, w, 1 };
            SDL_RenderFillRect(bolt_renderer, &line);
        }
    }
}

void bolt_draw_rounded_rect(float x, float y, float w, float h, float radius, int r, int g, int b) {
    SDL_SetRenderDrawColor(bolt_renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    // Kenarlari ciz
    SDL_FRect top    = { x + radius, y,         w - 2*radius, 1 };
    SDL_FRect bottom = { x + radius, y + h - 1, w - 2*radius, 1 };
    SDL_FRect left   = { x,         y + radius, 1,            h - 2*radius };
    SDL_FRect right_ = { x + w - 1, y + radius, 1,            h - 2*radius };
    SDL_RenderFillRect(bolt_renderer, &top);
    SDL_RenderFillRect(bolt_renderer, &bottom);
    SDL_RenderFillRect(bolt_renderer, &left);
    SDL_RenderFillRect(bolt_renderer, &right_);
    // Koseler (yaklasik cember ile)
    int segs = (int)radius;
    for (int i = 0; i < segs; i++) {
        float a0 = PI * 0.5f * i / segs, a1 = PI * 0.5f * (i+1) / segs;
        // Sol-ust
        SDL_RenderLine(bolt_renderer, x+radius - cosf(a0)*radius, y+radius - sinf(a0)*radius,
                                      x+radius - cosf(a1)*radius, y+radius - sinf(a1)*radius);
        // Sag-ust
        SDL_RenderLine(bolt_renderer, x+w-radius + sinf(a0)*radius, y+radius - cosf(a0)*radius,
                                      x+w-radius + sinf(a1)*radius, y+radius - cosf(a1)*radius);
        // Sol-alt
        SDL_RenderLine(bolt_renderer, x+radius - sinf(a0)*radius, y+h-radius + cosf(a0)*radius,
                                      x+radius - sinf(a1)*radius, y+h-radius + cosf(a1)*radius);
        // Sag-alt
        SDL_RenderLine(bolt_renderer, x+w-radius + cosf(a0)*radius, y+h-radius + sinf(a0)*radius,
                                      x+w-radius + cosf(a1)*radius, y+h-radius + sinf(a1)*radius);
    }
}

void bolt_draw_rounded_rect_filled(float x, float y, float w, float h, float radius, int r, int g, int b) {
    SDL_SetRenderDrawColor(bolt_renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255);
    // Ortayi doldur
    SDL_FRect mid  = { x + radius, y,          w - 2*radius, h };
    SDL_FRect leftp = { x,          y + radius, radius,       h - 2*radius };
    SDL_FRect rightp= { x+w-radius, y + radius, radius,       h - 2*radius };
    SDL_RenderFillRect(bolt_renderer, &mid);
    SDL_RenderFillRect(bolt_renderer, &leftp);
    SDL_RenderFillRect(bolt_renderer, &rightp);
    // Kose daireleri
    bolt_draw_circle_filled(x + radius,     y + radius,     radius, r, g, b);
    bolt_draw_circle_filled(x + w - radius, y + radius,     radius, r, g, b);
    bolt_draw_circle_filled(x + radius,     y + h - radius, radius, r, g, b);
    bolt_draw_circle_filled(x + w - radius, y + h - radius, radius, r, g, b);
}

// =============================================================
// 16. 3D IŞIKLANDIRMA
// =============================================================
BoltLight3D bolt_light_3d = { {-0.5f, -1.0f, -0.3f}, 255, 255, 255, 0.8f, 0.25f };

void bolt_draw_cube_lit(float x, float y, float z, float size, int r, int g, int b) {
    // Her yuz icin normal vektorune gore isik siddetini hesapla
    float normals[6][3] = {
        { 0, 0, 1},  // on
        { 0, 0,-1},  // arka
        { 1, 0, 0},  // sag
        {-1, 0, 0},  // sol
        { 0, 1, 0},  // ust
        { 0,-1, 0}   // alt
    };

    BoltVec3 ld = bolt_light_3d.direction;
    float llen = SDL_sqrtf(ld.x*ld.x + ld.y*ld.y + ld.z*ld.z);
    if (llen > 0) { ld.x /= llen; ld.y /= llen; ld.z /= llen; }

    for (int i = 0; i < 6; i++) {
        float dot = normals[i][0]*(-ld.x) + normals[i][1]*(-ld.y) + normals[i][2]*(-ld.z);
        if (dot < 0) dot = 0;
        float light = bolt_light_3d.ambient + dot * bolt_light_3d.intensity;
        if (light > 1) light = 1;

        int lr = (int)(r * light);
        int lg = (int)(g * light);
        int lb = (int)(b * light);

        float hs = size * 0.5f;
        BoltVec3 corners[4];
        if (i == 0) { // On yuz
            corners[0] = (BoltVec3){x-hs, y-hs, z+hs};
            corners[1] = (BoltVec3){x+hs, y-hs, z+hs};
            corners[2] = (BoltVec3){x+hs, y+hs, z+hs};
            corners[3] = (BoltVec3){x-hs, y+hs, z+hs};
        } else if (i == 1) { // Arka yuz
            corners[0] = (BoltVec3){x+hs, y-hs, z-hs};
            corners[1] = (BoltVec3){x-hs, y-hs, z-hs};
            corners[2] = (BoltVec3){x-hs, y+hs, z-hs};
            corners[3] = (BoltVec3){x+hs, y+hs, z-hs};
        } else if (i == 2) { // Sag
            corners[0] = (BoltVec3){x+hs, y-hs, z+hs};
            corners[1] = (BoltVec3){x+hs, y-hs, z-hs};
            corners[2] = (BoltVec3){x+hs, y+hs, z-hs};
            corners[3] = (BoltVec3){x+hs, y+hs, z+hs};
        } else if (i == 3) { // Sol
            corners[0] = (BoltVec3){x-hs, y-hs, z-hs};
            corners[1] = (BoltVec3){x-hs, y-hs, z+hs};
            corners[2] = (BoltVec3){x-hs, y+hs, z+hs};
            corners[3] = (BoltVec3){x-hs, y+hs, z-hs};
        } else if (i == 4) { // Ust
            corners[0] = (BoltVec3){x-hs, y-hs, z-hs};
            corners[1] = (BoltVec3){x+hs, y-hs, z-hs};
            corners[2] = (BoltVec3){x+hs, y-hs, z+hs};
            corners[3] = (BoltVec3){x-hs, y-hs, z+hs};
        } else { // Alt
            corners[0] = (BoltVec3){x-hs, y+hs, z+hs};
            corners[1] = (BoltVec3){x+hs, y+hs, z+hs};
            corners[2] = (BoltVec3){x+hs, y+hs, z-hs};
            corners[3] = (BoltVec3){x-hs, y+hs, z-hs};
        }

        BoltVec3 tc[4];
        bool visible = true;
        for (int k = 0; k < 4; k++) {
            tc[k] = bolt_transform_3d(corners[k]);
            if (tc[k].z < 0.1f) { visible = false; break; }
        }
        if (!visible) continue;

        SDL_FPoint p[4];
        for (int k = 0; k < 4; k++) p[k] = bolt_project_transformed(tc[k]);

        SDL_Vertex verts[4];
        for (int k = 0; k < 4; k++) {
            verts[k].position.x = p[k].x;
            verts[k].position.y = p[k].y;
            verts[k].color.r = (Uint8)lr / 255.0f;
            verts[k].color.g = (Uint8)lg / 255.0f;
            verts[k].color.b = (Uint8)lb / 255.0f;
            verts[k].color.a = 1.0f;
        }
        int idx[] = {0,1,2, 0,2,3};
        SDL_RenderGeometry(bolt_renderer, NULL, verts, 4, idx, 6);
    }
}

// =============================================================
// 17. OBJ MODEL YÜKLEYİCİ
// =============================================================
BoltModel3D* bolt_load_model(const char* obj_filepath) {
    FILE* f = fopen(obj_filepath, "r");
    if (!f) {
        SDL_Log("HATA: OBJ dosyasi acılamadi: %s", obj_filepath);
        return NULL;
    }

    // Ilk geciste kapasiteleri say
    int vc=0, nc=0, tc=0, fc=0;
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (line[0]=='v' && line[1]==' ') vc++;
        else if (line[0]=='v' && line[1]=='n') nc++;
        else if (line[0]=='v' && line[1]=='t') tc++;
        else if (line[0]=='f' && line[1]==' ') fc++;
    }
    rewind(f);

    float* raw_v = (float*)malloc(vc * 3 * sizeof(float));
    float* raw_n = (float*)malloc(nc * 3 * sizeof(float));
    float* raw_t = (float*)malloc(tc * 2 * sizeof(float));

    BoltModel3D* model = (BoltModel3D*)malloc(sizeof(BoltModel3D));
    model->vertices  = (float*)malloc(fc * 3 * 3 * sizeof(float));
    model->normals   = (float*)malloc(fc * 3 * 3 * sizeof(float));
    model->texcoords = (float*)malloc(fc * 3 * 2 * sizeof(float));
    model->indices   = (int*)malloc(fc * 3 * sizeof(int));
    model->vertex_count = 0;
    model->index_count  = 0;

    int vi=0, ni=0, ti_=0;
    while (fgets(line, sizeof(line), f)) {
        if (line[0]=='v' && line[1]==' ') {
            sscanf(line+2, "%f %f %f", &raw_v[vi*3], &raw_v[vi*3+1], &raw_v[vi*3+2]); vi++;
        } else if (line[0]=='v' && line[1]=='n') {
            sscanf(line+3, "%f %f %f", &raw_n[ni*3], &raw_n[ni*3+1], &raw_n[ni*3+2]); ni++;
        } else if (line[0]=='v' && line[1]=='t') {
            sscanf(line+3, "%f %f", &raw_t[ti_*2], &raw_t[ti_*2+1]); ti_++;
        } else if (line[0]=='f' && line[1]==' ') {
            int v_idx[3]={0}, t_idx[3]={0}, n_idx[3]={0};
            // Cok formatli OBJ: v, v/t, v//n, v/t/n
            sscanf(line+2, "%d/%d/%d %d/%d/%d %d/%d/%d",
                &v_idx[0],&t_idx[0],&n_idx[0],
                &v_idx[1],&t_idx[1],&n_idx[1],
                &v_idx[2],&t_idx[2],&n_idx[2]);
            for (int k=0; k<3; k++) {
                int base_v = model->vertex_count;
                int vi_ = (v_idx[k]-1) * 3;
                int ni_ = (n_idx[k]-1) * 3;
                int ti2 = (t_idx[k]-1) * 2;
                model->vertices [base_v*3  ] = (v_idx[k]>0 && vi_>=0) ? raw_v[vi_  ] : 0;
                model->vertices [base_v*3+1] = (v_idx[k]>0 && vi_>=0) ? raw_v[vi_+1] : 0;
                model->vertices [base_v*3+2] = (v_idx[k]>0 && vi_>=0) ? raw_v[vi_+2] : 0;
                model->normals  [base_v*3  ] = (n_idx[k]>0 && ni_>=0) ? raw_n[ni_  ] : 0;
                model->normals  [base_v*3+1] = (n_idx[k]>0 && ni_>=0) ? raw_n[ni_+1] : 0;
                model->normals  [base_v*3+2] = (n_idx[k]>0 && ni_>=0) ? raw_n[ni_+2] : 0;
                model->texcoords[base_v*2  ] = (t_idx[k]>0 && ti2>=0) ? raw_t[ti2  ] : 0;
                model->texcoords[base_v*2+1] = (t_idx[k]>0 && ti2>=0) ? raw_t[ti2+1] : 0;
                model->indices[model->index_count++] = model->vertex_count++;
            }
        }
    }
    fclose(f);
    free(raw_v); free(raw_n); free(raw_t);
    SDL_Log("OBJ Yuklendi: %s (%d vertex)", obj_filepath, model->vertex_count);
    return model;
}

void bolt_draw_model(BoltModel3D* model, float x, float y, float z, float scale, int r, int g, int b) {
    if (!model) return;
    BoltVec3 ld = bolt_light_3d.direction;
    float llen = SDL_sqrtf(ld.x*ld.x + ld.y*ld.y + ld.z*ld.z);
    if (llen > 0) { ld.x /= llen; ld.y /= llen; ld.z /= llen; }

    for (int i = 0; i < model->index_count; i += 3) {
        SDL_Vertex verts[3];
        bool visible = true;
        for (int k = 0; k < 3; k++) {
            int vi_ = model->indices[i + k] * 3;
            BoltVec3 wp = {
                x + model->vertices[vi_  ] * scale,
                y + model->vertices[vi_+1] * scale,
                z + model->vertices[vi_+2] * scale
            };
            BoltVec3 tp = bolt_transform_3d(wp);
            if (tp.z < 0.1f) { visible = false; break; }
            SDL_FPoint p2d = bolt_project_transformed(tp);

            // Işıklandırma: normal vektoru
            int ni_ = model->indices[i + k] * 3;
            float nx = model->normals[ni_], ny = model->normals[ni_+1], nz = model->normals[ni_+2];
            float dot = nx*(-ld.x) + ny*(-ld.y) + nz*(-ld.z);
            if (dot < 0) dot = 0;
            float light = bolt_light_3d.ambient + dot * bolt_light_3d.intensity;
            if (light > 1) light = 1;

            verts[k].position.x = p2d.x;
            verts[k].position.y = p2d.y;
            verts[k].color.r = (r * light) / 255.0f;
            verts[k].color.g = (g * light) / 255.0f;
            verts[k].color.b = (b * light) / 255.0f;
            verts[k].color.a = 1.0f;
            verts[k].tex_coord.x = model->texcoords[model->indices[i+k]*2];
            verts[k].tex_coord.y = model->texcoords[model->indices[i+k]*2+1];
        }
        if (visible) {
            int idx[] = {0, 1, 2};
            SDL_RenderGeometry(bolt_renderer, NULL, verts, 3, idx, 3);
        }
    }
}


// =============================================================
// 18. SAHNE YÖNETİMİ (Scene Management)
// =============================================================
#define BOLT_MAX_SCENES 32
static BoltScene bolt_scenes[BOLT_MAX_SCENES];
static int bolt_scene_count = 0;
static int bolt_active_scene = -1;
static int bolt_pending_scene = -1; // Geciktirilmis sahne degisimi

void bolt_scene_register(BoltScene scene) {
    if (bolt_scene_count >= BOLT_MAX_SCENES) return;
    bolt_scenes[bolt_scene_count++] = scene;
}

void bolt_scene_change(const char* name) {
    for (int i = 0; i < bolt_scene_count; i++) {
        if (bolt_scenes[i].name && strcmp(bolt_scenes[i].name, name) == 0) {
            bolt_pending_scene = i;
            return;
        }
    }
    SDL_Log("[SCENE] Sahne bulunamadi: %s", name);
}

void bolt_scene_update(void) {
    // Bekleyen sahne degisimini uygula
    if (bolt_pending_scene >= 0 && bolt_pending_scene != bolt_active_scene) {
        if (bolt_active_scene >= 0 && bolt_scenes[bolt_active_scene].on_exit)
            bolt_scenes[bolt_active_scene].on_exit();
        bolt_active_scene = bolt_pending_scene;
        bolt_pending_scene = -1;
        if (bolt_scenes[bolt_active_scene].on_enter)
            bolt_scenes[bolt_active_scene].on_enter();
    }
    if (bolt_active_scene < 0) return;
    if (bolt_scenes[bolt_active_scene].on_update)
        bolt_scenes[bolt_active_scene].on_update();
    if (bolt_scenes[bolt_active_scene].on_draw)
        bolt_scenes[bolt_active_scene].on_draw();
}

const char* bolt_scene_current_name(void) {
    if (bolt_active_scene < 0) return "NONE";
    return bolt_scenes[bolt_active_scene].name;
}

// =============================================================
// 19. BASİT FİZİK MOTORU (Simple 2D Physics)
// =============================================================
void bolt_body_init(BoltBody* body, float x, float y, float w, float h, float mass) {
    if (!body) return;
    body->x = x; body->y = y;
    body->vx = 0; body->vy = 0;
    body->ax = 0; body->ay = 0;
    body->w = w; body->h = h;
    body->mass = (mass > 0) ? mass : 1.0f;
    body->restitution = 0.3f;
    body->friction = 0.85f;
    body->grounded = false;
    body->active = true;
}

void bolt_body_apply_force(BoltBody* body, float fx, float fy) {
    if (!body || !body->active) return;
    body->ax += fx / body->mass;
    body->ay += fy / body->mass;
}

void bolt_body_apply_impulse(BoltBody* body, float ix, float iy) {
    if (!body || !body->active) return;
    body->vx += ix / body->mass;
    body->vy += iy / body->mass;
}

void bolt_body_set_velocity(BoltBody* body, float vx, float vy) {
    if (!body) return;
    body->vx = vx; body->vy = vy;
}

void bolt_body_stop(BoltBody* body) {
    if (!body) return;
    body->vx = 0; body->vy = 0;
    body->ax = 0; body->ay = 0;
}

void bolt_body_update(BoltBody* body, float gravity, float dt) {
    if (!body || !body->active) return;

    // Yerçekimi uygula
    body->ay += gravity;

    // Hizi guncelle
    body->vx += body->ax * dt;
    body->vy += body->ay * dt;

    // Surutunme (yatay)
    if (body->grounded) {
        body->vx *= body->friction;
    }

    // Pozisyonu guncelle
    body->x += body->vx * dt;
    body->y += body->vy * dt;

    // Ivmeyi sifirla (her kare sifirlanir, kuvvetler tekrar uygulanir)
    body->ax = 0; body->ay = 0;
    body->grounded = false;
}

bool bolt_body_collide_rect(BoltBody* a, BoltBody* b) {
    if (!a || !b) return false;

    // AABB Cakisma tespiti
    bool overlap_x = a->x < b->x + b->w && a->x + a->w > b->x;
    bool overlap_y = a->y < b->y + b->h && a->y + a->h > b->y;

    if (!overlap_x || !overlap_y) return false;

    // Cakisma tepkisi: hangi taraftan geldigi hesapla
    float dx_right  = (b->x + b->w) - a->x;
    float dx_left   = (a->x + a->w) - b->x;
    float dy_bottom = (b->y + b->h) - a->y;
    float dy_top    = (a->y + a->h) - b->y;

    float min_x = dx_right < dx_left ? dx_right : dx_left;
    float min_y = dy_bottom < dy_top ? dy_bottom : dy_top;

    if (min_x < min_y) {
        // Yatay cakisma
        if (dx_right < dx_left) { a->x += dx_right; if (a->vx < 0) a->vx = -a->vx * a->restitution; }
        else                    { a->x -= dx_left;  if (a->vx > 0) a->vx = -a->vx * a->restitution; }
    } else {
        // Dikey cakisma
        if (dy_bottom < dy_top) { a->y += dy_bottom; if (a->vy < 0) a->vy = -a->vy * a->restitution; }
        else {
            a->y -= dy_top;
            if (a->vy > 0) a->vy = -a->vy * a->restitution;
            a->grounded = true;
        }
    }
    return true;
}

// =============================================================
// 20. POST-PROCESSING EFEKTLERİ
// =============================================================

void bolt_fx_vignette(float strength) {
    // Ekranin 4 kenarinda saydam-siyah ucgenler cizerek vignette efekti
    int w = bolt_get_window_width();
    int h = bolt_get_window_height();
    int steps = 80;
    SDL_SetRenderDrawBlendMode(bolt_renderer, SDL_BLENDMODE_BLEND);
    for (int i = 0; i < steps; i++) {
        float t = (float)i / steps;
        Uint8 alpha = (Uint8)(t * t * strength * 255.0f);
        SDL_SetRenderDrawColor(bolt_renderer, 0, 0, 0, alpha);
        // Ust
        SDL_FRect rt = { (float)(i * w / steps / 2), (float)i, (float)(w - i * w / steps), (float)1 };
        SDL_RenderFillRect(bolt_renderer, &rt);
        // Alt
        SDL_FRect rb = { (float)(i * w / steps / 2), (float)(h - i - 1), (float)(w - i * w / steps), (float)1 };
        SDL_RenderFillRect(bolt_renderer, &rb);
        // Sol
        SDL_FRect rl = { (float)i, (float)(i * h / steps / 2), (float)1, (float)(h - i * h / steps) };
        SDL_RenderFillRect(bolt_renderer, &rl);
        // Sag
        SDL_FRect rr = { (float)(w - i - 1), (float)(i * h / steps / 2), (float)1, (float)(h - i * h / steps) };
        SDL_RenderFillRect(bolt_renderer, &rr);
    }
    SDL_SetRenderDrawBlendMode(bolt_renderer, SDL_BLENDMODE_NONE);
}

void bolt_fx_crt(float scanline_alpha) {
    // Her ikinci yatay cizgiye saydam siyah bant cekerek CRT efekti
    int h = bolt_get_window_height();
    int w = bolt_get_window_width();
    SDL_SetRenderDrawBlendMode(bolt_renderer, SDL_BLENDMODE_BLEND);
    Uint8 a = (Uint8)(scanline_alpha * 255.0f);
    SDL_SetRenderDrawColor(bolt_renderer, 0, 0, 0, a);
    for (int y = 0; y < h; y += 2) {
        SDL_FRect line = { 0, (float)y, (float)w, 1 };
        SDL_RenderFillRect(bolt_renderer, &line);
    }
    SDL_SetRenderDrawBlendMode(bolt_renderer, SDL_BLENDMODE_NONE);
}

void bolt_fx_flash(int r, int g, int b, float alpha) {
    int w = bolt_get_window_width();
    int h = bolt_get_window_height();
    SDL_SetRenderDrawBlendMode(bolt_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(bolt_renderer, (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)(alpha * 255.0f));
    SDL_FRect full = { 0, 0, (float)w, (float)h };
    SDL_RenderFillRect(bolt_renderer, &full);
    SDL_SetRenderDrawBlendMode(bolt_renderer, SDL_BLENDMODE_NONE);
}

void bolt_fx_fade_to_black(float alpha) {
    bolt_fx_flash(0, 0, 0, alpha);
}

// =============================================================
// 21. GAMEPAD TİTREŞİM (Haptic Rumble)
// =============================================================
void bolt_gamepad_rumble(int index, float low_freq, float high_freq, Uint32 duration_ms) {
    if (index < 0 || index >= 4) return;
    if (!bolt_gamepads[index]) return;
    Uint16 lo = (Uint16)(low_freq  * 65535.0f);
    Uint16 hi = (Uint16)(high_freq * 65535.0f);
    SDL_RumbleGamepad(bolt_gamepads[index], lo, hi, duration_ms);
}

#endif // BOLT_IMPLEMENTATION

