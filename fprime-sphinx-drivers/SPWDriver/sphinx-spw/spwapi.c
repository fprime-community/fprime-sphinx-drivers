/*****************************************************************************/
/*   This file is a part of the GRLIB VHDL IP LIBRARY */
/*   Copyright (C) 2004 GAISLER RESEARCH */

/*   This program is free software; you can redistribute it and/or modify */
/*   it under the terms of the GNU General Public License as published by */
/*   the Free Software Foundation; either version 2 of the License, or */
/*   (at your option) any later version. */

/*   See the file COPYING for the full details of the license. */
/*****************************************************************************/

#include <stdlib.h>
#include "spwapi.h"

static inline int loadmem(int addr)
{
  volatile int* ptr = (volatile int*)(long)addr;
  return *ptr;
}

static int ptrToInt(volatile const void* ptr)
{
  long tmp = (long)ptr;
  int ret = (int)tmp;
  return ret;
}

int spw_setparam(int nodeaddr, int clkdiv, int destkey,
                 int timetxen, int timerxen, int spwadr, 
                 int khz, struct spwvars *spw, int port,
                 int clkdivs)
{
        if ((nodeaddr < 0) || (nodeaddr > 255)) {
                return 1;
        }
        if ((clkdiv < 0) || (clkdiv > 255)) {
                return 1;
        }
        if ((clkdivs < 0) || (clkdivs > 255)) {
                return 1;
        }
        if ((destkey < 0) || (destkey > 255)) {
                return 1;
        }
        if ((timetxen < 0) || (timetxen > 1)) {
                return 1;
        }
        if ((timerxen < 0) || (timerxen > 1)) {
                return 1;
        }
        spw->timetxen = timetxen;
        spw->timerxen = timerxen;
        spw->destkey = destkey;
        spw->nodeaddr = nodeaddr;
        spw->clkdiv = clkdiv;
        spw->clkdivs = clkdivs;
        spw->khz = khz;
	spw->port = port;
        spw->regs = (struct spwregs *) (long)spwadr;
        return 0;
}

int spw_setparam_dma(int dmachan, int addr, int mask, int nospill,
                     int rxmaxlen, int txdescpnt, int rxdescpnt,
                     struct spwvars *spw)
{
        if ((addr < 0) || (addr > 255)) {
                return 1;
        }
        if ((mask < 0) || (mask > 255)) {
                return 1;
        }
        if ((rxmaxlen < 0) || (rxmaxlen > 33554432)) {
                return 1;
        }
        if ((nospill < 0) || (nospill > 1)) {
                return 1;
        }
        spw->dma[dmachan].nospill = nospill;
        spw->dma[dmachan].addr = addr;
        spw->dma[dmachan].mask = mask;
        spw->dma[dmachan].rxmaxlen = rxmaxlen;
        spw->dma[dmachan].txd = (struct txdescriptor *)(long)txdescpnt;
        spw->dma[dmachan].rxd = (struct rxdescriptor *)(long)rxdescpnt;
        return 0;
}


