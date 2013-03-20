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
// filename		:	CAN2515.h
// brief		:	FullMoni rev.B CAN�Ǘ�
// author		:	Tomoya Sato
// update		:	2013/03/20
// version		:	1.01
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// ���d�C���N���[�h�h�~
// --------------------------------------------------------------------
#ifndef _CAN2515_H_
#define _CAN2515_H_

// --------------------------------------------------------------------
// SPI�|�[�g �r�b�g����
// --------------------------------------------------------------------
#define CAN_SPI_CS_H	CAN_SPI_CS_PORT|=(1<<CAN_SPI_CS_BIT)
#define CAN_SPI_CS_L	CAN_SPI_CS_PORT&=~(1<<CAN_SPI_CS_BIT)

// --------------------------------------------------------------------
// CAN�r�b�g���[�g
// --------------------------------------------------------------------
#define CAN_BRP_20MHz_1MBPS		0			// FOSC=20MHz
#define CAN_BRP_20MHz_500KBPS	1			// FOSC=20MHz
#define CAN_BRP_20MHz_250KBPS	3			// FOSC=20MHz
#define CAN_BRP_20MHz_125KBPS	4			// FOSC=20MHz

// --------------------------------------------------------------------
// SPI�R�}���h �C���X�g���N�V����
// --------------------------------------------------------------------
#define SPI_INST_RESET		0xC0
#define SPI_INST_READ		0x03
#define SPI_INST_WRITE		0x02
#define SPI_INST_RD_RXBUF	0xC0
#define SPI_INST_LD_TXBUF	0x40
#define SPI_INST_RTS		0x80
#define SPI_INST_RD_STAT	0xA0
#define SPI_INST_RX_STAT	0xB0
#define SPI_INST_BIT_MOD	0x05

// --------------------------------------------------------------------
// ���^��M�o�b�t�@ �V�[�P���V�����E���[�h�^���C�g �C���X�g���N�V����
// --------------------------------------------------------------------
#define RD_RXBUF_RXB0SIDH	0x90
#define RD_RXBUF_RXB0D0		0x92
#define RD_RXBUF_RXB1SIDH	0x94
#define RD_RXBUF_RXB1D0		0x96
#define LD_TXBUF_TXB0SIDH	0x40
#define LD_TXBUF_TXB0D0		0x41
#define LD_TXBUF_TXB1SIDH	0x42
#define LD_TXBUF_TXB1D0		0x43
#define LD_TXBUF_TXB2SIDH	0x44
#define LD_TXBUF_TXB2D0		0x45

// --------------------------------------------------------------------
// CAN �h���C�o�i�}�N���j
// --------------------------------------------------------------------
// --------------------------------------------------------------------
// CAN�I�y���[�V�����E���[�h�ݒ�
// --------------------------------------------------------------------
#define CANSetOpMode(mode) CANBitModCmd(CANCTRL, 7<<5, mode<<5)

// --------------------------------------------------------------------
// ���荞�݋��ݒ�
// --------------------------------------------------------------------
#define RX0IE_Enable CANBitModCmd(CANINTE, 0x01, 0x01)
#define RX0IE_Disable CANBitModCmd(CANINTE, 0x01, 0x00)
#define RX1IE_Enable CANBitModCmd(CANINTE, 0x02, 0x02)
#define RX1IE_Disable CANBitModCmd(CANINTE, 0x02, 0x00)
#define TX0IE_Enable CANBitModCmd(CANINTE, 0x04, 0x04)
#define TX0IE_Disable CANBitModCmd(CANINTE, 0x04, 0x00)
#define TX1IE_Enable CANBitModCmd(CANINTE, 0x08, 0x08)
#define TX1IE_Disable CANBitModCmd(CANINTE, 0x08, 0x00)
#define TX2IE_Enable CANBitModCmd(CANINTE, 0x10, 0x10)
#define TX2IE_Disable CANBitModCmd(CANINTE, 0x10, 0x00)
#define ERRIE_Enable CANBitModCmd(CANINTE, 0x20, 0x20)
#define ERRIE_Disable CANBitModCmd(CANINTE, 0x20, 0x00)
#define WAKIE_Enable CANBitModCmd(CANINTE, 0x40, 0x40)
#define WAKIE_Disable CANBitModCmd(CANINTE, 0x40, 0x00)
#define MERRE_Enable CANBitModCmd(CANINTE, 0x80, 0x80)
#define MERRE_Disable CANBitModCmd(CANINTE, 0x80, 0x00)

