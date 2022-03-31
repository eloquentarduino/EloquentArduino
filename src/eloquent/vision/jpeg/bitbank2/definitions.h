//
// Created by Simone on 25/03/2022.
//

#pragma once

//
// JPEG Encoder
//
// written by Larry Bank
// bitbank@pobox.com
// Arduino port started 7/22/2021
// Original JPEG code written 20+ years ago :)
// The goal of this code is to encode JPEG images on embedded systems
//
// Copyright 2021 BitBank Software, Inc. All Rights Reserved.
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//    http://www.apache.org/licenses/LICENSE-2.0
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//===========================================================================
//
#ifndef __JPEGENC__
#define __JPEGENC__
#if defined( MICROPY_PY_SENSOR ) || defined( __MACH__ ) || defined( __LINUX__ ) || defined( __MCUXPRESSO )
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#define memcpy_P memcpy
#define PROGMEM
#else
#include <Arduino.h>
#endif
//
// JPEG Encoder
// Written by Larry Bank
// Copyright (c) 2021 BitBank Software, Inc.
//
// Designed to encode JPEG files from source images (8 or 24 bpp)
// using less than 20K of RAM
//
#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

/* Defines and variables */
#define JPEG_FILE_BUF_SIZE 2048

#define DCTSIZE 64

#if (INTPTR_MAX == INT64_MAX)
#define REGISTER_WIDTH 64
#define BIGINT int64_t
#define BIGUINT uint64_t
// structure for outputting variable length codes
typedef struct pil_code_tag
{
    unsigned char *pOut; // current output pointer
    int64_t iLen;  // length of data in accumulator
    uint64_t ulAcc; // code accumulator (holds codes until at least 64-bits ready to write
} PIL_CODE;
#define STORECODE(pOut, iLen, ulCode, ulAcc, iNewLen) \
        if (iLen+iNewLen > 64) \
                                                { uint64_t ul1, ul2 = ulAcc | (ulCode >> (iLen+iNewLen-64)); \
        ul1 = ul2 & (ul2 >> 4); ul1 &= (ul1 >> 2); ul1 &= (ul1 >> 1);  ul1 &= 0x0101010101010101; \
    if (ul1 == 0) \
        {*(uint64_t *)pOut = __builtin_bswap64(ul2); pOut += 8; \
     iLen -= 64; ulAcc = 0;} else \
        {while (iLen >= 8) \
            {unsigned char c = (unsigned char)(ulAcc >> 56); *pOut++ = c; \
            if (c == 0xff) { *pOut++ = 0;} ulAcc <<= 8; iLen -= 8; }}} \
        iLen += iNewLen; ulAcc |= (ulCode << (64-iLen));
#else
#define REGISTER_WIDTH 32
#define BIGINT int32_t
#define BIGUINT uint32_t
// structure for outputting variable length codes
typedef struct pil_code_tag
{
unsigned char *pOut; // current output pointer
int32_t iLen;  // length of data in accumulator
uint32_t ulAcc; // code accumulator (holds codes until at least 32-bits ready to write
} PIL_CODE;
// 32-bit output stage assumes that unaligned writes are not allowed
#define STORECODE(pOut, iLen, ulCode, ulAcc, iNewLen) \
        if (iLen+iNewLen > 32) { while (iLen >= 8) \
                        {unsigned char c = (unsigned char)(ulAcc >> 24); *pOut++ = c; \
        if (c == 0xff) { *pOut++ = 0;} ulAcc <<= 8; iLen -= 8; }} \
        iLen += iNewLen; ulAcc |= (ulCode << (32-iLen));
#endif

#define WRITEMOTO32(p, o, val) {uint32_t l = val; p[o] = (unsigned char)(l >> 24); p[o+1] = (unsigned char)(l >> 16); p[o+2] = (unsigned char)(l >> 8); p[o+3] = (unsigned char)l;}
#define WRITEMOTO16(p, o, val) {uint32_t l = val; p[o] = (unsigned char)(l >> 8); p[o+1] = (unsigned char)l;}

// Error codes returned by getLastError()
enum {
    JPEG_SUCCESS = 0,
    JPEG_INVALID_PARAMETER,
    JPEG_ENCODE_ERROR,
    JPEG_MEM_ERROR,
    JPEG_NO_BUFFER,
    JPEG_UNSUPPORTED_FEATURE,
    JPEG_INVALID_FILE
};
// Subsample types
enum {
    JPEG_SUBSAMPLE_444 = 0,
    JPEG_SUBSAMPLE_420
};

// Pixel types
enum {
    JPEG_PIXEL_GRAYSCALE = 0,
    JPEG_PIXEL_RGB565,
    JPEG_PIXEL_RGB888,
    JPEG_PIXEL_ARGB8888,
    JPEG_PIXEL_COUNT
};
// Compression quality
enum {
    JPEG_Q_BEST = 0,
    JPEG_Q_HIGH,
    JPEG_Q_MED,
    JPEG_Q_LOW
};

typedef struct jpeg_file_tag
{
    int32_t iPos; // current file position
    int32_t iSize; // file size
    uint8_t *pData; // memory file pointer
} JPEGFILE;

typedef int32_t (JPEG_WRITE_CALLBACK)(JPEGFILE *pFile, uint8_t *pBuf, int32_t iLen);

//
// our private structure to hold a JPEG image encode state
//
typedef struct jpeg_image_tag
{
    int iWidth, iHeight; // image size
    int iMCUWidth, iMCUHeight; // number of horizontal and vertical MCUs
    int x, y; // current MCU x/y
    uint8_t ucPixelType, ucSubSample, ucNumComponents;
    uint8_t ucMemType;
    uint8_t *pOutput, *pHighWater;
    int iBufferSize; // output buffer size provided by caller
    int iHeaderSize; // size of the PNG header
    int iCompressedSize; // size of flate output
    int iDataSize; // total output file size
    int iPitch; // bytes per line
    int iError;
    int iRestart; // current restart counter
    int iDCPred0, iDCPred1, iDCPred2; // DC predictor values for the 3 color components
    PIL_CODE pc;
    int *huffdc[2];
    signed short sQuantTable[DCTSIZE*4];
    signed char MCUc[6*DCTSIZE]; // captured image data
    signed short MCUs[DCTSIZE]; // final processed output
    JPEG_WRITE_CALLBACK *pfnWrite;
//    uint8_t ucHuffACDCBuf[4096]; // moved to FLASH
    JPEGFILE JPEGFile;
    uint8_t ucFileBuf[JPEG_FILE_BUF_SIZE]; // holds temp file data
} JPEGIMAGE;

typedef struct jpegencode_t
{
    int x, y; // current encoding position
    int cx, cy; // current width+height of the MCU
} JPEGENCODE;

#define JPEG_STATIC static

// Due to unaligned memory causing an exception, we have to do these macros the slow way
#define INTELSHORT(p) ((*p) + (*(p+1)<<8))
#define INTELLONG(p) ((*p) + (*(p+1)<<8) + (*(p+2)<<16) + (*(p+3)<<24))
#define MOTOSHORT(p) (((*(p))<<8) + (*(p+1)))
#define MOTOLONG(p) (((*p)<<24) + ((*(p+1))<<16) + ((*(p+2))<<8) + (*(p+3)))

#endif