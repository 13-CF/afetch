#define COLOR(BOLD, COLOR) "\033[" #BOLD ";" #COLOR "m"

/* BOLD COLOURS */
#define BBLACK   COLOR(1, 30)
#define BGRAY    COLOR(1, 90)
#define BRED     COLOR(1, 31)
#define BGREEN   COLOR(1, 32)
#define BYELLOW  COLOR(1, 33)
#define BBLUE    COLOR(1, 34)
#define BMAGENTA COLOR(1, 35)
#define BCYAN    COLOR(1, 36)
#define BWHITE   COLOR(1, 37)
/* NORMAL COLOURS */
#define BLACK   COLOR(0, 30)
#define RED     COLOR(0, 31)
#define GREEN   COLOR(0, 32)
#define YELLOW  COLOR(0, 33)
#define BLUE    COLOR(0, 34)
#define MAGENTA COLOR(0, 35)
#define CYAN    COLOR(0, 36)
#define WHITE   COLOR(0, 37)
/* OTHER */
#define RESET COLOR(0, )
#define BITAL COLOR(0, 3) 
