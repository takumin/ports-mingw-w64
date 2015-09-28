--- gcc/graphite-isl-ast-to-gimple.c.orig	2015-01-09 20:18:42 UTC
+++ gcc/graphite-isl-ast-to-gimple.c
@@ -21,7 +21,9 @@ along with GCC; see the file COPYING3.  
 #include "config.h"
 
 #ifdef HAVE_isl
+#include <isl/constraint.h>
 #include <isl/set.h>
+#include <isl/union_set.h>
 #include <isl/map.h>
 #include <isl/union_map.h>
 #include <isl/ast_build.h>