// --------------------------------------------------------------------
// ���荞�݃t���O�N���A
// --------------------------------------------------------------------
#define RX0IF_Clear CANBitModCmd(CANINTF, 0x01, 0x00)
#define RX1IF_Clear CANBitModCmd(CANINTF, 0x02, 0x00)
#define TX0IF_Clear CANBitModCmd(CANINTF, 0x04, 0x00)
#define TX1IF_Clear CANBitModCmd(CANINTF, 0x08, 0x00)
#define TX2IF_Clear CANBitModCmd(CANINTF, 0x10, 0x00)
#define ERRIF_Clear CANBitModCmd(CANINTF, 0x20, 0x00)
#define WAKIF_Clear CANBitModCmd(CANINTF, 0x40, 0x00)
#define MERRF_Clear CANBitModCmd(CANINTF, 0x80, 0x00)

#define RX0OVR_Clear CANBitModCmd(EFLG, 0x40, 0x00);
#define RX1OVR_Clear CANBitModCmd(EFLG, 0x80, 0x00);


// --------------------------------------------------------------------
// �G���[�J�E���^�N���A
// --------------------------------------------------------------------
#define TEC_Clear CANBitModCmd(TEC, 0xFF, 0x00)
#define REC_Clear CANBitModCmd(REC, 0xFF, 0x00)

// --------------------------------------------------------------------
// �I�y���[�V�����E���[�h CANCTRL/CANSTAT
// --------------------------------------------------------------------
#define CAM_MODE_NORMAL		0
#define CAM_MODE_SLEEP		1
#define CAM_MODE_LOOPBACK	2
#define CAM_MODE_LISTEN		3
#define CAM_MODE_CONFIG		4

// --------------------------------------------------------------------
// ���W�X�^ �o�C�g�E���[�h
// --------------------------------------------------------------------
#define CANReadReg(adrs) CANRegRead2B(SPI_INST_READ, adrs)

// --------------------------------------------------------------------
// �X�e�[�^�X�E���[�h
// --------------------------------------------------------------------
#define CANReadStat() CANRegRead2B(SPI_INST_RD_STAT, 0)

// --------------------------------------------------------------------
// ��M�X�e�[�^�X�E���[�h
// --------------------------------------------------------------------
#define CANReadRXStat() CANRegRead2B(SPI_INST_RX_STAT, 0)

// --------------------------------------------------------------------
// �t�B���^�E���[�h�̐ݒ�
// --------------------------------------------------------------------
#define CANSetFilterRxB0(mode) CANWriteReg(RXB0CTRL, mode<<5)
#define CANSetFilterRxB1(mode) CANWriteReg(RXB1CTRL, mode<<5)
// --------------------------------------------------------------------
// mode
// --------------------------------------------------------------------
#define FILTER_MOD_ALL_HIT 3		// �}�X�N�A�t�B���^�g�p����
#define FILTER_MOD_SID_HIT 1		// SID�Ń}�X�N�A�t�B���^�K�p


// --------------------------------------------------------------------
// ��M�o�b�t�@ �V�[�P���V�����E���[�h
// --------------------------------------------------------------------
#define CANRxB0MsgRead(buf) CANTxRxBufRW(RD_RXBUF_RXB0SIDH, 1, buf, 5)
#define CANRxB1MsgRead(buf) CANTxRxBufRW(RD_RXBUF_RXB1SIDH, 1, buf, 5)
#define CANRxB0DatRead(buf) CANTxRxBufRW(RD_RXBUF_RXB0D0, 1, buf, 8)
#define CANRxB1DatRead(buf) CANTxRxBufRW(RD_RXBUF_RXB1D0, 1, buf, 8)

// --------------------------------------------------------------------
// ��M�o�b�t�@ �V�[�P���V�����E���[�h(���b�Z�[�W�{�f�[�^)
// --------------------------------------------------------------------
#define CANRxB0Read(buf, dsiz) CANTxRxBufRW(RD_RXBUF_RXB0SIDH, 1, buf, 5+dsiz)
#define CANRxB1Read(buf, dsiz) CANTxRxBufRW(RD_RXBUF_RXB1SIDH, 1, buf, 5+dsiz)


// --------------------------------------------------------------------
// ���M�o�b�t�@ �V�[�P���V�����E���C�g
// --------------------------------------------------------------------
#define CANTxB0MsgWrite(buf) CANTxRxBufRW(LD_TXBUF_TXB0SIDH, 0, buf, 5)
#define CANTxB1MsgWrite(buf) CANTxRxBufRW(LD_TXBUF_TXB1SIDH, 0, buf, 5)
#define CANTxB2MsgWrite(buf) CANTxRxBufRW(LD_TXBUF_TXB2SIDH, 0, buf, 5)
#define CANTxB0DatWrite(buf) CANTxRxBufRW(LD_TXBUF_TXB0D0, 0, buf, 8)
#define CANTxB1DatWrite(buf) CANTxRxBufRW(LD_TXBUF_TXB1D0, 0, buf, 8)
#define CANTxB2DatWrite(buf) CANTxRxBufRW(LD_TXBUF_TXB2D0, 0, buf, 8)

