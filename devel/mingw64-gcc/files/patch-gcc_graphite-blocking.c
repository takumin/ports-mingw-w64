--- gcc/graphite-blocking.c.orig	2015-01-09 20:18:42 UTC
+++ gcc/graphite-blocking.c
@@ -24,6 +24,7 @@ along with GCC; see the file COPYING3.  
 #include "config.h"
 
 #ifdef HAVE_isl
+#include <isl/constraint.h>
 #include <isl/set.h>
 #include <isl/map.h>
 #include <isl/union_map.h>
