# Created by: Takumi Takahashi <takumiiinn@gmail.com>
# $FreeBSD$

PORTNAME=	gcc
PORTVERSION=	4.9.2
CATEGORIES=	devel
MASTER_SITES=	GCC

MAINTAINER?=	takumiiinn@gmail.com
COMMENT?=	GNU Compiler Collection 4.9 for MinGW-w64

LICENSE=	GPLv3 GPLv3RLE
LICENSE_COMB=	multi

PORT_TYPE?=	all
PORT_ARCH?=	multilib
THREADS_TYPE?=	win32
EXEPTION_TYPE?=	dwarf2

CPE_VENDOR=	gnu

USES=		cpe gmake iconv libtool makeinfo perl5 tar:bzip2
USE_PERL5=	build

LIB_DEPENDS+=	libgmp.so:${PORTSDIR}/math/gmp \
		libmpfr.so:${PORTSDIR}/math/mpfr \
		libmpc.so:${PORTSDIR}/math/mpc \
		libisl.so:${PORTSDIR}/devel/isl \
		libcloog-isl.so:${PORTSDIR}/math/cloog
BUILD_DEPENDS+=	${CROSS_TARGET}-as:${PORTSDIR}/devel/mingw-${PORT_ARCH}-binutils \
		${LOCALBASE}/${CROSS_TARGET}/include/_mingw.h:${PORTSDIR}/devel/mingw-w64-${PORT_ARCH}-headers
RUN_DEPENDS+=	${CROSS_TARGET}-as:${PORTSDIR}/devel/mingw-${PORT_ARCH}-binutils \
		${LOCALBASE}/${CROSS_TARGET}/include/_mingw.h:${PORTSDIR}/devel/mingw-w64-${PORT_ARCH}-headers

.if ${PORT_TYPE} == "all"
BUILD_DEPENDS+=	${LOCALBASE}/${CROSS_TARGET}/lib/libmingw32.a:${PORTSDIR}/devel/mingw-w64-${PORT_ARCH}-crt
RUN_DEPENDS+=	${LOCALBASE}/${CROSS_TARGET}/lib/libmingw32.a:${PORTSDIR}/devel/mingw-w64-${PORT_ARCH}-crt
. if ${THREADS_TYPE} == "posix"
BUILD_DEPENDS+=	${LOCALBASE}/${CROSS_TARGET}/lib/libpthread.a:${PORTSDIR}/devel/mingw-w64-${PORT_ARCH}-winpthreads
RUN_DEPENDS+=	${LOCALBASE}/${CROSS_TARGET}/lib/libpthread.a:${PORTSDIR}/devel/mingw-w64-${PORT_ARCH}-winpthreads
. endif
.endif

SRCDIR=		${WRKDIR}/gcc-${DISTVERSION}
WRKSRC=		${WRKDIR}/build
PATCH_WRKSRC=	${SRCDIR}

SSP_UNSAFE=	yes

LANGUAGES:=	c,c++
BINARIES=	c++ cpp g++ gcc gcov

.if ${PORT_TYPE} == "bootstrap"
ALL_TARGET=	all-gcc
INSTALL_TARGET=	install-gcc
UNIQUENAME=	${PKGNAMEPREFIX}${PORTNAME}${PKGNAMESUFFIX}
.endif