// --------------------------------------------------------------------
// ���M�o�b�t�@ �V�[�P���V�����E���C�g(���b�Z�[�W�{�f�[�^)
// --------------------------------------------------------------------
#define CANTxB0Write(buf, dsiz) CANTxRxBufRW(LD_TXBUF_TXB0SIDH, 0, buf, 5+dsiz)
#define CANTxB1Write(buf, dsiz) CANTxRxBufRW(LD_TXBUF_TXB1SIDH, 0, buf, 5+dsiz)
#define CANTxB2Write(buf, dsiz) CANTxRxBufRW(LD_TXBUF_TXB2SIDH, 0, buf, 5+dsiz)


// --------------------------------------------------------------------
// �t�B���^SID�ݒ�
// --------------------------------------------------------------------
#define CANSetSidFilter0(sid) CANSetSidFilteMask(RXF0SIDH, sid)
#define CANSetSidFilter1(sid) CANSetSidFilteMask(RXF1SIDH, sid)
#define CANSetSidFilter2(sid) CANSetSidFilteMask(RXF2SIDH, sid)
#define CANSetSidFilter3(sid) CANSetSidFilteMask(RXF3SIDH, sid)
#define CANSetSidFilter4(sid) CANSetSidFilteMask(RXF4SIDH, sid)
#define CANSetSidFilter5(sid) CANSetSidFilteMask(RXF5SIDH, sid)

// --------------------------------------------------------------------
// �}�X�NSID�ݒ�
// --------------------------------------------------------------------
#define CANSetSidMask0(sid) CANSetSidFilteMask(RXM0SIDH, sid)
#define CANSetSidMask1(sid) CANSetSidFilteMask(RXM1SIDH, sid)

#define MASK_SID_ALL_HIT   0x0000		// ���ׂă}�X�N
#define MASK_SID_CPL_MATCH 0x07FF		// �}�X�N���� ���S��v

// --------------------------------------------------------------------
// SID���W�X�^�l����}�N��
// --------------------------------------------------------------------
#define GET_SIDH(msg) (unsigned char)(msg >> 3)
#define GET_SIDL(msg) (unsigned char)(msg << 5)
#define MAKE_SID(sid_h, sid_l) ((unsigned int)sid_h<<3)|(sid_l>>5)


// --------------------------------------------------------------------
// SPI�R�}���h ��M�X�e�[�^�X�\��(��M�X�e�[�^�X�E���[�h�E�R�}���h)
// --------------------------------------------------------------------
struct tag_RXSTAT
{
	unsigned char FilterMatch:3;	// b0-b2 �q�b�g�����t�B���^�̔ԍ�
	unsigned char RemoteFrm:1;		// b3 (1)�����[�g�E�t���[��/(0)�f�[�^�E�t���[��
	unsigned char ExtMsg:1;			// b4 (1)�g��ID/(0)�W��ID
	unsigned char b5:1;				// b5
	unsigned char MsgInRXB0:1;		// b6 RXB0�Ƀ��b�Z�[�W����
	unsigned char MsgInRXB1:1;		// b7 RXB1�Ƀ��b�Z�[�W����
};

enum t_RXSTAT
{
	FilterMatch0 = 0,		// b0 �q�b�g�����t�B���^�̔ԍ�
	FilterMatch1 = 1,		// b1 �q�b�g�����t�B���^�̔ԍ�
	FilterMatch2 = 2,		// b2 �q�b�g�����t�B���^�̔ԍ�
	RemoteFrm = 3,			// b3 (1)�����[�g�E�t���[��/(0)�f�[�^�E�t���[��
	ExtMsg = 4,				// b4 (1)�g��ID/(0)�W��ID
//	b5 = 5,					// b5
	MsgInRXB0 = 6,			// b6 RXB0�Ƀ��b�Z�[�W����
	MsgInRXB1 = 7			// b7 RXB1�Ƀ��b�Z�[�W����
};



// --------------------------------------------------------------------
// �v���g�^�C�v�錾
// --------------------------------------------------------------------
void CANInit(unsigned char brp);
unsigned char CANRxCheck(unsigned char rxbnum);
void CANReset(void);
void CANWriteReg(unsigned char adrs, unsigned char data);
unsigned char CANRegRead2B(unsigned char inst, unsigned char adrs);
void CANSetSidFilteMask(unsigned char adrs, unsigned int sid);
void CANBitModCmd(unsigned char adrs, unsigned char mask, unsigned char data);
void CANTxRxBufRW(unsigned char inst, unsigned char readop, unsigned char *data, unsigned char cnt);
void CANSetSidFilteMask(unsigned char adrs, unsigned int sid);

// --------------------------------------------------------------------
// MCP2515 ���W�X�^�\���̃^�O
// --------------------------------------------------------------------
// --------------------------------------------------------------------
// CNF1 �R���t�B�M�����[�V����1���W�X�^ (0x2A)
// --------------------------------------------------------------------
struct tag_CNF1
{
	unsigned char BRP:6;		// b0-b5
	unsigned char SJW0:1;		// b6
	unsigned char SJW1:1;		// b7
};

