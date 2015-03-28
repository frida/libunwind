FRIDA_HOST ?= qnx-i486

all: integrate

configure:
	(. ../build/fs-env-$(FRIDA_HOST).rc \
		&& autoreconf -ifv \
		&& rm -rf ../build/fs-tmp-$(FRIDA_HOST)/libunwind \
		&& mkdir ../build/fs-tmp-$(FRIDA_HOST)/libunwind \
		&& cd ../build/fs-tmp-$(FRIDA_HOST)/libunwind \
		&& ../../../libunwind/configure)

check:
	(. ../build/fs-env-$(FRIDA_HOST).rc \
		&& make -C ../build/fs-tmp-$(FRIDA_HOST)/libunwind install \
		&& $$CC -Wall -pipe -O0 -I../build/fs-$(FRIDA_HOST)/include -L../build/fs-$(FRIDA_HOST)/lib frida-test.c -o frida-test -lunwind -llzma)
	scp frida-test qnx:/root/
	ssh qnx "/root/frida-test"

integrate:
	(. ../build/fs-env-$(FRIDA_HOST).rc && make -C ../build/fs-tmp-$(FRIDA_HOST)/libunwind install)
	cp ../build/fs-$(FRIDA_HOST)/lib/libunwind.a ../build/sdk-$(FRIDA_HOST)/lib/libunwind.a
	(. ../build/frida-env-$(FRIDA_HOST).rc && make -C ../build/tmp-$(FRIDA_HOST)/frida-gum)

.PHONY: configure check integrate