int spw_init(struct spwvars *spw)
{
        int i;
        int tmp;
        /*determine grspw version by checking if timer and disconnect register exists */
        spw->regs->timer = 0xFFFFFF;
        tmp = loadmem(ptrToInt(&(spw->regs->timer)));
        spw->ver = 0;
        // does some attempted write, if the write DIDN'T WORK, then version up
        if (!tmp) 
                spw->ver = 1;
        tmp = loadmem(ptrToInt(&(spw->regs->ctrl)));
        // loads vars from readonly values of ctrl
        spw->rmap = (tmp >> 31) & 1;
        spw->rxunaligned = (tmp >> 30) & 1;
        spw->rmapcrc = (tmp >> 29) & 1;
        // apparently there is a concept of multiple dmachans per core - but not for us (should be 1)
        spw->dmachan = ((tmp >> 27) & 3) + 1;
        // some unknown legacy thing
        spw->pnp = ((tmp >> 18) & 3);
        // some unknown legacy thing
        if ((tmp >> 24) & 1) {
            tmp = loadmem(ptrToInt(&(spw->regs->intdist.ctrl)));
            spw->intdist = ((tmp >> 13) & 7);        
        } else {
            spw->intdist = 0;
        }
        tmp = loadmem(ptrToInt(&(spw->regs->status)));
        // some unknown legacy thing (we should have exactly 64 txdesc, 128 rxdesc)
        spw->ntxdesc = 64 << ((tmp >> 24) & 3);
        spw->nrxdesc = 128 << ((tmp >> 26) & 3);
        /*reset core */
        // don't we already do this in spw_reset??? so you reset before init, and again during init?
        spw->regs->ctrl = (1 << 6); 
        tmp = loadmem(ptrToInt(&(spw->regs->ctrl)));
        // when RS is 1, that means it's "resetting"???
        while ((tmp >> 6) & 1) {
                tmp = loadmem(ptrToInt(&(spw->regs->ctrl)));
        }
        spw->regs->nodeaddr = spw->nodeaddr; /*set node address*/
        spw->regs->clkdiv = spw->clkdiv | (spw->clkdivs << 8);  /* set clock divisor */

        // basically, i < 1
        for(i = 0; i < spw->dmachan; i++) {
                spw->regs->dma[i].rxmaxlen = spw->dma[i].rxmaxlen; /*set rx maxlength*/
                // failed to write it for some reason?
                if (loadmem(ptrToInt(&(spw->regs->dma[i].rxmaxlen))) != spw->dma[i].rxmaxlen) {
                        return 1;
                }
        }
        // legacy (timer dealt with in hardware now)
        if (spw->khz) 
                spw->regs->timer = ((spw->khz*64)/10000) | ((((spw->khz*850)/1000000)-3) << 12);
        if (spw->rmap == 1) {
                spw->regs->destkey = spw->destkey;
        }
        // i < 1
        for(i = 0; i < spw->dmachan; i++) {
          // clears flags, aborts TX
          spw->regs->dma[i].ctrl = 0x00CC01E0; /*clear status, set ctrl for dma chan*/
          // the ENTIRE dma ctrl register should end up as zero? (i guess it's possible)
          if (loadmem(ptrToInt(&(spw->regs->dma[i].ctrl))) != 0) {
                  return 2;
          }
          ///* set tx descriptor pointer*/
          //// allocates 2x the memory and picks the slot that is aligned to sz (1024)
          //if ((spw->dma[i].txd = (struct txdescriptor *)almalloc(spw->ntxdesc*16)) == NULL) {
          /* verify alignment */
          if ((ptrToInt((spw->dma[i].txd)) & ((spw->ntxdesc * 16)-1)) != 0) {
                  return 3;
          }
          // txpnt is the next descriptor to activate
          spw->dma[i].txpnt = 0;
          // txchkpnt is the descriptor to check status of (should always be <= txpnt)
          spw->dma[i].txchkpnt = 0;
          // set table address
          spw->regs->dma[i].txdesc = ptrToInt(spw->dma[i].txd);
          ///* set rx descriptor pointer*/
          //if (( spw->dma[i].rxd = (struct rxdescriptor *)almalloc(spw->nrxdesc*8)) == NULL) {
          /* verify alignment */
          if ((ptrToInt((spw->dma[i].rxd)) & ((spw->nrxdesc * 8)-1)) != 0) {
                  return 4;
          }
          spw->dma[i].rxpnt = 0;
          spw->dma[i].rxchkpnt = 0;
          spw->regs->dma[i].rxdesc = ptrToInt(spw->dma[i].rxd);
        }
        spw->regs->status = 0xFFF; /*clear status*/
        // start link. no idea what port is for
        spw->regs->ctrl = 0x2 | (spw->timetxen << 10) | (spw->timerxen << 11) | (spw->port << 21); /*set ctrl*/
        for(i = 0; i < spw->dmachan; i++) {
            spw->regs->dma[i].ctrl = loadmem(ptrToInt(&(spw->regs->dma[i].ctrl))) | (spw->dma[i].nospill << 12);
        }
        return 0;
}

int wait_running(struct spwvars *spw) 
{
        int i;
        int j;
        
        j = 0;
        while (((loadmem(ptrToInt(&(spw->regs->status))) >> 21) & 7) != 5) {
                if (j > 1000) {
                        return 1;
                }
                for(i = 0; i < 1000; i++) {}
		j++;
        }
        return 0;
}

