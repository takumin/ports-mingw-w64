# Created by: Takumi Takahashi <takumiiinn@gmail.com>
# $FreeBSD$

PORTNAME=	mingw-w64
PKGNAMESUFFIX?=	-crt
PORTVERSION=	4.0.1
CATEGORIES=	devel
MASTER_SITES=	SF/${PORTNAME}/${PORTNAME}/${PORTNAME}-release
DISTNAME=	${PORTNAME}-v${PORTVERSION}

MAINTAINER?=	takumiiinn@gmail.com
COMMENT?=	MinGW-w64 for headers and runtime

PORT_TYPE?=	crt

USES=		gmake libtool tar:bzip2

.if ${PORT_TYPE} == "winpthreads"
WRKSRC_SUBDIR=	${PORTNAME}-libraries/${PORT_TYPE}
.else
WRKSRC_SUBDIR=	${PORTNAME}-${PORT_TYPE}
.endif

.if ${PORT_TYPE} == "crt" || ${PORT_TYPE} == "winpthreads"
BUILD_DEPENDS+=	${CROSS_TARGET}-as:${PORTSDIR}/devel/${PORTNAME}-binutils \
		${CROSS_TARGET}-gcc-bootstrap:${PORTSDIR}/devel/${PORTNAME}-gcc-bootstrap \
		${LOCALBASE}/${CROSS_TARGET}/include/_mingw.h:${PORTSDIR}/devel/${PORTNAME}-headers
. if ${PORT_TYPE} == "winpthreads"
BUILD_DEPENDS+=	${LOCALBASE}/${CROSS_TARGET}/lib/libmingw32.a:${PORTSDIR}/devel/mingw-w64-crt
. endif
.endif

.if ${PORT_TYPE} == "crt" || ${PORT_TYPE} == "winpthreads"
CC:=	${CROSS_TARGET}-gcc-bootstrap
CPP:=	${CROSS_TARGET}-cpp-bootstrap
CXX:=	${CROSS_TARGET}-g++-bootstrap
.endif

GNU_CONFIGURE=		yes
GNU_CONFIGURE_PREFIX=	${PREFIX}/${CROSS_TARGET}
CONFIGURE_ARGS+=	--host=${CROSS_TARGET}

.if ${PORT_TYPE} == "headers"
CONFIGURE_ARGS+=	--enable-sdk=all \
			--enable-secure-api
.elif ${PORT_TYPE} == "crt"
CONFIGURE_ARGS+=	--enable-lib32 \
			--enable-lib64 \
			--enable-wildcard
.endif

SSP_UNSAFE=	yes
PLIST=		${.CURDIR}/../mingw-w64-crt/pkg-plist.${PORT_TYPE}
PLIST_SUB=	CROSS_TARGET=${CROSS_TARGET}

.include <bsd.port.pre.mk>

.if ${ARCH} == "amd64"
CONFIGURE_TARGET=	x86_64-portbld-${OPSYS:tl}${OSREL}
CROSS_ARCH=	x86_64
.else
CONFIGURE_TARGET=	${ARCH}-portbld-${OPSYS:tl}${OSREL}
CROSS_ARCH=	i686
.endif

CROSS_TARGET=	${CROSS_ARCH}-w64-mingw32

pre-configure:
.if ${PORT_TYPE} == "crt"
	${ECHO_CMD} '/* Dummy header */' > ${LOCALBASE}/${CROSS_TARGET}/include/pthread_signal.h
	${ECHO_CMD} '/* Dummy header */' > ${LOCALBASE}/${CROSS_TARGET}/include/pthread_time.h
	${ECHO_CMD} '/* Dummy header */' > ${LOCALBASE}/${CROSS_TARGET}/include/pthread_unistd.h
.elif ${PORT_TYPE} == "winpthreads"
	${REINPLACE_CMD} -e 's@^RCFLAGS.*$$@RCFLAGS = --preprocessor=${CROSS_TARGET}-cpp-bootstrap@' ${WRKSRC}/Makefile
.endif

post-stage:
.if ${PORT_TYPE} == "headers"
	${RM} ${STAGEDIR}${PREFIX}/${CROSS_TARGET}/include/pthread_signal.h
	${RM} ${STAGEDIR}${PREFIX}/${CROSS_TARGET}/include/pthread_time.h
	${RM} ${STAGEDIR}${PREFIX}/${CROSS_TARGET}/include/pthread_unistd.h
.elif ${PORT_TYPE} == "crt"
	${RM} ${LOCALBASE}/${CROSS_TARGET}/include/pthread_signal.h
	${RM} ${LOCALBASE}/${CROSS_TARGET}/include/pthread_time.h
	${RM} ${LOCALBASE}/${CROSS_TARGET}/include/pthread_unistd.h
.endif

.include <bsd.port.post.mk>
