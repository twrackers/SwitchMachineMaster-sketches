#ifndef _SWITCH_MACHINE_CMDS__H_
#define _SWITCH_MACHINE_CMDS__H_

// Each command code has a Hamming distance
// of at least 2 bits from all other codes.
// Additional codes which would meet this
// criterion are (using only high 4 bits):
//   0x80  0xC0  0xE0  0xF0
// The same 4-bit patterns are used for the
// channel codes, but in the low 4 bits of
// the command byte.  Refresh and reset
// commands affect all channels so they
// don't require a channel code.

enum E_CMD {
  eMain    = 0x10,
  eDiv     = 0x20,
  eRefresh = 0x40,  // no channel code
  eReset   = 0x70   // no channel code
};

enum E_CHAN {
  eChan0 = 0x01,
  eChan1 = 0x02,
  eChan2 = 0x04,
  eChan3 = 0x07
};

#endif

