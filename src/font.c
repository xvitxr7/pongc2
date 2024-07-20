#include "font.h"
#include "state.h"
#include <SDL2/SDL_render.h>
#include <string.h>

struct pc_font pc_pong_sans;

void pc_init_font() {
    for (int i = 0; i < PC_CHAR_COUNT; i++) {
        pc_pong_sans.chars[i] = 0;

        pc_pong_sans.indices[i].w = 3;
        pc_pong_sans.indices[i].h = 5;
    }

    pc_pong_sans.chars['a'] = " * "
                           "* *"
                           "***"
                           "* *"
                           "* *";

    pc_pong_sans.chars['b'] = "** "
                           "* *"
                           "** "
                           "* *"
                           "** ";

    pc_pong_sans.chars['c'] = "***"
                           "*  "
                           "*  "
                           "*  "
                           "***";


    pc_pong_sans.chars['d'] = "** "
                           "* *"
                           "* *"
                           "* *"
                           "** ";

    pc_pong_sans.chars['e'] = "***"
                           "*  "
                           "***"
                           "*  "
                           "***";

    pc_pong_sans.chars['f'] = "***"
                           "*  "
                           "***"
                           "*  "
                           "*  ";

    pc_pong_sans.chars['g'] = "***"
                           "*  "
                           "* *"
                           "* *"
                           "***";

    pc_pong_sans.chars['h'] = "* *"
                           "* *"
                           "***"
                           "* *"
                           "* *";

    pc_pong_sans.chars['i'] = "***"
                           " * "
                           " * "
                           " * "
                           "***";

    pc_pong_sans.chars['j'] = "  *"
                           "  *"
                           "* *"
                           "* *"
                           "***";

    pc_pong_sans.chars['k'] = "* *"
                           "* *"
                           "** "
                           "* *"
                           "* *";

    pc_pong_sans.chars['l'] = "*  "
                           "*  "
                           "*  "
                           "*  "
                           "***";

    pc_pong_sans.indices['m'].w = 5;
    pc_pong_sans.chars['m'] = "** **"
                              "* * *"
                              "*   *"
                              "*   *"
                              "*   *";

    pc_pong_sans.indices['n'].w = 4;
    pc_pong_sans.chars['n'] = "*  *"
                              "** *"
                              "* **"
                              "* **"
                              "*  *";

    pc_pong_sans.indices['o'].w = 4;
    pc_pong_sans.chars['o'] = "****"
                              "*  *"
                              "*  *"
                              "*  *"
                              "****";

    pc_pong_sans.chars['p'] = "***"
                           "* *"
                           "***"
                           "*  "
                           "*  ";

    pc_pong_sans.indices['q'].w = 4;
    pc_pong_sans.chars['q'] = "*** "
                           "* * "
                           "* * "
                           "*** "
                           "  **";

    pc_pong_sans.chars['r'] = "***"
                           "* *"
                           "***"
                           "** "
                           "* *";

    pc_pong_sans.chars['s'] = "***"
                           "*  "
                           "***"
                           "  *"
                           "***";

    pc_pong_sans.chars['t'] = "***"
                           " * "
                           " * "
                           " * "
                           " * ";

    pc_pong_sans.chars['u'] = "* *"
                           "* *"
                           "* *"
                           "* *"
                           "***";

    pc_pong_sans.chars['v'] = "* *"
                           "* *"
                           "* *"
                           "* *"
                           " * ";

    pc_pong_sans.indices['w'].w = 5;
    pc_pong_sans.chars['w'] = "*   *"
                           "*   *"
                           "*   *"
                           "* * *"
                           " *** ";

    pc_pong_sans.chars['x'] = "* *"
                           "* *"
                           " * "
                           "* *"
                           "* *";

    pc_pong_sans.chars['y'] = "* *"
                           "* *"
                           " * "
                           " * "
                           " * ";

    pc_pong_sans.chars['z'] = "***"
                           "  *"
                           " * "
                           "*  "
                           "***";

    pc_pong_sans.indices['@'].w = 4;
    pc_pong_sans.chars['@'] = "****"
                           "*  *"
                           "* **"
                           "*   "
                           "****";

    pc_pong_sans.chars['?'] = "***"
                           " -*"
                           " * "
                           "   "
                           " * ";

    pc_pong_sans.indices['!'].w = 1;
    pc_pong_sans.chars['!'] = "*"
                           "*"
                           "*"
                           " "
                           "*";

    pc_pong_sans.chars['*'] = "   "
                           "*_*"
                           " * "
                           "*-*"
                           "   ";

    pc_pong_sans.indices['['].w = 2;
    pc_pong_sans.chars['['] = "**"
                           "* "
                           "* "
                           "* "
                           "**";

    pc_pong_sans.indices[']'].w = 2;
    pc_pong_sans.chars[']'] = "**"
                           " *"
                           " *"
                           " *"
                           "**";

    pc_pong_sans.indices['('].w = 2;
    pc_pong_sans.chars['('] = " *"
                           "* "
                           "* "
                           "* "
                           " *";

    pc_pong_sans.indices[')'].w = 2;
    pc_pong_sans.chars[')'] = "* "
                           " *"
                           " *"
                           " *"
                           "* ";

    pc_pong_sans.chars['{'] = " **"
                           " * "
                           "*  "
                           " * "
                           " **";

    pc_pong_sans.chars['}'] = "** "
                           " * "
                           "  *"
                           " * "
                           "** ";

    pc_pong_sans.chars['/'] = "  *"
                           "  *"
                           " * "
                           "*  "
                           "*  ";

    pc_pong_sans.chars['\\'] = "*  "
                            "*  "
                            " * "
                            "  *"
                            "  *";

    pc_pong_sans.chars['%'] = "* *"
                           "  *"
                           " * "
                           "*  "
                           "* *";


    pc_pong_sans.indices['-'].w = 3;
    pc_pong_sans.indices['-'].h = 3;
    pc_pong_sans.chars['-'] = "   "
                              "   "
                              "***";

    pc_pong_sans.indices['.'].w = 1;
    pc_pong_sans.chars['.'] = " "
                              " "
                              " "
                              " "
                              "*";

    pc_pong_sans.indices[':'].w = 1;
    pc_pong_sans.chars[':'] = " "
                              "*"
                              " "
                              "*"
                              " ";


    pc_pong_sans.chars['$'] = "***"
                           "*| "
                           "***"
                           " |*"
                           "***";

    pc_pong_sans.chars['0'] = "***"
                           "* *"
                           "* *"
                           "* *"
                           "***";

    pc_pong_sans.indices['1'].w = 2;
    pc_pong_sans.chars['1'] = " *"
                           "**"
                           " *"
                           " *"
                           " *";

    pc_pong_sans.chars['2'] = "** "
                           "  *"
                           " * "
                           "*  "
                           "***";

    pc_pong_sans.chars['3'] = "** "
                           "  *"
                           " * "
                           "  *"
                           "** ";

    pc_pong_sans.chars['4'] = "* *"
                           "* *"
                           "***"
                           "  *"
                           "  *";

    pc_pong_sans.chars['5'] = "***"
                           "*  "
                           "** "
                           "  *"
                           "** ";

    pc_pong_sans.chars['6'] = " **"
                           "*  "
                           "***"
                           "* *"
                           "***";

    pc_pong_sans.chars['7'] = "***"
                           "  *"
                           " * "
                           "*  "
                           "*  ";

    pc_pong_sans.chars['8'] = "***"
                           "* *"
                           "***"
                           "* *"
                           "***";

    pc_pong_sans.chars['9'] = "***"
                           "* *"
                           "***"
                           "  *"
                           "***";

    pc_pong_sans.chars[' '] = "   "
                           "   "
                           "   "
                           "   ";
}

