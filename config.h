#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx = 2; /* border pixel of windows */
static const unsigned int gappx = 5;    /* gaps between windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int systraypinning =
    0; /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor
          X */
static const unsigned int systrayspacing = 2; /* systray spacing */
static const int systraypinningfailfirst = 1; /* 1: if pinning fails, display
systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray = 1;             /* 0 means no systray */
static const int smartgaps =
    0; /* 1 means no outer gap when there is only one window */
static const int showbar = 1;   /* 0 means no bar */
static const int topbar = 1;    /* 0 means botom bar */
static const int viewontag = 1; /* Switch view on tag switch */
static const char *fonts[] = {"Fira Code:size=9:antialias=true:autohint=true"};
static const char dmenufont[] =
    "Fira Code:size=10:antialias=true:autohint=true";
// static const char col_gray1[] = "#222222";
// static const char col_gray2[] = "#444444";
// static const char col_gray3[] = "#bbbbbb";
// static const char col_gray4[] = "#ffffff";

// gruvbox dark
// static const char col_gray1[] = "#282828";
// static const char col_gray2[] = "#3c3836";
// static const char col_gray3[] = "#ebdbb2";
// static const char col_gray4[] = "#fdf1c7";
// static const char col_cyan[] = "#d79921";

// gruvbox light
// static const char col_gray1[] = "#fdf1c7";
// static const char col_gray2[] = "#ebdbb2";
// static const char col_gray3[] = "#3c3836";
// static const char col_gray4[] = "#282828";
// static const char col_cyan[] = "#fabd2f";

// static const char col_border[] = "#42A5F5";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
// static const char *colors[][3] = {
//[>               fg         bg         border   <]
//[SchemeNorm] = {col_gray3, col_gray1, col_gray2},
//[SchemeSel] = {col_gray4, col_cyan, col_border},
//[SchemeHid] = {col_cyan, col_gray1, col_border},
//};
static char normbgcolor[] = "#2E3440";
static char normbordercolor[] = "#3B4252";
static char normfgcolor[] = "#ECEFF4";
static char selfgcolor[] = "#D8DEE9";
static char selbordercolor[] = "#5E81AC";
static char selbgcolor[] = "#5E81AC";
static char termcol0[] = "#3b4252";  /* black   */
static char termcol1[] = "#bf616a";  /* red     */
static char termcol2[] = "#a3be8c";  /* green   */
static char termcol3[] = "#ebcb8b";  /* yellow  */
static char termcol4[] = "#81a1c1";  /* blue    */
static char termcol5[] = "#b48ead";  /* magenta */
static char termcol6[] = "#88c0d0";  /* cyan    */
static char termcol7[] = "#e5e9f0";  /* white   */
static char termcol8[] = "#4c566a";  /* black   */
static char termcol9[] = "#bf616a";  /* red     */
static char termcol10[] = "#a3be8c"; /* green   */
static char termcol11[] = "#ebcb8b"; /* yellow  */
static char termcol12[] = "#81a1c1"; /* blue    */
static char termcol13[] = "#b48ead"; /* magenta */
static char termcol14[] = "#8fbcbb"; /* cyan    */
static char termcol15[] = "#eceff4"; /* white   */
static char *termcolor[] = {
    termcol0,  termcol1,  termcol2,  termcol3,  termcol4,  termcol5,
    termcol6,  termcol7,  termcol8,  termcol9,  termcol10, termcol11,
    termcol12, termcol13, termcol14, termcol15,
};
static char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = {normfgcolor, normbgcolor, normbordercolor},
    [SchemeSel] = {selfgcolor, selbgcolor, selbordercolor},
};

static const unsigned int alphas[][3] = {
    [SchemeNorm] = {OPAQUE, baralpha, borderalpha},
    [SchemeSel] = {OPAQUE, baralpha, borderalpha},
};

/* tagging */
// static const char *tags[] = {"\uf120", "\uf7ae", "\uf121", "\uf04b",
// "\ue62e",
//"\uf251", "\ue727", "\uf537", "\uf684"};
static const char *tags[] = {"", "", "", "", "", "", "", "", ""};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING)  = title
     */
    /* class      		instance    title       tags mask     isfloating
     * monitor
     */
    {"Gimp", NULL, NULL, 0, 1, -1},
};

/* layout(s) */
static const float mfact = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;   /* number of clients in master area */
static const int resizehints =
    1; /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    {"[ ]", tile}, /* first entry is default */
    {"><>", NULL}, /* no layout function means floating behavior */
    {"[M]", monocle},
    {"HHH", grid},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

