/*
 * Copyright (c) 2016 Thomas Pornin <pornin@bolet.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining 
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be 
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "bearssl.h"

/*
 * A sample server certificate chain with a single intermediate CA.
 * Certificate key type: EC
 * Signing algorithm for both certificates: ECDSA
 */

static const unsigned char CERT0[] = {
	0x30, 0x82, 0x01, 0xB0, 0x30, 0x82, 0x01, 0x56, 0xA0, 0x03, 0x02, 0x01,
	0x02, 0x02, 0x14, 0x1C, 0x4D, 0x00, 0x91, 0x69, 0xE2, 0x46, 0xAC, 0x90,
	0x7C, 0x64, 0x5C, 0x53, 0xF1, 0xFF, 0xB7, 0xC1, 0xCB, 0x6E, 0x7A, 0x30,
	0x0A, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x30,
	0x27, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02,
	0x43, 0x41, 0x31, 0x18, 0x30, 0x16, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13,
	0x0F, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x6D, 0x65, 0x64, 0x69, 0x61, 0x74,
	0x65, 0x20, 0x43, 0x41, 0x30, 0x1E, 0x17, 0x0D, 0x31, 0x30, 0x30, 0x31,
	0x30, 0x31, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x5A, 0x17, 0x0D, 0x33,
	0x37, 0x31, 0x32, 0x33, 0x31, 0x32, 0x33, 0x35, 0x39, 0x35, 0x39, 0x5A,
	0x30, 0x21, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13,
	0x02, 0x43, 0x41, 0x31, 0x12, 0x30, 0x10, 0x06, 0x03, 0x55, 0x04, 0x03,
	0x13, 0x09, 0x6C, 0x6F, 0x63, 0x61, 0x6C, 0x68, 0x6F, 0x73, 0x74, 0x30,
	0x59, 0x30, 0x13, 0x06, 0x07, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02, 0x01,
	0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07, 0x03, 0x42,
	0x00, 0x04, 0x5F, 0x38, 0x9D, 0xA7, 0xFF, 0x4D, 0x8A, 0xAF, 0xF6, 0x34,
	0x39, 0x46, 0x1A, 0xFC, 0x3A, 0xDF, 0xF4, 0x23, 0xAA, 0xA9, 0xEA, 0xFB,
	0xC5, 0x08, 0xDE, 0x00, 0x8E, 0xBE, 0x79, 0xA5, 0x37, 0x58, 0x4C, 0x6D,
	0xDD, 0x01, 0xCA, 0xAB, 0x47, 0xDF, 0x89, 0xB6, 0xC7, 0x17, 0x1F, 0x38,
	0xFC, 0x1D, 0x20, 0x14, 0xDD, 0x45, 0xC0, 0xE0, 0x8F, 0x93, 0x4E, 0x38,
	0x0B, 0xFC, 0xE9, 0x99, 0xA1, 0x49, 0xA3, 0x66, 0x30, 0x64, 0x30, 0x1F,
	0x06, 0x03, 0x55, 0x1D, 0x23, 0x04, 0x18, 0x30, 0x16, 0x80, 0x14, 0xF0,
	0xD0, 0xF1, 0x22, 0xF9, 0x7A, 0x48, 0x17, 0x06, 0x7B, 0x3D, 0xBD, 0xB8,
	0xF5, 0xCD, 0x55, 0x9C, 0x5C, 0x3E, 0x70, 0x30, 0x1D, 0x06, 0x03, 0x55,
	0x1D, 0x0E, 0x04, 0x16, 0x04, 0x14, 0xC3, 0x0E, 0x86, 0xAA, 0x75, 0xB4,
	0x15, 0xC0, 0xE5, 0x95, 0x09, 0x32, 0xBE, 0x5E, 0x92, 0x75, 0xA9, 0xE4,
	0x44, 0x9B, 0x30, 0x0C, 0x06, 0x03, 0x55, 0x1D, 0x13, 0x01, 0x01, 0xFF,
	0x04, 0x02, 0x30, 0x00, 0x30, 0x14, 0x06, 0x03, 0x55, 0x1D, 0x11, 0x04,
	0x0D, 0x30, 0x0B, 0x82, 0x09, 0x6C, 0x6F, 0x63, 0x61, 0x6C, 0x68, 0x6F,
	0x73, 0x74, 0x30, 0x0A, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04,
	0x03, 0x02, 0x03, 0x48, 0x00, 0x30, 0x45, 0x02, 0x21, 0x00, 0x91, 0xFB,
	0xF4, 0x04, 0xD0, 0xE5, 0x2E, 0x01, 0xD4, 0x8C, 0xF0, 0x17, 0x62, 0x0F,
	0xDC, 0xCC, 0x80, 0xCA, 0x18, 0xC4, 0x40, 0x7C, 0x27, 0x03, 0xCB, 0x34,
	0x03, 0x0D, 0x9B, 0xC8, 0x59, 0x4D, 0x02, 0x20, 0x05, 0x55, 0x69, 0xE2,
	0xD8, 0xA1, 0x40, 0x33, 0x34, 0x0E, 0x7E, 0x49, 0x32, 0x64, 0x1D, 0x3F,
	0x6B, 0x1F, 0xD0, 0x2D, 0xB7, 0x2F, 0x52, 0x04, 0x56, 0xAF, 0xD3, 0x37,
	0x8F, 0x87, 0x99, 0xA2
};