// --------------------------------------------------------------------
// CNF2 �R���t�B�M�����[�V����2���W�X�^ (0x29)
// --------------------------------------------------------------------
struct tag_CNF2
{
	unsigned char PRSEG:3;		// b0-b2
	unsigned char PHSEG1:3;		// b3-b5
	unsigned char SAM:1;		// b6
	unsigned char BTLMODE:1;	// b7
};

// --------------------------------------------------------------------
// CNF3 �R���t�B�M�����[�V����3���W�X�^ (0x28)
// --------------------------------------------------------------------
struct tag_CNF3
{
	unsigned char PHSEG2:3;		// b0-b2
	unsigned char b3:1;			// b3
	unsigned char b4:1;			// b4
	unsigned char b5:1;			// b5
	unsigned char WAKFIL:1;		// b6
	unsigned char SOF:1;		// b7
};

// --------------------------------------------------------------------
// CANCTRL CAN�R���g���[���E���W�X�^ (0xXF)
// --------------------------------------------------------------------
struct tag_CANCTRL
{
	unsigned char CLKPRE:2;		// b0-b1
	unsigned char CLKEN:1;		// b2
	unsigned char OSM:1;		// b3
	unsigned char ABAT:1;		// b4
	unsigned char REQOP:3;		// b5-b7
};

// --------------------------------------------------------------------
// CANSTAT CAN�X�e�[�^�X�E���W�X�^ (0xXE)
// --------------------------------------------------------------------
struct tag_CANSTAT
{
	unsigned char b0:1;			// b0
	unsigned char ICOD:3;		// b1-b3
	unsigned char b4:1;			// b4
	unsigned char OPMOD:3;		// b5-b7
};

// --------------------------------------------------------------------
// CANINTE ���荞�݋����W�X�^ (0x2B)
// --------------------------------------------------------------------
struct tag_CANINTE
{
	unsigned char RX0IE:1;		// b0
	unsigned char RX1IE:1;		// b1
	unsigned char TX0IE:1;		// b2
	unsigned char TX1IE:1;		// b3
	unsigned char TX2IE:1;		// b4
	unsigned char ERRIE:1;		// b5
	unsigned char WAKIE:1;		// b6
	unsigned char MERRE:1;		// b7
};

// --------------------------------------------------------------------
// CANINTF ���荞�݃t���O�E���W�X�^ (0x2C)
// --------------------------------------------------------------------
struct tag_CANINTF
{
	unsigned char RX0IF:1;		// b0
	unsigned char RX1IF:1;		// b1
	unsigned char TX0IF:1;		// b2
	unsigned char TX1IF:1;		// b3
	unsigned char TX2IF:1;		// b4
	unsigned char ERRIF:1;		// b5
	unsigned char WAKIF:1;		// b6
	unsigned char MERRF:1;		// b7
};

// --------------------------------------------------------------------
// EFLG �G���[�E�t���O (0x2D)
// --------------------------------------------------------------------
struct tag_EFLG
{
	unsigned char EWARN:1;		// b0
	unsigned char RXWAR:1;		// b1
	unsigned char TXWAR:1;		// b2
	unsigned char RXEP:1;		// b3
	unsigned char TXEP:1;		// b4
	unsigned char TXBO:1;		// b5
	unsigned char RX0OVR:1;		// b6
	unsigned char RX1OVR:1;		// b7
};

// --------------------------------------------------------------------
// TXBnCTRL ���M�o�b�t�@n �R���g���[���E���W�X�^ (n = 0, 1, 2) (0x30, 0x40, 0x50)
// --------------------------------------------------------------------
struct tag_TXBnCTRL
{
	unsigned char TXP:2;		// b0-b1
	unsigned char b2:1;			// b2
	unsigned char TXREQ:1;		// b3
	unsigned char TXERR:1;		// b4
	unsigned char MLOA:1;		// b5
	unsigned char ABTF:1;		// b6
	unsigned char b7:1;			// b7
};

// --------------------------------------------------------------------
// TXBnDLC ���M�o�b�t�@n DLC���W�X�^(n = 0, 1, 2) (0x35, 0x45, 0x55)
// --------------------------------------------------------------------
struct tag_TXBnDLC
{
	unsigned char	DLC:4;		// b0-b3
	unsigned char	b4:1;		// b4
	unsigned char	b5:1;		// b5
	unsigned char	RTR:1;		// b6
	unsigned char	b7:1;		// b7
};

