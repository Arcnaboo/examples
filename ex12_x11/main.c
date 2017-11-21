/**
 *
 * Title: ex12_x11/main.c, X11 Example
 *
 * Description: This example shows how to draw basic shapes with X11.
 *				NOTE: include the -lX11 library when compiling
 *				IMPORTANT NOTE: This example MUST be run in VNC not SSH.
 *
 * Reference: https://www.x.org/releases/X11R7.7/doc/libX11/libX11/libX11.html
 *
 * Modified by: MD & VS
 *
 * Date: 20/7/2016
 */

#include "stdio.h"
#include "stdlib.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/Xproto.h>

int main(int argc,char **argv) {

   	int blackColor,whiteColor,thescreen;
   	Display *thedisplay;
   	GC thecontext;
   	XColor xcolour;
   	Colormap thecolormap;
   	Window thewindow;
	XEvent anevent;

	/* Setup a window */
   	thedisplay  = XOpenDisplay(NULL);
   	blackColor  = BlackPixel(thedisplay,DefaultScreen(thedisplay));
   	whiteColor  = WhitePixel(thedisplay,DefaultScreen(thedisplay));
   	thescreen   = DefaultScreen(thedisplay);
   	thecolormap = DefaultColormap(thedisplay,thescreen);

   	/* Create the window */
   	thewindow = XCreateSimpleWindow(thedisplay,   DefaultRootWindow(thedisplay),0,0,  300,300,0,blackColor,blackColor);
   	XSelectInput(thedisplay,thewindow,StructureNotifyMask);
   	XMapWindow(thedisplay,thewindow);

   	/* Get the context */
   	thecontext = XCreateGC(thedisplay,thewindow,0,NULL);
   	XSetBackground(thedisplay,thecontext,blackColor);
   	XSetForeground(thedisplay,thecontext,whiteColor);

	/* Wait for the MapNotify event */
   	for (;;) {
    	XNextEvent(thedisplay, &anevent);
      	if (anevent.type == MapNotify)
        	break;
   	}
   
   	/* Erase the display (In the background colour) */
   	//XClearWindow(thedisplay,thewindow);

	/* Draw a green diagonal line */
	xcolour.red = 0; 
	xcolour.green = 0xFFFF; 
	xcolour.blue = 0;
   	xcolour.flags = DoRed | DoGreen | DoBlue;
   	XAllocColor(thedisplay,thecolormap,&xcolour);

	/* Set the foreground colour to green */
   	XSetForeground(thedisplay,thecontext,xcolour.pixel);

   	/* Draw a line (In the foreground colour) */
   	XDrawLine(thedisplay,thewindow,thecontext,10,10,390,390);
   	XFlush(thedisplay);

   	/* Draw a red filled rectangle */
   	xcolour.red = 0xFFFF; 
	xcolour.green = 0; 
	xcolour.blue = 0;
   	xcolour.flags = DoRed | DoGreen | DoBlue;
   	XAllocColor(thedisplay,thecolormap,&xcolour);

	/* Set the foreground colour to red */
   	XSetForeground(thedisplay,thecontext,xcolour.pixel);

	/* Draw a rectangle (In the foreground colour) */
   	XFillRectangle(thedisplay,thewindow,thecontext,100,100,200,200);
   	XFlush(thedisplay);

   	/* Display for 10s, before exiting */
	sleep(100);
   	XFreeGC(thedisplay,thecontext);
   	XUnmapWindow(thedisplay,thewindow);
   	XDestroyWindow(thedisplay,thewindow);
   	XCloseDisplay(thedisplay);

	return 0;
}

