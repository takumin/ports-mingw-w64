--- gcc/graphite-poly.h.orig	2015-01-05 12:33:28 UTC
+++ gcc/graphite-poly.h
@@ -22,6 +22,11 @@ along with GCC; see the file COPYING3.  
 #ifndef GCC_GRAPHITE_POLY_H
 #define GCC_GRAPHITE_POLY_H
 
+#ifndef HAVE_ISL_OPTIONS_SET_SCHEDULE_SERIALIZE_SCCS
+# define isl_stat int
+# define isl_stat_ok 0
+#endif
+
 typedef struct poly_dr *poly_dr_p;
 
 typedef struct poly_bb *poly_bb_p;
