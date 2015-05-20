#include <stdint.h>
#if 0
#include <signal.h>
#endif
#include <assert.h>
#include <cmath>
#include <cstdio>

#if 0
#include <SDL.h>
#endif
#include <SDL2/SDL.h>
#include <vector>

#include "nesemu1.hh"
#include "SMB.hpp"

// This file has been modified from it's original form
// The original copyright is as follows.
// Most of this shouldn't be needed after everything has been translated
/* NESEMU1 : EMULATOR FOR THE NINTENDO ENTERTAINMENT SYSTEM (R) ARCHITECTURE  */
/* Written by and copyright (C) 2011  Joel Yliluoma - http://iki.fi/bisqwit/  */
/* Trademarks are owned by their respective owners. Lawyers love tautologies. */

static const char* inputfn = "input.fmv";

static const char* romFileName = "Super Mario Bros. (JU) (PRG0) [!].nes";
//static const char* romFileName = "docs/smbdisHL/smb.nes";

// Integer types
typedef uint_least32_t u32;
typedef uint_least16_t u16;
typedef uint_least8_t   u8;
typedef  int_least8_t   s8;

// Bitfield utilities
template<unsigned bitno, unsigned nbits=1, typename T=u8>
struct RegBit
{
	T data;
	enum { mask = (1u << nbits) - 1u };
	template<typename T2>
	RegBit& operator=(T2 val)
	{
		data = (data & ~(mask << bitno)) | ((nbits > 1 ? val & mask : !!val) << bitno);
		return *this;
	}
	operator unsigned() const { return (data >> bitno) & mask; }
	RegBit& operator++ ()     { return *this = *this + 1; }
	unsigned operator++ (int) { unsigned r = *this; ++*this; return r; }
};

namespace IO
{
#if 0
	SDL_Surface *s;
#endif
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	Uint32* frameBuffer;
	void Init()
	{
#if 0
		SDL_Init(SDL_INIT_VIDEO);
		SDL_InitSubSystem(SDL_INIT_VIDEO);
		s = SDL_SetVideoMode(256, 240, 32,0);
		signal(SIGINT, SIG_DFL);
#endif
		SDL_Init(SDL_INIT_VIDEO);

		window = SDL_CreateWindow(
			"SDL_app",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			256 * 3,
			240 * 3,
			0
		);

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		SDL_RenderSetLogicalSize(renderer, 256, 240);
		texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 256, 240);

		frameBuffer = new Uint32[256 * 240];
	}

	void PutPixel(unsigned px,unsigned py, unsigned pixel, int offset)
	{
		// The input value is a NES color index (with de-emphasis bits).
		// We need RGB values. To produce a RGB value, we emulate the NTSC circuitry.
		// For most part, this process is described at:
		//    http://wiki.nesdev.com/w/index.php/NTSC_video
		// Incidentally, this code is shorter than a table of 64*8 RGB values.
		static unsigned palette[3][64][512] = {}, prev=~0u;
		// Caching the generated colors
		if(prev == ~0u)
			for(int o=0; o<3; ++o)
			for(int u=0; u<3; ++u)
			for(int p0=0; p0<512; ++p0)
			for(int p1=0; p1<64; ++p1)
			{
				// Calculate the luma and chroma by emulating the relevant circuits:
				auto s = "\372\273\32\305\35\311I\330D\357}\13D!}N";
				int y=0, i=0, q=0;
				for(int p=0; p<12; ++p) // 12 samples of NTSC signal constitute a color.
				{
					// Sample either the previous or the current pixel.
					int r = (p+o*4)%12, pixel = r < 8-u*2 ? p0 : p1; // Use pixel=p0 to disable artifacts.
					// Decode the color index.
					int c = pixel%16, l = c<0xE ? pixel/4 & 12 : 4, e=p0/64;
					// NES NTSC modulator (square wave between up to four voltage levels):
					int b = 40 + s[(c > 12*((c+8+p)%12 < 6)) + 2*!(0451326 >> p/2*3 & e) + l];
					// Ideal TV NTSC demodulator:
					y += b;
					i += b * int(std::cos(M_PI * p / 6) * 5909);
					q += b * int(std::sin(M_PI * p / 6) * 5909);
				}
				// Convert the YIQ color into RGB
				auto gammafix = [=](float f) { return f <= 0.f ? 0.f : std::pow(f, 2.2f / 1.8f); };
				auto clamp    = [](int v) { return v>255 ? 255 : v; };
				// Store color at subpixel precision
				if(u==2) palette[o][p1][p0] += 0x10000*clamp(255 * gammafix(y/1980.f + i* 0.947f/9e6f + q* 0.624f/9e6f));
				if(u==1) palette[o][p1][p0] += 0x00100*clamp(255 * gammafix(y/1980.f + i*-0.275f/9e6f + q*-0.636f/9e6f));
				if(u==0) palette[o][p1][p0] += 0x00001*clamp(255 * gammafix(y/1980.f + i*-1.109f/9e6f + q* 1.709f/9e6f));
			}
		// Store the RGB color into the frame buffer.
#if 0
		((u32*) s->pixels) [py * 256 + px] = palette[offset][prev%64][pixel];
#endif
		frameBuffer[py * 256 + px] = palette[offset][prev % 64][pixel];
		prev = pixel;
	}
	void FlushScanline(unsigned py)
	{
#if 0
		if(py == 239) SDL_Flip(s);
#endif
		if(py == 239)
		{
			SDL_UpdateTexture(texture, NULL, frameBuffer, sizeof(Uint32) * 256);

			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, texture, NULL, NULL);
			SDL_RenderPresent(renderer);
			SDL_Delay(10);
		}
	}

	int joy_current[2]={0,0}, joy_next[2]={0,0}, joypos[2]={0,0};
	void JoyStrobe(unsigned v)
	{
		if(v) { joy_current[0] = joy_next[0]; joypos[0]=0; }
		if(v) { joy_current[1] = joy_next[1]; joypos[1]=0; }
	}
	u8 JoyRead(unsigned idx)
	{
		static const u8 masks[8] = {0x20,0x10,0x40,0x80,0x04,0x08,0x02,0x01};
		return ((joy_current[idx] & masks[joypos[idx]++ & 7]) ? 1 : 0);
	}
}

namespace GamePak
{
	std::vector<u8> ROM, VRAM(0x2000);
	unsigned mappernum;
	const unsigned VROM_Granularity = 0x0400, VROM_Pages = 0x2000 / VROM_Granularity;
	const unsigned ROM_Granularity  = 0x2000, ROM_Pages = 0x10000 / ROM_Granularity;
	unsigned char NRAM[0x1000], PRAM[0x2000];
	unsigned char* banks[ROM_Pages]  = {};
	unsigned char* Vbanks[VROM_Pages] = {};
	unsigned char *Nta[4] = { NRAM+0x0000, NRAM+0x0400, NRAM+0x0000, NRAM+0x0400 };

