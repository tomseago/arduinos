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
        , ANIM_RAINBOW\
        , ANIM_BRIGHT_FO\
        , ANIM_RANDO_FADE\
        , ANIM_SPARKLE\
        \
        , ANIM_LAST\
    };
    

#define ANIMATION_SIGNATURES \
    ANIM_SIG(FLOOD) \
    ANIM_SIG(RAINBOW) \
    ANIM_SIG(BRIGHT_FO) \
    ANIM_SIG(RANDO_FADE) \
    ANIM_SIG(SPARKLE) \
    
#define ANIMATION_DRAWS \
    ANIM_DRAW(FLOOD) \
    ANIM_DRAW(RAINBOW) \
    ANIM_DRAW(BRIGHT_FO) \
    ANIM_DRAW(RANDO_FADE) \
    ANIM_DRAW(SPARKLE) \


#define ANIMATIONS_BEGIN \
    ANIM_BEGIN(FLOOD) \
    ANIM_BEGIN(RAINBOW) \
    ANIM_BEGIN(BRIGHT_FO) \
    ANIM_BEGIN(RANDO_FADE) \
    ANIM_BEGIN(SPARKLE) \


#endif //  _ANIMS_H_



