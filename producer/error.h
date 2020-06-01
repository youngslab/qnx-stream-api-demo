/*
 * $QNXLicenseC:
 * Copyright 2011, QNX Software Systems Limited. All Rights Reserved.
 *
 * This software is QNX Confidential Information subject to 
 * confidentiality restrictions. DISCLOSURE OF THIS SOFTWARE 
 * IS PROHIBITED UNLESS AUTHORIZED BY QNX SOFTWARE SYSTEMS IN 
 * WRITING.
 *
 * You must obtain a written license from and pay applicable license 
 * fees to QNX Software Systems Limited before you may reproduce, modify
 * or distribute this software, or any work that includes all or part 
 * of this software. For more information visit 
 * http://licensing.qnx.com or email licensing@qnx.com.
 * 
 * This file may contain contributions from others.  Please review 
 * this entire file for other proprietary rights or license notices, 
 * as well as the QNX Development Suite License Guide at 
 * http://licensing.qnx.com/license-guide/ for other information.
 * $
 */

#ifndef ERROR_H_
#define ERROR_H_

#ifdef __cplusplus
extern "C" {
#endif

void egl_perror(const char *msg);

#ifdef __cplusplus
}
#endif

#endif /*ERROR_H_*/

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn.ott.qnx.com/product/graphics/branches/release-2.1.x/apps/screen/demos/gles2-gears/error.h $ $Rev: 680328 $")
#endif
