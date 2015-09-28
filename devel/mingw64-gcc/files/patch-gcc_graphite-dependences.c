--- gcc/graphite-dependences.c.orig	2015-01-09 20:18:42 UTC
+++ gcc/graphite-dependences.c
@@ -22,6 +22,7 @@ along with GCC; see the file COPYING3.  
 #include "config.h"
 
 #ifdef HAVE_isl
+#include <isl/constraint.h>
 #include <isl/set.h>
 #include <isl/map.h>
 #include <isl/union_map.h>
@@ -227,7 +228,7 @@ scop_get_transformed_schedule (scop_p sc
 /* Helper function used on each MAP of a isl_union_map.  Computes the
    maximal output dimension.  */
 
-static int
+static isl_stat
 max_number_of_out_dimensions (__isl_take isl_map *map, void *user)
 {
   int global_max = *((int *) user);
@@ -239,7 +240,7 @@ max_number_of_out_dimensions (__isl_take
 
   isl_map_free (map);
   isl_space_free (space);
-  return 0;
+  return isl_stat_ok;
 }
 
 /* Extends the output dimension of MAP to MAX dimensions.  */
@@ -263,12 +264,12 @@ struct extend_schedule_str {
 
 /* Helper function for extend_schedule.  */
 
-static int
+static isl_stat
 extend_schedule_1 (__isl_take isl_map *map, void *user)
 {
   struct extend_schedule_str *str = (struct extend_schedule_str *) user;
   str->umap = isl_union_map_add_map (str->umap, extend_map (map, str->max));
-  return 0;
+  return isl_stat_ok;
 }
 
 /* Return a relation that has uniform output dimensions.  */
@@ -277,16 +278,16 @@ __isl_give isl_union_map *
 extend_schedule (__isl_take isl_union_map *x)
 {
   int max = 0;
-  int res;
+  isl_stat res;
   struct extend_schedule_str str;
 
   res = isl_union_map_foreach_map (x, max_number_of_out_dimensions, (void *) &max);
-  gcc_assert (res == 0);
+  gcc_assert (res == isl_stat_ok);
 
   str.max = max;
   str.umap = isl_union_map_empty (isl_union_map_get_space (x));
   res = isl_union_map_foreach_map (x, extend_schedule_1, (void *) &str);
-  gcc_assert (res == 0);
+  gcc_assert (res == isl_stat_ok);
 
   isl_union_map_free (x);
   return str.umap;