void draw_char(char c, float _x, float _y, uint32_t _scale) {
    const char* character = pc_pong_sans.chars[c];

    const int width  = pc_pong_sans.indices[c].w;
    const int height = pc_pong_sans.indices[c].h;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            SDL_FRect r;
            char dc = character[y * width + x];

            switch (dc) {
                case '*': {
                    r.x = _x + (x * _scale);
                    r.y = _y + (y * _scale);
                    r.w = _scale;
                    r.h = _scale;
                } break;

                case '-': {
                    r.x = _x + (x * _scale);
                    r.y = _y + ((y * _scale) - (_scale / 2.f));
                    r.w = _scale;
                    r.h = _scale / 2.f;
                } break;

                case '_': {
                    r.x = _x + (x * _scale);
                    r.y = _y + ((y * _scale) + (_scale / 2.f));
                    r.w = _scale;
                    r.h = _scale / 2.f;
                } break;

                case '|': {
                    r.x = _x + ((x * _scale) + (_scale / 2.5f));
                    r.y = _y + (y * _scale);
                    r.w = _scale / 2.5f;
                    r.h = _scale;
                } break;

                default: continue; break;
            }

            SDL_RenderFillRectF(pc_state.renderer, &r);
        }
    }
}

void pc_draw_text(const char* _text, float _x, float _y, uint32_t _scale) {
    char buf[strlen(_text)];
    strcpy(buf, _text);

    // The initial parameters.
    float ix = _x, iy = _y;

    uint32_t scale = _scale;

    for (int i = 0; i != strlen(buf); i++) {
        char c = tolower(buf[i]);

        const int width  = pc_pong_sans.indices[c].w;
        const int height = pc_pong_sans.indices[c].h;

        if (c == '\n') {
            _x = ix;
            _y += height * _scale + _scale;
            continue;
        }

        if (pc_pong_sans.chars[c] == 0 || c == '\0') continue;

        const float scale_w = scale * width, scale_h = scale * height;
        draw_char(c, _x, _y, scale);
        _x += scale_w + scale;
    }
}