// --------------------------------------------------------------------
// RXB0CTRL ��M�o�b�t�@0 �R���g���[���E���W�X�^ (0x60)
// --------------------------------------------------------------------
struct tag_RXB0CTRL
{
	unsigned char FILHIT0:1;	// b0
	unsigned char BUKT1:1;		// b1
	unsigned char BUKT:1;		// b2
	unsigned char RXRTR:1;		// b3
	unsigned char b4:1;			// b4
	unsigned char RXM:2;		// b5-b6
	unsigned char b7:1;			// b7
};

// --------------------------------------------------------------------
// RXBnDLC ��M�o�b�t�@n DLC���W�X�^(n = 0, 1) (0x65, 0x75)
// --------------------------------------------------------------------
struct tag_RXBnDLC
{
	unsigned char DLC:4;		// b0-b3
	unsigned char RB0:1;		// b4
	unsigned char RB1:1;		// b5
	unsigned char RTR:1;		// b6
	unsigned char b7:1;			// b7
};

// --------------------------------------------------------------------
// RXB1CTRL ��M�o�b�t�@1 �R���g���[���E���W�X�^ (0x70)
// --------------------------------------------------------------------
struct tag_RXB1CTRL
{
	unsigned char FILHIT:3;		// b0-b2
	unsigned char RXRTR:1;		// b3
	unsigned char b4:1;			// b4
	unsigned char RXM:2;		// b5-b6
	unsigned char b7:1;			// b7
};

// --------------------------------------------------------------------
// ���W�X�^�E�A�h���X
// --------------------------------------------------------------------
#define CAN_CNF1	0x2A		// �R���t�B�M�����[�V����1���W�X�^
#define CAN_CNF2	0x29		// �R���t�B�M�����[�V����2���W�X�^
#define CAN_CNF3	0x28		// �R���t�B�M�����[�V����3���W�X�^
#define CANCTRL		0x0F		// CAN�R���g���[���E���W�X�^
#define CANSTAT		0x0E		// CAN�X�e�[�^�X�E���W�X�^
#define CANINTE		0x2B		// ���荞�݋����W�X�^
#define CANINTF		0x2C		// ���荞�݃t���O�E���W�X�^
#define EFLG		0x2D		// �G���[�E�t���O

// --------------------------------------------------------------------
// ���M�o�b�t�@0
// --------------------------------------------------------------------
#define TXB0CTRL	0x30		// ���M�o�b�t�@0 �R���g���[���E���W�X�^
#define TXB0SIDH	0x31		// ���M�o�b�t�@0 �W��ID HIGH
#define TXB0SIDL	0x32		// ���M�o�b�t�@0 �W��ID LOW
#define TXB0EID8	0x33		// ���M�o�b�t�@0 �g��ID HIGH
#define TXB0EID0	0x34		// ���M�o�b�t�@0 �g��ID LOW
#define TXB0DLC		0x35		// ���M�o�b�t�@0 DLC (�f�[�^���R�[�h)���W�X�^
#define TXB0D0		0x36		// ���M�o�b�t�@0 D0(�擪�A�h���X)

// --------------------------------------------------------------------
// ���M�o�b�t�@1
// --------------------------------------------------------------------
#define TXB1CTRL	0x40		// ���M�o�b�t�@1 �R���g���[���E���W�X�^
#define TXB1SIDH	0x41		// ���M�o�b�t�@1 �W��ID HIGH
#define TXB1SIDL	0x42		// ���M�o�b�t�@1 �W��ID LOW
#define TXB1EID8	0x43		// ���M�o�b�t�@1 �g��ID HIGH
#define TXB1EID0	0x44		// ���M�o�b�t�@1 �g��ID LOW
#define TXB1DLC		0x45		// ���M�o�b�t�@1 DLC (�f�[�^���R�[�h)���W�X�^
#define TXB1D0		0x46		// ���M�o�b�t�@1 D0(�擪�A�h���X)

// --------------------------------------------------------------------
// ���M�o�b�t�@2
// --------------------------------------------------------------------
#define TXB2CTRL	0x50		// ���M�o�b�t�@2 �R���g���[���E���W�X�^
#define TXB2SIDH	0x51		// ���M�o�b�t�@2 �W��ID HIGH
#define TXB2SIDL	0x52		// ���M�o�b�t�@2 �W��ID LOW
#define TXB2EID8	0x53		// ���M�o�b�t�@2 �g��ID HIGH
#define TXB2EID0	0x54		// ���M�o�b�t�@2 �g��ID LOW
#define TXB2DLC		0x55		// ���M�o�b�t�@2 DLC (�f�[�^���R�[�h)���W�X�^
#define TXB2D0		0x56		// ���M�o�b�t�@2 D0(�擪�A�h���X)

#define TXRTSCTRL	0x0D		// TXnRTS�s�� �R���g���[���A�X�e�[�^�X