	template<unsigned npages,unsigned char*(&b)[npages], std::vector<u8>& r, unsigned granu>
	static void SetPages(unsigned size, unsigned baseaddr, unsigned index)
	{
		for(unsigned v = r.size() + index * size,
					 p = baseaddr / granu;
					 p < (baseaddr + size) / granu && p < npages;
					 ++p, v += granu)
			b[p] = &r[v % r.size()];
	}
	auto& SetROM  = SetPages< ROM_Pages, banks, ROM, ROM_Granularity>;
	auto& SetVROM = SetPages<VROM_Pages,Vbanks,VRAM,VROM_Granularity>;

	u8 Access(unsigned addr, u8 value, bool write)
	{
		if(write && addr >= 0x8000 && mappernum == 7) // e.g. Rare games
		{
			SetROM(0x8000, 0x8000, (value&7));
			Nta[0] = Nta[1] = Nta[2] = Nta[3] = &NRAM[0x400 * ((value>>4)&1)];
		}
		if(write && addr >= 0x8000 && mappernum == 2) // e.g. Rockman, Castlevania
		{
			SetROM(0x4000, 0x8000, value);
		}
		if(write && addr >= 0x8000 && mappernum == 3) // e.g. Kage, Solomon's Key
		{
			value &= Access(addr,0,false); // Simulate bus conflict
			SetVROM(0x2000, 0x0000, (value&3));
		}
		if(write && addr >= 0x8000 && mappernum == 1) // e.g. Rockman 2, Simon's Quest
		{
			static u8 regs[4]={0x0C,0,0,0}, counter=0, cache=0;
			if(value & 0x80) { regs[0]=0x0C; goto configure; }
			cache |= (value&1) << counter;
			if(++counter == 5)
			{
				regs[ (addr>>13) & 3 ] = value = cache;
			configure:
				cache = counter = 0;
				static const u8 sel[4][4] = { {0,0,0,0}, {1,1,1,1}, {0,1,0,1}, {0,0,1,1} };
				for(unsigned m=0; m<4; ++m) Nta[m] = &NRAM[0x400 * sel[regs[0]&3][m]];
				SetVROM(0x1000, 0x0000, ((regs[0]&16) ? regs[1] : ((regs[1]&~1)+0)));
				SetVROM(0x1000, 0x1000, ((regs[0]&16) ? regs[2] : ((regs[1]&~1)+1)));
				switch( (regs[0]>>2)&3 )
				{
					case 0: case 1:
						SetROM(0x8000, 0x8000, (regs[3] & 0xE) / 2);
						break;
					case 2:
						SetROM(0x4000, 0x8000, 0);
						SetROM(0x4000, 0xC000, (regs[3] & 0xF));
						break;
					case 3:
						SetROM(0x4000, 0x8000, (regs[3] & 0xF));
						SetROM(0x4000, 0xC000, ~0);
						break;
				}
			}
		}
		if( (addr >> 13) == 3 ) return PRAM[addr & 0x1FFF ];
		return banks[ (addr / ROM_Granularity) % ROM_Pages] [addr % ROM_Granularity];
	}
	void Init()
	{
		SetVROM(0x2000, 0x0000, 0);
		for(unsigned v=0; v<4; ++v) SetROM(0x4000, v*0x4000, v==3 ? -1 : 0);
	}
}

namespace CPU /* CPU: Ricoh RP2A03 (based on MOS6502, almost the same as in Commodore 64) */
{
	u8 RAM[0x800];
	bool reset=true, nmi=false, nmi_edge_detected=false, intr=false;

	template<bool write> u8 MemAccess(u16 addr, u8 v=0);
	u8 RB(u16 addr)      { return MemAccess<0>(addr); }
	u8 WB(u16 addr,u8 v) { return MemAccess<1>(addr, v); }
	void tick();
}

namespace PPU /* Picture Processing Unit */
{
	union regtype // PPU register file
	{
		u32 value;
		// Reg0 (write)             // Reg1 (write)             // Reg2 (read)
		RegBit<0,8,u32> sysctrl;    RegBit< 8,8,u32> dispctrl;  RegBit<16,8,u32> status;
		RegBit<0,2,u32> BaseNTA;    RegBit< 8,1,u32> Grayscale; RegBit<21,1,u32> SPoverflow;
		RegBit<2,1,u32> Inc;        RegBit< 9,1,u32> ShowBG8;   RegBit<22,1,u32> SP0hit;
		RegBit<3,1,u32> SPaddr;     RegBit<10,1,u32> ShowSP8;   RegBit<23,1,u32> InVBlank;
		RegBit<4,1,u32> BGaddr;     RegBit<11,1,u32> ShowBG;    // Reg3 (write)
		RegBit<5,1,u32> SPsize;     RegBit<12,1,u32> ShowSP;    RegBit<24,8,u32> OAMaddr;
		RegBit<6,1,u32> SlaveFlag;  RegBit<11,2,u32> ShowBGSP;  RegBit<24,2,u32> OAMdata;
		RegBit<7,1,u32> NMIenabled; RegBit<13,3,u32> EmpRGB;    RegBit<26,6,u32> OAMindex;
	} reg;
	// Raw memory data as read&written by the game
	u8 palette[32], OAM[256];
	// Decoded sprite information, used & changed during each scanline
	struct { u8 sprindex, y, index, attr, x; u16 pattern; } OAM2[8], OAM3[8];

	union scrolltype
	{
		RegBit<3,16,u32> raw;       // raw VRAM address (16-bit)
		RegBit<0, 8,u32> xscroll;   // low 8 bits of first write to 2005
		RegBit<0, 3,u32> xfine;     // low 3 bits of first write to 2005
		RegBit<3, 5,u32> xcoarse;   // high 5 bits of first write to 2005
		RegBit<8, 5,u32> ycoarse;   // high 5 bits of second write to 2005
		RegBit<13,2,u32> basenta;   // nametable index (copied from 2000)
		RegBit<13,1,u32> basenta_h; // horizontal nametable index
		RegBit<14,1,u32> basenta_v; // vertical   nametable index
		RegBit<15,3,u32> yfine;     // low 3 bits of second write to 2005
		RegBit<11,8,u32> vaddrhi;   // first write to 2006 (with high 2 bits set to zero)
		RegBit<3, 8,u32> vaddrlo;   // second write to 2006
	} scroll, vaddr;

	unsigned pat_addr, sprinpos, sproutpos, sprrenpos, sprtmp;
	u16 tileattr, tilepat, ioaddr;
	u32 bg_shift_pat, bg_shift_attr;