/* commands */

static const char *dmenucmd[] = {"rofi", "-show", "drun", NULL};
// static char dmenumon[2] =
//"0"; [> component of dmenucmd, manipulated in spawn() <]
// static const char *dmenucmd[] = {"dmenu_run", "-m",  dmenumon,    "-fn",
// dmenufont,   "-nb", normbgcolor, "-nf",
// normfgcolor, "-sb", selbgcolor,  "-sf",
// selfgcolor,  NULL};
static const char *termcmd[] = {"st", NULL};
static const char *browsercmd[] = {"firefox", NULL};
// static const char *musiccmd[] = {"yesplaymusic", NULL};
// static const char *volup[] = {"~/scripts/dwm/volup.sh", NULL};
// static const char *voldown[] = {"~/scripts/dwm/voldown.sh", NULL};
static const char *screenlock[] = {"slock", NULL};
// static const char *screenshotcmd[] = {
//"/home/xingji/Desktop/scripts/screenshot.sh", NULL};
static const char *volup[] = {"amixer", "-qM",   "set", "Master",
                              "2%+",    "umute", NULL};
static const char *voldown[] = {"amixer", "-qM",   "set", "Master",
                                "2%-",    "umute", NULL};
static const char *mute[] = {"amixer", "-qM", "set", "Master", "toggle", NULL};
static const char *lightup[] = {"xbacklight", "-inc", "2", NULL};
static const char *lightdown[] = {"xbacklight", "-dec", "2", NULL};
static const char *dolphin[] = {"dolphin", NULL};

static Key keys[] = {
    /* modifier     	        key        	function        argument */
    {MODKEY, XK_d, spawn, {.v = dmenucmd}},
    {MODKEY, XK_Return, spawn, {.v = termcmd}},
    {MODKEY, XK_b, spawn, {.v = browsercmd}},
    //{MODKEY | ShiftMask, XK_m, spawn, {.v = musiccmd}},
    //{0, XK_Print, spawn, {.v = screenshotcmd}},
    {MODKEY | ShiftMask, XK_Up, spawn, {.v = lightup}},
    {MODKEY | ShiftMask, XK_Down, spawn, {.v = lightdown}},
    {MODKEY | ShiftMask, XK_Right, spawn, {.v = volup}},
    {MODKEY | ShiftMask, XK_Left, spawn, {.v = voldown}},
    {MODKEY | ShiftMask, XK_m, spawn, {.v = mute}},
    {MODKEY | ShiftMask, XK_d, spawn, {.v = dolphin}},
    {MODKEY, XK_o, togglebar, {0}},
    {MODKEY | ShiftMask, XK_u, rotatestack, {.i = +1}},
    {MODKEY | ShiftMask, XK_e, rotatestack, {.i = -1}},
    {MODKEY, XK_u, focusstack, {.i = +1}},
    {MODKEY, XK_e, focusstack, {.i = -1}},
    {MODKEY, XK_n, incnmaster, {.i = +1}},
    {MODKEY, XK_i, incnmaster, {.i = -1}},
    {MODKEY | ShiftMask, XK_n, setmfact, {.f = -0.05}},
    {MODKEY | ShiftMask, XK_i, setmfact, {.f = +0.05}},
    {MODKEY, XK_z, hidewin, {0}},
    {MODKEY | ShiftMask, XK_z, restorewin, {0}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_a, spawn, {.v = screenlock}},
    {MODKEY | ShiftMask, XK_q, killclient, {0}},
    {MODKEY | ControlMask, XK_q, quit, {0}},
    {MODKEY | ShiftMask, XK_r, quit, {1}},
    {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
    {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
    {MODKEY, XK_g, setlayout, {.v = &layouts[3]}},
    {MODKEY, XK_space, setlayout, {0}},
    {MODKEY | ShiftMask, XK_f, fullscreen, {0}},
    {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    {MODKEY, XK_comma, focusmon, {.i = -1}},
    {MODKEY, XK_period, focusmon, {.i = +1}},
    {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
    {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
            TAGKEYS(XK_9, 8){MODKEY | ControlMask, XK_c, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click               	event mask      button          function
       argument*/
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkWinTitle, 0, Button1, togglewin, {0}},
    {ClkWinTitle, 0, Button2, zoom, {0}},
    {ClkStatusText, 0, Button2, spawn, {.v = termcmd}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
