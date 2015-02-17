// Copyright 2013 The Go Authors.  All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package runtime

import "unsafe"

type sigctxt struct {
	info *siginfo
	ctxt unsafe.Pointer
}

func (c *sigctxt) regs() *sigcontext { return &(*ucontext)(c.ctxt).uc_mcontext }
func (c *sigctxt) x0() uint64        { return c.regs().regs[0] }
func (c *sigctxt) x1() uint64        { return c.regs().regs[1] }
func (c *sigctxt) x2() uint64        { return c.regs().regs[2] }
func (c *sigctxt) x3() uint64        { return c.regs().regs[3] }
func (c *sigctxt) x4() uint64        { return c.regs().regs[4] }
func (c *sigctxt) x5() uint64        { return c.regs().regs[5] }
func (c *sigctxt) x6() uint64        { return c.regs().regs[6] }
func (c *sigctxt) x7() uint64        { return c.regs().regs[7] }
func (c *sigctxt) x8() uint64        { return c.regs().regs[8] }
func (c *sigctxt) x9() uint64        { return c.regs().regs[9] }
func (c *sigctxt) x10() uint64       { return c.regs().regs[10] }
func (c *sigctxt) x11() uint64       { return c.regs().regs[11] }
func (c *sigctxt) x12() uint64       { return c.regs().regs[12] }
func (c *sigctxt) x13() uint64       { return c.regs().regs[13] }
func (c *sigctxt) x14() uint64       { return c.regs().regs[14] }
func (c *sigctxt) x15() uint64       { return c.regs().regs[15] }
func (c *sigctxt) x16() uint64       { return c.regs().regs[16] }
func (c *sigctxt) x17() uint64       { return c.regs().regs[17] }
func (c *sigctxt) x18() uint64       { return c.regs().regs[18] }
func (c *sigctxt) x19() uint64       { return c.regs().regs[19] }
func (c *sigctxt) x20() uint64       { return c.regs().regs[20] }
func (c *sigctxt) x21() uint64       { return c.regs().regs[21] }
func (c *sigctxt) x22() uint64       { return c.regs().regs[22] }
func (c *sigctxt) x23() uint64       { return c.regs().regs[23] }
func (c *sigctxt) x24() uint64       { return c.regs().regs[24] }
func (c *sigctxt) x25() uint64       { return c.regs().regs[25] }
func (c *sigctxt) x26() uint64       { return c.regs().regs[26] }
func (c *sigctxt) x27() uint64       { return c.regs().regs[27] }
func (c *sigctxt) x28() uint64       { return c.regs().regs[28] }
func (c *sigctxt) x29() uint64       { return c.regs().regs[29] }
func (c *sigctxt) lr() uint64        { return c.regs().regs[30] }
func (c *sigctxt) sp() uint64        { return c.regs().sp }
func (c *sigctxt) pc() uint64        { return c.regs().pc }
func (c *sigctxt) pstate() uint64    { return c.regs().pstate }
func (c *sigctxt) fault() uint64     { return c.regs().fault_address }

func (c *sigctxt) sigcode() uint64 { return uint64(c.info.si_code) }
func (c *sigctxt) sigaddr() uint64 { return c.info.si_addr }

func (c *sigctxt) set_pc(x uint64)  { c.regs().pc = x }
func (c *sigctxt) set_sp(x uint64)  { c.regs().sp = x }
func (c *sigctxt) set_lr(x uint64)  { c.regs().regs[30] = x }
func (c *sigctxt) set_r28(x uint64) { c.regs().regs[28] = x }

func (c *sigctxt) set_sigaddr(x uint64) {
	*(*uintptr)(add(unsafe.Pointer(c.info), 2*ptrSize)) = uintptr(x)
}