	int scanline=241, x=0, scanline_end=341, VBlankState=0, cycle_counter=0;
	int read_buffer=0, open_bus=0, open_bus_decay_timer=0;
	bool even_odd_toggle=false, offset_toggle=false;

	/* Memory mapping: Convert PPU memory address into a reference to relevant data */
	u8& mmap(int i)
	{
		i &= 0x3FFF;
		if(i >= 0x3F00) { if(i%4==0) i &= 0x0F; return palette[i & 0x1F]; }
		if(i < 0x2000) return GamePak::Vbanks[(i / GamePak::VROM_Granularity) % GamePak::VROM_Pages]
											 [ i % GamePak::VROM_Granularity];
		return                GamePak::Nta[   (i>>10)&3][i&0x3FF];
	}
	// External I/O: read or write
	u8 Access(u16 index, u8 v, bool write)
	{
		auto RefreshOpenBus = [&](u8 v) { return open_bus_decay_timer = 77777, open_bus = v; };
		u8 res = open_bus;
		if(write) RefreshOpenBus(v);
		switch(index) // Which port from $200x?
		{
			case 0: if(write) { reg.sysctrl  = v; scroll.basenta = reg.BaseNTA; } break;
			case 1: if(write) { reg.dispctrl = v; } break;
			case 2: if(write) break;
					res = reg.status | (open_bus & 0x1F);
					reg.InVBlank = false;  // Reading $2002 clears the vblank flag.
					offset_toggle = false; // Also resets the toggle for address updates.
					if(VBlankState != -5)
						VBlankState = 0; // This also may cancel the setting of InVBlank.
					break;
			case 3: if(write) reg.OAMaddr        = v; break; // Index into Object Attribute Memory
			case 4: if(write) OAM[reg.OAMaddr++] = v;        // Write or read the OAM (sprites).
					else res = RefreshOpenBus(OAM[reg.OAMaddr] & (reg.OAMdata==2 ? 0xE3 : 0xFF));
					break;
			case 5: if(!write) break; // Set background scrolling offset
				if(offset_toggle) { scroll.yfine   = v & 7; scroll.ycoarse = v >> 3; }
				else              { scroll.xscroll = v; }
				offset_toggle = !offset_toggle;
				break;
			case 6: if(!write) break; // Set video memory position for reads/writes
				if(offset_toggle) { scroll.vaddrlo = v; vaddr.raw = (unsigned) scroll.raw; }
				else              { scroll.vaddrhi = v & 0x3F; }
				offset_toggle = !offset_toggle;
				break;
			case 7:
				res = read_buffer;
				u8& t = mmap(vaddr.raw); // Access the video memory.
				if(write) res = t = v;
				else { if((vaddr.raw & 0x3F00) == 0x3F00) // palette?
						  res = read_buffer = (open_bus & 0xC0) | (t & 0x3F);
					   read_buffer = t; }
				RefreshOpenBus(res);
				vaddr.raw = vaddr.raw + (reg.Inc ? 32 : 1); // The address is automatically updated.
				break;
		}
		return res;
	}
	void rendering_tick()
	{
		bool tile_decode_mode = 0x10FFFF & (1u << (x/16)); // When x is 0..255, 320..335

		// Each action happens in two steps: 1) select memory address; 2) receive data and react on it.
		switch(x % 8)
		{
			case 2: // Point to attribute table
				ioaddr = 0x23C0 + 0x400*vaddr.basenta + 8*(vaddr.ycoarse/4) + (vaddr.xcoarse/4);
				if(tile_decode_mode) break; // Or nametable, with sprites.
			case 0: // Point to nametable
				ioaddr = 0x2000 + (vaddr.raw & 0xFFF);
				// Reset sprite data
				if(x == 0) { sprinpos = sproutpos = 0; if(reg.ShowSP) reg.OAMaddr = 0; }
				if(!reg.ShowBG) break;
				// Reset scrolling (vertical once, horizontal each scanline)
				if(x == 304 && scanline == -1) vaddr.raw = (unsigned) scroll.raw;
				if(x == 256) { vaddr.xcoarse   = (unsigned)scroll.xcoarse;
							   vaddr.basenta_h = (unsigned)scroll.basenta_h;
							   sprrenpos = 0; }
				break;
			case 1:
				if(x == 337 && scanline == -1 && even_odd_toggle && reg.ShowBG) scanline_end = 340;
				// Name table access
				pat_addr = 0x1000*reg.BGaddr + 16*mmap(ioaddr) + vaddr.yfine;
				if(!tile_decode_mode) break;
				// Push the current tile into shift registers.
				// The bitmap pattern is 16 bits, while the attribute is 2 bits, repeated 8 times.
				bg_shift_pat  = (bg_shift_pat  >> 16) + 0x00010000 * tilepat;
				bg_shift_attr = (bg_shift_attr >> 16) + 0x55550000 * tileattr;
				break;
			case 3:
				// Attribute table access
				if(tile_decode_mode)
				{
					tileattr = (mmap(ioaddr) >> ((vaddr.xcoarse&2) + 2*(vaddr.ycoarse&2))) & 3;
					// Go to the next tile horizontally (and switch nametable if it wraps)
					if(!++vaddr.xcoarse) { vaddr.basenta_h = 1-vaddr.basenta_h; }
					// At the edge of the screen, do the same but vertically
					if(x==251 && !++vaddr.yfine && ++vaddr.ycoarse == 30)
						{ vaddr.ycoarse = 0; vaddr.basenta_v = 1-vaddr.basenta_v; }
				}
				else if(sprrenpos < sproutpos)
				{
					// Select sprite pattern instead of background pattern
					auto& o = OAM3[sprrenpos]; // Sprite to render on next scanline
					memcpy(&o, &OAM2[sprrenpos], sizeof(o));
					unsigned y = (scanline) - o.y;
					if(o.attr & 0x80) y ^= (reg.SPsize ? 15 : 7);
					pat_addr = 0x1000 * (reg.SPsize ? (o.index & 0x01) : reg.SPaddr);
					pat_addr +=  0x10 * (reg.SPsize ? (o.index & 0xFE) : (o.index & 0xFF));
					pat_addr += (y&7) + (y&8)*2;
				}
				break;
			// Pattern table bytes
			case 5:
				tilepat = mmap(pat_addr|0);
				break;
			case 7: // Interleave the bits of the two pattern bytes
				unsigned p = tilepat | (mmap(pat_addr|8) << 8);
				p = (p&0xF00F) | ((p&0x0F00)>>4) | ((p&0x00F0)<<4);
				p = (p&0xC3C3) | ((p&0x3030)>>2) | ((p&0x0C0C)<<2);
				p = (p&0x9999) | ((p&0x4444)>>1) | ((p&0x2222)<<1);
				tilepat = p;
				// When decoding sprites, save the sprite graphics and move to next sprite
				if(!tile_decode_mode && sprrenpos < sproutpos)
					OAM3[sprrenpos++].pattern = tilepat;
				break;
		}
		// Find which sprites are visible on next scanline (TODO: implement crazy 9-sprite malfunction)
		switch(x>=64 && x<256 && x%2 ? (reg.OAMaddr++ & 3) : 4)
		{
			default:
				// Access OAM (object attribute memory)
				sprtmp = OAM[reg.OAMaddr];
				break;
			case 0:
				if(sprinpos >= 64) { reg.OAMaddr=0; break; }
				++sprinpos; // next sprite
				if(sproutpos<8) OAM2[sproutpos].y        = sprtmp;
				if(sproutpos<8) OAM2[sproutpos].sprindex = reg.OAMindex;
			   {int y1 = sprtmp, y2 = sprtmp + (reg.SPsize?16:8);
				if(!( scanline >= y1 && scanline < y2 ))
					reg.OAMaddr = sprinpos != 2 ? reg.OAMaddr+3 : 8;}
				break;
			case 1:
				if(sproutpos<8) OAM2[sproutpos].index = sprtmp;
				break;
			case 2:
				if(sproutpos<8) OAM2[sproutpos].attr  = sprtmp;
				break;
			case 3:
				if(sproutpos<8) OAM2[sproutpos].x = sprtmp;
				if(sproutpos<8) ++sproutpos; else reg.SPoverflow = true;
				if(sprinpos == 2) reg.OAMaddr = 8;
				break;
		}
	}
	void render_pixel()
	{
		bool edge   = u8(x+8) < 16; // 0..7, 248..255
		bool showbg = reg.ShowBG && (!edge || reg.ShowBG8);
		bool showsp = reg.ShowSP && (!edge || reg.ShowSP8);

		// Render the background
		unsigned fx = scroll.xfine, xpos = 15 - (( (x&7) + fx + 8*!!(x&7) ) & 15);

		unsigned pixel = 0, attr = 0;
		if(showbg) // Pick a pixel from the shift registers
		{
			pixel = (bg_shift_pat  >> (xpos*2)) & 3;
			attr  = (bg_shift_attr >> (xpos*2)) & (pixel ? 3 : 0);
		}
		else if( (vaddr.raw & 0x3F00) == 0x3F00 && !reg.ShowBGSP )
			pixel = vaddr.raw;

		// Overlay the sprites
		if(showsp)
			for(unsigned sno=0; sno<sprrenpos; ++sno)
			{
				auto& s = OAM3[sno];
				// Check if this sprite is horizontally in range
				unsigned xdiff = x - s.x;
				if(xdiff >= 8) continue; // Also matches negative values
				// Determine which pixel to display; skip transparent pixels
				if(!(s.attr & 0x40)) xdiff = 7-xdiff;
				u8 spritepixel = (s.pattern >> (xdiff*2)) & 3;
				if(!spritepixel) continue;
				// Register sprite-0 hit if applicable
				if(x < 255 && pixel && s.sprindex == 0) reg.SP0hit = true;
				// Render the pixel unless behind-background placement wanted
				if(!(s.attr & 0x20) || !pixel)
				{
					attr = (s.attr & 3) + 4;
					pixel = spritepixel;
				}
				// Only process the first non-transparent sprite pixel.
				break;
			}
		pixel = palette[ (attr*4 + pixel) & 0x1F ] & (reg.Grayscale ? 0x30 : 0x3F);
		IO::PutPixel(x, scanline, pixel | (reg.EmpRGB << 6), cycle_counter);
	}

