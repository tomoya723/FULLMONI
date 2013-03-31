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
// filename		:	CAN2515.c
// brief		:	FullMoni rev.B CAN�Ǘ�
// author		:	Tomoya Sato
// update		:	2013/03/31
// version		:	1.02
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// ���[�U�[�w�b�_�t�@�C��
// --------------------------------------------------------------------
#include "iodefine.h"
#include "CAN2515.h"
#include "spi.h"

// --------------------------------------------------------------------
// MPC2515������
// --------------------------------------------------------------------
void CANInit(unsigned char brp)
{
	unsigned char reg;
	
	CAN_SPI_CS_H;
	
	CANReset();
	
	CANSetOpMode(CAM_MODE_CONFIG);
	
	reg = 64 + brp;
	CANWriteReg(CAN_CNF1, reg);
	
	reg = 0x92;
	CANWriteReg(CAN_CNF2, reg);
	
	reg = 0x02;
	CANWriteReg(CAN_CNF3, reg);
	
//	CANSetOpMode(CAM_MODE_NORMAL);
//	CANSetOpMode(CAM_MODE_LISTEN);
}


// --------------------------------------------------------------------
// CAN��M�`�F�b�N
// --------------------------------------------------------------------
unsigned char CANRxCheck(unsigned char rxbnum)
{
	unsigned char rxstat;
	
	rxstat = CANReadRXStat();			// ��M�X�e�[�^�X�擾
	
	if(rxbnum == 0)
	{
		return rxstat & 1<<MsgInRXB0;
	}
	else if(rxbnum == 1)
	{
		return rxstat & 1<<MsgInRXB1;
	}
	
	return rxstat & ( (1<<MsgInRXB0) | (1<<MsgInRXB1) );
}


// --------------------------------------------------------------------
// CAN���Z�b�g
// --------------------------------------------------------------------
void CANReset(void)
{
	CAN_SPI_CS_L;
	
	SPI_TxRx(SPI_INST_RESET);		// ���Z�b�g
	
	CAN_SPI_CS_H;
}


// --------------------------------------------------------------------
// CAN���W�X�^ �o�C�g�E���C�g
// --------------------------------------------------------------------
void CANWriteReg(unsigned char adrs, unsigned char data)
{
	CAN_SPI_CS_L;
	
	SPI_TxRx(SPI_INST_WRITE);		// �o�C�g�E���C�g
	SPI_TxRx(adrs);
	SPI_TxRx(data);
	
	CAN_SPI_CS_H;
}

// --------------------------------------------------------------------
// CAN���W�X�^�E���[�h
// �X�e�[�^�X�E���[�h
// ��M�X�e�[�^�X�E���[�h  (3�@�\���p���[�`��)
// --------------------------------------------------------------------
unsigned char CANRegRead2B(unsigned char inst, unsigned char adrs)
{
	unsigned char dat;
	
	CAN_SPI_CS_L;
	
	// 2�o�C�g�o��(�f�[�^���͖͂���)
	SPI_TxRx(inst);			// �C���X�g���N�V����
	SPI_TxRx(adrs);
	
	// �f�[�^����(�X�e�[�^�X�̏ꍇ�́A2��ڂ̃��s�[�g�f�[�^)
	dat = 0;
	dat = SPI_TxRx(0xFF);
	
	CAN_SPI_CS_H;
	
	return dat;
}

#ifndef CANSetSidFilteMask
// --------------------------------------------------------------------
// CAN SID �t�B���^�A�}�X�N�ݒ� (���p���[�`��)
// --------------------------------------------------------------------
void CANSetSidFilteMask(unsigned char adrs, unsigned int sid)
{
	CANWriteReg(adrs, (unsigned char)(sid>>3));			// HIGH
	CANWriteReg(adrs + 1, (unsigned char)(sid<<5));		// LOW
}
#endif


// --------------------------------------------------------------------
// CAN�r�b�g�E���f�t�@�C�E�R�}���h
// --------------------------------------------------------------------
void CANBitModCmd(unsigned char adrs, unsigned char mask, unsigned char data)
{
	CAN_SPI_CS_L;
	
	SPI_TxRx(SPI_INST_BIT_MOD);			// �r�b�g�E���f�t�@�C
	SPI_TxRx(adrs);
	SPI_TxRx(mask);
	SPI_TxRx(data);
	
	CAN_SPI_CS_H;
}


// --------------------------------------------------------------------
// CAN���^��M�o�b�t�@ �V�[�P���V�����E���[�h�^���C�g (���p���[�`��)
// --------------------------------------------------------------------
void CANTxRxBufRW(unsigned char inst, unsigned char readop, unsigned char *data, unsigned char cnt)
{
	unsigned char dat;
	unsigned char p;
	
	CAN_SPI_CS_L;
	
	// �C���X�g���N�V�����̑��M
	SPI_TxRx(inst);
	
	// =============== ���M/��M�o�b�t�@���e�̑���M =================
	if(readop)
	{
		// �f�[�^��M
		for(p = 0; p < cnt; p++)
		{
			dat = 0;
			dat = SPI_TxRx(0xFF);
			data[p] = dat;
		}
	}
	else
	{
		// �f�[�^���M
		for(p = 0; p < cnt; p++)
		{
			dat = data[p];
			SPI_TxRx(dat);
		}
	}
	
	CAN_SPI_CS_H;
}
