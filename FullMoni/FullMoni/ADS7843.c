// --------------------------------------------------------------------
// Copylight (C) 2013, Tomoya Sato( http://pub.ne.jp/nacci_tomoya )
//
// This file is part of FullMoni firmwere.
//
// FullMoni is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option ) any later version.
//
// FullMoni is distributed in the hope that it will be useful,
// but WITHIOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FullMoni. if not, see <http:/www.gnu.org/licenses/>.
//
// filename		:	ADS7843.c
// brief		:	FullMoni rev.B �^�b�`�p�l���Ǘ�
// author		:	Tomoya Sato
// update		:	2013/06/16
// version		:	1.03
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// ���[�U�[�w�b�_�t�@�C��
// --------------------------------------------------------------------
#include "iodefine.h"
#include "ADS7843.h"

// --------------------------------------------------------------------
// �O���[�o���ϐ��錾
// --------------------------------------------------------------------
volatile unsigned int g_TouchX, g_TouchY;

// --------------------------------------------------------------------
// �^�b�`�p�l�� ������
// --------------------------------------------------------------------
void Init_ADS7843(void)
{
	// SPI�o�X �A�C�h��
	TP_SPI_SCK_L;
	TP_SPI_CS_H;
	TP_SPI_SO_L;
}

// --------------------------------------------------------------------
// �^�b�`�p�l�� X���l �ǂݍ���
// --------------------------------------------------------------------
unsigned int Touch_SampX(void)
{
	unsigned long dat1;
	unsigned int i, j, dat2;
	
	TP_SPI_SCK_L;
	TP_SPI_CS_L;
	TP_SPI_SO_L;
	
	// 8�r�b�g�o��
	for(i = 0; i < 8; i++)
	{
		if(( 0x94 >> (7 -i)) & 0x1)
		{
			TP_SPI_SO_H;
		}
		else
		{
			TP_SPI_SO_L;
		}
		for( j = 0; j < 50; j++ );
		TP_SPI_SCK_H;
		for( j = 0; j < 50; j++ );
		TP_SPI_SCK_L;
		for( j = 0; j < 50; j++ );
	}
	for(j = 0; j < 1000; j++ );
	// 12�r�b�g����
	dat1 = 0;
	for(i = 0; i < 12; i++)
	{
		dat1 = dat1 << 1;
		
		for( j = 0; j < 50; j++ );
		TP_SPI_SCK_H;
		for( j = 0; j < 50; j++ );
		TP_SPI_SCK_L;
		for( j = 0; j < 50; j++ );
		
		if(TP_SPI_SI)
		{
			dat1 |= 1;
		}
	}
	for(j = 0; j < 100; j++ );
	TP_SPI_CS_H;
	
	dat2 = (((dat1 - 230) * 320)) / (3850 - 230);	// �t�����W�n�ɕϊ�
	if(dat2 > 320) dat2 = 0;						// ���~�b�g

	return dat2;
}

// --------------------------------------------------------------------
// �^�b�`�p�l�� Y���l �ǂݍ���
// --------------------------------------------------------------------
unsigned int Touch_SampY(void)
{
	long dat1;
	unsigned int i, j, dat2;
	
	TP_SPI_SCK_L;
	TP_SPI_CS_L;
	TP_SPI_SO_L;
	
	// 8�r�b�g�o��
	for(i = 0; i < 8; i++)
	{
		if(( 0xd4 >> (7 -i)) & 0x1)
		{
			TP_SPI_SO_H;
		}
		else
		{
			TP_SPI_SO_L;
		}
		for( j = 0; j < 50; j++ );
		TP_SPI_SCK_H;
		for( j = 0; j < 50; j++ );
		TP_SPI_SCK_L;
		for( j = 0; j < 50; j++ );
	}
	for(j = 0; j < 1000; j++ );
	// 12�r�b�g����
	dat1 = 0;
	for(i = 0; i < 12; i++)
	{
		dat1 = dat1 << 1;
		
		for( j = 0; j < 50; j++ );
		TP_SPI_SCK_H;
		for( j = 0; j < 50; j++ );
		TP_SPI_SCK_L;
		for( j = 0; j < 50; j++ );
		
		if(TP_SPI_SI)
		{
			dat1 |= 1;
		}
	}
	for(j = 0; j < 100; j++ );
	TP_SPI_CS_H;
	
	dat2 = (((dat1 - 230) * 240)) / (3850 - 230);	// �t�����W�n�ɕϊ�
	dat2 = (dat2 - 240) * -1;						// �����]
	if(dat2 > 240) dat2 = 0;						// ���~�b�g
	return dat2;
}

// --------------------------------------------------------------------
// �^�b�`�p�l�� �댟�o�h�~�ǂݍ���
// --------------------------------------------------------------------
void Touch_Read(void)
{
//		g_TouchX = Touch_SampX();
//		g_TouchY = Touch_SampY();

	unsigned int i, X[6], Y[6], Xavr, Yavr, Xsum, Ysum, j1, j2;
	int n;
	
	X[0] = Touch_SampX();	Y[0] = Touch_SampY();
	X[1] = Touch_SampX();	Y[1] = Touch_SampY();
	X[2] = Touch_SampX();	Y[2] = Touch_SampY();
	X[3] = Touch_SampX();	Y[3] = Touch_SampY();
	X[4] = Touch_SampX();	Y[4] = Touch_SampY();
	X[5] = Touch_SampX();	Y[5] = Touch_SampY();
	
	Xavr = (X[0] + X[1] + X[2] + X[3] + X[4] + X[5]) / 6;
	Yavr = (Y[0] + Y[1] + Y[2] + Y[3] + Y[4] + Y[5]) / 6;
	
	j1 = 0;
	j2 = 0;
	Xsum = 0;
	Ysum = 0;
	
	for(i = 0; i < 6; i++)
	{
		n = X[i] - Xavr;
		if(abs(n) < 10)
		{
			Xsum = Xsum + X[i];
			j1++;
		}
		n = Y[i] - Yavr;
		if(abs(n) < 10)
		{
			Ysum = Ysum + Y[i];
			j2++;
		}
	}
	if(( j1 <= 3) || ( j2 <= 3))
	{
		g_TouchX = 999;
		g_TouchY = 999;
	}
	else
	{
		g_TouchX = Xsum / j1;
		g_TouchY = Ysum / j2;
	}	
}
