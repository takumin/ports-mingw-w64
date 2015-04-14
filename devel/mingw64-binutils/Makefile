# Created by: Takumi Takahashi <takumiiinn@gmail.com>
# $FreeBSD$

PORTNAME=	binutils
PORTVERSION=	2.25
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_SOURCEWARE}
MASTER_SITE_SUBDIR=	binutils/releases
PKGNAMEPREFIX=	mingw64-

MAINTAINER=	takumiiinn@gmail.com
COMMENT=	GNU binary tools for MinGW-w64

LICENSE=	GPLv3 LGPL3
LICENSE_COMB=	multi

LICENSE_FILE_GPLv3=	${WRKSRC}/COPYING3
LICENSE_FILE_LGPL3=	${WRKSRC}/COPYING3.LIB

CPE_VENDOR=	gnu

USES=		cpe bison gmake libtool tar:bzip2 compiler:env
BUILD_DEPENDS+=	${LOCALBASE}/lib/libgmp.so:${PORTSDIR}/math/gmp \
		${LOCALBASE}/lib/libmpfr.so:${PORTSDIR}/math/mpfr

GNU_CONFIGURE=	yes
CONFIGURE_ARGS+=--target=${CROSS_TARGET} \
		--enable-targets=x86_64-w64-mingw32,i686-w64-mingw32 \
		--disable-nls

PLIST_SUB=	CROSS_TARGET=${CROSS_TARGET}
INFO_PATH=	info/${CROSS_TARGET}
INFO=		as bfd binutils gprof ld

.include <bsd.port.pre.mk>

.if ${ARCH} == "amd64"
CONFIGURE_TARGET=	x86_64-portbld-${OPSYS:tl}${OSREL}
CROSS_ARCH=		x86_64
.else
CONFIGURE_TARGET=	${ARCH}-portbld-${OPSYS:tl}${OSREL}
CROSS_ARCH=		i686
.endif

CROSS_TARGET=	${CROSS_ARCH}-w64-mingw32

post-stage:
	${LN} -f ${STAGEDIR}${PREFIX}/bin/${CROSS_TARGET}-size ${STAGEDIR}${PREFIX}/${CROSS_TARGET}/bin/size

.include <bsd.port.post.mk>