	// PPU::tick() -- This function is called 3 times per each CPU cycle.
	// Each call iterates through one pixel of the screen.
	// The screen is divided into 262 scanlines, each having 341 columns, as such:
	//
	//           x=0                 x=256      x=340
	//       ___|____________________|__________|
	//  y=-1    | pre-render scanline| prepare  | >
	//       ___|____________________| sprites _| > Graphics
	//  y=0     | visible area       | for the  | > processing
	//          | - this is rendered | next     | > scanlines
	//  y=239   |   on the screen.   | scanline | >
	//       ___|____________________|______
	//  y=240   | idle
	//       ___|_______________________________
	//  y=241   | vertical blanking (idle)
	//          | 20 scanlines long
	//  y=260___|____________________|__________|
	//
	// On actual PPU, the scanline begins actually before x=0, with
	// sync/colorburst/black/background color being rendered, and
	// ends after x=256 with background/black being rendered first,
	// but in this emulator we only care about the visible area.
	//
	// When background rendering is enabled, scanline -1 is
	// 340 or 341 pixels long, alternating each frame.
	// In all other situations the scanline is 341 pixels long.
	// Thus, it takes 89341 or 89342 PPU::tick() calls to render 1 frame.
	void tick()
	{
		// Set/clear vblank where needed
		switch(VBlankState)
		{
			case -5: reg.status = 0; break;
			case 2: reg.InVBlank = true; break;
			case 0: CPU::nmi = reg.InVBlank && reg.NMIenabled; break;
		}
		if(VBlankState != 0) VBlankState += (VBlankState < 0 ? 1 : -1);
		if(open_bus_decay_timer) if(!--open_bus_decay_timer) open_bus = 0;

		// Graphics processing scanline?
		if(scanline < 240)
		{
			/* Process graphics for this cycle */
			if(reg.ShowBGSP) rendering_tick();
			if(scanline >= 0 && x < 256) render_pixel();
		}

		// Done with the cycle. Check for end of scanline.
		if(++cycle_counter == 3) cycle_counter = 0; // For NTSC pixel shifting
		if(++x >= scanline_end)
		{
			// Begin new scanline
			IO::FlushScanline(scanline);
			scanline_end = 341;
			x            = 0;
			// Does something special happen on the new scanline?
			switch(scanline += 1)
			{
				case 261: // Begin of rendering
					scanline = -1; // pre-render line
					even_odd_toggle = !even_odd_toggle;
					// Clear vblank flag
					VBlankState = -5;
					break;
				case 241: // Begin of vertical blanking
#if 0
					// I cheat here: I did not bother to learn how to use SDL events,
					// so I simply read button presses from a movie file, which happens
					// to be a TAS, rather than from the keyboard or from a joystick.
					static FILE* fp = fopen(inputfn, "rb");
					if(fp)
					{
						static unsigned ctrlmask = 0;
						if(!ftell(fp))
						{
							fseek(fp, 0x05, SEEK_SET);
							ctrlmask = fgetc(fp);
							fseek(fp, 0x90, SEEK_SET); // Famtasia Movie format.
						}
						if(ctrlmask & 0x80) { IO::joy_next[0] = fgetc(fp); if(feof(fp)) IO::joy_next[0] = 0; }
						if(ctrlmask & 0x40) { IO::joy_next[1] = fgetc(fp); if(feof(fp)) IO::joy_next[1] = 0; }
					}
#endif
					// Get input
					SDL_PumpEvents();
					const Uint8* keys = SDL_GetKeyboardState(NULL);
					if( keys[SDL_SCANCODE_ESCAPE] )
					{
						exit(0);
					}
					IO::joy_next[0] = 0x0;
					if( keys[SDL_SCANCODE_RIGHT] ) IO::joy_next[0] += 0x1;
					if( keys[SDL_SCANCODE_LEFT] ) IO::joy_next[0] += 0x2;
					if( keys[SDL_SCANCODE_UP] ) IO::joy_next[0] += 0x4;
					if( keys[SDL_SCANCODE_DOWN] ) IO::joy_next[0] += 0x8;
					if( keys[SDL_SCANCODE_Z] ) IO::joy_next[0] += 0x10;
					if( keys[SDL_SCANCODE_X] ) IO::joy_next[0] += 0x20;
					if( keys[SDL_SCANCODE_SPACE] ) IO::joy_next[0] += 0x40;
					if( keys[SDL_SCANCODE_RETURN] ) IO::joy_next[0] += 0x80;

					// Set vblank flag
					VBlankState = 2;
			}
		}
	}
}

