#ifndef ETI_MENU
#define ETI_MENU
#endif

#ifdef PDC_WIDE
#define TEXT TEXT_ncurses
#endif

#include <curses.h>
#include "WINeti.h"

#ifdef __cplusplus
extern "C" {
#endif

void myFunction();

#ifdef __cplusplus
}
#endif

#if defined(BUILDING_MENU)
#define MENU_IMPEXP PDC_EXPORT
#else
#define MENU_IMPEXP PDC_IMPORT
#endif

#define MENU_WRAPPED_VAR(type,name) extern MENU_IMPEXP type name(void)

#define MENU_EXPORT(type) MENU_IMPEXP type
#define MENU_EXPORT_VAR(type) MENU_IMPEXP type

typedef int Menu_Options;
typedef int Item_Options;

/* Menu options: */
#define O_ONEVALUE (0x01)
#define O_SHOWDESC (0x02)
#define O_ROWMAJOR (0x04)
#define O_IGNORECASE (0x08)
#define O_SHOWMATCH (0x10)
#define O_NONCYCLIC (0x20)
#define O_MOUSE_MENU (0x40)

/* Item options: */
#define O_SELECTABLE (0x01)

#if !PDC_OPAQUE_MENU
typedef struct
{
    const char *str;
    unsigned short length;
} TEXT;
#endif /* !PDC_OPAQUE_MENU */

struct tagMENU;

typedef struct tagITEM
#if !PDC_OPAQUE_MENU
{
    TEXT name; /* name of menu item */
    TEXT description; /* description of item, optional in display */
    struct tagMENU *imenu; /* Pointer to parent menu */
    void *userptr; /* Pointer to user defined per item data */
    Item_Options opt; /* Item options */
    short index; /* Item number if connected to a menu */
    short y; /* y and x location of item in menu */
    short x;
    bool value; /* Selection value */

    struct tagITEM *left;   /* neighbor items                            */
    struct tagITEM *right;
    struct tagITEM *up;
    struct tagITEM *down;

} ITEM;
#endif /* !PDC_OPAQUE_MENU */

typedef void (*Menu_Hook) (struct tagMENU *);

typedef struct tagMENU
#if 1 /* not yet: !PDC_OPAQUE_MENU */
{
    short height; /* Nr. of chars high */
    short width; /* Nr. of chars wide */
    short rows; /* Nr. of items high */
    short cols; /* Nr. of items wide */
    short frows; /* Nr. of formatted items high */
    short fcols; /* Nr. of formatted items wide */
    short arows; /* Nr. of items high (actual) */
    short namelen; /* Max. name length */
    short desclen; /* Max. description length */
    short marklen; /* Length of mark, if any */
    short itemlen; /* Length of one item */
    short spc_desc; /* Spacing for descriptor */
    short spc_cols; /* Spacing for columns */
    short spc_rows; /* Spacing for rows */
    char *pattern; /* Buffer to store match chars */
    short pindex; /* Index into pattern buffer */
    WINDOW *win; /* Window containing menu */
    WINDOW *sub; /* Subwindow for menu display */
    WINDOW *userwin; /* User's window */
    WINDOW *usersub; /* User's subwindow */
} MENU;
#endif /* 1 !PDC_OPAQUE_MENU */

/* Define keys */

#define REQ_LEFT_ITEM           (KEY_MAX + 1)
#define REQ_RIGHT_ITEM          (KEY_MAX + 2)
#define REQ_UP_ITEM             (KEY_MAX + 3)
#define REQ_DOWN_ITEM           (KEY_MAX + 4)
#define REQ_SCR_ULINE           (KEY_MAX + 5)
#define REQ_SCR_DLINE           (KEY_MAX + 6)
#define REQ_SCR_DPAGE           (KEY_MAX + 7)
#define REQ_SCR_UPAGE           (KEY_MAX + 8)
#define REQ_FIRST_ITEM          (KEY_MAX + 9)
#define REQ_LAST_ITEM           (KEY_MAX + 10)
#define REQ_NEXT_ITEM           (KEY_MAX + 11)
#define REQ_PREV_ITEM           (KEY_MAX + 12)
#define REQ_TOGGLE_ITEM         (KEY_MAX + 13)
#define REQ_CLEAR_PATTERN       (KEY_MAX + 14)
#define REQ_BACK_PATTERN        (KEY_MAX + 15)
#define REQ_NEXT_MATCH          (KEY_MAX + 16)
#define REQ_PREV_MATCH          (KEY_MAX + 17)

