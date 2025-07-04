/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 15; 
static const unsigned int bargapx   = 0; 
static const unsigned int bargapy   = 0; 
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
// static const char *fonts[]          = { "JetBrainsMonoNL NFP:size=10:style=Bold", "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true" };
// static const char col_gray1[]       = "#222222";
// static const char col_gray2[]       = "#444444";
// static const char col_gray3[]       = "#bbbbbb";
// static const char col_gray4[]       = "#eeeeee";
static const char *fonts[]          = { "Fixedsys Excelsior:size=12:antialias=true:autohint=false", "JetBrainsMonoNL NFP:size=10:style=Bold", "NotoColorEmoji:pixelsize=10:antialias=true:autohint=true" };
static const char col_gray1[]       = "#d3d7cf";
static const char col_gray2[]       = "#d3d7cf";
static const char col_gray3[]       = "#000000";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#0000aa";
static const char col_red[]        = "#ff0000";
static const char col_white[]        = "#ffffff";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	// [SchemeNorm] = { col_gray3, col_gray1, col_white },
	// [SchemeSel]  = { col_gray4, col_red,  col_red  },
	[SchemeNorm] = { col_gray3, col_gray1, col_cyan },
	[SchemeSel]  = { col_gray4, col_cyan,  col_gray2  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                instance    title      tags mask     isfloating   isterminal  noswallow  monitor */
	{ "super_overlay",      NULL,       NULL,      0,                       0,          -1 }, // 1,           0,
	{ "Alacritty",          NULL,       NULL,      0,                       0,          -1 }, // 0,           1,
	{ "floorp",            	"Devtools", NULL,      0,                       1,          -1 }, // 1,           0,
//	{ "floorp",         	"Navigator",NULL,      0,                       1,          0  }, // 0,           0,
//	{ "Spotify",  			NULL,       NULL,      0,                       0,          2  }, // 0,           0,
	{ "floorp",             "Toolkit",  NULL,      0,                       1,          -1 }, // 1,           0,
	{ "TelegramDesktop",    NULL,       NULL,      0,                       0,          1 }, // 0,           0,
	{ "AyuGramDesktop",    NULL,       NULL,      0,                       0,          1 }, // 0,           0,
};


/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 2;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[@]",      fibonacci },
	{ "[M]",      monocle },
	{ "[]=",      tile },    /* first entry is default */
	{ "PENIS",      tile2 },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }
#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *termcmd[]  = { "alacritty", NULL };
static const char *editorcmd[]  = { "code", NULL };
static const char *flameshotcmd[]  = { "flameshot", "gui", NULL };
static const char *filemanagercmd[]  = { "dolphin", NULL };

static const char *roficmd[]  = { "rofi", "-show", "drun", NULL };
static const char *clipboardcmd[]  = { "rofi", "-modi", "\"clipboard:greenclip print\"", "-show", "clipboard", NULL };
static const char *spotifycmd[]  = { "spotify", NULL };
static const char *telegramcmd[]  = { "telegram-desktop", NULL };
static const char *xcolorcmd[]  = { "sh", "-c", "notify-send \"$(xcolor)\"", NULL };
static const char *overlaycmd[]  = { "overlay", NULL };

static const int swallowfloating    = 0;

static const Key keys[] = {
	/* modifier                     key        function        argument */
	
	//  ____  ____   ___        ___   _
	// / ___||  _ \ / \ \      / / \ | |
	// \___ \| |_) / _ \ \ /\ / /|  \| |
	//  ___) |  __/ ___ \ V  V / | |\  |
	// |____/|_| /_/   \_\_/\_/  |_| \_|
	{ MODKEY,                       XK_a,      spawn,           {.v = roficmd } },
	{ MODKEY,                       XK_v,      spawn,           {.v = clipboardcmd } },
	{ MODKEY,                       XK_c,      spawn,           {.v = editorcmd } },
	{ MODKEY,                       XK_t,      spawn,           {.v = termcmd } },
	{ MODKEY,                       XK_e,      spawn,           {.v = filemanagercmd } },
	{ MODKEY,                       XK_space,  spawn,           {.v = overlaycmd } },
	{ ControlMask,                  XK_Print,  spawn,           {.v = xcolorcmd} },
 
	{ MODKEY,                       XK_b,      togglebar,       {0} },
	{ MODKEY,                       XK_h,      setmfact,        {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,        {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,            {0} },
	{ MODKEY,             			XK_q,      killclient,      {0} },
	{ MODKEY,             			XK_Print,  spawn,     	    {.v = flameshotcmd} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating,  {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscreen,{0} },
	{ MODKEY|Mod1Mask,              XK_s,      setlayout,       {.v = &layouts[0]} },
	{ MODKEY|Mod1Mask,              XK_t,      setlayout,       {.v = &layouts[1]} },
	{ MODKEY|Mod1Mask,              XK_v,      setlayout,       {.v = &layouts[2]} },
	{ MODKEY|Mod1Mask,              XK_b,      setlayout,       {.v = &layouts[3]} },
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
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkStatusText,        MODKEY,         Button3,        sigstatusbar,   {.i = 6} },
	{ ClkStatusText,        MODKEY|Mod1Mask|ControlMask,    Button3,        sigstatusbar,   {.i = 7} },
	{ ClkStatusText,        0,              8,        sigstatusbar,   {.i = 8} },
	{ ClkStatusText,        0,              9,        sigstatusbar,   {.i = 9} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