// --------------------------------------------------------------------
// ��M�o�b�t�@0
// --------------------------------------------------------------------
#define RXB0CTRL	0x60		// ��M�o�b�t�@0 �R���g���[���E���W�X�^
#define RXB0SIDH	0x61		// ��M�o�b�t�@0 �W��ID HIGH
#define RXB0SIDL	0x62		// ��M�o�b�t�@0 �W��ID LOW
#define RXB0EID8	0x63		// ��M�o�b�t�@0 �g��ID HIGH
#define RXB0EID0	0x64		// ��M�o�b�t�@0 �g��ID LOW
#define RXB0DLC		0x65		// ��M�o�b�t�@0 DLC (�f�[�^���R�[�h)���W�X�^
#define RXB0D0		0x66		// ��M�o�b�t�@0 D0(�擪�A�h���X)

// --------------------------------------------------------------------
// ��M�o�b�t�@1
// --------------------------------------------------------------------
#define RXB1CTRL	0x70		// ��M�o�b�t�@1 �R���g���[���E���W�X�^
#define RXB1SIDH	0x71		// ��M�o�b�t�@1 �W��ID HIGH
#define RXB1SIDL	0x72		// ��M�o�b�t�@1 �W��ID LOW
#define RXB1EID8	0x73		// ��M�o�b�t�@1 �g��ID HIGH
#define RXB1EID0	0x74		// ��M�o�b�t�@1 �g��ID LOW
#define RXB1DLC		0x75		// ��M�o�b�t�@1 DLC (�f�[�^���R�[�h)���W�X�^
#define RXB1D0		0x76		// ��M�o�b�t�@1 D0(�擪�A�h���X)

#define BFPCTRL		0x0C		// BFCTRL RXnBF�s�� �R���g���[��,�X�e�[�^�X

// --------------------------------------------------------------------
// �t�B���^0
// --------------------------------------------------------------------
#define RXF0SIDH	0x00		// �t�B���^0�W��ID HIGH
#define RXF0SIDL	0x01		// �t�B���^0�W��ID LOW
#define RXF0EID8	0x02		// �t�B���^0�g��ID HIGH
#define RXF0EID0	0x03		// �t�B���^0�g��ID LOW

// --------------------------------------------------------------------
// �t�B���^1
// --------------------------------------------------------------------
#define RXF1SIDH	0x04		// �t�B���^1�W��ID HIGH
#define RXF1SIDL	0x05		// �t�B���^1�W��ID LOW
#define RXF1EID8	0x06		// �t�B���^1�g��ID HIGH
#define RXF1EID0	0x07		// �t�B���^1�g��ID LOW

// --------------------------------------------------------------------
// �t�B���^2
// --------------------------------------------------------------------
#define RXF2SIDH	0x08		// �t�B���^2�W��ID HIGH
#define RXF2SIDL	0x09		// �t�B���^2�W��ID LOW
#define RXF2EID8	0x0A		// �t�B���^2�g��ID HIGH
#define RXF2EID0	0x0B		// �t�B���^2�g��ID LOW

// --------------------------------------------------------------------
// �t�B���^3
// --------------------------------------------------------------------
#define RXF3SIDH	0x10		// �t�B���^3�W��ID HIGH
#define RXF3SIDL	0x11		// �t�B���^3�W��ID LOW
#define RXF3EID8	0x12		// �t�B���^3�g��ID HIGH
#define RXF3EID0	0x13		// �t�B���^3�g��ID LOW

// --------------------------------------------------------------------
// �t�B���^4
// --------------------------------------------------------------------
#define RXF4SIDH	0x14		// �t�B���^4�W��ID HIGH
#define RXF4SIDL	0x15		// �t�B���^4�W��ID LOW
#define RXF4EID8	0x16		// �t�B���^4�g��ID HIGH
#define RXF4EID0	0x17		// �t�B���^4�g��ID LOW

// --------------------------------------------------------------------
// �t�B���^5
// --------------------------------------------------------------------
#define RXF5SIDH	0x18		// �t�B���^5�W��ID HIGH
#define RXF5SIDL	0x19		// �t�B���^5�W��ID LOW
#define RXF5EID8	0x1A		// �t�B���^5�g��ID HIGH
#define RXF5EID0	0x1B		// �t�B���^5�g��ID LOW


// --------------------------------------------------------------------
// �}�X�N0
// --------------------------------------------------------------------
#define RXM0SIDH	0x20		// �}�X�N0�W��ID HIGH
#define RXM0SIDL	0x21		// �}�X�N0�W��ID LOW
#define RXM0EID8	0x22		// �}�X�N0�g��ID HIGH
#define RXM0EID0	0x23		// �}�X�N0�g��ID LOW

// --------------------------------------------------------------------
// �}�X�N1
// --------------------------------------------------------------------
#define RXM1SIDH	0x24		// �}�X�N1�W��ID HIGH
#define RXM1SIDL	0x25		// �}�X�N1�W��ID LOW
#define RXM1EID8	0x26		// �}�X�N1�g��ID HIGH
#define RXM1EID0	0x27		// �}�X�N1�g��ID LOW

