--- gcc/graphite-sese-to-poly.c.orig	2015-01-15 13:28:42 UTC
+++ gcc/graphite-sese-to-poly.c
@@ -21,6 +21,7 @@ along with GCC; see the file COPYING3.  
 #include "config.h"
 
 #ifdef HAVE_isl
+#include <isl/constraint.h>
 #include <isl/set.h>
 #include <isl/map.h>
 #include <isl/union_map.h>
