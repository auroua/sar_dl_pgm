/*=========================================================================
 *=========================================================================
  == [DISCLAIMER]: THIS SOFTWARE AND ANY ACCOMPANYING DOCUMENTATION IS   ==
  == RELEASED "AS IS".  THE U.S. GOVERNMENT MAKES NO WARRANTY OF ANY     ==
  == KIND, EXPRESS OR IMPLIED, CONCERNING THIS SOFTWARE AND ANY          ==
  == ACCOMPANYING DOCUMENTATION, INCLUDING, WITHOUT LIMITATION, ANY      ==
  == WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  ==
  == IN NO EVENT WILL THE U.S. GOVERNMENT BE LIABLE FOR ANY DAMAGES      ==
  == ARISING OUT OF THE USE, OR INABILITY TO USE, THIS SOFTWARE OR ANY   ==
  == ACCOMPANYING DOCUMENTATION, EVEN IF INFORMED IN ADVANCE OF THE      ==
  == POSSIBLITY OF SUCH DAMAGES.                                         ==
  =========================================================================
  =========================================================================*/


/*-------------------------------------------------------------------------
 *                      Routine: mstar2jpeg (Version 2.0)
 *                       Author: John F. Querns, Veridian Engineering
 *                         Date: 24 September 1998
 *
 * What's new in Version 2.0:
 *
 * (1)  Recoded auto-enhancement section to use a better algorithm for target
 *      chips.  Use same enhancement scheme for full scenes.
 *
 * (2)  Added code to check current CPU for byte ordering. If little-endian,
 *      code automatically byteswaps input data before any further processing
 *      is done.
 *
 *-------------------------------------------------------------------------
 *
 * Purpose: This routine converts MSTAR fullscene and target chip images
 *          to 8-bit JPEG-compressed (JFIF) images.  It makes use of ideas
 *          from example code supplied by the following group:
 *
 *                    Independent JPEG Group (IPG)
 *
 *          See the file, "Acknowledgments.txt" for the appropriate
 *          Copyright notice.  The IPG portions of this code (i.e.
 *          library calls) come from libjpeg.a, which is copyright
 *          (C) 1991, 1992, 1993, 1994, Thomas G. Lane.
 *
 *          The MSTAR imagery is outputted as 8-bit to better facilitate
 *          VIEWING of the imagery using standard commercial software.
 *
 *-------------------------------------------------------------------------
 *
 * [Calls]:
 *
 *     char *read_switch()   -- Utility to extract arguments from
 *                              input switches.  This was extracted
 *                              from code developed by Otto Milvang,
 *                              U. of Oslo and is part of the B-LAB
 *                              XITE software.
 *
 *                              Copyright 1990, Blab, UiO
 *                              Image processing lab,
 *                              Department of Informatics
 *                              University of Oslo
 *
 *                              See "Acknowledgments.txt" for full
 *                              copyright notice.
 *
 *     float
 *     byteswap_SR_IR()      -- Does big-endian to little-endian float
 *                              byteswap..this is specifically for the
 *                              case of Sun big-endian to PC-Intel
 *                              little-endian data.
 *
 *     unsigned short
 *     byteswap_SUS_IUS()    -- Does big-endian to little-endian swap for
 *                              unsigned short (16-bit) numbers. This is
 *                              specifically for the case of Sun big-
 *                              endian to PC-Intel little-endian data.
 *
 *     int
 *     CheckByteOrder()      -- This checks the byte order for the CPU that
 *                              this routine is compiled run on. If the
 *                              CPU is little-endian, it will return a 0
 *                              value (LSB_FIRST); else, it will return a 1
 *                              (MSB_FIRST).
 *
 *                              Taken from:
 *
 *                                Encyclopedia of Graphic File
 *                                Formats, Murray & Van Ryper,
 *                                O'Reilly & Associates, 1994,
 *                                pp. 114-115.
 *
 *-------------------------------------------------------------------------
 *
 * [Methodology]:
 *
 *     This routine converts ONLY the MAGNITUDE data portion of MSTAR
 *     files (i.e. it ignores the PHASE data).  The output JPEG file
 *     represents the compressed 8-bit value of the original MAGNITUDE
 *     data portion of the MSTAR files:
 *
 *          [FULLSCENE IMAGES]: Unsigned 16-bit data linearly scaled to
 *                              unsigned 8-bit.
 *
 *          [CHIP IMAGES]     : 32-bit floating point linearly scaled to
 *                              unsigned 8-bit.
 *
 *     Scaling Method:
 *     --------------
 *
 *          Given: OP     = Output pixel
 *                 IP     = Input pixel
 *                 RANGE  = Range of gray values in input image (MAX-MIN)
 *                 MIN    = Minimum pixel value in input image
 *                 T      = Temporary value
 *
 *          Then:  T   =TARGET_LINK_LIBRARIES(main pthread)   ((FLOAT) (IP - MIN) / RANGE) * 255.0
 *                 OP  = (unsigned char) (T + 0.5);
 *
 *-------------------------------------------------------------------------
 *
 * [Enhancement]:
 *
 *    The MSTAR data is very dark and will need contrast enhancement to
 *    increase the dynamic range for suitable VIEWING.  This routine
 *    includes a switch option (-e) to automatically increase the image
 *    contrast, producing a "nicer" looking image.  The default mode
 *    is NOT to enhance the image, but to allow the user to enhance
 *    the image using an appropriate software tool.
 *
 *       NOTE: The enhancement algorithm works well for most chips and
 *             full scenes, but not all.
 *
 *    [ALGORITHM]:
 *
 *      TARGET CHIPS/
 *      CLUTTER FULLSCENES : New histogram-based method applied....
 *
 *      TARGET FULLSCENES  : Same. Multiplies pixel value by constant
 *                           and clips to 255.
 *i

I
a
 *------------------------------------------------------------------------
 *
 * [ASCII Header]:
 *
 *    This routine includes a switch option (-h) that allows the dumping
 *    of the MSTAR Phoenix header to an output file.  The output header
 *    will use name of input MSTAR file as its basename and will have the
 *    extension: ".hdr".  The default mode is NOT to dump header.
 *
 *-----------------------------------------------------------------------
 *
 * [INFORMATION]:
 *
 *    This routine includes a switch option (-v) that turns on the
 *    verbose mode.  The code normally runs in quiet mode, but will,
 *    if the -v switch is entered, echo what processes are being run.
 *
 *-----------------------------------------------------------------------
 *
 * [Syntax/Usage]:
 *
 *    mstar2jpeg -i <MSTAR input> -o <JPEG output> [-e] [-q] qf [-h] [-v]
 *
 *            Options: [-e] -- Auto-contrast enhancement [Def: none]
 *                     [-q] -- Compression quality factor (5-95, def:75)
 *                     [-h] -- Dump Phoenix header
 *                     [-v] -- verbose mode
 *
 *-----------------------------------------------------------------------
 *
 * [Contacts]:
 *
 *   John F. Querns
 *   Veridian Engineering (Dayton Group)
 *   5200 Springfield Pike, Dayton, OH 45431
 *   email: jquerns@dytn.veridian.com
 *
 *   Veridian Contractor Area
 *   Area B  Bldg 23  Rm 115
 *   2010 Fifth Street
 *   Wright Patterson AFB, OH  45433-7001
 *   Work : (937) 255-1116, Ext 2818
 *   email: jquerns@mbvlab.wpafb.af.mil
 *
 *-------------------------------------------------------------------------
 *
 * [Versions]:
 *
 *   1.0: 2 Jun 1997
 *
 *   2.0: 24 September 1998 -
 *        Added auto data byte swap to little-endian if necessary. [JQuerns]
 *        Improved automatic enhancement algorithm. [JQuerns]
 *
 *------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include "/usr/include/jpeglib.h"

#define MSTAR_CHIP     0           /* Implies MSTAR target chip file..     */
#define MSTAR_FSCENE   1           /* Implies MSTAR fullscene target file  */
#define MSTAR_CLUT     2           /* Implies MSTAR fullscene clutter file */

