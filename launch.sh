#!/bin/bash
qemu-system-x86_64 -enable-kvm -cpu host -cdrom dist/x86_64/kernel.iso