// --------------------------------------------------------------------
// CAN�o�X �G���[�E�J�E���^
// --------------------------------------------------------------------
#define TEC			0x1C
#define REC			0x1D

// --------------------------------------------------------------------
// ���W�X�^�E�r�b�g�E���P�[�V����
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// CNF1 �R���t�B�M�����[�V����1���W�X�^ (0x2A)
// --------------------------------------------------------------------
enum t_CNF1
{
	SJW1 = 7,		// b7
	SJW0 = 6,		// b6
	BRP5 = 5,		// b5
	BRP4 = 4,		// b4
	BRP3 = 3,		// b3
	BRP2 = 2,		// b2
	BRP1 = 1,		// b1
	BRP0 = 0		// b0
};

// --------------------------------------------------------------------
// CNF2 �R���t�B�M�����[�V����2���W�X�^ (0x29)
// --------------------------------------------------------------------
enum t_CNF2
{
	BTLMODE = 7,	// b7
	SAM	= 6,		// b6
	PHSEG12 = 5,	// b5
	PHSEG11 = 4,	// b4
	PHSEG10 = 3,	// b3
	PRSEG2 = 2,		// b2
	PRSEG1 = 1,		// b1
	PRSEG0 = 0,		// b0
};

// --------------------------------------------------------------------
// CNF3 �R���t�B�M�����[�V����3���W�X�^ (0x28)
// --------------------------------------------------------------------
enum t_CNF3
{
	SOF = 7,		// b7
	WAKFIL = 6,		// b6
	b5 = 5,			// b5
	b4 = 4,			// b4
	b3 = 3,			// b3
	PHSEG22 = 2,	// b2
	PHSEG21 = 1,	// b1
	PHSEG20 = 0		// b0
};

// --------------------------------------------------------------------
// CANCTRL CAN�R���g���[���E���W�X�^ (0xXF)
// --------------------------------------------------------------------
enum t_CANCTRL
{
	REQOP2 = 7,		// b7
	REQOP1 = 6,		// b6
	REQOP0 = 5,		// b5
	ABAT = 4,		// b4
	OSM = 3,		// b3
	CLKEN = 2,		// b2
	CLKPRE1 = 1,	// b1
	CLKPRE0 = 0		// b0
};

// --------------------------------------------------------------------
// CANSTAT CAN�X�e�[�^�X�E���W�X�^ (0xXE)
// --------------------------------------------------------------------
enum t_CANSTAT
{
	OPMOD2 = 7,		// b7
	OPMOD1 = 6,		// b6
	OPMOD0 = 5,		// b5
//	b4 = 4,			// b4
	ICOD2 = 3,		// b3
	ICOD1 = 2,		// b2
	ICOD0 = 1,		// b1
//	b0 = 0			// b0
};

// --------------------------------------------------------------------
// CANINTE ���荞�݋����W�X�^ (0x2B)
// --------------------------------------------------------------------
enum t_CANINTE
{
	MERRE = 7,		// b7
	WAKIE = 6,		// b6
	ERRIE = 5,		// b5
	TX2IE = 4,		// b4
	TX1IE = 3,		// b3
	TX0IE = 2,		// b2
	RX1IE = 1,		// b1
	RX0IE = 0,		// b0
};

// --------------------------------------------------------------------
// CANINTF ���荞�݃t���O�E���W�X�^ (0x2C)
// --------------------------------------------------------------------
enum t_CANINTF
{
	MERRF = 7,		// b7
	WAKIF = 6,		// b6
	ERRIF = 5,		// b5
	TX2IF = 4,		// b4
	TX1IF = 3,		// b3
	TX0IF = 2,		// b2
	RX1IF = 1,		// b1
	RX0IF = 0		// b0
};

// --------------------------------------------------------------------
// EFLG �G���[�E�t���O (0x2D)
// --------------------------------------------------------------------
enum t_EFLG
{
	RX1OVR = 7,		// b7
	RX0OVR = 6,		// b6
	TXBO = 5,		// b5
	TXEP = 4,		// b4
	RXEP = 3,		// b3
	TXWAR = 2,		// b2
	RXWAR = 1,		// b1
	EWARN = 0		// b0
};

// --------------------------------------------------------------------
// TXBnCTRL ���M�o�b�t�@n �R���g���[���E���W�X�^ (n = 0, 1, 2) (0x30, 0x40, 0x50)
// --------------------------------------------------------------------
enum t_TXBnCTRL
{
//	b7 = 7,			// b7
	ABTF = 6,		// b6
	MLOA = 5,		// b5
	TXERR = 4,		// b4
	TXREQ = 3,		// b3
//	b3 = 2,			// b2
	TXP1 = 1,		// b1
	TXP0 = 0		// b0

};

