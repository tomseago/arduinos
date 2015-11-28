#ifndef _ANIMS_H_
#define _ANIMS_H_

#define ANIM_SIG(x) void x##_setup(); void x##_drawFrame();
#define ANIM_DRAW(name) case ANIM_##name: name##_drawFrame(); break;
#define ANIM_BEGIN(name)  case ANIM_##name: name##_setup(); name##_drawFrame(); break;



#define ANIMATION_ENUM \
    enum animName_t {\
        ANIM_NONE = 0\
        \
        , ANIM_FLOOD\
        , ANIM_SPARKLE\
        \
        , ANIM_LAST\
        , ANIM_RAINBOW\
        , ANIM_BRIGHT_FO\
        , ANIM_RANDO_FADE\
        , ANIM_WHITE\
        , ANIM_JORDAN_RUNWAY\
    };
    

#define ANIMATION_SIGNATURES \
    ANIM_SIG(FLOOD) \
    ANIM_SIG(RAINBOW) \
    ANIM_SIG(BRIGHT_FO) \
    ANIM_SIG(RANDO_FADE) \
    ANIM_SIG(SPARKLE) \
    ANIM_SIG(WHITE) \
    ANIM_SIG(JORDAN_RUNWAY) \
    
    
#define ANIMATION_DRAWS \
    ANIM_DRAW(FLOOD) \
    ANIM_DRAW(RAINBOW) \
    ANIM_DRAW(BRIGHT_FO) \
    ANIM_DRAW(RANDO_FADE) \
    ANIM_DRAW(SPARKLE) \
    ANIM_DRAW(WHITE) \
    ANIM_DRAW(JORDAN_RUNWAY) \


#define ANIMATIONS_BEGIN \
    ANIM_BEGIN(FLOOD) \
    ANIM_BEGIN(RAINBOW) \
    ANIM_BEGIN(BRIGHT_FO) \
    ANIM_BEGIN(RANDO_FADE) \
    ANIM_BEGIN(SPARKLE) \
    ANIM_BEGIN(WHITE) \
    ANIM_BEGIN(JORDAN_RUNWAY) \


#endif //  _ANIMS_H_

