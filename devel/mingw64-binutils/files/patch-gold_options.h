--- gold/options.h.orig	2014-10-14 07:32:04 UTC
+++ gold/options.h
@@ -715,9 +715,9 @@ class General_options
 	      N_("Output cross reference table"),
 	      N_("Do not output cross reference table"));
 
-  DEFINE_bool(ctors_in_init_array, options::TWO_DASHES, '\0', true,
-	      N_("Use DT_INIT_ARRAY for all constructors (default)"),
-	      N_("Handle constructors as directed by compiler"));
+  DEFINE_bool(ctors_in_init_array, options::TWO_DASHES, '\0', false,
+	      N_("Use DT_INIT_ARRAY for all constructors"),
+	      N_("Handle constructors as directed by compiler (default)"));
 
   DEFINE_bool(define_common, options::TWO_DASHES, 'd', false,
 	      N_("Define common symbols"),