namespace APU /* Audio Processing Unit */
{
	static const u8 LengthCounters[32] = { 10,254,20, 2,40, 4,80, 6,160, 8,60,10,14,12,26,14,
										   12, 16,24,18,48,20,96,22,192,24,72,26,16,28,32,30 };
	static const u16 NoisePeriods[16] = { 2,4,8,16,32,48,64,80,101,127,190,254,381,508,1017,2034 };
	static const u16 DMCperiods[16] = { 428,380,340,320,286,254,226,214,190,160,142,128,106,84,72,54 };

	bool FiveCycleDivider = false, IRQdisable = true, ChannelsEnabled[5] = { false };
	bool PeriodicIRQ = false, DMC_IRQ = false;
	bool count(int& v, int reset) { return --v < 0 ? (v=reset),true : false; }

	struct channel
	{
		int length_counter, linear_counter, address, envelope;
		int sweep_delay, env_delay, wave_counter, hold, phase, level;
		union // Per-channel register file
		{
			// 4000, 4004, 400C, 4012:            // 4001, 4005, 4013:            // 4002, 4006, 400A, 400E:
			RegBit<0,8,u32> reg0;                 RegBit< 8,8,u32> reg1;          RegBit<16,8,u32> reg2;
			RegBit<6,2,u32> DutyCycle;            RegBit< 8,3,u32> SweepShift;    RegBit<16,4,u32> NoiseFreq;
			RegBit<4,1,u32> EnvDecayDisable;      RegBit<11,1,u32> SweepDecrease; RegBit<23,1,u32> NoiseType;
			RegBit<0,4,u32> EnvDecayRate;         RegBit<12,3,u32> SweepRate;     RegBit<16,11,u32> WaveLength;
			RegBit<5,1,u32> EnvDecayLoopEnable;   RegBit<15,1,u32> SweepEnable;   // 4003, 4007, 400B, 400F, 4010:
			RegBit<0,4,u32> FixedVolume;          RegBit< 8,8,u32> PCMlength;     RegBit<24,8,u32> reg3;
			RegBit<5,1,u32> LengthCounterDisable;                                 RegBit<27,5,u32> LengthCounterInit;
			RegBit<0,7,u32> LinearCounterInit;                                    RegBit<30,1,u32> LoopEnabled;
			RegBit<7,1,u32> LinearCounterDisable;                                 RegBit<31,1,u32> IRQenable;
		} reg;

		// Function for updating the wave generators and taking the sample for each channel.
		template<unsigned c>
		int tick()
		{
			channel& ch = *this;
			if(!ChannelsEnabled[c]) return c==4 ? 64 : 8;
			int wl = (ch.reg.WaveLength+1) * (c >= 2 ? 1 : 2);
			if(c == 3) wl = NoisePeriods[ ch.reg.NoiseFreq ];
			int volume = ch.length_counter ? ch.reg.EnvDecayDisable ? ch.reg.FixedVolume : ch.envelope : 0;
			// Sample may change at wavelen intervals.
			auto& S = ch.level;
			if(!count(ch.wave_counter, wl)) return S;
			switch(c)
			{
				default:// Square wave. With four different 8-step binary waveforms (32 bits of data total).
					if(wl < 8) return S = 8;
					return S = (0xF33C0C04u & (1u << (++ch.phase % 8 + ch.reg.DutyCycle * 8))) ? volume : 0;

				case 2: // Triangle wave
					if(ch.length_counter && ch.linear_counter && wl >= 3) ++ch.phase;
					return S = (ch.phase & 15) ^ ((ch.phase & 16) ? 15 : 0);

				case 3: // Noise: Linear feedback shift register
					if(!ch.hold) ch.hold = 1;
					ch.hold = (ch.hold >> 1)
						  | (((ch.hold ^ (ch.hold >> (ch.reg.NoiseType ? 6 : 1))) & 1) << 14);
					return S = (ch.hold & 1) ? 0 : volume;

				case 4: // Delta modulation channel (DMC)
					// hold = 8 bit value, phase = number of bits buffered
					if(ch.phase == 0) // Nothing in sample buffer?
					{
						if(!ch.length_counter && ch.reg.LoopEnabled) // Loop?
						{
							ch.length_counter = ch.reg.PCMlength*16 + 1;
							ch.address        = (ch.reg.reg0 | 0x300) << 6;
						}
						if(ch.length_counter > 0) // Load next 8 bits if available
						{
							// Note: Re-entrant! But not recursive, because even
							// the shortest wave length is greater than the read time.
							// TODO: proper clock
							if(ch.reg.WaveLength>20)
								for(unsigned t=0; t<3; ++t) CPU::RB(u16(ch.address) | 0x8000); // timing
							ch.hold  = CPU::RB(u16(ch.address++) | 0x8000); // Fetch byte
							ch.phase = 8;
							--ch.length_counter;
						}
						else // Otherwise, disable channel or issue IRQ
							ChannelsEnabled[4] = ch.reg.IRQenable && (CPU::intr = DMC_IRQ = true);
					}
					if(ch.phase != 0) // Update the signal if sample buffer nonempty
					{
						int v = ch.linear_counter;
						if(ch.hold & (0x80 >> --ch.phase)) v += 2; else v -= 2;
						if(v >= 0 && v <= 0x7F) ch.linear_counter = v;
					}
					return S = ch.linear_counter;
			}
		}
	} channels[5] = { };

	struct { short lo, hi; } hz240counter = { 0,0 };

