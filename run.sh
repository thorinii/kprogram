#! /bin/bash
 
qemu_cmdline="qemu-system-x86_64 -cpu core2duo -m 256 -monitor stdio -s"
kernel_binary="kprogram.bin" 
 
function fail() { echo "$1"; exit 1; }
function prereq() {
	local c x
	if [ "$1" = "f" ]; then c=stat;x=file; else c=which;x=program; fi
	if [ -z "$3" ]; then
		$c "$2" >/dev/null || fail "$x $2 not found"
	else
		$c "$2" >/dev/null || fail "$x $2 (from package $3) not found"
	fi
}
 
# check prerequisites
prereq f kprogram.bin
prereq x qemu

$qemu_cmdline -kernel "$kernel_binary" -vga std $1
 
echo
