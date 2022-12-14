group "default" {
	targets = ["host"]
}

target "host" {
	target = "bake"
	output = [ "./BuildProducts" ]
}

target "linux" {
	target = "bake"
	platforms = [ "linux/arm64", "linux/amd64", "linux/i386", "linux/arm/v6", "linux/s390x" ]
	output = [ "./BuildProducts" ]
}

target "multiboot-i686" {
	target = "multiboot-i686-bake"
	platforms = [ "linux/i686" ]
	output = [ "./BuildProducts" ]
}

target "dos-x86" {
	target = "dos-x86-watcom-bake"
	output = [ "./BuildProducts" ]
}