#define LSB_FIRST    0             /* Implies little-endian CPU... */
#define MSB_FIRST    1             /* Implies big-endian CPU...    */

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE  1
#endif

#ifndef MAX
#define MAX(x,y)   (((x) > (y)) ? (x) : (y))
#endif

#ifndef MIN
#define MIN(x,y)   (((x) < (y)) ? (x) : (y))
#endif

/* Function declarations... */
extern char          *read_switch();
static float          byteswap_SR_IR();
static unsigned short byteswap_SUS_IUS();
static int            CheckByteOrder();


void transform(char* input,char* output){
    {
        FILE *MSTARfp=NULL;              /* Ptr to input MSTAR file          */
        FILE *HDRfp=NULL;                /* Ptr to (opt.) output Header file */
        FILE *JPEGfp=NULL;               /* Ptr to output JPEG file          */

        unsigned char *pic8;             /* Ptr to 8-bit image buffer...     */

        int   i, j, w, h, h2, numgot;

        int   HDRflag=FALSE;             /* If TRUE, dump Phoenix header..   */
        int   ENHANCEflag=FALSE;         /* If TRUE, apply enhancement..     */
        int   VERBOSEflag=FALSE;         /* If TRUE, keep user informed...   */

        char *HDRopt, *ENHopt;           /* Input argument ptr variables...  */
        char *VERBopt, *QFopt;           /* Input argument ptr variables...  */

        char *MSTARname=NULL;            /* Ptr to input MSTAR filename...   */
        char *JPEGname=NULL;             /* Ptr to output JPEG filename...   */
        char  HDRname[40];               /* Buffer to hold opt. hdr filename */

        int            phlen, nhlen, mstartype;
        int            region1, region2, region3, region4;
        long           magloc, bytesPerImage, nchunks;
        char          *tptr=NULL, *phdr;
//        unsigned char  tbuff[2048], ival;
        unsigned char  tbuff[2048], ival;

        unsigned short *FSCENEdata=NULL, smax, smin, srange;
        float          *CHIPdata=NULL, efactor;
        int            qfactor, isum, radarmode;

/* 8-bit linear scaling variables */
        float          fscale, f1, f2, fmax, fmin, frange;

/* Byte Order Variables */
        int            byteorder;
        unsigned char  bigfloatbuf[4];   /* BigEndian float buffer... */
        float          littlefloatval;   /* LittleEndian float value  */
        unsigned char  bigushortbuf[2];  /* BigEndian ushort buffer...*/
        unsigned short littleushortval;  /* LittleEndian ushort value.*/


/* Enhancement Algorithm Variables */
        int            hist8[256];
        int            histmax, histmin, histrange, numcolors=0;
        int            maxPixelCountBin, minPixelCountBin;
        int            CountBinRange;
        float          fsum, t1, hval;
        float          scaleAdj, threshVal, threshLim;


/**********************************************************
 *                   JPEG-RELATED VARIABLES               *
 **********************************************************/

/* This struct contains the JPEG compression parameters and pointers to
 * working space (which is allocated as needed by the JPEG library).
 * It is possible to have several such structures, representing multiple
 * compression/decompression processes, in existence at once.  We refer
 * to any one struct (and its associated working data) as a "JPEG object".
 */
        struct jpeg_compress_struct  cinfo;

/* This struct represents a JPEG error handler.  It is declared separately
 * because applications often want to supply a specialized error handler
 * (see the second half of this file for an example).  But here we just
 * take the easy way out and use the standard error handler, which will
 * print a message on stderr and call exit() if compression fails.
 */
        struct jpeg_error_mgr        jerr;

        JSAMPROW                     rowptr[1];
        unsigned int                 clen;

/************************ B E G I N  C O D E ****************************/

/* Extract Input & Output filenames */
        MSTARname = input;
        JPEGname  = output;


//MSTARname2 = read_switch("aaaaa", "bbbbb", "-i", 1, NULL);
//fprintf(stderr,MSTARname2);

/* Extract optional arguments (if any) */

/****************************************************
 * Compression Quality Factor:                      *
 * --------------------------                       *
 *                                                  *
 * 1) If "-q" NOT ENTERED, routine ASSUMES quality  *
 *    factor of 75.                                 *
 *                                                  *
 * 2) If "-q" ENTERED, routine assigns inputted     *
 *    quality factor as long as it meets limits.    *
 *                                                  *
 ****************************************************/
        qfactor = 75;
/* Check for Enhancement Option */
        ENHANCEflag = TRUE;
/* Check for VERBOSE option */
        VERBOSEflag = FALSE;
/* Check to see if ouput header name needs forming */

        if (VERBOSEflag == TRUE)
        {
            printf("\n\nMSTAR to JPEG conversion: started!\n");
        }

/***************** MAIN MSTAR PROCESSING AREA ********************/

/* Open input MSTAR file for reading */
        MSTARfp = fopen(MSTARname,"rb");
        if (MSTARfp == NULL)
        {
            fprintf(stderr,
                    "\n\nError: Unable to open [%s] for reading!\n\n", MSTARname);
            exit(1);
        }

/****************************************************
 * Read first 2K bytes to figure out some header    *
 * parameters....                                   *
 ****************************************************/

        if (VERBOSEflag == TRUE)
        {
            printf("Determining input image/hdr information...\n");
        }

        fread(tbuff, sizeof(char), 2048, MSTARfp);
        rewind(MSTARfp);

/* Extract Phoenix Summary header length */
        tptr = (char *) strstr(tbuff,"PhoenixHeaderLength= ");
        if (tptr == (char *) NULL)
        {
            fprintf(stderr,"Can not determine Phoenix header length!\n");
            fclose(MSTARfp);
            exit(1);
        } else
        {
            sscanf((tptr+20), "%d", &phlen);
        }

/* Check for and extract native header length */
        tptr = (char *) strstr(tbuff,"native_header_length= ");
        if (tptr == (char *) NULL)
        {
            fprintf(stderr,"Can not determine native header length!\n");
            fclose(MSTARfp);
            exit(1);
        } else
        {
            sscanf((tptr+21), "%d", &nhlen);
        }

/* Extract MSTAR column width */
        tptr = (char *) strstr(tbuff,"NumberOfColumns= ");
        if (tptr == (char *) NULL)
        {
            fprintf(stderr,
                    "Error: Can not determine MSTAR image width");
            fclose(MSTARfp);
            exit(1);
        } else
        {
            sscanf((tptr+16), "%d", &w);
        }

/* Extract MSTAR row height */
        tptr = (char *) strstr(tbuff,"NumberOfRows= ");
        if (tptr == (char *) NULL)
        {
            fprintf(stderr,
                    "Error: Can not determine MSTAR image height!");
            fclose(MSTARfp);
            exit(1);
        } else
        {
            sscanf((tptr+13), "%d",&h);
        }

/* Determine MSTAR image type */
        tptr = (char *) strstr(tbuff,"RadarMode= ");
        if (tptr == (char *) NULL)
        {
            fprintf(stderr,
                    "Error: Can not determine MSTAR image radar mode!\n\n");
            fclose(MSTARfp);
            exit(1);
        } else
        {
            sscanf((tptr+16), "%d", &radarmode);
        }

/* Set MSTAR image type */
        if (nhlen == 0)
        {/* Implies FLOAT MSTAR chip image */
            mstartype = MSTAR_CHIP;
            if (VERBOSEflag == TRUE)
            {
                printf("==> MSTAR target chip image detected...\n");
            }
        } else
        {
            switch (radarmode)
            {
                case 4: /* Strip mode */
                    mstartype = MSTAR_CLUT;
                    break;
                case 5: /* Spotlight */
                default:
                    mstartype = MSTAR_FSCENE;
                    break;
            }

            if (VERBOSEflag == TRUE)
            {
                switch (mstartype)
                {
                    case MSTAR_CLUT:
                        printf("==> MSTAR fullscene clutter image detected...\n");
                        break;
                    case MSTAR_FSCENE:
                        printf("==> MSTAR fullscene target image detected...\n");
                        break;
                }
            }
        }

/*******************************************************
 * If HEADER FLAG = TRUE:                              *
 * Allocate memory to header buffer, read Phoenix hdr, *
 * and write out to output file...free header buffer.. *
 *******************************************************/
        if (HDRflag == TRUE)
        {
            HDRfp = fopen(HDRname, "w");
            if (HDRfp == NULL)
            {
                fprintf(stderr,
                        "Error: unable to open header file [%s] for writing!\n",
                        HDRname);
                fclose(MSTARfp);
                exit(1);
            }

            phdr = (char *) malloc(phlen+1);
            if (phdr == (char *) NULL)
            {
                fprintf(stderr,
                        "Error: unable to allocate header memory!\n");
                fclose(MSTARfp);
                fclose(HDRfp);
                unlink(HDRname);
                exit(1);
            }

            fread(phdr, sizeof(char), phlen, MSTARfp);
            fwrite(phdr, sizeof(char), phlen, HDRfp);
            fclose(HDRfp);
            free(phdr);

            if (VERBOSEflag == TRUE)
            {
                printf("Phoenix header written to [%s]...\n", HDRname);
            }
        }

/***********************************************************
 * Set up file location to point to MSTAR magnitude data.. *
 ***********************************************************/
        switch (mstartype)
        {
            case MSTAR_CHIP:
                magloc  = phlen;
                fseek(MSTARfp, magloc, 0);
                break;
            case MSTAR_CLUT:
            case MSTAR_FSCENE:
                magloc  = phlen + nhlen; /* nhlen = 512 */
                fseek(MSTARfp, magloc, 0);
                break;
        }

/******************************************************
 * Check byte-order, swap bytes if necessary...       *
 * Allocate memory, read data,  & convert to 8-bit    *
 * based on 'mstartype'                               *
 ******************************************************/

/* Check byteorder */
        byteorder = (int) CheckByteOrder();
        switch (byteorder)
        {
            case LSB_FIRST:

                if (VERBOSEflag == TRUE)
                {
                    printf("==> Little-Endian CPU detected: Will byteswap before scaling data!\n");
                }
                break;

            case MSB_FIRST:

                if (VERBOSEflag == TRUE)
                {
                    printf("==> Big-Endian CPU detected: No byteswap needed!\n");
                }
                break;
        }


/******************************************************
 * Allocate memory, read data,  & convert to 8-bit    *
 * based on 'mstartype'                               *
 ******************************************************/
        numgot = 0;
        nchunks = w * h;
        switch (mstartype)
        {
            case MSTAR_CHIP:
                bytesPerImage = nchunks * sizeof(float);
                CHIPdata = (float *) malloc(bytesPerImage);
                if (CHIPdata == (float *) NULL)
                {
                    fprintf(stderr,
                            "Error: Unable to malloc CHIP memory!\n");
                    fclose(MSTARfp);
                    exit(1);
                }

                pic8 = (unsigned char *) calloc((size_t) w * h, (size_t) 1);
                if (pic8 == (unsigned char *) NULL)
                {
                    fprintf(stderr,
                            "Error: Unable to malloc output 8-bit memory!\n");
                    fclose(MSTARfp);
                    free(CHIPdata);
                    exit(1);
                }

                if (VERBOSEflag == TRUE)
                {
                    printf("Reading MSTAR Chip magnitude data...\n");
                }

                switch (byteorder)
                {
                    case LSB_FIRST: /* Little-endian..do byteswap */

                        if (VERBOSEflag == TRUE)
                        {
                            printf("Performing auto-byteswap...\n");
                        }
                        for (i = 0; i < nchunks; i++)
                        {
                            fread(bigfloatbuf, sizeof(char), 4, MSTARfp);
                            littlefloatval = byteswap_SR_IR(bigfloatbuf);
                            CHIPdata[i] = littlefloatval;
                        }
                        break;

                    case MSB_FIRST: /* Big-endian..no swap */

                        numgot = fread(CHIPdata, sizeof(float), nchunks, MSTARfp);
                        break;
                }

                if (VERBOSEflag == TRUE)
                {
                    printf("Scaling MSTAR Chip magnitude data to 8-bit...\n");
                }

                fmax = 0.0;
                fmin = 100000.0;
                for (i = 0; i < nchunks; i++)
                {
                    fmax = MAX(CHIPdata[i], fmax);
                    fmin = MIN(CHIPdata[i], fmin);
                }
                frange = fmax - fmin;
                fscale = 255.0 / frange;

                for (i = 0; i < nchunks; i++)
                {
                    f1 = CHIPdata[i] - fmin;
                    f2 = f1 * fscale;
                    pic8[i] = (unsigned char) (f2 + 0.5);
                }
                free(CHIPdata);
                break;

            case MSTAR_CLUT:
            case MSTAR_FSCENE:
                bytesPerImage = nchunks * sizeof(short);
                FSCENEdata = (unsigned short *) malloc( bytesPerImage );
                if (FSCENEdata == (unsigned short *) NULL)
                {
                    fprintf(stderr,
                            "Error: Unable to malloc fullscene memory!\n");
                    fclose(MSTARfp);
                    exit(1);
                }

                pic8 = (unsigned char *) calloc((size_t) w * h, (size_t) 1);
                if (pic8 == (unsigned char *) NULL)
                {
                    fprintf(stderr,
                            "Error: Unable to malloc output 8-bit memory!\n");
                    fclose(MSTARfp);
                    free(FSCENEdata);
                    exit(1);
                }

                if (VERBOSEflag == TRUE)
                {
                    printf("Reading MSTAR fullscene magnitude data...\n");
                }

                switch (byteorder)
                {
                    case LSB_FIRST: /* Little-endian..do byteswap */

                        if (VERBOSEflag == TRUE)
                        {
                            printf("Performing auto-byteswap...\n");
                        }
                        for (i = 0; i < nchunks; i++)
                        {
                            fread(bigushortbuf, sizeof(char), 2, MSTARfp);
                            littleushortval = byteswap_SUS_IUS(bigushortbuf);
                            FSCENEdata[i] = littleushortval;
                        }
                        break;

                    case MSB_FIRST: /* Big-endian..no swap */

                        numgot = fread(FSCENEdata, sizeof(short), nchunks, MSTARfp);
                        break;
                }

                if (VERBOSEflag == TRUE)
                {
                    printf("\nScaling MSTAR fullscene magnitude data to 8-bit...");
                }

                smax = 0;
                smin = 65535;
                for (i = 0; i < nchunks; i++)
                {
                    smax = MAX(FSCENEdata[i], smax);
                    smin = MIN(FSCENEdata[i], smin);
                }
                srange = smax - smin;
                fscale = 255.0 / (float) srange;

                for (i = 0; i < nchunks; i++)
                {
                    f1 = (float) (FSCENEdata[i] - smin);
                    f2 = f1 * fscale;
                    pic8[i] = (unsigned char) (f2 + 0.5);
                }

                free(FSCENEdata);
                break;
        }

        fclose(MSTARfp);

/************* MAIN ENHANCEMENT PROCESSING AREA **************/
        if (ENHANCEflag == TRUE)
        {
            if (VERBOSEflag == TRUE)
            {
                printf("Contrast-Adjusting 8-bit data..\n");
            }

/*********** NEW ENHANCEMENT ALGORITHM *******************/

/* Initialize histogram array */
            for (i = 0; i < 256; i++)
            {
                hist8[i] = 0;
            }

/* Calculate histogram of MSTAR 8-bit data */
            for (i = 0; i < nchunks; i++)
            {
                ival = pic8[i];
                hist8[ival]++;
            }

/******************************************
 * Calculate number of grayscale values.. *
 ******************************************/
            for (i = 0; i < 256; i++)
            {
                if (hist8[i] > 0)
                {
                    numcolors++;
                }
            }

/* Find MAX & MIN COUNTS of Histogram BINS */
            histmax = 0;
            histmin = nchunks;
            for (i = 0; i < 256; i++)
            {
                histmax = MAX(hist8[i], histmax);
                histmin = MIN(hist8[i], histmin);
            }

/* Find BIN where MAX & MIN Pixel Counts are */
            maxPixelCountBin = 0;      /* Assume Bin#0   has maximum pixel count.. */
            minPixelCountBin = 255;    /* Assume Bin#255 has minimum pixel count.. */
            for (i = 0; i < 256; i++)
            {
                if (hist8[i] == histmax)
                {/* Do this just in case > 1 bin has histmax values */
                    maxPixelCountBin = MAX(maxPixelCountBin, i);
                }

                if (hist8[i] == histmin)
                {/* Do this just in case > 1 bin has histmin values */
                    minPixelCountBin = MIN(minPixelCountBin, i);
                }
            }
            CountBinRange = abs(maxPixelCountBin - minPixelCountBin);

/* Adjust Pixel Contrast */
            for (i = 0; i < nchunks; i++)
            {
                switch (mstartype)
                {
                    case MSTAR_CHIP:
                    case MSTAR_CLUT:

                        ival = pic8[i];
                        if (minPixelCountBin > maxPixelCountBin)
                        {
                            threshVal = (float) (minPixelCountBin - maxPixelCountBin);
                            if (ival > threshVal)
                            {
                                f1 = 255.0;
                            } else
                            {
                                scaleAdj = 255.0 /threshVal;
                                f1 = scaleAdj * (float) ival;
                            }
                        } else
                        {
                            f1 = 3.0 * (float) ival;
                        }

                        break;

                    case MSTAR_FSCENE:
                        f1 = (float) pic8[i] * 20.0;
                        break;
                }

/*********** NEW ENHANCEMENT ALGORITHM *******************/

                if (f1 > 255.0)
                {
                    pic8[i] = 255;
                } else
                {
                    pic8[i] = (unsigned char) (f1 + 0.5);
                }
            }

        }

/************* MAIN JPEG PROCESSING AREA ********************/

        if (VERBOSEflag == TRUE)
        {
            printf("Setting up JPEG parameters....\n");
        }

/* Step 1: allocate and initialize JPEG compression object */

/* We have to set up the error handler first, in case the initialization
 * step fails.  (Unlikely, but it could happen if you are out of memory.)
 * This routine fills in the contents of struct jerr, and returns jerr's
 * address which we place into the link field in cinfo.
 */
        cinfo.err = jpeg_std_error(&jerr);

/* Now we can initialize the JPEG compression object. */
        jpeg_create_compress(&cinfo);

/* Step 2: specify data destination (eg, a file) */
        JPEGfp = fopen(JPEGname, "wb");
        if (JPEGfp == NULL)
        {
            fprintf(stderr,
                    "Error: unable to open output JPEG file [%s]\n",
                    JPEGname);
            exit(1);
        }
        jpeg_stdio_dest(&cinfo, JPEGfp);

/* Step 3: Set parameters for compression..these 4 parameters
 *         MUST be filled in...*/
        cinfo.image_width  = w;
        cinfo.image_height = h;
        cinfo.input_components = 1;
        cinfo.in_color_space = JCS_GRAYSCALE;

/* Now use the library's routine to set default compression parameters.
 * (You must set at least cinfo.in_color_space before calling this,
 * since the defaults depend on the source color space.)
 */
        jpeg_set_defaults(&cinfo);

/* Change parameters you want to change..limit to baseline-JPEG values */
/* Set quality...no smoothing */
        jpeg_set_quality(&cinfo, qfactor, TRUE);
        cinfo.smoothing_factor = 0;

        if (VERBOSEflag == TRUE)
        {
            printf("\nCompressing data...");
        }

/* Step 4: Start compressor
 *         TRUE ensures we write a complete interchange-JPEG file */
        jpeg_start_compress(&cinfo, TRUE);

/* Step 5: while (scan lines remain to be written)....
 *               jpeg_write_scanlines(...);
 *
 * Here we use the library's state variable cinfo.next_scanline as the
 * loop counter, so that we don't have to keep track ourselves.
 * To keep things simple, we pass one scanline per call; you can pass
 * more if you wish, though.
 */

        if (VERBOSEflag == TRUE)
        {
            printf("Writing data. to JPEG file: [%s]\n", JPEGname);
        }

        while (cinfo.next_scanline < cinfo.image_height)
        {
            rowptr[0] = (JSAMPROW) &pic8[cinfo.next_scanline * w];
            (void) jpeg_write_scanlines(&cinfo, rowptr, (JDIMENSION) 1);
        }

/* Step 6: Finish compression */
        jpeg_finish_compress(&cinfo);

/* After finish_compress, we can close the output file. */
        fclose(JPEGfp);

/* Step 7: release JPEG compression object */
        jpeg_destroy_compress(&cinfo);

        if (VERBOSEflag == TRUE)
        {
            printf("\nMSTAR to JPEG conversion: completed!\n\n");
        }

        //exit(0);
    }
}


