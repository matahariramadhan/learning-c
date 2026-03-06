# Phase 0 Notes

## VirtualBox blocked by KVM

Error:
`VT-x is being used by another hypervisor (VERR_VMX_IN_VMX_ROOT_MODE)`

Cause:
`kvm` and `kvm_intel` were loaded on the host, so VirtualBox could not use hardware virtualization.

Temporary fix:

```bash
sudo modprobe -r kvm_intel
sudo modprobe -r kvm
```

Check:

```bash
lsmod | grep kvm
```

Lesson:
Only one hypervisor stack should control VT-x at a time.
