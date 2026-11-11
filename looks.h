#pragma once

#define RESET     "\033[0m"
#define BOLD      "\033[1m"
#define ITALIC    "\033[3m"
#define DIM       "\033[2m"
#define GREEN     "\033[38;2;140;235;60m"
#define ORANGE    "\033[38;2;255;150;20m"
#define CREAM     "\033[38;2;255;246;220m"
#define TURQUOISE "\033[38;2;60;230;220m"

void print_banner(void);
void display_prompt(void);