	void Write(u8 index, u8 value)
	{
		channel& ch = channels[(index/4) % 5];
		switch(index<0x10 ? index%4 : index)
		{
			case 0: if(ch.reg.LinearCounterDisable) ch.linear_counter=value&0x7F; ch.reg.reg0 = value; break;
			case 1: ch.reg.reg1 = value; ch.sweep_delay = ch.reg.SweepRate; break;
			case 2: ch.reg.reg2 = value; break;
			case 3:
				ch.reg.reg3 = value;
				if(ChannelsEnabled[index/4])
					ch.length_counter = LengthCounters[ch.reg.LengthCounterInit];
				ch.linear_counter = ch.reg.LinearCounterInit;
				ch.env_delay      = ch.reg.EnvDecayRate;
				ch.envelope       = 15;
				if(index < 8) ch.phase = 0;
				break;
			case 0x10: ch.reg.reg3 = value; ch.reg.WaveLength = DMCperiods[value&0x0F]; break;
			case 0x12: ch.reg.reg0 = value; ch.address = (ch.reg.reg0 | 0x300) << 6; break;
			case 0x13: ch.reg.reg1 = value; ch.length_counter = ch.reg.PCMlength*16 + 1; break; // sample length
			case 0x11: ch.linear_counter = value & 0x7F; break; // dac value
			case 0x15:
				for(unsigned c=0; c<5; ++c)
					ChannelsEnabled[c] = value & (1 << c);
				for(unsigned c=0; c<5; ++c)
					if(!ChannelsEnabled[c])
						channels[c].length_counter = 0;
					else if(c == 4 && channels[c].length_counter == 0)
						channels[c].length_counter = ch.reg.PCMlength*16 + 1;
				break;
			case 0x17:
				IRQdisable       = value & 0x40;
				FiveCycleDivider = value & 0x80;
				hz240counter     = { 0,0 };
				if(IRQdisable) PeriodicIRQ = DMC_IRQ = false;
		}
	}
	u8 Read()
	{
		u8 res = 0;
		for(unsigned c=0; c<5; ++c) res |= (channels[c].length_counter ? 1 << c : 0);
		if(PeriodicIRQ) res |= 0x40; PeriodicIRQ = false;
		if(DMC_IRQ)     res |= 0x80; DMC_IRQ     = false;
		CPU::intr = false;
		return res;
	}

	void tick() // Invoked at CPU's rate.
	{
		// Divide CPU clock by 7457.5 to get a 240 Hz, which controls certain events.
		if((hz240counter.lo += 2) >= 14915)
		{
			hz240counter.lo -= 14915;
			if(++hz240counter.hi >= 4+FiveCycleDivider) hz240counter.hi = 0;

			// 60 Hz interval: IRQ. IRQ is not invoked in five-cycle mode (48 Hz).
			if(!IRQdisable && !FiveCycleDivider && hz240counter.hi==0)
				CPU::intr = PeriodicIRQ = true;

			// Some events are invoked at 96 Hz or 120 Hz rate. Others, 192 Hz or 240 Hz.
			bool HalfTick = (hz240counter.hi&5)==1, FullTick = hz240counter.hi < 4;
			for(unsigned c=0; c<4; ++c)
			{
				channel& ch = channels[c];
				int wl = ch.reg.WaveLength;

				// Length tick (all channels except DMC, but different disable bit for triangle wave)
				if(HalfTick && ch.length_counter
				&& !(c==2 ? ch.reg.LinearCounterDisable : ch.reg.LengthCounterDisable))
					ch.length_counter -= 1;

				// Sweep tick (square waves only)
				if(HalfTick && c < 2 && count(ch.sweep_delay, ch.reg.SweepRate))
					if(wl >= 8 && ch.reg.SweepEnable && ch.reg.SweepShift)
					{
						int s = wl >> ch.reg.SweepShift, d[4] = {s, s, ~s, -s};
						wl += d[ch.reg.SweepDecrease*2 + c];
						if(wl < 0x800) ch.reg.WaveLength = wl;
					}

				// Linear tick (triangle wave only)
				if(FullTick && c == 2)
					ch.linear_counter = ch.reg.LinearCounterDisable
					? ch.reg.LinearCounterInit
					: (ch.linear_counter > 0 ? ch.linear_counter - 1 : 0);

				// Envelope tick (square and noise channels)
				if(FullTick && c != 2 && count(ch.env_delay, ch.reg.EnvDecayRate))
					if(ch.envelope > 0 || ch.reg.EnvDecayLoopEnable)
						ch.envelope = (ch.envelope-1) & 15;
			}
		}

		// Mix the audio: Get the momentary sample from each channel and mix them.
		#define s(c) channels[c].tick<c==1 ? 0 : c>()
		auto v = [](float m,float n, float d) { return n!=0.f ? m/n : d; };
		short sample = 30000 *
		  (v(95.88f,  (100.f + v(8128.f, s(0) + s(1), -100.f)), 0.f)
		+  v(159.79f, (100.f + v(1.0, s(2)/8227.f + s(3)/12241.f + s(4)/22638.f, -100.f)), 0.f)
		  - 0.5f
		  );
		#undef s

#if 0
		// I cheat here: I did not bother to learn how to use SDL mixer, let alone use it in <5 lines of code,
		// so I simply use a combination of external programs for outputting the audio.
		// Hooray for Unix principles! A/V sync will be ensured in post-process.
		//return; // Disable sound because already device is in use
		static FILE* fp = popen("resample mr1789800 r48000 | aplay -fdat 2>/dev/null", "w");
		fputc(sample, fp);
		fputc(sample/256, fp);
#endif
	}
}

namespace CPU
{
	void tick()
	{
		// PPU clock: 3 times the CPU rate
		for(unsigned n=0; n<3; ++n) PPU::tick();
		// APU clock: 1 times the CPU rate
		for(unsigned n=0; n<1; ++n) APU::tick();
	}

	template<bool write> u8 MemAccess(u16 addr, u8 v)
	{
		// Memory writes are turned into reads while reset is being signalled
		if(reset && write) return MemAccess<0>(addr);

		tick();
		// Map the memory from CPU's viewpoint.
		/**/ if(addr < 0x2000) { u8& r = RAM[addr & 0x7FF]; if(!write)return r; r=v; }
		else if(addr < 0x4000) return PPU::Access(addr&7, v, write);
		else if(addr < 0x4018)
			switch(addr & 0x1F)
			{
				case 0x14: // OAM DMA: Copy 256 bytes from RAM into PPU's sprite memory
					if(write) for(unsigned b=0; b<256; ++b) WB(0x2004, RB((v&7)*0x0100+b));
					return 0;
				case 0x15: if(!write) return APU::Read();    APU::Write(0x15,v); break;
				case 0x16: if(!write) return IO::JoyRead(0); IO::JoyStrobe(v); break;
				case 0x17: if(!write) return IO::JoyRead(1); // write:passthru
				default: if(!write) break;
						 APU::Write(addr&0x1F, v);
			}
		else return GamePak::Access(addr, v, write);
		return 0;
	}

