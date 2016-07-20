/* custom made by thibaud on 2011-03-19. Not entirely accurate */

union ic_scrReg {
	struct { uint32_t
		target:4, /*[3:0]*/
			hole31:27, /*[30:4]*/
		state:1; /*[31]*/
	} bits;

	uint32_t value;
};

struct ghub_int_ctrler {
	union ic_scrReg scr[256]; /* +0x0 */
	uint32_t line_sets[8]; /* +0x400 */
	uint32_t pad0[(0x500-0x420)/4]; /* +0x420 */
	uint8_t line_source[16]; /* +0x500 */
	uint32_t line_clears; /* +0x510 */
};