// --------------------------------------------------------------------
// TXBnDLC ���M�o�b�t�@n DLC���W�X�^(n = 0, 1, 2) (0x35, 0x45, 0x55)
// --------------------------------------------------------------------
enum t_TXBnDLC
{
//	b7 = 7,			// b7
	RTR = 6,		// b6
//	b5 = 5,			// b5
//	b4 = 4,			// b4
	DLC3 = 3,		// b3
	DLC2 = 2,		// b2
	DLC1 = 1,		// b1
	DLC0 = 0		// b0

};

// --------------------------------------------------------------------
// RXB0CTRL ��M�o�b�t�@0 �R���g���[���E���W�X�^ (0x60)
// --------------------------------------------------------------------
enum t_RXB0CTRL
{
//	b7 = 7,			// b7
	RXM1 = 6,		// b6
	RXM0 = 5,		// b5
//	b4 = 4,			// b4
	RXRTR = 3,		// b3
	BUKT = 2,		// b2
	BUKT1 = 1,		// b1
	FILHIT0 = 0,	// b0
};

// --------------------------------------------------------------------
// RXBnDLC ��M�o�b�t�@n DLC���W�X�^(n = 0, 1) (0x65, 0x75)
// --------------------------------------------------------------------
enum t_RXBnDLC
{
//	b7 = 7,			// b7
//	RTR = 6,		// b6
	RB1 = 5,		// b5
	RB0 = 4,		// b4
//	DLC3 = 3,		// b3
//	DLC2 = 2,		// b2
//	DLC1 = 1,		// b1
//	DLC0 = 0		// b0
};

// --------------------------------------------------------------------
// RXB1CTRL ��M�o�b�t�@1 �R���g���[���E���W�X�^ (0x70)
// --------------------------------------------------------------------
enum t_RXB1CTRL
{
//	b7 = 7,			// b7
//	RXM1 = 6,		// b6
//	RXM0 = 5,		// b5
//	b4 = 4,			// b4
//	RXRTR = 3,		// b3
	FILHIT2 = 2,	// b2
	FILHIT1 = 1,	// b1
//	FILHIT0 = 0		// b0
};

// --------------------------------------------------------------------
// TXnRTS�s�� �R���g���[���A�X�e�[�^�X
// --------------------------------------------------------------------
enum t_TXRTSCTRL
{
//	b7 = 7,			// b7
//	b6 = 6,			// b6
	B2RTS = 5,
	B1RTS = 4,
	B0RTS = 3,
	B2RTSM = 2,
	B1RTSM = 1,
	B0RTSM = 0
};

// --------------------------------------------------------------------
// BFCTRL RXnBF�s�� �R���g���[��,�X�e�[�^�X
// --------------------------------------------------------------------
enum t_BFPCTRL
{
//	b7 = 7,			// b7
//	b6 = 6,			// b6
	B1BFS = 5,
	B0BFS = 4,
	B1BFE = 3,
	B0BFE = 2,
	B1BFM = 1,
	B0BFM = 0
};

// --------------------------------------------------------------------
// RXFnSIDL �t�B���^n�W��ID LOW (n = 0, 1, 2, 3, 4, 5)
// (�A�h���X�F0x01, 0x05, 0x09, 0x11, 0x15, 0x19)
// --------------------------------------------------------------------
#define EXIDE	3	// b3: �g��ID���r�b�g
					//   1 = �g��ID(29�r�b�g)�݂̂ɓK�p
					//   0 = �W��ID(11�r�b�g)�݂̂ɓK�p

// TXBnSIDL ���M�o�b�t�@n�W��ID LOW (n = 0, 1, 2)
// (�A�h���X�F0x32, 0x42, 0x52)

//#define EXIDE	3	// �g��ID���r�b�g
					//   1 = �g��ID(29�r�b�g)
					//   0 = �W��ID(11�r�b�g)

// --------------------------------------------------------------------
// RXBnSIDL ��M�o�b�t�@n�W��ID LOW (n = 0, 1)
// (�A�h���X�F0x62, 0x72)
// --------------------------------------------------------------------
#define SRR		4	// �W���t���[���E�����[�g���M�v��
					//   IDE"��0�̂Ƃ��̂ݗL��
					//     1 = �W���t���[���̃����[�g���M�v������M
					//     0 = �W���f�[�^�t���[������M

#define IDE		3	// ��MID�̃t�H�[�}�b�g
					//   1 = �g��ID(29�r�b�g)
					//   0 = �W��ID(11�r�b�g)

// --------------------------------------------------------------------
// SPI�|�[�g��`
// --------------------------------------------------------------------
#define CAN_SPI_CS_BIT   	2
#define CAN_SPI_CS_DDR   	P1.DDR
#define CAN_SPI_CS_PORT   	P1.DR.BYTE

// --------------------------------------------------------------------
// ���d�C���N���[�h�h�~
// --------------------------------------------------------------------
#endif /* _CAN2515_H_ */
