/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const int corner_radius      = 0;
static const unsigned int gappx     = 4;
static const unsigned int snap      = 10;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#444444";
//static const char col_gray3[]       = "#905eb5";
static const char col_gray3[]       = "#d3bd97";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char main_col[]        = "#918274";
static const char light_gray[]	    = "#484848";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { main_col, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray3, col_gray1, main_col },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ "dmenu",    NULL,       NULL,       0,            1,           -1 },
	{ "floating", NULL,       NULL,       0,            1,           -1 },
	{ "pcmanfm",  NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[D]",      deck },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-l", "15", "-m", dmenumon, "-x", "40", "-y", "60", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", main_col, "-sf", col_gray1, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *floaterm[] = { "st", "-c", "floating", "-g", "100x30+200+200", NULL };
static const char *musiccmd[] = { "st", "-e", "unath", NULL };
static const char *filemanager[] = { "st", "-c", "floating", "-g", "100x30+500+200", "-e", "xplr", NULL };
static const char *unath[] = { "st", "-c", "floating", "-f", "mono:pixelsize=5", "-g", "41x13+100+100", "-t", "unath", NULL };

#include <X11/XF86keysym.h>

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = floaterm } },
	{ MODKEY,												XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_m,      spawn,          {.v = musiccmd } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = filemanager } },
	{ MODKEY,	                			XK_u,      spawn,          {.v = unath } },
	{ MODKEY|ControlMask,						XK_Return, spawn,	 			   SHCMD("bash ~/Scripts/lang.sh") },
	{ Mod1Mask,											XK_Shift_L,spawn,	  			 SHCMD("bash ~/Scripts/lang.sh") },
	{ MODKEY,												XK_w,      spawn,          SHCMD("firefox") },
	{ MODKEY|ShiftMask,							XK_w,      spawn,          SHCMD("librewolf --private-window") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
  { MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_f,      togglefullscreen,{0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,             	        XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,             	        XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0 } },
  { MODKEY|ControlMask,           XK_equal,  spawn,          SHCMD("brightnessctl set +100") },
  { MODKEY|ControlMask,           XK_minus,  spawn,          SHCMD("brightnessctl set 100-") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

	{ 0, XF86XK_AudioMute,					spawn,		SHCMD("amixer set Master playback toggle") },
	{ 0, XF86XK_AudioRaiseVolume,		spawn,		SHCMD("pactl set-sink-volume 0 +2%; bash ~/Scripts/rbar.sh") },
	{ 0, XF86XK_AudioLowerVolume,		spawn,		SHCMD("pactl set-sink-volume 0 -2%; bash ~/Scripts/rbar.sh") },
	{ 0, XF86XK_AudioPrev,					spawn,		SHCMD("mpc prev") },
	{ 0, XF86XK_AudioNext,					spawn,		SHCMD("mpc next") },
	{ 0, XF86XK_AudioPlay,					spawn,		SHCMD("mpc toggle") },
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

