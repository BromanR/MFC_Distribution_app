#pragma once
#ifndef R32M_H
#define R32M_H


void  rninit   ( unsigned long iufir );
void  rnrest   ( void );
void  rnconst  ( unsigned long iufir );
void  rnconfix ( unsigned nmb );

unsigned long rnfirst (void);
unsigned long rnlast  (void);
unsigned long rnconrd (void);

double  rnunif ( void );
double  rnexp  ( void );
double  rnnorm ( void );

#endif