int set_txdesc(int dmachan, int pnt, struct spwvars *spw) 
{
        spw->regs->dma[dmachan].txdesc = pnt;
        spw->dma[dmachan].txpnt = 0;
        spw->dma[dmachan].txchkpnt = 0;
        if (loadmem(ptrToInt(&(spw->regs->dma[dmachan].txdesc))) != pnt) {
                return 1;
        }
        return 0;
}

int set_rxdesc(int dmachan, int pnt, struct spwvars *spw) 
{
        spw->regs->dma[dmachan].rxdesc = pnt;
        spw->dma[dmachan].rxpnt = 0;
        spw->dma[dmachan].rxchkpnt = 0;
        if (loadmem(ptrToInt(&(spw->regs->dma[dmachan].rxdesc))) != pnt) {
                return 1;
        }
        return 0;
}

void spw_disable(struct spwvars *spw) 
{
        spw->regs->ctrl = loadmem(ptrToInt(&(spw->regs->ctrl))) | 0x1;
}

void spw_enable(struct spwvars *spw) 
{
    spw->regs->ctrl = loadmem(ptrToInt(&(spw->regs->ctrl))) & ~0x1;
}

void spw_start(struct spwvars *spw) 
{
    spw->regs->ctrl = loadmem(ptrToInt(&(spw->regs->ctrl))) | 0x2;
}

void spw_stop(struct spwvars *spw) 
{
        spw->regs->ctrl = loadmem(ptrToInt(&(spw->regs->ctrl))) & ~0x2;
}

int spw_setclockdiv(struct spwvars *spw) 
{
        if ( (spw->clkdiv < 0) || (spw->clkdiv > 255) ) {
                return 1;
        } else {
                spw->regs->clkdiv = spw->clkdiv;
                return 0;
        }
}

int spw_set_nodeadr(struct spwvars *spw) 
{
        if ( (spw->nodeaddr < 0) || (spw->nodeaddr > 255) || 
             (spw->mask < 0) || (spw->mask > 255) ) {
                return 1;
        } else {
                spw->regs->nodeaddr = (spw->nodeaddr & 0xFF) | ((spw->mask & 0xFF) << 8);
                return 0;
        }
}

int spw_set_chanadr(int dmachan, struct spwvars *spw) 
{
        if ( (spw->dma[dmachan].addr < 0) || (spw->dma[dmachan].addr > 255) || 
             (spw->dma[dmachan].mask < 0) || (spw->dma[dmachan].mask > 255) ) {
                return 1;
        } else {
                spw->regs->dma[dmachan].addr = (spw->dma[dmachan].addr & 0xFF) | ((spw->dma[dmachan].mask & 0xFF) << 8);
                return 0;
        }
}

int spw_set_rxmaxlength(int dmachan, struct spwvars *spw) 
{
        if ((spw->dma[dmachan].rxmaxlen < 4) || (spw->dma[dmachan].rxmaxlen > 33554431)) {
                return 1;
        } else {
                spw->regs->dma[dmachan].rxmaxlen = spw->dma[dmachan].rxmaxlen;
                return 0;
        }
}