/****************** Subfunctions **********************/

/************************************************
 * Function:    byteswap_SR_IR                  *
 *   Author:    Dave Hascher (Veridian Inc.)    *
 *     Date:    06/05/97                        *
 *    Email:    dhascher@dytn.veridian.com      *
 ************************************************
 * 'SR' --> Sun 32-bit float value              *
 * 'IR' --> PC-Intel 32-bit float value         *
 ************************************************/

static float byteswap_SR_IR(pointer)
        unsigned char *pointer;
{
    float *temp;
    unsigned char iarray[4], *charptr;

    iarray[0] = *(pointer + 3);
    iarray[1] = *(pointer + 2);
    iarray[2] = *(pointer + 1);
    iarray[3] = *(pointer );
    charptr = iarray;
    temp    = (float *) charptr;
    return *(temp);
}


/************************************************
 * Function:    byteswap_SUS_IUS                *
 *   Author:    John Querns (Veridian Inc.)     *
 *     Date:    06/05/97                        *
 *    Email:    jquerns@dytn.veridian.com       *
 ************************************************
 * 'SUS' --> Sun 16-bit uns short value         *
 * 'IUS' --> PC-Intel 16-bit uns short value    *
 ************************************************/

static unsigned short byteswap_SUS_IUS(pointer)
        unsigned char *pointer;
{
    unsigned short *temp;
    unsigned char iarray[2], *charptr;

    iarray[0] = *(pointer + 1);
    iarray[1] = *(pointer );
    charptr = iarray;
    temp    = (unsigned short *) charptr;
    return *(temp);
}



