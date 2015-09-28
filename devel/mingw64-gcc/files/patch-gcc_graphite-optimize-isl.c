--- gcc/graphite-optimize-isl.c.orig	2015-01-09 20:18:42 UTC
+++ gcc/graphite-optimize-isl.c
@@ -21,7 +21,9 @@ along with GCC; see the file COPYING3.  
 #include "config.h"
 
 #ifdef HAVE_isl
+#include <isl/constraint.h>
 #include <isl/set.h>
+#include <isl/union_set.h>
 #include <isl/map.h>
 #include <isl/union_map.h>
 #include <isl/schedule.h>
@@ -530,13 +532,13 @@ getScheduleMap (isl_schedule *Schedule, 
   return ScheduleMap;
 }
 
-static int
+static isl_stat
 getSingleMap (__isl_take isl_map *map, void *user)
 {
   isl_map **singleMap = (isl_map **) user;
   *singleMap = map;
 
-  return 0;
+  return isl_stat_ok;
 }
 
 static void
@@ -608,7 +610,11 @@ optimize_isl (scop_p scop)
 
   isl_options_set_schedule_max_constant_term (scop->ctx, CONSTANT_BOUND);
   isl_options_set_schedule_maximize_band_depth (scop->ctx, 1);
+#ifdef HAVE_ISL_OPTIONS_SET_SCHEDULE_SERIALIZE_SCCS
+  isl_options_set_schedule_serialize_sccs (scop->ctx, 1);
+#else
   isl_options_set_schedule_fuse (scop->ctx, ISL_SCHEDULE_FUSE_MIN);
+#endif
   isl_options_set_on_error (scop->ctx, ISL_ON_ERROR_CONTINUE);
 
 #ifdef HAVE_ISL_SCHED_CONSTRAINTS_COMPUTE_SCHEDULE