	// CPU registers:
	u16 PC=0xC000;
	u8 A=0,X=0,Y=0,S=0;
	union /* Status flags: */
	{
		u8 raw;
		RegBit<0> C; // carry
		RegBit<1> Z; // zero
		RegBit<2> I; // interrupt enable/disable
		RegBit<3> D; // decimal mode (unsupported on NES, but flag exists)
		// 4,5 (0x10,0x20) don't exist
		RegBit<6> V; // overflow
		RegBit<7> N; // negative
	} P;

	u16 wrap(u16 oldaddr, u16 newaddr)  { return (oldaddr & 0xFF00) + u8(newaddr); }
	void Misfire(u16 old, u16 addr) { u16 q = wrap(old, addr); if(q != addr) RB(q); }
	u8   Pop()        { return RB(0x100 | u8(++S)); }
	void Push(u8 v)   { WB(0x100 | u8(S--), v); }

	template<u16 op> // Execute a single CPU instruction, defined by opcode "op".
	void Ins()       // With template magic, the compiler will literally synthesize >256 different functions.
	{
		// Note: op 0x100 means "NMI", 0x101 means "Reset", 0x102 means "IRQ". They are implemented in terms of "BRK".
		// User is responsible for ensuring that WB() will not store into memory while Reset is being processed.
		unsigned addr=0, d=0, t=0xFF, c=0, sb=0, pbits = op<0x100 ? 0x30 : 0x20;

		// Define the opcode decoding matrix, which decides which micro-operations constitute
		// any particular opcode. (Note: The PLA of 6502 works on a slightly different principle.)
		enum { o8 = op/8, o8m = 1 << (op%8) };
		// Fetch op'th item from a bitstring encoded in a data-specific variant of base64,
		// where each character transmits 8 bits of information rather than 6.
		// This peculiar encoding was chosen to reduce the source code size.
		// Enum temporaries are used in order to ensure compile-time evaluation.
		#define t(s,code) { enum { \
			i=o8m & (s[o8]>90 ? (130+" (),-089<>?BCFGHJLSVWZ[^hlmnxy|}"[s[o8]-94]) \
							  : (s[o8]-" (("[s[o8]/39])) }; if(i) { code; } }

		/* Decode address operand */
		t("                                !", addr = 0xFFFA) // NMI vector location
		t("                                *", addr = 0xFFFC) // Reset vector location
		t("!                               ,", addr = 0xFFFE) // Interrupt vector location
		t("zy}z{y}zzy}zzy}zzy}zzy}zzy}zzy}z ", addr = RB(PC++))
		t("2 yy2 yy2 yy2 yy2 XX2 XX2 yy2 yy ", d = X) // register index
		t("  62  62  62  62  om  om  62  62 ", d = Y)
		t("2 y 2 y 2 y 2 y 2 y 2 y 2 y 2 y  ", addr=u8(addr+d); d=0; tick())              // add zeropage-index
		t(" y z!y z y z y z y z y z y z y z ", addr=u8(addr);   addr+=256*RB(PC++))       // absolute address
		t("3 6 2 6 2 6 286 2 6 2 6 2 6 2 6 /", addr=RB(c=addr); addr+=256*RB(wrap(c,c+1)))// indirect w/ page wrap
		t("  *Z  *Z  *Z  *Z      6z  *Z  *Z ", Misfire(addr, addr+d)) // abs. load: extra misread when cross-page
		t("  4k  4k  4k  4k  6z      4k  4k ", RB(wrap(addr, addr+d)))// abs. store: always issue a misread
		/* Load source operand */
		t("aa__ff__ab__,4  ____ -  ____     ", t &= A) // Many operations take A or X as operand. Some try in
		t("                knnn     4  99   ", t &= X) // error to take both; the outcome is an AND operation.
		t("                9989    99       ", t &= Y) // sty,dey,iny,tya,cpy
		t("                       4         ", t &= S) // tsx, las
		t("!!!!  !!  !!  !!  !   !!  !!  !!/", t &= P.raw|pbits; c = t)// php, flag test/set/clear, interrupts
		t("_^__dc___^__            ed__98   ", c = t; t = 0xFF)        // save as second operand
		t("vuwvzywvvuwvvuwv    zy|zzywvzywv ", t &= RB(addr+d)) // memory operand
		t(",2  ,2  ,2  ,2  -2  -2  -2  -2   ", t &= RB(PC++))   // immediate operand
		/* Operations that mogrify memory operands directly */
		t("    88                           ", P.V = t & 0x40; P.N = t & 0x80) // bit
		t("    nink    nnnk                 ", sb = P.C)       // rol,rla, ror,rra,arr
		t("nnnknnnk     0                   ", P.C = t & 0x80) // rol,rla, asl,slo,[arr,anc]
		t("        nnnknink                 ", P.C = t & 0x01) // lsr,sre, ror,rra,asr
		t("ninknink                         ", t = (t << 1) | (sb * 0x01))
		t("        nnnknnnk                 ", t = (t >> 1) | (sb * 0x80))
		t("                 !      kink     ", t = u8(t - 1))  // dec,dex,dey,dcp
		t("                         !  khnk ", t = u8(t + 1))  // inc,inx,iny,isb
		/* Store modified value (memory) */
		t("kgnkkgnkkgnkkgnkzy|J    kgnkkgnk ", WB(addr+d, t))
		t("                   q             ", WB(wrap(addr, addr+d), t &= ((addr+d) >> 8))) // [shx,shy,shs,sha?]
		/* Some operations used up one clock cycle that we did not account for yet */
		t("rpstljstqjstrjst - - - -kjstkjst/", tick()) // nop,flag ops,inc,dec,shifts,stack,transregister,interrupts
		/* Stack operations and unconditional jumps */
		t("     !  !    !                   ", tick(); t = Pop())                        // pla,plp,rti
		t("        !   !                    ", RB(PC++); PC = Pop(); PC |= (Pop() << 8)) // rti,rts
		t("            !                    ", RB(PC++))  // rts
		t("!   !                           /", d=PC+(op?-1:1); Push(d>>8); Push(d))      // jsr, interrupts
		t("!   !    8   8                  /", PC = addr) // jmp, jsr, interrupts
		t("!!       !                      /", Push(t))   // pha, php, interrupts
		/* Bitmasks */
		t("! !!  !!  !!  !!  !   !!  !!  !!/", t = 1)
		t("  !   !                   !!  !! ", t <<= 1)
		t("! !   !   !!  !!       !   !   !/", t <<= 2)
		t("  !   !   !   !        !         ", t <<= 4)
		t("   !       !           !   !____ ", t = u8(~t)) // sbc, isb,      clear flag
		t("`^__   !       !               !/", t = c | t)  // ora, slo,      set flag
		t("  !!dc`_  !!  !   !   !!  !!  !  ", t = c & t)  // and, bit, rla, clear/test flag
		t("        _^__                     ", t = c ^ t)  // eor, sre
		/* Conditional branches */
		t("      !       !       !       !  ", if(t)  { tick(); Misfire(PC, addr = s8(addr) + PC); PC=addr; })
		t("  !       !       !       !      ", if(!t) { tick(); Misfire(PC, addr = s8(addr) + PC); PC=addr; })
		/* Addition and subtraction */
		t("            _^__            ____ ", c = t; t += A + P.C; P.V = (c^t) & (A^t) & 0x80; P.C = t & 0x100)
		t("                        ed__98   ", t = c - t; P.C = ~t & 0x100) // cmp,cpx,cpy, dcp, sbx
		/* Store modified value (register) */
		t("aa__aa__aa__ab__ 4 !____    ____ ", A = t)
		t("                    nnnn 4   !   ", X = t) // ldx, dex, tax, inx, tsx,lax,las,sbx
		t("                 !  9988 !       ", Y = t) // ldy, dey, tay, iny
		t("                   4   0         ", S = t) // txs, las, shs
		t("!  ! ! !!  !   !       !   !   !/", P.raw = t & ~0x30) // plp, rti, flag set/clear
		/* Generic status flag updates */
		t("wwwvwwwvwwwvwxwv 5 !}}||{}wv{{wv ", P.N = t & 0x80)
		t("wwwv||wvwwwvwxwv 5 !}}||{}wv{{wv ", P.Z = u8(t) == 0)
		t("             0                   ", P.V = (((t >> 5)+1)&2))         // [arr]
		/* All implemented opcodes are cycle-accurate and memory-access-accurate.
		 * [] means that this particular separate rule exists only to provide the indicated unofficial opcode(s).
		 */
	}

	void Op()
	{
		/* Check the state of NMI flag */
		bool nmi_now = nmi;

		unsigned op = RB(PC++);

		if(reset)                              { op=0x101; }
		else if(nmi_now && !nmi_edge_detected) { op=0x100; nmi_edge_detected = true; }
		else if(intr && !P.I)                  { op=0x102; }
		if(!nmi_now) nmi_edge_detected=false;

		// Define function pointers for each opcode (00..FF) and each interrupt (100,101,102)
		#define c(n) Ins<0x##n>,Ins<0x##n+1>,
		#define o(n) c(n)c(n+2)c(n+4)c(n+6)
		static void(*const i[0x108])() =
		{
			o(00)o(08)o(10)o(18)o(20)o(28)o(30)o(38)
			o(40)o(48)o(50)o(58)o(60)o(68)o(70)o(78)
			o(80)o(88)o(90)o(98)o(A0)o(A8)o(B0)o(B8)
			o(C0)o(C8)o(D0)o(D8)o(E0)o(E8)o(F0)o(F8) o(100)
		};
		#undef o
		#undef c
		i[op]();

		reset = false;
	}
}