/**********************************
 *   checkByteOrder()             *
 **********************************
 * Taken from:                    *
 *                                *
 *   Encyclopedia of Graphic File *
 *   Formats, Murray & Van Ryper, *
 *   O'Reilly & Associates, 1994, *
 *   pp. 114-115.                 *
 *                                *
 * Desc: Checks byte-order of CPU.*
 **********************************/

static int CheckByteOrder(void)

{
    short   w = 0x0001;
    char   *b = (char *) &w;

    return(b[0] ? LSB_FIRST : MSB_FIRST);
}
/************************ LAST LINE OF mstar2jpeg.c ************************/

// Linux 下操作方法
//./mstar2jpeg -i  '/home/auroua/workspace/matlab/SAR-Data/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/15_DEG/COL1/SCENE1/BTR_60/HB03333.003'
//-o '/home/auroua/workspace/matlab/SAR-Data/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD1/15_DEG/COL1/SCENE1/BTR_60/HB033332.jpg' -e -qf

#define MAX_LINE 300

void write_filename(char* dir){
    system(dir);
}

int main(){

    //char* dir = "ls /home/auroua/workspace/matlab/SAR-Data/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TRAIN/17_DEG/BMP2/SN_9566/ > /home/auroua/SN_9566.txt";
    //write_filename(dir);

    //char* input = "/home/auroua/workspace/matlab/SAR-Data/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TRAIN/17_DEG/BMP2/SN_9563/HB03788.000";
    //char* output = "/home/auroua/workspace/matlab/SAR-Data/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TRAIN/17_DEG/BMP2/SN_9563/HB03788.000.JPG ";
    //transform(input,output);

//    char* base_dir = "/home/auroua/workspace/matlab/SAR-Data/MSTAR_Data/MSTAR_PUBLIC_TARGETS_CHIPS_T72_BMP2_BTR70_SLICY/TARGETS/TEST/15_DEG/T72/SN_S7/";
//    char buf[MAX_LINE];  /*缓冲区*/
//    FILE *fp;            /*文件指针*/
//    int len;             /*行字符个数*/
//    int base_dir_len;
//    char* ends = ".jpg";
//
//    if((fp = fopen("/home/auroua/workspace/matlab/SAR-Data/filenames/15_SN_S7.txt","r")) == NULL)
//    {
//        perror("fail to read");
//        exit (1) ;
//    }
//
//    while(fgets(buf,MAX_LINE,fp) != NULL)
//    {
//        len = strlen(buf);
//        char *result = malloc(strlen(base_dir)+len+1);//+1 for the zero-terminator
//        char *result_jpg = malloc(strlen(base_dir)+len+1+4);//+1 for the zero-terminator
//        buf[len-1] = '\0';  /*去掉换行符*/
//        if (result == NULL) exit (1);
//        strcpy(result, base_dir);
//        strcat(result, buf);
//
//        strcpy(result_jpg, result);
//        strcat(result_jpg, ends);
//
//        //printf("%s\n",buf);
//
//        printf("%s\n",result);
//        printf("%s\n",result_jpg);
//
//        transform(result,result_jpg);
//
//        free(result);
//        free(result_jpg);
//    }
    transform("/home/aurora/hdd/workspace/data/mstar/MSTAR_Data/MSTAR_PUBLIC_MIXED_TARGETS_CD2/17_DEG/COL2/SCENE1/ZSU_23_4/HB19491.026", "/home/aurora/hdd/workspace/data/sar_total_data/HB19491.JPG");
    return 0;
}