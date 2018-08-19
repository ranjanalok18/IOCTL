KDIR = /lib/modules/`uname -r`/build

PWD = `pwd`

obj-m=id1.o

default:
	make -C ${KDIR} M=${PWD} modules

clean:
	make -C ${KDIR} M=${PWD} clean