int main(int/*argc*/, char** argv)
{
#if 0
	// Open the ROM file specified on commandline
	FILE* fp = fopen(argv[1], "rb");
#endif
	FILE* fp = fopen(romFileName, "rb");
	inputfn = argv[2];

	// Read the ROM file header
	assert(fgetc(fp)=='N' && fgetc(fp)=='E' && fgetc(fp)=='S' && fgetc(fp)=='\32');
	u8 rom16count = fgetc(fp);
	u8 vrom8count = fgetc(fp);
	u8 ctrlbyte   = fgetc(fp);
	u8 mappernum  = fgetc(fp) | (ctrlbyte>>4);
	fgetc(fp);fgetc(fp);fgetc(fp);fgetc(fp);fgetc(fp);fgetc(fp);fgetc(fp);fgetc(fp);
	if(mappernum >= 0x40) mappernum &= 15;
	GamePak::mappernum = mappernum;

	// Read the ROM data
	if(rom16count) GamePak::ROM.resize(rom16count * 0x4000);
	if(vrom8count) GamePak::VRAM.resize(vrom8count * 0x2000);
	fread(&GamePak::ROM[0], rom16count, 0x4000, fp);
	fread(&GamePak::VRAM[0], vrom8count, 0x2000, fp);

	fclose(fp);
	printf("%u * 16kB ROM, %u * 8kB VROM, mapper %u, ctrlbyte %02X\n", rom16count, vrom8count, mappernum, ctrlbyte);

	// Start emulation
	GamePak::Init();
	IO::Init();
	PPU::reg.value = 0;

	// Pre-initialize RAM the same way as FCEUX does, to improve TAS sync.
	for(unsigned a=0; a<0x800; ++a)
		CPU::RAM[a] = (a&4) ? 0xFF : 0x00;

	printf("vectors:\nnmi:%04x\nreset:%04x\nirq:%04x\n",
		(u32)CPU::RB(0xfffa) + ((u32)CPU::RB(0xfffb) << 8),
		(u32)CPU::RB(0xfffc) + ((u32)CPU::RB(0xfffd) << 8),
		(u32)CPU::RB(0xfffe) + ((u32)CPU::RB(0xffff) << 8)
	);
	SMB_Init();

	// Run the CPU until the program is killed.
	for(;;)
	{
		// Check if we have to redirect the current program counter address to C++ code
		if( SMB_TranslationTable[CPU::PC] != nullptr )
		{
			// Call the translated function
			SMB_TranslationTable[CPU::PC]();

			// Execute an RTS instruction
			// Pull the top two bytes off the stack
			u16 nextInstruction = (u16)CPU::Pop() + ((u16)CPU::Pop() << 8) + 1;

			// Set the PC to that plus one
			CPU::PC = nextInstruction;
			//printf("Returning to %04x\n", (u32)nextInstruction);
		}
		else
		{
			//printf("%04x\n", (u32)CPU::PC);
			CPU::Op();
		}
	}

	return 0;
}

// Implementation of nesemu1.hh

byte readMemory( int address )
{
	return CPU::RB(address);
}

void writeMemory( int address, byte value )
{
	CPU::WB(address, value);
}

byte readA()
{
	return CPU::A;
}

byte readX()
{
	return CPU::X;
}

byte readY()
{
	return CPU::Y;
}

void writeA( byte value )
{
	CPU::A = value;
}

void writeX( byte value )
{
	CPU::X = value;
}

void writeY( byte value )
{
	CPU::Y = value;
}