static const unsigned char CERT1[] = {
	0x30, 0x82, 0x01, 0xA9, 0x30, 0x82, 0x01, 0x4E, 0xA0, 0x03, 0x02, 0x01,
	0x02, 0x02, 0x14, 0x20, 0xD3, 0xEB, 0xE2, 0x8C, 0xFE, 0xDA, 0xE6, 0xA3,
	0x2C, 0x5E, 0x3B, 0xF2, 0x66, 0x3A, 0x2B, 0x36, 0x7B, 0xB0, 0xCA, 0x30,
	0x0A, 0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x30,
	0x1C, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06, 0x13, 0x02,
	0x43, 0x41, 0x31, 0x0D, 0x30, 0x0B, 0x06, 0x03, 0x55, 0x04, 0x03, 0x13,
	0x04, 0x52, 0x6F, 0x6F, 0x74, 0x30, 0x1E, 0x17, 0x0D, 0x31, 0x30, 0x30,
	0x31, 0x30, 0x31, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x5A, 0x17, 0x0D,
	0x33, 0x37, 0x31, 0x32, 0x33, 0x31, 0x32, 0x33, 0x35, 0x39, 0x35, 0x39,
	0x5A, 0x30, 0x27, 0x31, 0x0B, 0x30, 0x09, 0x06, 0x03, 0x55, 0x04, 0x06,
	0x13, 0x02, 0x43, 0x41, 0x31, 0x18, 0x30, 0x16, 0x06, 0x03, 0x55, 0x04,
	0x03, 0x13, 0x0F, 0x49, 0x6E, 0x74, 0x65, 0x72, 0x6D, 0x65, 0x64, 0x69,
	0x61, 0x74, 0x65, 0x20, 0x43, 0x41, 0x30, 0x59, 0x30, 0x13, 0x06, 0x07,
	0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x02, 0x01, 0x06, 0x08, 0x2A, 0x86, 0x48,
	0xCE, 0x3D, 0x03, 0x01, 0x07, 0x03, 0x42, 0x00, 0x04, 0x70, 0x2E, 0x92,
	0x82, 0x01, 0x17, 0x6C, 0x6D, 0xAB, 0xE1, 0xD1, 0x63, 0x09, 0x48, 0x49,
	0xD2, 0xA6, 0x35, 0x52, 0xD3, 0x3C, 0x73, 0xBB, 0xB2, 0x88, 0x37, 0x98,
	0x87, 0xF1, 0x8D, 0xE0, 0xEC, 0x65, 0x9A, 0x0E, 0x13, 0xF5, 0xED, 0x91,
	0x61, 0xC8, 0xB6, 0x6D, 0x33, 0x84, 0x6E, 0xAE, 0x8E, 0x55, 0x80, 0xCD,
	0x49, 0x9E, 0x07, 0xBF, 0xD0, 0xAE, 0x9D, 0xE6, 0xD0, 0xB3, 0x27, 0x16,
	0xA1, 0xA3, 0x63, 0x30, 0x61, 0x30, 0x1F, 0x06, 0x03, 0x55, 0x1D, 0x23,
	0x04, 0x18, 0x30, 0x16, 0x80, 0x14, 0x95, 0x41, 0xB4, 0xE2, 0x67, 0xAA,
	0xF1, 0x7F, 0xBC, 0x8F, 0x79, 0xF3, 0x68, 0x14, 0x5A, 0x6B, 0x92, 0x16,
	0xA2, 0x40, 0x30, 0x1D, 0x06, 0x03, 0x55, 0x1D, 0x0E, 0x04, 0x16, 0x04,
	0x14, 0xF0, 0xD0, 0xF1, 0x22, 0xF9, 0x7A, 0x48, 0x17, 0x06, 0x7B, 0x3D,
	0xBD, 0xB8, 0xF5, 0xCD, 0x55, 0x9C, 0x5C, 0x3E, 0x70, 0x30, 0x0E, 0x06,
	0x03, 0x55, 0x1D, 0x0F, 0x01, 0x01, 0xFF, 0x04, 0x04, 0x03, 0x02, 0x00,
	0x86, 0x30, 0x0F, 0x06, 0x03, 0x55, 0x1D, 0x13, 0x01, 0x01, 0xFF, 0x04,
	0x05, 0x30, 0x03, 0x01, 0x01, 0xFF, 0x30, 0x0A, 0x06, 0x08, 0x2A, 0x86,
	0x48, 0xCE, 0x3D, 0x04, 0x03, 0x02, 0x03, 0x49, 0x00, 0x30, 0x46, 0x02,
	0x21, 0x00, 0x85, 0xE3, 0x46, 0x68, 0x99, 0xD6, 0x02, 0x7A, 0x59, 0x66,
	0x1C, 0xB7, 0x4F, 0x35, 0x2D, 0x08, 0x36, 0x38, 0x61, 0x7E, 0x05, 0x48,
	0xD8, 0x69, 0x43, 0x1F, 0xEB, 0x56, 0xE9, 0xAD, 0x06, 0x0E, 0x02, 0x21,
	0x00, 0x82, 0x70, 0xB4, 0x62, 0x03, 0x49, 0x46, 0xC8, 0x54, 0x59, 0x05,
	0xD9, 0x78, 0xDB, 0x53, 0x1C, 0xE0, 0x6E, 0x66, 0xF5, 0x0F, 0x14, 0x3B,
	0xC9, 0x2D, 0x38, 0x12, 0x70, 0x91, 0x56, 0xF9, 0xA9
};

static const br_x509_certificate CHAIN[] = {
	{ (unsigned char *)CERT0, sizeof CERT0 },
	{ (unsigned char *)CERT1, sizeof CERT1 }
};

#define CHAIN_LEN   2