int spw_tx(int dmachan, int hcrc, int dcrc, int skipcrcsize, int hsize, char *hbuf, int dsize, char *dbuf, struct spwvars *spw) 
{
        if ((dsize < 0) || (dsize > 16777215)) {
                return 6;
        }
        if ((hsize < 0) || (hsize > 255)) {
                return 5;
        }
        if ((dbuf == NULL) || (hbuf == NULL)) {
                return 4;
        }
        // hw crc enabled by hcrc/dcrc == 1, requires rmap or rmapcrc
        if ( (((hcrc == 1) || (dcrc == 1)) && ((spw->rmapcrc | spw->rmap) == 0)) || (hcrc < 0) || (hcrc > 1) || (dcrc < 0) || (dcrc > 1)) {
                return 3;
        } 
        if ((skipcrcsize < 0) || (skipcrcsize > 15) ) {
                return 2;
        }
        // pointed tx descriptor is still EN (i.e. entire table is full?)
        if ((loadmem(ptrToInt(&(spw->dma[dmachan].txd[spw->dma[dmachan].txpnt].ctrl))) >> 12) & 1) {
                return 1;
        }
        spw->dma[dmachan].txd[spw->dma[dmachan].txpnt].haddr = ptrToInt(hbuf);
        spw->dma[dmachan].txd[spw->dma[dmachan].txpnt].dlen = dsize;
        spw->dma[dmachan].txd[spw->dma[dmachan].txpnt].daddr = ptrToInt(dbuf);
        if (spw->dma[dmachan].txpnt == (spw->ntxdesc-1)) {
                spw->dma[dmachan].txd[spw->dma[dmachan].txpnt].ctrl = 0x3000 | hsize | (hcrc << 16) | (dcrc << 17) | (skipcrcsize << 8);
                spw->dma[dmachan].txpnt = 0;
        } else {
                spw->dma[dmachan].txd[spw->dma[dmachan].txpnt].ctrl = 0x1000 | hsize | (hcrc << 16) | (dcrc << 17) | (skipcrcsize << 8);
                spw->dma[dmachan].txpnt++;
        }
        
        spw->regs->dma[dmachan].ctrl = (loadmem(ptrToInt(&(spw->regs->dma[dmachan].ctrl))) & 0xF8C6FAAA) | 1;
        
        return 0;
}

int spw_rx(int dmachan, char *buf, struct spwvars *spw) 
{
        if (((loadmem(ptrToInt(&(spw->dma[dmachan].rxd[spw->dma[dmachan].rxpnt].ctrl))) >> 25) & 1)) {
                return 1;
        }
        spw->dma[dmachan].rxd[spw->dma[dmachan].rxpnt].daddr = ptrToInt(buf);
        if (spw->dma[dmachan].rxpnt == (spw->nrxdesc-1)) {
                spw->dma[dmachan].rxd[spw->dma[dmachan].rxpnt].ctrl = 0x6000000;
                spw->dma[dmachan].rxpnt = 0;
        } else {
                spw->dma[dmachan].rxd[spw->dma[dmachan].rxpnt].ctrl = 0x2000000;
                spw->dma[dmachan].rxpnt++;
        }
        spw->regs->dma[dmachan].ctrl = ((loadmem(ptrToInt(&(spw->regs->dma[dmachan].ctrl))) & 0xF8C8F955) | 2) | (1 << 11);
        return 0;
}

int spw_checkrx(int dmachan, int *size, struct rxstatus *rxs, struct spwvars *spw) 
{
  int tmp;

  // load rx desc from chk pointer
  tmp = loadmem(ptrToInt(&(spw->dma[dmachan].rxd[spw->dma[dmachan].rxchkpnt].ctrl)));

  // no longer EN
  if (!((tmp >> 25) & 1)) {

    // save size from packet length
    *size = tmp & 0x1FFFFFF;

    // collect all of the statuses
    rxs->truncated = (tmp >> 31) & 1;
    rxs->dcrcerr = (tmp >> 30) & 1;
    rxs->hcrcerr = (tmp >> 29) & 1;
    rxs->eep = (tmp >> 28) & 1;

    // increment chk ptr
    if (spw->dma[dmachan].rxchkpnt == (spw->nrxdesc-1)) {
      spw->dma[dmachan].rxchkpnt = 0;
    } else {
      spw->dma[dmachan].rxchkpnt++;
    }

    return 1;

  } else {
    return 0;
  }
}

int spw_checktx(int dmachan, struct spwvars *spw)
{
    int tmp;

    // ctrl of descriptor pointed by chk pointer (not cur pointer)
    tmp = loadmem(ptrToInt(&(spw->dma[dmachan].txd[spw->dma[dmachan].txchkpnt].ctrl)));

    // if no longer EN
    if (!((tmp >> 12) & 1)) {

      // increment chk pointer
      if (spw->dma[dmachan].txchkpnt == (spw->ntxdesc-1)) {
        spw->dma[dmachan].txchkpnt = 0;
      } else {
        spw->dma[dmachan].txchkpnt++;
      }

      // link error
      if ((tmp >> 15) & 1) {
        return 2;
      } else {
        return 1;
      }

    } else {
      return 0;
    }
}

