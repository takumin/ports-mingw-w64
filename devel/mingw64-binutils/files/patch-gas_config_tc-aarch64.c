--- gas/config/tc-aarch64.c.orig	2015-07-21 08:20:58 UTC
+++ gas/config/tc-aarch64.c
@@ -55,9 +55,6 @@ static const aarch64_feature_set *march_
 /* Constants for known architecture features.  */
 static const aarch64_feature_set cpu_default = CPU_DEFAULT;
 
-static const aarch64_feature_set aarch64_arch_any = AARCH64_ANY;
-static const aarch64_feature_set aarch64_arch_none = AARCH64_ARCH_NONE;
-
 #ifdef OBJ_ELF
 /* Pre-defined "_GLOBAL_OFFSET_TABLE_"	*/
 static symbolS *GOT_symbol;
