obj-m += hello_world_module.o
KDIR = /lib/modules/5.11.15-051115-generic/build

all:
	make -C $(KDIR)  M=$(shell pwd) modules
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
