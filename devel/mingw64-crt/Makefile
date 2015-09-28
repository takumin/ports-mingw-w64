# Created by: Takumi Takahashi <takumiiinn@gmail.com>
# $FreeBSD$

PORTNAME=	mingw64
PORTVERSION=	4.0.4
CATEGORIES=	devel
MASTER_SITES=	SF/mingw-w64/mingw-w64/mingw-w64-release
PKGNAMESUFFIX?=	-crt
DISTNAME=	mingw-w64-v${PORTVERSION}

MAINTAINER?=	takumiiinn@gmail.com
COMMENT?=	MinGW-w64 for headers and runtime

PORT_TYPE=	${PKGNAMESUFFIX:S/-//}

USES=		gmake libtool tar:bzip2

.if ${PORT_TYPE} == "headers" || ${PORT_TYPE} == "crt"
WRKSRC_SUBDIR=	mingw-w64-${PORT_TYPE}
.elif ${PORT_TYPE} == "libmangle" || ${PORT_TYPE} == "pseh" || \
	${PORT_TYPE} == "winpthreads" || ${PORT_TYPE} == "winstorecompat"
WRKSRC_SUBDIR=	mingw-w64-libraries/${PORT_TYPE}
.else
WRKSRC_SUBDIR=	mingw-w64-tools/${PORT_TYPE}
.endif

.if ! ${PORT_TYPE} == "headers"
BUILD_DEPENDS+=	${CROSS_TARGET}-as:${PORTSDIR}/devel/${PORTNAME}-binutils \
		${CROSS_TARGET}-gcc-bootstrap:${PORTSDIR}/devel/${PORTNAME}-gcc-bootstrap \
		${LOCALBASE}/${CROSS_TARGET}/include/_mingw.h:${PORTSDIR}/devel/${PORTNAME}-headers
. if ! ${PORT_TYPE} == "crt"
BUILD_DEPENDS+=	${LOCALBASE}/${CROSS_TARGET}/lib/libmingw32.a:${PORTSDIR}/devel/${PORTNAME}-crt
. endif
.endif

.if ! ${PORT_TYPE} == "headers"
CC:=		${CROSS_TARGET}-gcc-bootstrap
CPP:=		${CROSS_TARGET}-cpp-bootstrap
CXX:=		${CROSS_TARGET}-g++-bootstrap
_GCC_RUNTIME:=	${LOCALBASE}/lib/${PORTNAME}-bootstrap
CFLAGS+=	-Wl,-rpath=${_GCC_RUNTIME}
CXXFLAGS+=	-Wl,-rpath=${_GCC_RUNTIME}
LDFLAGS+=	-Wl,-rpath=${_GCC_RUNTIME} -L${_GCC_RUNTIME}
.endif

GNU_CONFIGURE=		yes
GNU_CONFIGURE_PREFIX=	${PREFIX}/${CROSS_TARGET}
CONFIGURE_ARGS+=	--host=${CROSS_TARGET}

.if ${PORT_TYPE} == "headers"
CONFIGURE_ARGS+=	--enable-sdk=all \
			--enable-secure-api
.elif ${PORT_TYPE} == "crt"
CONFIGURE_ARGS+=	--enable-wildcard
.endif

SSP_UNSAFE=	yes
PLIST=		${.CURDIR}/../${PORTNAME}-crt/pkg-plist.${PORT_TYPE}
PLIST_SUB=	CROSS_TARGET=${CROSS_TARGET}

.include <bsd.port.pre.mk>

.if ${ARCH} == "amd64"
CONFIGURE_TARGET=	x86_64-portbld-${OPSYS:tl}${OSREL}
CONFIGURE_ARGS+=	--enable-lib64 --disable-lib32
CROSS_ARCH=		x86_64
.else
CONFIGURE_TARGET=	${ARCH}-portbld-${OPSYS:tl}${OSREL}
CONFIGURE_ARGS+=	--enable-lib32 --disable-lib64
CROSS_ARCH=		i686
.endif

CROSS_TARGET=	${CROSS_ARCH}-w64-mingw32

#pre-configure:
#.if ${PORT_TYPE} == "crt"
#	${ECHO_CMD} '/* Dummy header */' > ${LOCALBASE}/${CROSS_TARGET}/include/pthread_signal.h
#	${ECHO_CMD} '/* Dummy header */' > ${LOCALBASE}/${CROSS_TARGET}/include/pthread_time.h
#	${ECHO_CMD} '/* Dummy header */' > ${LOCALBASE}/${CROSS_TARGET}/include/pthread_unistd.h
#.endif

post-configure:
.if ${PORT_TYPE} == "winpthreads"
	${REINPLACE_CMD} -e 's@^RCFLAGS.*$$@RCFLAGS = --preprocessor=${CROSS_TARGET}-cpp-bootstrap@' ${WRKSRC}/Makefile
.endif

#post-stage:
#.if ${PORT_TYPE} == "headers"
#	${RM} ${STAGEDIR}${PREFIX}/${CROSS_TARGET}/include/pthread_signal.h
#	${RM} ${STAGEDIR}${PREFIX}/${CROSS_TARGET}/include/pthread_time.h
#	${RM} ${STAGEDIR}${PREFIX}/${CROSS_TARGET}/include/pthread_unistd.h
#.elif ${PORT_TYPE} == "crt"
#	${RM} ${LOCALBASE}/${CROSS_TARGET}/include/pthread_signal.h
#	${RM} ${LOCALBASE}/${CROSS_TARGET}/include/pthread_time.h
#	${RM} ${LOCALBASE}/${CROSS_TARGET}/include/pthread_unistd.h
#.endif
#.if ${PORT_TYPE} == "crt"
#	${LN} -s ${CROSS_TARGET} ${STAGEDIR}${PREFIX}/mingw
#	${LN} -s lib ${STAGEDIR}${PREFIX}/${CROSS_TARGET}/lib64
#.endif

.include <bsd.port.post.mk>
