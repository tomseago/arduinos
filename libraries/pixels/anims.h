#ifndef _ANIMS_H_
#define _ANIMS_H_

#define ANIM_SIG(x) void x##_setup(); void x##_drawFrame();
#define ANIM_DRAW(name) case ANIM_##name: name##_drawFrame(); break;
#define ANIM_BEGIN(name)  case ANIM_##name: name##_setup(); name##_drawFrame(); break;



#define ANIMATION_ENUM \
    enum animName_t {\
        ANIM_NONE = 0\
        \
        , ANIM_WHITE\
        , ANIM_HALF_WHITE\
        \
        , ANIM_LAST\
        \
        , ANIM_FLOOD\
        , ANIM_SPARKLE\
        , ANIM_RAINBOW\
        , ANIM_BRIGHT_FO\
        , ANIM_RANDO_FADE\
        \
    };
        // , ANIM_JORDAN_RUNWAY\
        // , ANIM_JPERF_START\
        // \
        // , ANIM_JPERF_FBLOBS\
        // , ANIM_JPERF_FSPARKLE\
        // , ANIM_JPERF_FPULSES\
        // , ANIM_JPERF_FSPOTS\
        // , ANIM_JPERF_BREATH\
        // \
        // , ANIM_JPERF_MBOUNCE\
        // , ANIM_JPERF_MSNARE\
        // , ANIM_JPERF_OFF\
        // , ANIM_JPERF_MSPARKLE\
        // , ANIM_JPERF_MCLAP\
        // , ANIM_JPERF_MBOUNCE_END\
        // \
        // , ANIM_JPERF_END\
    

#define ANIMATION_SIGNATURES \
    ANIM_SIG(FLOOD) \
    ANIM_SIG(RAINBOW) \
    ANIM_SIG(BRIGHT_FO) \
    ANIM_SIG(RANDO_FADE) \
    ANIM_SIG(SPARKLE) \
    ANIM_SIG(WHITE) \
    ANIM_SIG(HALF_WHITE) \

    // ANIM_SIG(JORDAN_RUNWAY) \
    // ANIM_SIG(JPERF_START) \
    // ANIM_SIG(JPERF_FBLOBS) \ 
    // ANIM_SIG(JPERF_FSPARKLE) \ 
    // ANIM_SIG(JPERF_FPULSES) \ 
    // ANIM_SIG(JPERF_FSPOTS) \ 
    // ANIM_SIG(JPERF_BREATH) \ 
    // ANIM_SIG(JPERF_MBOUNCE) \ 
    // ANIM_SIG(JPERF_MSNARE) \ 
    // ANIM_SIG(JPERF_OFF) \ 
    // ANIM_SIG(JPERF_MSPARKLE) \ 
    // ANIM_SIG(JPERF_MCLAP) \ 
    // ANIM_SIG(JPERF_MBOUNCE_END) \ 
    // ANIM_SIG(JPERF_END) \ 
 

    
#define ANIMATION_DRAWS \
    ANIM_DRAW(FLOOD) \
    ANIM_DRAW(RAINBOW) \
    ANIM_DRAW(BRIGHT_FO) \
    ANIM_DRAW(RANDO_FADE) \
    ANIM_DRAW(SPARKLE) \
    ANIM_DRAW(WHITE) \
    ANIM_DRAW(HALF_WHITE) \

    // ANIM_DRAW(JORDAN_RUNWAY) \
    // ANIM_DRAW(JPERF_START) \ 
    // ANIM_DRAW(JPERF_FBLOBS) \ 
    // ANIM_DRAW(JPERF_FSPARKLE) \ 
    // ANIM_DRAW(JPERF_FPULSES) \ 
    // ANIM_DRAW(JPERF_FSPOTS) \ 
    // ANIM_DRAW(JPERF_BREATH) \ 
    // ANIM_DRAW(JPERF_MBOUNCE) \ 
    // ANIM_DRAW(JPERF_MSNARE) \ 
    // ANIM_DRAW(JPERF_OFF) \ 
    // ANIM_DRAW(JPERF_MSPARKLE) \ 
    // ANIM_DRAW(JPERF_MCLAP) \ 
    // ANIM_DRAW(JPERF_MBOUNCE_END) \ 
    // ANIM_DRAW(JPERF_END) \ 


#define ANIMATIONS_BEGIN \
    ANIM_BEGIN(FLOOD) \
    ANIM_BEGIN(RAINBOW) \
    ANIM_BEGIN(BRIGHT_FO) \
    ANIM_BEGIN(RANDO_FADE) \
    ANIM_BEGIN(SPARKLE) \
    ANIM_BEGIN(WHITE) \
    ANIM_BEGIN(HALF_WHITE) \

    // ANIM_BEGIN(JORDAN_RUNWAY) \
    // ANIM_BEGIN(JPERF_START) \ 
    // ANIM_BEGIN(JPERF_FBLOBS) \ 
    // ANIM_BEGIN(JPERF_FSPARKLE) \ 
    // ANIM_BEGIN(JPERF_FPULSES) \ 
    // ANIM_BEGIN(JPERF_FSPOTS) \ 
    // ANIM_BEGIN(JPERF_BREATH) \ 
    // ANIM_BEGIN(JPERF_MBOUNCE) \ 
    // ANIM_BEGIN(JPERF_MSNARE) \ 
    // ANIM_BEGIN(JPERF_OFF) \ 
    // ANIM_BEGIN(JPERF_MSPARKLE) \ 
    // ANIM_BEGIN(JPERF_MCLAP) \ 
    // ANIM_BEGIN(JPERF_MBOUNCE_END) \ 
    // ANIM_BEGIN(JPERF_END) \ 


#endif //  _ANIMS_H_