#define MIN_MENU_COMMAND        (KEY_MAX + 1)
#define MAX_MENU_COMMAND        (KEY_MAX + 17)

/*
 * Some AT&T code expects MAX_COMMAND to be out-of-band not
 * just for menu commands but for forms ones as well.
 */
#if defined(MAX_COMMAND)
#  if (MAX_MENU_COMMAND > MAX_COMMAND)
#    error Something is wrong -- MAX_MENU_COMMAND is greater than MAX_COMMAND
#  elif (MAX_COMMAND != (KEY_MAX + 128))
#    error Something is wrong -- MAX_COMMAND is already inconsistently defined.
#  endif
#else
#  define MAX_COMMAND (KEY_MAX + 128)
#endif

/* --------- prototypes for libmenu functions ----------------------------- */

extern ITEM **menu_items(const MENU *);
extern ITEM *current_item(const MENU *);
extern ITEM *new_item(const char *, const char *);

extern MENU *new_menu(ITEM **);

extern Item_Options item_opts(const ITEM *);
extern Menu_Options menu_opts(const MENU *);

extern Menu_Hook item_init(const MENU *);
extern Menu_Hook item_term(const MENU *);
extern Menu_Hook menu_init(const MENU *);
extern Menu_Hook menu_term(const MENU *);

extern WINDOW *menu_sub(const MENU *);
extern WINDOW *menu_win(const MENU *);

extern const char *item_description(const ITEM *);
extern const char *item_name(const ITEM *);
extern const char *menu_mark(const MENU *);
extern const char *menu_request_name(int);

extern char *menu_pattern(const MENU *);

extern void *menu_userptr(const MENU *);
extern void *item_userptr(const ITEM *);

extern chtype menu_back(const MENU *);
extern chtype menu_fore(const MENU *);
extern chtype menu_grey(const MENU *);

extern int free_item(ITEM *);
extern int free_menu(MENU *);
extern int item_count(const MENU *);
extern int item_index(const ITEM *);
extern int item_opts_off(ITEM *, Item_Options);
extern int item_opts_on(ITEM *, Item_Options);
extern int menu_driver(MENU *, int);
extern int menu_opts_off(MENU *, Menu_Options);
extern int menu_opts_on(MENU *, Menu_Options);
extern int menu_pad(const MENU *);
extern int pos_menu_cursor(const MENU *);
extern int post_menu(MENU *);
extern int scale_menu(const MENU *, int *, int *);
extern int set_current_item(MENU *, ITEM *);
extern int set_item_init(MENU *, Menu_Hook);
extern int set_item_opts(ITEM *, Item_Options);
extern int set_item_term(MENU *, Menu_Hook);
extern int set_item_userptr(ITEM *, void *);
extern int set_item_value(ITEM *, bool);
extern int set_menu_back(MENU *, chtype);
extern int set_menu_fore(MENU *, chtype);
extern int set_menu_format(MENU *, int, int);
extern int set_menu_grey(MENU *, chtype);
extern int set_menu_init(MENU *, Menu_Hook);
extern int set_menu_items(MENU *, ITEM **);
extern int set_menu_mark(MENU *, const char *);
extern int set_menu_opts(MENU *, Menu_Options);
extern int set_menu_pad(MENU *, int);
extern int set_menu_pattern(MENU *, const char *);
extern int set_menu_sub(MENU *, WINDOW *);
extern int set_menu_term(MENU *, Menu_Hook);
extern int set_menu_userptr(MENU *, void *);
extern int set_menu_win(MENU *, WINDOW *);
extern int set_top_row(MENU *, int);
extern int top_row(const MENU *);
extern int unpost_menu(MENU *);
extern int menu_request_by_name(const char *);
extern int set_menu_spacing(MENU *, int, int, int);
extern int menu_spacing(const MENU *, int *, int *, int *);
extern bool item_value(const ITEM *);
extern bool item_visible(const ITEM *);
extern void menu_format(const MENU *, int *, int *);
