/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "BitstreamVeraSansMono Nerd Font Mono:style=Roman:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray4, col_gray2,  col_gray2  },
	[SchemeTitle]  = { col_gray3, col_gray1,  col_gray1  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define HOLDKEY XK_s // replace 0 with the keysym to activate holdbar

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static const char *inclightlarge[] = { "light", "-A", "10", NULL };
static const char *inclightmed[] = { "light", "-A", "1", NULL };
static const char *inclightsmall[] = { "light", "-A", "0.1", NULL };

static const char *declightlarge[] = { "light", "-U", "10", NULL };
static const char *declightmed[] = { "light", "-U", "1", NULL };
static const char *declightsmall[] = { "light", "-U", "0.1", NULL };

static const char *incvollarge[] = { "amixer", "-q", "sset", "Master", "10%+", NULL };
static const char *incvolsmall[] = { "amixer", "-q", "sset", "Master", "1%+", NULL };

static const char *decvollarge[] = { "amixer", "-q", "sset", "Master", "10%-", NULL };
static const char *decvolsmall[] = { "amixer", "-q", "sset", "Master", "1%-", NULL };

static const char *voltoggle[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };

static const char *incmiclarge[] = { "amixer", "-q", "sset", "Capture", "10%+", NULL };
static const char *incmicsmall[] = { "amixer", "-q", "sset", "Capture", "1%+", NULL };

static const char *decmiclarge[] = { "amixer", "-q", "sset", "Capture", "10%-", NULL };
static const char *decmicsmall[] = { "amixer", "-q", "sset", "Capture", "1%-", NULL };

static const char *mictoggle[] = { "amixer", "-q", "sset", "Capture", "toggle", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
    /* brightness keys */
    { MODKEY|ControlMask,           XF86XK_MonBrightnessUp,   spawn, {.v = inclightsmall } }, 
    { MODKEY,                       XF86XK_MonBrightnessUp,   spawn, {.v = inclightmed } }, 
    { 0,                            XF86XK_MonBrightnessUp,   spawn, {.v = inclightlarge } }, 
    { MODKEY|ControlMask,           XF86XK_MonBrightnessDown, spawn, {.v = declightsmall } }, 
    { MODKEY,                       XF86XK_MonBrightnessDown, spawn, {.v = declightmed } }, 
    { 0,                            XF86XK_MonBrightnessDown, spawn, {.v = declightlarge } }, 
    /* speaker keys */
    { MODKEY,                       XF86XK_AudioRaiseVolume, spawn, {.v = incvolsmall } }, 
    { 0,                            XF86XK_AudioRaiseVolume, spawn, {.v = incvollarge } }, 
    { MODKEY,                       XF86XK_AudioLowerVolume, spawn, {.v = decvolsmall } }, 
    { 0,                            XF86XK_AudioLowerVolume, spawn, {.v = decvollarge } }, 
    { 0,                            XF86XK_AudioMute, spawn, {.v = voltoggle } }, 
    /* microphone keys */
    { Mod1Mask|MODKEY,              XF86XK_AudioRaiseVolume, spawn, {.v = incmicsmall } }, 
    { Mod1Mask,                     XF86XK_AudioRaiseVolume, spawn, {.v = incmiclarge } }, 
    { Mod1Mask|MODKEY,              XF86XK_AudioLowerVolume, spawn, {.v = decmicsmall } }, 
    { Mod1Mask,                     XF86XK_AudioLowerVolume, spawn, {.v = decmiclarge } }, 
    { 0,                            XF86XK_AudioMicMute, spawn, {.v = mictoggle } }, 
    /* regular bindings */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_n,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ MODKEY,                       HOLDKEY,   holdbar,        {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

