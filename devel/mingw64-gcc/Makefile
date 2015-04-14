# Created by: Takumi Takahashi <takumiiinn@gmail.com>
# $FreeBSD$

PORTNAME=	gcc
PORTVERSION=	4.9.2
CATEGORIES=	devel
MASTER_SITES=	GCC
PKGNAMEPREFIX=	mingw64-

MAINTAINER?=	takumiiinn@gmail.com
COMMENT?=	GNU Compiler Collection 4.9 for MinGW-w64

LICENSE=	GPLv3 GPLv3RLE
LICENSE_COMB=	multi

CPE_VENDOR=	gnu

OPTIONS_DEFINE=		SJLJ

OPTIONS_SINGLE=		THR
OPTIONS_SINGLE_THR=	WIN32 POSIX

OPTIONS_DEFAULT=	WIN32

WIN32_DESC=		Win32 API Threads model
POSIX_DESC=		POSIX Threads model
SJLJ_DESC=		Exception handling for setjump/longjmp

.ifndef PKGNAMESUFFIX
PORT_TYPE=	core
.else
PORT_TYPE=	${PKGNAMESUFFIX:S/-//}
.endif

USES=		cpe gmake iconv libtool makeinfo perl5 tar:bzip2
USE_PERL5=	build

LIB_DEPENDS+=	libgmp.so:${PORTSDIR}/math/gmp \
		libmpfr.so:${PORTSDIR}/math/mpfr \
		libmpc.so:${PORTSDIR}/math/mpc \
		libisl.so:${PORTSDIR}/devel/isl \
		libcloog-isl.so:${PORTSDIR}/math/cloog
BUILD_DEPENDS+=	${CROSS_TARGET}-as:${PORTSDIR}/devel/${PKGNAMEPREFIX}binutils \
		${LOCALBASE}/${CROSS_TARGET}/include/_mingw.h:${PORTSDIR}/devel/${PKGNAMEPREFIX}headers
RUN_DEPENDS+=	${CROSS_TARGET}-as:${PORTSDIR}/devel/${PKGNAMEPREFIX}binutils \
		${LOCALBASE}/${CROSS_TARGET}/include/_mingw.h:${PORTSDIR}/devel/${PKGNAMEPREFIX}headers

.if ${PORT_TYPE} == "core"
BUILD_DEPENDS+=	${LOCALBASE}/${CROSS_TARGET}/lib/libmingw32.a:${PORTSDIR}/devel/${PKGNAMEPREFIX}crt \
		${LOCALBASE}/${CROSS_TARGET}/lib/libpthread.a:${PORTSDIR}/devel/${PKGNAMEPREFIX}winpthreads
RUN_DEPENDS+=	${LOCALBASE}/${CROSS_TARGET}/lib/libmingw32.a:${PORTSDIR}/devel/${PKGNAMEPREFIX}crt \
		${LOCALBASE}/${CROSS_TARGET}/lib/libpthread.a:${PORTSDIR}/devel/${PKGNAMEPREFIX}winpthreads
.endif

.include <bsd.port.options.mk>

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

CONFIGURE_ARGS+=	--target=${CROSS_TARGET} \
			--enable-targets=all

.if ${PORT_OPTIONS:MWIN32}
CONFIGURE_ARGS+=	--enable-threads=win32
.elif ${PORT_OPTIONS:MPOSIX}
CONFIGURE_ARGS+=	--enable-threads=posix
.endif

.if ${PORT_OPTIONS:MSJLJ}
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
CONFIGURE_ARGS+=	--program-prefix=${CROSS_TARGET}- \
			--program-suffix=${PKGNAMESUFFIX}
.else
CONFIGURE_ARGS+=	--with-host-libstdcxx="-lstdc++ -lsupc++"
.endif

CONFIGURE_ARGS+=	--libdir=${PREFIX}/lib/${PKGNAMEPREFIX}${PKGNAMESUFFIX:S/-//} \
			--libexecdir=${PREFIX}/libexec/${PKGNAMEPREFIX}${PKGNAMESUFFIX:S/-//} \
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
PLIST=			${.CURDIR}/../mingw-gcc/pkg-plist.${PORT_TYPE}

.if ${PORT_TYPE} == "core"
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

pre-everything::
	@${ECHO_MSG} "Making GCC ${PORTVERSION} for Host:${CONFIGURE_TARGET} Target:${CROSS_TARGET} [${LANGUAGES}]"

pre-configure:
	cd ${SRCDIR} ; contrib/gcc_update --touch
	@${RM} -f ${SRCDIR}/gcc/*/*.info*
	@${MKDIR} ${CONFIGURE_WRKSRC}

post-stage:
	${RM} -rf ${STAGEDIR}${PREFIX}/include
	${RM} -rf ${STAGEDIR}${PREFIX}/info
	${RM} -f ${STAGEDIR}${PREFIX}/man/man1/*
	${MKDIR} ${STAGEDIR}${PREFIX}/${CROSS_TARGET}/bin
.if ${PORT_TYPE} == "bootstrap"
. for F in ${BINARIES}
	${LN} -f ${STAGEDIR}${PREFIX}/bin/${CROSS_TARGET}-$F${PKGNAMESUFFIX} \
		${STAGEDIR}${PREFIX}/${CROSS_TARGET}/bin/$F${PKGNAMESUFFIX}
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