void send_time(struct spwvars *spw)
{
        int i;
        while( ((loadmem(ptrToInt(&(spw->regs->ctrl))) >> 4) & 1)) {
                for(i = 0; i < 16; i++) {}
        }
        spw->regs->ctrl = loadmem(ptrToInt(&(spw->regs->ctrl))) | (1 << 4);
}

int send_time_exp(int ctrl, int time, struct spwvars *spw)
{
        int i;
        int code;
        if ((time < 0) || (time > 63)) {
                //printf("Illegal time-value\n");
                return -1;
        }
        if (time == 0) {
                time = 63;
        } else {
                time = time - 1;
        }
        code = ((ctrl << 6) & 0xC0) | time;
        
        while( ((loadmem(ptrToInt(&(spw->regs->ctrl))) >> 4) & 1)) {
                for(i = 0; i < 16; i++) {}
        }
        spw->regs->timereg = (loadmem(ptrToInt(&(spw->regs->timereg))) & 0xFFFFFF00) | (0xFF & code);
        spw->regs->ctrl = loadmem(ptrToInt(&(spw->regs->ctrl))) | (1 << 4);
        return 0;
}

int check_time(struct spwvars *spw) 
{
        int tmp = loadmem(ptrToInt(&(spw->regs->status))) & 1;
        if (tmp) {
                spw->regs->status = loadmem(ptrToInt(&(spw->regs->status))) | 1;
        }
        return tmp;
}

int get_time(struct spwvars *spw) 
{
        return (loadmem(ptrToInt(&(spw->regs->timereg))) & 0x3F );
}

int get_time_ctrl(struct spwvars *spw) 
{
        return ((loadmem(ptrToInt(&(spw->regs->timereg))) >> 6) & 0x3);
}

void spw_reset(struct spwvars *spw) 
{
  spw->regs->ctrl = loadmem(ptrToInt(&(spw->regs->ctrl))) | (1 << 6);
}
        
void spw_rmapen(struct spwvars *spw) 
{
  spw->regs->ctrl = loadmem(ptrToInt(&(spw->regs->ctrl))) | (1 << 16);
}

void spw_rmapdis(struct spwvars *spw) 
{
    spw->regs->ctrl = loadmem(ptrToInt(&(spw->regs->ctrl))) & ~(1 << 16);
}

void spw_pnpen(struct spwvars *spw) 
{
  spw->regs->ctrl = loadmem(ptrToInt(&(spw->regs->ctrl))) | (1 << 15);
}

void spw_pnppdis(struct spwvars *spw) 
{
    spw->regs->ctrl = loadmem(ptrToInt(&(spw->regs->ctrl))) & ~(1 << 15);
}

int spw_setdestkey(struct spwvars *spw) 
{
  if ((spw->destkey < 0) || (spw->destkey > 255)) {
    return 1;
  }
  spw->regs->destkey = spw->destkey;
  return 0;
}

void spw_setsepaddr(int dmachan, struct spwvars *spw) 
{
        spw->regs->dma[dmachan].ctrl = loadmem(ptrToInt(&(spw->regs->dma[dmachan].ctrl))) | (1 << 13);
}

void spw_disablesepaddr(int dmachan, struct spwvars *spw) 
{
        spw->regs->dma[dmachan].ctrl = loadmem(ptrToInt(&(spw->regs->dma[dmachan].ctrl))) & ~(1 << 13);
}


void spw_enablerx(int dmachan, struct spwvars *spw) 
{
        spw->regs->dma[dmachan].ctrl = loadmem(ptrToInt(&(spw->regs->dma[dmachan].ctrl))) | 0x2;
}


void spw_disablerx(int dmachan, struct spwvars *spw) 
{
    spw->regs->dma[dmachan].ctrl = loadmem(ptrToInt(&(spw->regs->dma[dmachan].ctrl))) & ~0x2;
}

void spw_disable_promiscuous(struct spwvars *spw) 
{
    spw->regs->ctrl = loadmem(ptrToInt(&(spw->regs->ctrl))) & ~(1 << 5);
}

void spw_enable_promiscuous(struct spwvars *spw) 
{
        spw->regs->ctrl = loadmem(ptrToInt(&(spw->regs->ctrl))) | (1 << 5);
}
