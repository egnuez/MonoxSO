default:
	@echo "< kernel | floppy | iso | install_bl | run_bochs_floppy | run_bochs_cdrom | run_qemu_kernel | run_qemu_cdrom | run_vbost >"

# Crea el Kernel
kernel:
	$(MAKE) -C kernel/

# Crea imagen de floppy y le graba el MBR
floppy:
	rm -f boot.img
	mkfs.msdos -C boot.img 1440
	dd bs=512 count=1 if=boot/boot.bin of=boot.img conv=notrunc

# Genera imagen
iso:
	cp kernel/bin/kernel.elf PreMonox/boot/
	grub-mkrescue -o PreMonox.iso PreMonox/

# Mete en el floppy el segundo stage del bootloader y el kernel
install_bl:
	mount -o loop boot.img /mnt/
	cp boot/2ndstage.bin /mnt/
	cp kernel/bin/kernel.bin /mnt/
	umount /mnt/

run_bochs_floppy:
	bochs -f bochs_floppy.cfg

run_bochs_cdrom:
	bochs -f bochs_cdrom.cfg

run_qemu_kernel:
	qemu-system-x86_64 -kernel kernel/bin/kernel.elf

run_qemu_cdrom:
	qemu-system-x86_64 -boot d -cdrom PreMonox.iso -m 512

run_vbost:
	# You need to create a Virtual Machine before.
	virtualbox --startvm 'PreMonox'

clean:
	rm -f *.iso *.img PreMonox/boot/kernel.elf
	$(MAKE) -C kernel/ clean

.PHONY: kernel
