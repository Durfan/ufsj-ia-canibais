#ifndef _MAIN_H
#define _MAIN_H

#define _GNU_SOURCE

#define M 3 // Missionaries
#define C 3 // Cannibals
#define B 1 // Lado inicial
#define MAPSIZE 32

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <linux/limits.h>

#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

#include "struct.h"
#include "solve.h"
#include "util.h"
#include "graph.h"
#include "stack.h"
#include "search.h"

#endif // _MAIN_H
