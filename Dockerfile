ARG DIST=stable

FROM debian:${DIST}-slim AS base

ENV LC_ALL C
ENV TZ=UTC
ENV DEBIAN_FRONTEND=noninteractive

RUN echo 'APT::Install-Recommends "0"; \n\
APT::Install-Suggests "0"; \n\
APT::Get::Assume-Yes "true"; \n\
' > /etc/apt/apt.conf.d/noninteractive

RUN apt-get update && \
	apt-get upgrade

RUN apt-get install build-essential autoconf automake libtool clang

RUN mkdir -p /src /dest /build
VOLUME [ "/dest" ]
WORKDIR /build



FROM --platform=$BUILDPLATFORM base AS hostbase

FROM hostbase AS c64base

RUN apt-get install build-essential cc65

FROM z88dk/z88dk AS z80base

FROM --platform=$BUILDPLATFORM hostbase AS x86base

RUN apt-get install bcc bin86 elks-libc

#FROM --platform=linux/amd64 ykode/openwatcom:1.9-ubi AS watcom
#RUN yum install -y automake autoconf libtool

FROM --platform=linux/amd64 alpine AS watcom
## https://github.com/crempp/watcom-docker

# Setup the build environment all in one pass. This helps us to reduce image
# size by doing cleanup in the same layer as the setup.
RUN apk add --no-cache --update --virtual .build-deps \
      g++ \
      gcc \
      git \
      make \
      musl-dev \
    # Build and install Watcom package
    && cd /tmp \
    && git clone https://github.com/open-watcom/open-watcom-v2.git \
    && cd open-watcom-v2 \
    && echo "export OWNOBUILD=\"nt386 wgml\"" >> setvars.sh \
    && echo "export OWGUINOBUILD=1" >> setvars.sh \
    && ./build.sh \
    && cp build/binbuild/* /usr/local/bin \
    && cd / \
    # Clean up after ourselves (do this in the same layer)
    && rm -rf /tmp/open-watcom-v2 \
    && apk del .build-deps \
    && rm -rf /var/cache/apk/*

CMD ["/bin/sh"]

###############################################################################
## Multi-architecture hosted Linux build target
###############################################################################

FROM base AS build
COPY . /src
RUN cd /src && autoreconf -fvi
RUN /src/configure --prefix="" && \
	make && \
	make check && \
	make install DESTDIR=/dest && \
	ls -lR /dest

FROM scratch AS bake
COPY --from=build /dest/ /

###############################################################################
## i386-pc Multiboot ELF build target
###############################################################################

FROM --platform=linux/i386 build AS multiboot-i686-build
RUN ./configure --prefix="" --host=i686-pc-elf && \
	make && \
	make check && \
	make install DESTDIR=/dest && \
	ls -lR /dest
FROM scratch AS multiboot-i686-bake
COPY --from=multiboot-i686-build /dest/ /

###############################################################################
## 8086 hosted DOS build target
###############################################################################

#FROM watcom AS dos-x86-watcom-build
FROM --platform=linux/amd64 lapinlabs/watcom AS dos-x86-watcom-build
RUN mkdir /src /dest /build
WORKDIR /build
RUN apk add autoconf automake libtool make
COPY . /src
RUN cd /src && autoreconf -fvi
RUN PATH=/usr/local/bin:$PATH /src/configure --prefix="" --host=i86-pc-msdos --disable-idl CC="bowcc" CPP="bowcc -E" LD="wcl" && \
	make && \
	make check && \
	make install DESTDIR=/dest && \
	ls -lR /dest
FROM scratch AS dos-x86-watcom-bake
COPY --from=dos-x86-watcom-build /dest/ /

FROM --platform=$BUILDPLATFORM x86base AS dos-x86-bcc-build
COPY . /src
RUN autoreconf -fvi
RUN ./configure --prefix="" --host=i86-pc-msdos --disable-idl CC="bcc -ansi -0 -Md -d" LD="ld86" || ( cat config.log ; exit 77 ) && \
	make && \
	make check && \
	make install DESTDIR=/dest && \
	ls -lR /dest
FROM scratch AS dos-x86-bcc-bake
COPY --from=dos-x86-bcc-build /dest/ /

## Devcontainer

FROM --platform=$BUILDPLATFORM hostbase AS devcontainer
RUN apt-get install curl gnupg apt-transport-https ca-certificates lsb-release apt-utils dialog
RUN mkdir /workspace /me
VOLUME /me
WORKDIR /me
RUN sed -i -e "s@:/root:@:/me:@" /etc/passwd
RUN curl -fsSL https://download.docker.com/linux/debian/gpg | gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
RUN echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/debian \
  $(lsb_release -cs) stable" | tee /etc/apt/sources.list.d/docker.list > /dev/null
RUN apt-get update
RUN apt-get upgrade
RUN apt-get install docker-ce docker-ce-cli containerd.io
RUN apt-get install git less openssh-client


