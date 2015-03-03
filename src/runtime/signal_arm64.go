// Copyright 2014 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

// +build linux

package runtime

import "unsafe"

func dumpregs(c *sigctxt) {
	print("x0      ", hex(c.x0()), "\n")
	print("x1      ", hex(c.x1()), "\n")
	print("x2      ", hex(c.x2()), "\n")
	print("x3      ", hex(c.x3()), "\n")
	print("x4      ", hex(c.x4()), "\n")
	print("x5      ", hex(c.x5()), "\n")
	print("x6      ", hex(c.x6()), "\n")
	print("x7      ", hex(c.x7()), "\n")
	print("x8      ", hex(c.x8()), "\n")
	print("x9      ", hex(c.x9()), "\n")
	print("x10     ", hex(c.x10()), "\n")
	print("x11     ", hex(c.x11()), "\n")
	print("x12     ", hex(c.x12()), "\n")
	print("x13     ", hex(c.x13()), "\n")
	print("x14     ", hex(c.x14()), "\n")
	print("x15     ", hex(c.x15()), "\n")
	print("x16     ", hex(c.x16()), "\n")
	print("x17     ", hex(c.x17()), "\n")
	print("x18     ", hex(c.x18()), "\n")
	print("x19     ", hex(c.x19()), "\n")
	print("x20     ", hex(c.x20()), "\n")
	print("x21     ", hex(c.x21()), "\n")
	print("x22     ", hex(c.x22()), "\n")
	print("x23     ", hex(c.x23()), "\n")
	print("x24     ", hex(c.x24()), "\n")
	print("x25     ", hex(c.x25()), "\n")
	print("x26     ", hex(c.x26()), "\n")
	print("x27     ", hex(c.x27()), "\n")
	print("x28     ", hex(c.x28()), "\n")
	print("x29     ", hex(c.x29()), "\n")
	print("lr      ", hex(c.lr()), "\n")
	print("sp      ", hex(c.sp()), "\n")
	print("pc      ", hex(c.pc()), "\n")
	print("fault   ", hex(c.fault()), "\n")
}

func sighandler(sig uint32, info *siginfo, ctxt unsafe.Pointer, gp *g) {
	_g_ := getg()
	c := &sigctxt{info, ctxt}

	if sig == _SIGPROF {
		sigprof((*byte)(unsafe.Pointer(uintptr(c.pc()))), (*byte)(unsafe.Pointer(uintptr(c.sp()))), (*byte)(unsafe.Pointer(uintptr(c.lr()))), gp, _g_.m)
		return
	}

	flags := int32(_SigThrow)
	if sig < uint32(len(sigtable)) {
		flags = sigtable[sig].flags
	}
	if c.sigcode() != _SI_USER && flags&_SigPanic != 0 {
		// Make it look like a call to the signal func.
		// Have to pass arguments out of band since
		// augmenting the stack frame would break
		// the unwinding code.
		gp.sig = sig
		gp.sigcode0 = uintptr(c.sigcode())
		gp.sigcode1 = uintptr(c.fault())
		gp.sigpc = uintptr(c.pc())

		// We arrange lr, and pc to pretend the panicking
		// function calls sigpanic directly.
		// Always save LR to stack so that panics in leaf
		// functions are correctly handled. This smashes
		// the stack frame but we're not going back there
		// anyway.
		sp := c.sp() - 8 // sizeof uint64
		c.set_sp(sp)
		*(*uint64)(unsafe.Pointer(uintptr(sp))) = c.lr()

		// Don't bother saving PC if it's zero, which is
		// probably a call to a nil func: the old link register
		// is more useful in the stack trace.
		if gp.sigpc != 0 {
			c.set_lr(uint64(gp.sigpc))
		}

		// In case we are panicking from external C code
		c.set_r28(uint64(uintptr(unsafe.Pointer(gp))))
		c.set_pc(uint64(funcPC(sigpanic)))
		return
	}

	if c.sigcode() == _SI_USER || flags&_SigNotify != 0 {
		if sigsend(sig) {
			return
		}
	}

	if flags&_SigKill != 0 {
		exit(2)
	}

	if flags&_SigThrow == 0 {
		return
	}

	_g_.m.throwing = 1
	_g_.m.caughtsig = gp
	startpanic()

	if sig < uint32(len(sigtable)) {
		print(sigtable[sig].name, "\n")
	} else {
		print("Signal ", sig, "\n")
	}

	print("PC=", hex(c.pc()), "\n")
	if _g_.m.lockedg != nil && _g_.m.ncgo > 0 && gp == _g_.m.g0 {
		print("signal arrived during cgo execution\n")
		gp = _g_.m.lockedg
	}
	print("\n")

	var docrash bool
	if gotraceback(&docrash) > 0 {
		goroutineheader(gp)
		tracebacktrap(uintptr(c.pc()), uintptr(c.sp()), uintptr(c.lr()), gp)
		tracebackothers(gp)
		print("\n")
		dumpregs(c)
	}

	if docrash {
		crash()
	}

	exit(2)
}
