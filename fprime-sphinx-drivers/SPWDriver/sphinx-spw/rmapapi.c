/*****************************************************************************/
/*   This file is a part of the GRLIB VHDL IP LIBRARY */
/*   Copyright (C) 2004 GAISLER RESEARCH */

/*   This program is free software; you can redistribute it and/or modify */
/*   it under the terms of the GNU General Public License as published by */
/*   the Free Software Foundation; either version 2 of the License, or */
/*   (at your option) any later version. */

/*   See the file COPYING for the full details of the license. */
/*****************************************************************************/

#include <Fw/Types/CAssert.hpp>
#include <stdlib.h>
#include "rmapapi.h"

int build_rmap_hdr(struct rmap_pkt *pkt, char *hdr, int *size)
{
        int i;
        int j;
        int type;
        int write;
        int srcspalen;
        if ((pkt->type != readcmd) && (pkt->type != writecmd) && (pkt->type != rmwcmd) &&
            (pkt->type != readrep) && (pkt->type != writerep) && (pkt->type != rmwrep)) {
                return 1;
        }
        if ((pkt->verify != yes) && (pkt->verify != no)) {
                return 1;
        }
        if ((pkt->ack != yes) && (pkt->ack != no)) {
                return 2;
        }
        if ((pkt->incr != yes) && (pkt->incr != no)) {
                return 3;
        }
        if ( (pkt->dstspalen < 0) || (pkt->dstspalen > 228) ) {
                return 4;
        }
        if ( (pkt->srcspalen < 0) || (pkt->srcspalen > 12) ) {
                return 5;
        }
        if( (pkt->destkey < 0) || (pkt->destkey > 255) ) {
                return 6;
        }
        if( (pkt->destaddr < 0) || (pkt->destaddr > 255) ) {
                return 7;
        }
        if( (pkt->srcaddr < 0) || (pkt->srcaddr > 255) ) {
                return 9;
        }
        if( (pkt->tid < 0) || (pkt->tid > 65535) ) {
                return 10;
        }
        if( (pkt->len < 0) || (pkt->len > 16777215) ) {
                return 11;
        }
        if( (pkt->status < 0) || (pkt->status > 12) ) {
                return 12;
        }
        if ((pkt->type == writecmd) || (pkt->type == writerep)) {
                write = 1;
        } else {
                write = 0;
        }
        if ((pkt->type == writecmd) || (pkt->type == readcmd) || (pkt->type == rmwcmd)) {
                type = 1;
                *size = pkt->dstspalen + 15;
                srcspalen = pkt->srcspalen/4;
                if ( (pkt->srcspalen % 4) != 0) {
                        srcspalen = srcspalen + 1;
                }
                *size = srcspalen * 4 + *size;
                for(i = 0; i < pkt->dstspalen; i++) {
                        hdr[i] = pkt->dstspa[i];
                }
                hdr[pkt->dstspalen] = (char)pkt->destaddr;
                hdr[pkt->dstspalen+1] = (char)0x01;
                hdr[pkt->dstspalen+2] = (char)0;
                hdr[pkt->dstspalen+2] = hdr[pkt->dstspalen+2] | (type << 6) | 
                        (write << 5) | (pkt->verify << 4) | (pkt->ack << 3) | (pkt->incr << 2) | srcspalen;
                hdr[pkt->dstspalen+3] = (char)pkt->destkey;
                j = 0;
                for(i = 0; i < srcspalen*4; i++) {
                        if ((srcspalen*4-i) > (pkt->srcspalen)) {
                                hdr[pkt->dstspalen+4+i] = 0x00;
                        } else {
                                hdr[pkt->dstspalen+4+i] = pkt->srcspa[j];
                                j++;
                        }
                        
                }
                hdr[pkt->dstspalen+4+srcspalen*4] = (char)pkt->srcaddr;
                hdr[pkt->dstspalen+5+srcspalen*4] = (char)((pkt->tid >> 8) & 0xFF);
                hdr[pkt->dstspalen+6+srcspalen*4] = (char)(pkt->tid & 0xFF);
                hdr[pkt->dstspalen+7+srcspalen*4] = (char)0;
                hdr[pkt->dstspalen+8+srcspalen*4] = (char)((pkt->addr >> 24) & 0xFF);
                hdr[pkt->dstspalen+9+srcspalen*4] = (char)((pkt->addr >> 16) & 0xFF);
                hdr[pkt->dstspalen+10+srcspalen*4] = (char)((pkt->addr >> 8) & 0xFF);
                hdr[pkt->dstspalen+11+srcspalen*4] = (char)(pkt->addr & 0xFF);
                hdr[pkt->dstspalen+12+srcspalen*4] = (char)((pkt->len >> 16) & 0xFF);
                hdr[pkt->dstspalen+13+srcspalen*4] = (char)((pkt->len >> 8) & 0xFF);
                hdr[pkt->dstspalen+14+srcspalen*4] = (char)(pkt->len & 0xFF);
        } else {
                type = 0;
                if (pkt->type == writerep) {
                        *size = pkt->srcspalen + 7;
                } else {
                        *size = pkt->srcspalen + 11;
                }
                srcspalen = pkt->srcspalen/4;
                if ( (pkt->srcspalen % 4) != 0) {
                        srcspalen = srcspalen + 1;
                }
                for(i = 0; i < pkt->srcspalen; i++) {
                        hdr[i] = pkt->srcspa[i];
                }
                hdr[pkt->srcspalen] = (char)pkt->srcaddr;
                hdr[pkt->srcspalen+1] = (char)0x01;
                hdr[pkt->srcspalen+2] = (char)0;
                hdr[pkt->srcspalen+2] = hdr[pkt->srcspalen+2] | (type << 6) | 
                        (write << 5) | (pkt->verify << 4) | (pkt->ack << 3) | (pkt->incr << 2) | srcspalen;
                hdr[pkt->srcspalen+3] = (char)pkt->status;
                hdr[pkt->srcspalen+4] = (char)pkt->destaddr;
                hdr[pkt->srcspalen+5] = (char)((pkt->tid >> 8) & 0xFF);
                hdr[pkt->srcspalen+6] = (char)(pkt->tid & 0xFF);
                if (pkt->type != writerep) {
                        hdr[pkt->srcspalen+7] = (char)0;
                        hdr[pkt->srcspalen+8] = (char)((pkt->len >> 16) & 0xFF);
                        hdr[pkt->srcspalen+9] = (char)((pkt->len >> 8) & 0xFF);
                        hdr[pkt->srcspalen+10] = (char)(pkt->len & 0xFF);
                }
        }
        return 0;
}



