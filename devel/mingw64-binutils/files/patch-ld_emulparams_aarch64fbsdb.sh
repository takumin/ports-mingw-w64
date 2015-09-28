--- ld/emulparams/aarch64fbsdb.sh.orig	2015-09-28 16:11:55 UTC
+++ ld/emulparams/aarch64fbsdb.sh
@@ -0,0 +1,2 @@
+. ${srcdir}/emulparams/aarch64fbsd.sh
+OUTPUT_FORMAT="elf64-bigaarch64"
