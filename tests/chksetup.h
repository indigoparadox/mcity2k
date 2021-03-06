
#ifndef CHKSETUP_H
#define CHKSETUP_H

#include <stdint.h>

#include <check.h>

#define TEST_CITY_FILENAME "test1.sc2"
#define TEST_CITY_REALNAME "Test1"

void setup_mcityfile();
void teardown_mcityfile();

#ifdef CHKSETUP_C
uint8_t* mcityfile_bytes = NULL;
uint32_t mcityfile_sz = 0;
#else
extern uint8_t* mcityfile_bytes;
extern uint32_t mcityfile_sz;
#endif /* CHKSETUP_C */

#endif /* !CHKSETUP_H */