int parse_rmap_pkt(struct rmap_pkt *pkt, char *hdr, int *size)
{
  FW_CASSERT(pkt != NULL);
  FW_CASSERT(hdr != NULL);
  FW_CASSERT(size != NULL);

  struct rmap_pkt tpkt;

  const unsigned char* uhdr = (unsigned char*)hdr;

  // assumes logical addressing
  tpkt.dstspalen = 0;
  tpkt.dstspa = NULL;
  tpkt.srcspalen = 0;
  tpkt.srcspa = NULL;

  char protocol_id = uhdr[1];
  if (protocol_id != 1) {
    // protocol id not rmap
    return 1;
  }

  char flag = uhdr[2];
  char cmd = (flag >> 6) & 1;
  char write = (flag >> 5) & 1;
  char verify = (flag >> 4) & 1;
  char ack = (flag >> 3) & 1;
  char incr = (flag >> 2) & 1;
  char srcspalen = flag & 0x3;
  if (cmd) {
    if (write) {
      tpkt.type = writecmd;
    } else {
      if (!verify) {
        tpkt.type = readcmd;
      } else {
        tpkt.type = rmwcmd;
      }
    }
  } else {
    if (write) {
      tpkt.type = writerep;
    } else {
      if (!verify) {
        tpkt.type = readrep;
      } else {
        tpkt.type = rmwrep;
      }
    }
  }
  tpkt.verify = verify ? yes : no;
  tpkt.ack = ack ? yes : no;
  tpkt.incr = incr ? yes : no;
  if (srcspalen > 0) {
    // path addressing NOT supported
    return 255;
  }

  if (cmd) {
    // command
    tpkt.destaddr = uhdr[0];
    tpkt.destkey = uhdr[3];
    tpkt.status = 0;
    tpkt.srcaddr = uhdr[4];
    tpkt.tid = ((uhdr[5] << 8) | uhdr[6]);

    if (uhdr[7] != 0) {
      // nonzero extended addr or reserved area, not supported
      return 254;
    }

    tpkt.addr = (uhdr[8] << 24) | (uhdr[9] << 16) | (uhdr[10] << 8) | uhdr[11];
    tpkt.len = (uhdr[12] << 16) | (uhdr[13] << 8) | uhdr[14];

    *size = 15;

  } else {
    // reply
    tpkt.srcaddr = uhdr[0];
    tpkt.destkey = 0;
    tpkt.status = uhdr[3];
    tpkt.destaddr = uhdr[4];
    tpkt.tid = ((uhdr[5] << 8) | uhdr[6]);
    tpkt.addr = 0;

    if (write) {
      // write reply ends here
      tpkt.len = 0;
      *size = 7;

    } else {
      // read and rmw reply has additional len param
      tpkt.len = (uhdr[8] << 16) | (uhdr[9] << 8) | uhdr[10];
      *size = 11;

    }
  }

  *pkt = tpkt;
  return 0;
}