GNU_CONFIGURE=		yes
CONFIGURE_SCRIPT=	../${SRCDIR:S/${WRKDIR}\///}/configure
CONFIGURE_ARGS+=	--target=${CROSS_TARGET}
.if ${PORT_ARCH} == "multilib"
CONFIGURE_ARGS+=	--enable-targets=x86_64-w64-mingw32,i686-w64-mingw32
.else
CONFIGURE_ARGS+=	--disable-multilib
.endif
.if ${THREADS_TYPE} == "win32"
CONFIGURE_ARGS+=	--enable-threads=win32
.elif ${THREADS_TYPE} == "posix"
CONFIGURE_ARGS+=	--enable-threads=posix
.endif
.if ${EXEPTION_TYPE} == "dwarf2"
CONFIGURE_ARGS+=	--with-dwarf2
.elif ${EXEPTION_TYPE} == "sjlj"
CONFIGURE_ARGS+=	--enable-sjlj-exceptions
.endif
CONFIGURE_ARGS+=	--enable-languages=${LANGUAGES} \
			--enable-version-specific-runtime-libs \
			--enable-fully-dynamic-string \
			--enable-libstdcxx-time=yes \
			--disable-bootstrap \
			--disable-nls \
			--disable-win32-registry
.if ${PORT_TYPE} == "bootstrap"
CONFIGURE_ARGS+=	--libdir=${PREFIX}/lib/mingw-w64-bootstrap \
			--libexecdir=${PREFIX}/libexec/mingw-w64-bootstrap \
			--program-prefix=${CROSS_TARGET}- \
			--program-suffix=-bootstrap
.else
CONFIGURE_ARGS+=	--libdir=${PREFIX}/lib/mingw-w64 \
			--libexecdir=${PREFIX}/libexec/mingw-w64
.endif
CONFIGURE_ARGS+=	--with-host-libstdcxx="-lstdc++ -lsupc++" \
			--with-as=${LOCALBASE}/bin/${CROSS_TARGET}-as \
			--with-ld=${LOCALBASE}/bin/${CROSS_TARGET}-ld \
			--with-gmp=${LOCALBASE} \
			--with-mpfr=${LOCALBASE} \
			--with-mpc=${LOCALBASE} \
			--disable-isl-version-check \
			--with-isl=${LOCALBASE} \
			--with-cloog=${LOCALBASE} \
			${ICONV_CONFIGURE_ARG} \
			--with-pkgversion="FreeBSD Ports Collection for MinGW-w64" \
			--with-system-zlib
MAKE_ARGS+=		MAKEINFOFLAGS="--no-split"
USE_LDCONFIG=		yes
PLIST_SUB=		GCC_VERSION=${PORTVERSION} \
			GNU_HOST=${CONFIGURE_TARGET} \
			GNU_TARGET=${CROSS_TARGET}
PLIST=			${.CURDIR}/../mingw-gcc/pkg-plist.${PORT_ARCH}-${THREADS_TYPE}-${EXEPTION_TYPE}
.if ${PORT_TYPE} == "bootstrap"
INFO_PATH=		info/${CROSS_TARGET}-gcc
INFO=			cpp cppinternals gcc gccinstall gccint libquadmath
.endif

.include <bsd.port.pre.mk>

.if ${ARCH} == "amd64"
CONFIGURE_TARGET=	x86_64-portbld-${OPSYS:tl}${OSREL}
CROSS_ARCH=		x86_64
.else
CONFIGURE_TARGET=	${ARCH}-portbld-${OPSYS:tl}${OSREL}
CROSS_ARCH=		i686
.endif

CROSS_TARGET=	${CROSS_ARCH}-w64-mingw32
PKGNAMEPREFIX=	mingw-${PORT_ARCH}-
.if ${EXEPTION_TYPE} == "dwarf2" && ( ${PORT_ARCH} == "multilib" || ${PORT_ARCH} == "x86_64" )
PKGNAMESUFFIX=	-${THREADS_TYPE}-seh
.else
PKGNAMESUFFIX=	-${THREADS_TYPE}-${EXEPTION_TYPE}
.endif
.if ${PORT_TYPE} == "bootstrap"
PKGNAMESUFFIX+=	-bootstrap
.endif

pre-everything::
	@${ECHO_MSG} "Making GCC ${PORTVERSION} for Host:${CONFIGURE_TARGET} Target:${CROSS_TARGET} [${LANGUAGES}]"

pre-configure:
	cd ${SRCDIR} ; contrib/gcc_update --touch
	@${RM} -f ${SRCDIR}/gcc/*/*.info*
	@${MKDIR} ${CONFIGURE_WRKSRC}

post-stage:
.if ${PORT_TYPE} == "bootstrap"
	${RM} -rf ${STAGEDIR}${PREFIX}/include
	${RM} -rf ${STAGEDIR}${PREFIX}/info
	${RM} -f ${STAGEDIR}${PREFIX}/man/man1/*
. for F in ${BINARIES}
	${LN} -f ${STAGEDIR}${PREFIX}/bin/${CROSS_TARGET}-$F-bootstrap \
		${STAGEDIR}${PREFIX}/${CROSS_TARGET}/bin/$F-bootstrap
. endfor
.else
. for F in ${BINARIES}
	${LN} -f ${STAGEDIR}${PREFIX}/bin/${CROSS_TARGET}-$F \
		${STAGEDIR}${PREFIX}/${CROSS_TARGET}/bin/$F
. endfor
.endif
	${RM} -f ${STAGEDIR}${PREFIX}/man/man7/*
	${MKDIR} ${STAGEDIR}${PREFIX}/${CROSS_TARGET}/bin

.include <bsd.port.post.mk>
