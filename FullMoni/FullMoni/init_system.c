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
// filename		:	initsystem.c
// brief		:	FullMoni rev.B �V�X�e��������
// author		:	Tomoya Sato
// update		:	2013/03/31
// version		:	1.02
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// �V�X�e���w�b�_�t�@�C��
// --------------------------------------------------------------------
#include <machine.h>

// --------------------------------------------------------------------
// ���[�U�[�w�b�_�t�@�C��
// --------------------------------------------------------------------
#include "iodefine.h"
#include "TFTLCD35.h"
#include "CAN2515.h"

// --------------------------------------------------------------------
// CPG������
// --------------------------------------------------------------------
void Init_CPG(void)
{
	//-----------------------------------------
	// Set All Internal Clocks in Maximum Speed
	//-----------------------------------------
	// ICLK = EXTAL x 4 (48MHz)
	// PCLK = EXTAL x 2 (24MHz)
	// BCLK = EXTAL x 4 (48MHz)
	SCKCR.WORD = (0 << 8) + (1 << 4) + (0 << 0);
}

// --------------------------------------------------------------------
// INTC������
// --------------------------------------------------------------------
void Init_INTC(void)
{
	//-------------------
	// Interrupt Mode = 2
	//-------------------
	INTC.INTCR.BIT.INTM = 2;
	//--------------------------------
	// Set Current Interrupt Level = 0
	//--------------------------------
 	set_imask_exr(0);
	
	// MCP2515 CANIRQ �w��
	P1.ICR.BIT.B3			=    1;
	PFC.PFCRC.BIT.ITS3		=    0;
	INTC.IPRA.BIT._IRQ3		=    5;
	INTC.ISCR_L.BIT.IRQ3SC  = 0x01;
	INTC.IER.BIT.IRQ3E		=    1;
	INTC.ISR.BIT.IRQ3F		=    0;
	
}

// --------------------------------------------------------------------
// MSTP������
// --------------------------------------------------------------------
void Init_MSTP(void)
{
	//-------------------------------------------
	// Clear Module Stop for All Internal Modules
	//-------------------------------------------
	MSTP.CRA.BIT.ACSE		= 0;
	MSTP.CRA.BIT._EXDMAC	= 0;
	MSTP.CRA.BIT._DMAC		= 0;
	MSTP.CRA.BIT._DTC		= 0;
	MSTP.CRA.BIT._TMR23		= 0;
	MSTP.CRA.BIT._TMR01		= 0;
	MSTP.CRA.BIT._DA		= 0;
	MSTP.CRA.BIT._AD0		= 0;
	MSTP.CRA.BIT._TPUU		= 0;
	MSTP.CRA.BIT._TPUL		= 0;
	
	MSTP.CRB.BIT._PPG0		= 0;
	MSTP.CRB.BIT._SCI4		= 0;
	MSTP.CRB.BIT._SCI2		= 0;
	MSTP.CRB.BIT._SCI1		= 0;
	MSTP.CRB.BIT._SCI0		= 0;
	MSTP.CRB.BIT._IIC1		= 0;
	MSTP.CRB.BIT._IIC0		= 0;
	MSTP.CRB.BIT._UBC		= 0;
	
	MSTP._CRC.BIT._SCI5		= 0;
	MSTP._CRC.BIT._SCI6		= 0;
	MSTP._CRC.BIT._TMR45	= 0;
	MSTP._CRC.BIT._TMR67	= 0;
	MSTP._CRC.BIT._USB		= 0;
	MSTP._CRC.BIT._CRC		= 0;
	MSTP._CRC.BIT._AD1		= 0;
	MSTP._CRC.BIT._PPG1		= 0;
	MSTP._CRC.BIT._RAM_4	= 0;
	MSTP._CRC.BIT._RAM32	= 0;
	MSTP._CRC.BIT._RAM10	= 0;
}

// --------------------------------------------------------------------
// GPIO������
// --------------------------------------------------------------------
void Init_GPIO(void)
{
	//---------------------
	// Enable External Bus
	//---------------------
	SYSCR.BIT.EXPE			= 1;		// �O���o�X���[�h�I��
	//-------------
	// P1
	//-------------
	// P10 : O : TFT LCD Command/Data Switch
	// P11 : I : ADS7843E INT
	// P12 : O : MCP2515 CS
	// P13 : I : MCP2515 INT
	// P14 : O : MAX3232ID TxD5
	// P15 : I : MAX3232ID RxD5
	// P16 : I/O : BR24L04F-W SDA0
	// P17 : O : BR24L04F-W SDL0
	P1.DDR = 0x95;
	P1.ICR.BIT.B4 = 1;
	P1.ICR.BIT.B5 = 1;
	P1.ICR.BIT.B6 = 1;
	P1.ICR.BIT.B7 = 1;
	P1.DR.BIT.B6 = 1;
	P1.DR.BIT.B7 = 1;
	//-------------
	// P2
	//-------------
	// P20 : O : MCP2515 SCK0
	// P21 : I : MCP2515 RxD0
	// P22 : O : MCP2515 TxD0
	// P23 : O : BEEP OUT
	// P24 : O : TFT LCD Reset
	// P25 : O : TFT LCD Back Light Control PWM
	// P26 : I : Reserve
	// P27 : O : MAX3232ID FC-Logger select Switch
	P2.DR.BIT.B3 = 0;
	P2.DDR = 0xBD;
	P2.ICR.BIT.B1 = 1;
	P2.DR.BIT.B7 = 1;
	//-------------
	// P5
	//-------------
	// P50 : I : Reserve
	// P51 : I : Reserve
	// P52 : I : Reserve
	// P53 : I : Reserve
	// P54 : I : Reserve
	// P55 : I : Reserve
	// P56 : I : Reserve
	// P57 : I : Reserve
	//-------------
	// P6
	//-------------
	// P60 : O : ADS7843E TxD4
	// P61 : I : ADS7843E RxD4
	// P62 : O : ADS7843E SCK4
	// P63 : O : ADS7843E CS
	// P64 : I : Reserve
	// P65 : I : Reserve
	P6.DDR = 0x0D;
//	P6.ICR.BIT.B1 = 1;
	//-------------
	// PA
	//-------------
	// PA0 : I : Reserve
	// PA1 : O : RD/WR
	// PA2 : I : Reserve
	// PA3 : O : LLWR
	// PA4 : O : LHWR
	// PA5 : O : RD
	// PA6 : I : Reserve
	// PA7 : I : Reserve
	PA.DDR = 0x3A;
	//-------------
	// PB
	//-------------
	// PB0 : I : Reserve
	// PB1 : O : CS1
	// PB2 : O : CS2-A
	// PB3 : O : LED(Red)
	PB.DDR = 0x0E;
	//-------------
	// PD
	//-------------
	// BSC Address
	PD.DDR = 0xFF; // Enable  A7-A0 Output
	//-------------
	// PE
	//-------------
	// BSC Address
	PE.DDR = 0xFF; // Enable A15-A8 Output
	//-------------
	// PF
	//-------------
	// BSC Address
	PF.DDR = 0x1F; // Enable A18-A16 Output
	//-------------
	// PH
	//-------------
	PH.DDR = 0xFF; // Enable D7-D0 Output
	//-------------
	// PI
	//-------------
	PI.DDR = 0xFF; // Enable D15-D8 Output
	//----------------------
	// PJ (Single Chip Mode)
	//----------------------
	//----------------------
	// PK
	//----------------------
	//-------------
	// PM
	//-------------
	// PM0 : O : LED(Yellow)
	// PM1 : I : TC7W125FU RxD6
	// PM2 : I : Reserve
	PM.DDR = 0x01;
}


// --------------------------------------------------------------------
// BSC������
// --------------------------------------------------------------------
void Init_BSC(void)
{
	// --------------------------------------------------------------------
	// PFC
	// --------------------------------------------------------------------
	PFC.PFCR0.BIT.CS1E		= 1;		// �o�͑I��		CS1		SRAM�`�b�v�Z���N�g
	PFC.PFCR0.BIT.CS2E		= 1;		// �o�͑I��		CS2-A	LCD�`�b�v�Z���N�g
	PFC.PFCR2.BIT.RDWRE		= 1;		// �o�͐ݒ�		RD/^WR
	PFC.PFCR4.BIT.A18E		= 1;		// �o�͐ݒ�		A18
	PFC.PFCR4.BIT.A17E		= 1;		// �o�͐ݒ�		A17
	PFC.PFCR4.BIT.A16E		= 1;		// �o�͐ݒ�		A16
	PFC.PFCR6.BIT.LHWROE	= 1;		// �o�͐ݒ�		PA4=LHWR
	PFC.PFCR8.BYTE			= 0x00;		// EXDMAC1����[�q P14-P17
	PFC.PFCR9.BIT.TPUMS4	= 1;		// TIOCA4 P25�A�E�g�v�g�R���y�A
	PFC.PFCR9.BIT.TPUMS4	= 1;		// TIOCA4 P25�A�E�g�v�g�R���y�A
	
	// --------------------------------------------------------------------
	// BSC
	// --------------------------------------------------------------------
	BSC.ABWCR.BIT.ABWH1		= 0;		// 16bit���ݒ�H	CS1
	BSC.ABWCR.BIT.ABWL1		= 1;		// 16bit���ݒ�L	CS1
	BSC.ABWCR.BIT.ABWH2		= 0;		// 16bit���ݒ�H	CS2
	BSC.ABWCR.BIT.ABWL2		= 1;		// 16bit���ݒ�L	CS2
	BSC.ASTCR.WORD			= 0x0000;	// �O���o�X�E�F�C�g�X�e�[�g�}������
	BSC.WTCRA.WORD			= 0x0000;	// �O���o�X�E�F�C�g�X�e�[�g��(1)
	BSC.WTCRB.WORD			= 0x0000;	// �O���o�X�E�F�C�g�X�e�[�g��(2)
	BSC.RDNCR.WORD			= 0x0000;	// �O���o�X���[�h�X�g���[�u�^�C�~���O
	BSC.CSACR.WORD			= 0x0000;	// �O���o�XCS�A�T�[�g���Ԋg��
	BSC.IDLCR.WORD			= 0x0000;	// �O���o�X�A�C�h���T�C�N��
	BSC.BCR1.WORD			= 0x0000;	// �o�X�R���g���[�����W�X�^1
	BSC.BCR2.BYTE			= 0x02;		// �o�X�R���g���[�����W�X�^2
	BSC.ENDIANCR.BYTE		= 0x00;		// �G���f�B�A���R���g���[�����W�X�^
	BSC.SRAMCR.WORD			= 0x0600;	// SRAM���[�h�R���g���[�����W�X�^
	BSC.BROMCR.WORD			= 0x0000;	// �o�[�X�gROM�C���^�[�t�F�[�X�R���g���[�����W�X�^
	BSC.MPXCR.WORD			= 0x0000;	// �A�h���X�f�[�^MPX�R���g���[�����W�X�^
}

// --------------------------------------------------------------------
// EXDMAC������
// --------------------------------------------------------------------
void Init_EXDMAC(void)
{
	//=========================================
	// Configure EXDMAC0 for TFT LCD Refresh Cycle
	//=========================================
	//--------------------------
	// Start EXDMAC0
	//--------------------------
//	MSTP.CRA.BIT._EXDMAC  = 0;
	//------------------------
	// Initialize EXDMAC0
	//------------------------
	EXDMAC0.EDSAR			= 0x200000;		//*ADATA		// EXDMA �\�[�X�A�h���X���W�X�^
	EXDMAC0.EDDAR			= 0x400000;		//LCD_D			// EXDMA �f�X�e�B�l�[�V�����A�h���X���W�X�^
	EXDMAC0.EDOFR			= 0x00000000;					// EXDMA �I�t�Z�b�g���W�X�^
	EXDMAC0.EDTCR			= 0x00025800;					// EXDMA �]���J�E���g���W�X�^ 320*240*2=0x00025800
//	EXDMAC0.EDBSR			= (320 << 16) + (320 << 0);		// EXDMA �u���b�N�T�C�Y���W�X�^
	EXDMAC0.EDMDR.LONG		= 0x00004006;					// EXDMA ���[�h�R���g���[�����W�X�^
	EXDMAC0.EDACR.LONG		= 0x00200000;					// EXDMA �A�h���X�R���g���[�����W�X�^
}

// --------------------------------------------------------------------
// DMA������
// --------------------------------------------------------------------
void Init_DMAC(void)
{
	//=========================================
	// Configure DMAC0 for TFT LCD Graphic Copy
	//=========================================
	//--------------------------
	// Start DMAC0
	//--------------------------
//	MSTP.CRA.BIT._DMAC = 0;
	//------------------------
	// Initialize DMAC0
	//------------------------
	DMAC0.DOFR			= 0x00000000;	// DMA �I�t�Z�b�g���W�X�^
	DMAC0.DMDR.LONG		= 0x00004005;	// DMA ���[�h�R���g���[�����W�X�^
	DMAC0.DACR.LONG		= 0x00220000;	// DMA �A�h���X�R���g���[�����W�X�^
	
	//=========================================
	// Configure DMAC1 for TFT LCD Paint
	//=========================================
	//------------------------
	// Initialize DMAC1
	//------------------------
	DMAC1.DOFR			= 0x00000000;	// DMA �I�t�Z�b�g���W�X�^
	DMAC1.DMDR.LONG		= 0x00004005;	// DMA ���[�h�R���g���[�����W�X�^
	DMAC1.DACR.LONG		= 0x00020000;	// DMA �A�h���X�R���g���[�����W�X�^
	
	//=========================================
	// Configure DMAC2 for TFT LCD Graphic Copy Large
	//=========================================
	//------------------------
	// Initialize DMAC2
	//------------------------
	DMAC2.DOFR			= 0x00000004;	// DMA �I�t�Z�b�g���W�X�^
	DMAC2.DMDR.LONG		= 0x00004005;	// DMA ���[�h�R���g���[�����W�X�^
	DMAC2.DACR.LONG		= 0x00210000;	// DMA �A�h���X�R���g���[�����W�X�^

}

// --------------------------------------------------------------------
// TPU������
// --------------------------------------------------------------------
void Init_TPU(void)
{
	TPU.TSTR.BYTE			= 0x00;		// �^�C�}�X�^�[�g���W�X�^�N���A
	
	//--------------------------
	// Module Start TPU0-5
	//--------------------------
//	MSTP.CRA.BIT._TPUL  = 0;
	//=========================================
	// Configure TPU0 for TFT LCD Refresh Cycle
	//=========================================
	//----------------------------
	// Set Interrupt Request Level
	//----------------------------
	INTC.IPRF.BIT._TPU0 = 4;
	//----------------------------
	// Initialize TPU0
	//----------------------------
	TPU0.TCR.BYTE			= 0x2B;		// �^�C�}�R���g���[�����W�X�^(TGRA�ŃN���A/�����/�Ӂ^64)
	TPU0.TIOR.BYTE.H		= 0x00;		// �^�C�}I/O�R���g���[�����W�X�^(H)
	TPU0.TIOR.BYTE.L		= 0x00;		// �^�C�}I/O�R���g���[�����W�X�^(L)
	TPU0.TIER.BYTE			= 0x41;		// �^�C�}�C���^���v�g�C�l�[�u�����W�X�^
	TPU0.TSR.BYTE			= 0xC0;		// �^�C�}�X�e�[�^�X���W�X�^
	TPU0.TCNT				= 0x0000;	// �^�C�}�J�E���^
//	TPU0.TGRA				= 0x249F;	// �^�C�}�W�F�l�������W�X�^A(fps40)
//	TPU0.TGRA				= 0x30D4;	// �^�C�}�W�F�l�������W�X�^A(fps30)
	TPU0.TGRA				= 0x493E;	// �^�C�}�W�F�l�������W�X�^A(fps20)
//	TPU0.TGRA				= 0x927C;	// �^�C�}�W�F�l�������W�X�^A(fps10)
	TPU0.TGRB				= 0;		// �^�C�}�W�F�l�������W�X�^B
	TPU0.TGRC				= 0;		// �^�C�}�W�F�l�������W�X�^C
	TPU0.TGRD				= 0;		// �^�C�}�W�F�l�������W�X�^D
	TPU0.TMDR.BYTE			= 0xC0;		// �^�C�}���[�h���W�X�^(���ׂĒʏ퓮��)
	
	//=========================================
	// Configure TPU3 for BEEP
	//=========================================
	//----------------------------
	// Set Interrupt Request Level
	//----------------------------
	INTC.IPRG.BIT._TPU3 = 3;
	//----------------------------
	// Initialize TPU3
	//----------------------------
	TPU3.TCR.BYTE			= 0xA8;		// �^�C�}�R���g���[�����W�X�^(TGRA�ŃN���A/�����/�Ӂ^1)
	TPU3.TIOR.BYTE.H		= 0x00;		// �^�C�}I/O�R���g���[�����W�X�^(H)
	TPU3.TIOR.BYTE.L		= 0x21;		// �^�C�}I/O�R���g���[�����W�X�^(L)
	TPU3.TIER.BYTE			= 0x40;		// �^�C�}�C���^���v�g�C�l�[�u�����W�X�^
	TPU3.TSR.BYTE			= 0xC0;		// �^�C�}�X�e�[�^�X���W�X�^
	TPU3.TCNT				= 0x0000;	// �^�C�}�J�E���^
	TPU3.TGRC				= 0x1770;	// �^�C�}�W�F�l�������W�X�^A(4KHz)
//	TPU3.TGRD				= 0x0BB8;	// �^�C�}�W�F�l�������W�X�^B(50%)	(�ő剹)
	TPU3.TGRD				= 0x0000;	// �^�C�}�W�F�l�������W�X�^B(0%)	(����)
	TPU3.TMDR.BYTE			= 0xC3;		// �^�C�}���[�h���W�X�^(PWM���[�h2)
	
	//=========================================
	// Configure TPU4 for TFT LCD Back Light PWM
	//=========================================
	//----------------------------
	// Set Interrupt Request Level
	//----------------------------
	INTC.IPRG.BIT._TPU4 = 3;
	//----------------------------
	// Initialize TPU4
	//----------------------------
	TPU4.TCR.BYTE			= 0x28;		// �^�C�}�R���g���[�����W�X�^(TGRA�ŃN���A/�����/�Ӂ^1)
	TPU4.TIOR.BYTE			= 0x21;		// �^�C�}I/O�R���g���[�����W�X�^
	TPU4.TIER.BYTE			= 0x40;		// �^�C�}�C���^���v�g�C�l�[�u�����W�X�^
	TPU4.TSR.BYTE			= 0xC0;		// �^�C�}�X�e�[�^�X���W�X�^
	TPU4.TCNT				= 0x0000;	// �^�C�}�J�E���^
	TPU4.TGRA				= 0x2580;	// �^�C�}�W�F�l�������W�X�^A(2.5KHz)
	TPU4.TGRB				= 0x2579;	// �^�C�}�W�F�l�������W�X�^B(0%)
	TPU4.TMDR.BYTE			= 0xC2;		// �^�C�}���[�h���W�X�^(PWM���[�h1)
	
	//=========================================
	// Configure TPU6 for LED Dimmer Cycle
	//=========================================
	//----------------------------
	// Set Interrupt Request Level
	//----------------------------
	INTC.IPRL.BIT._TPU6A = 5;
	//----------------------------
	// Initialize TPU6
	//----------------------------
	TPU6.TCR.BYTE			= 0x28;		// �^�C�}�R���g���[�����W�X�^(TGRA�ŃN���A/�����/�Ӂ^1)
	TPU6.TIOR.BYTE.H		= 0x00;		// �^�C�}I/O�R���g���[�����W�X�^(H)
	TPU6.TIOR.BYTE.L		= 0x00;		// �^�C�}I/O�R���g���[�����W�X�^(L)
	TPU6.TIER.BYTE			= 0x41;		// �^�C�}�C���^���v�g�C�l�[�u�����W�X�^
	TPU6.TSR.BYTE			= 0xC0;		// �^�C�}�X�e�[�^�X���W�X�^
	TPU6.TCNT				= 0x0000;	// �^�C�}�J�E���^
	TPU6.TGRA				= 0x2EE0;	// �^�C�}�W�F�l�������W�X�^A(2KHz)
	TPU6.TGRB				= 0;		// �^�C�}�W�F�l�������W�X�^B
	TPU6.TGRC				= 0;		// �^�C�}�W�F�l�������W�X�^C
	TPU6.TGRD				= 0;		// �^�C�}�W�F�l�������W�X�^D
	TPU6.TMDR.BYTE			= 0xC0;		// �^�C�}���[�h���W�X�^(���ׂĒʏ퓮��)
	
//	TPU.TSTR.BYTE			= 0x00;		// �^�C�}�X�^�[�g���W�X�^
	TPU.TSYR.BYTE			= 0x00;		// �^�C�}�V���N�����W�X�^
}

//=============================
// Global : UART Software FIFO
//=============================
#define UART_FIFO_DEPTH 256          // UART FIFO Depth
unsigned char gUART_FIFO_Tx[UART_FIFO_DEPTH]; // Tx FIFO Buffer
unsigned long gUART_FIFO_Tx_WP;               // Tx FIFO Read Pointer
unsigned long gUART_FIFO_Tx_RP;               // Tx FIFO Write Pointer
unsigned long gUART_FIFO_Tx_DC;               // Tx FIFO Data Count;
unsigned char gUART_FIFO_Rx[UART_FIFO_DEPTH]; // Rx FIFO Buffer
unsigned long gUART_FIFO_Rx_WP;               // Rx FIFO Read Pointer
unsigned long gUART_FIFO_Rx_RP;               // Rx FIFO Write Pointer
unsigned long gUART_FIFO_Rx_DC;               // Rx FIFO Data Count;

//======================
// Global : Ctrl-C
//======================
unsigned char gUART_Ctrl_C;

// --------------------------------------------------------------------
// UART(SCI5)������
// --------------------------------------------------------------------
void Init_UART(void)
{
	volatile unsigned long i;
	//------------------------
	// P14 : SCI5 TxD5
	// P15 : SCI5 RxD5
	//------------------------
	P1.ICR.BIT.B1 = 5;
	//------------------------
	// Start SCI5 System Clock
	//------------------------
//	MSTP._CRC.BIT._SCI5 = 0;
	//------------------------
	// Initialize FIFO
	//------------------------
	gUART_FIFO_Tx_WP = 0;
	gUART_FIFO_Tx_RP = 0;
	gUART_FIFO_Tx_DC = 0;
	gUART_FIFO_Rx_WP = 0;
	gUART_FIFO_Rx_RP = 0;
	gUART_FIFO_Rx_DC = 0;
	//------------------------
	// Initialize Global
	//------------------------
	gUART_Ctrl_C = 0;
	//-----------------------------
	// Set Interrupt Request Level
	//-----------------------------
	INTC.IPRQ.BIT._SCI5 = 6;
	//------------------------
	// Reset TE, RE
	//------------------------
	SCI5.SCR.BIT.TE  = 0;
	SCI5.SCR.BIT.RE  = 0;
	//------------------------
	// UART Mode
	//   8bit, No-Parity, 1-Stop
	//   Baud Rate = 38400bps
	//   PCLK = 24MHz
	//   CKS  = 0
	//   BRR = 24M / (64 * 2^(-1) * 38400) - 1 = 19
	//------------------------
	SCI5.SCR.BIT.CKE = 0;
	SCI5.SMR.BYTE = 0x00;  //00000000
	SCI5.BRR = 19;
	//------------------------
	// Wait for 1bit period (30us)
	//------------------------
	for (i = 0; i < 30000 / 20; i++);
	//------------------------
	// Enable Interrupt RXI
	//------------------------
	SCI5.SCR.BIT.RIE = 1;
	//------------------------
	// Set TE, RE
	//------------------------
	SCI5.SCR.BIT.TE  = 1;
	SCI5.SCR.BIT.RE  = 1;
}

// --------------------------------------------------------------------
// UART ���M����
// --------------------------------------------------------------------
unsigned char UART_Tx(unsigned char byte)
{
    unsigned char possible;
    unsigned char tie_bkup;

    //----------------------------------------------
    // Disable Interrupt TXI (still TDRE flag is ON)
    //----------------------------------------------
    tie_bkup = SCI5.SCR.BIT.TIE;
    //------------------------
    // Check FIFO Tx
    //------------------------
    possible = (gUART_FIFO_Tx_DC < UART_FIFO_DEPTH)? 1 : 0;
    //------------------------
    // Set the Tx Data in FIFO
    //------------------------
    if (possible)
    {
        gUART_FIFO_Tx[gUART_FIFO_Tx_WP] = byte;
        gUART_FIFO_Tx_WP = (gUART_FIFO_Tx_WP + 1) % UART_FIFO_DEPTH;
        gUART_FIFO_Tx_DC = gUART_FIFO_Tx_DC + 1;
        tie_bkup = 1;
    }
    //------------------------
    // Revert TIE
    //------------------------
    SCI5.SCR.BIT.TIE = tie_bkup;

    return possible;
}

// --------------------------------------------------------------------
// UART ���M����
// --------------------------------------------------------------------
void UART_Tx_Char(unsigned char byte)
{
    while(UART_Tx(byte) == 0);
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
unsigned char UART_Rx_Possible(void)
{
    unsigned char possible;
    unsigned char rie_bkup;

    //------------------------
    // Disable Interrupt RXI
    //------------------------
    rie_bkup = SCI5.SCR.BIT.RIE;
    SCI5.SCR.BIT.RIE = 0;
    //------------------------
    // Check FIFO Rx
    //------------------------
    possible = (gUART_FIFO_Rx_DC > 0)? 1 : 0;
    //------------------------
    // Revert RIE
    //------------------------
    SCI5.SCR.BIT.RIE = rie_bkup;

    return possible;
}

// --------------------------------------------------------------------
// UART ��M����
// --------------------------------------------------------------------
unsigned char UART_Rx(unsigned char *byte)
{
    unsigned char possible;
    unsigned char rie_bkup;

    //------------------------
    // Disable Interrupt RXI
    //------------------------
    rie_bkup = SCI5.SCR.BIT.RIE;
    //------------------------
    // Check FIFO Rx
    //------------------------
    possible = (gUART_FIFO_Rx_DC > 0)? 1 : 0;
    //---------------------------
    // Get the Rx Data from FIFO
    //---------------------------
    if (possible)
    {
        *byte = gUART_FIFO_Rx[gUART_FIFO_Rx_RP];
        gUART_FIFO_Rx_RP = (gUART_FIFO_Rx_RP + 1) % UART_FIFO_DEPTH;
        gUART_FIFO_Rx_DC = gUART_FIFO_Rx_DC - 1;
        rie_bkup = 1;
    }
    //------------------------
    // Revert RIE
    //------------------------
    SCI5.SCR.BIT.RIE = rie_bkup;

    return possible;
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
unsigned char UART_Rx_Char(void)
{
    unsigned char byte;

    while(UART_Rx(&byte) == 0);
    return byte;
}

// --------------------------------------------------------------------
// 
// --------------------------------------------------------------------
unsigned char UART_Found_Ctrl_C(void)
{
    unsigned char result;

    result = gUART_Ctrl_C;
    gUART_Ctrl_C = 0;
    return result;
}

// --------------------------------------------------------------------
// UART ���M�n���h��
// --------------------------------------------------------------------
void Int_Handler_UART_Tx(void)
{
    //------------------------
    // If FIFO Tx has Data
    //------------------------
    if (gUART_FIFO_Tx_DC > 0)
    {
        // Read FIFO Tx and Set TDR
        SCI5.TDR = gUART_FIFO_Tx[gUART_FIFO_Tx_RP];
        gUART_FIFO_Tx_RP = (gUART_FIFO_Tx_RP + 1) % UART_FIFO_DEPTH;
        gUART_FIFO_Tx_DC = gUART_FIFO_Tx_DC - 1;
        // Clear TDRE
        SCI5.SSR.BIT.TDRE = 0; // read 1 and write 0
    }
    //-------------------------
    // If FIFO Tx has no Data
    //-------------------------
    else
    {
        // Disable Interrupt TXI (still TDRE flag is ON)
        SCI5.SCR.BIT.TIE = 0;
    }
}

// --------------------------------------------------------------------
// UART ��M�n���h��
// --------------------------------------------------------------------
void Int_Handler_UART_Rx(void)
{
    unsigned char byte;

    //------------------------
    // If FIFO Rx has Room
    //------------------------
    if (gUART_FIFO_Rx_DC < UART_FIFO_DEPTH)
    {
        // Read RDR and Set FIFO Rx
        byte = SCI5.RDR;
        if (byte == 0x03) // Ctrl-C ?
        {
            gUART_Ctrl_C = 1;
        }
		UART_Tx_Char(byte);
		TPU3.TGRD = byte << 8;
        gUART_FIFO_Rx[gUART_FIFO_Rx_WP] = byte;
        gUART_FIFO_Rx_WP = (gUART_FIFO_Rx_WP + 1) % UART_FIFO_DEPTH;
        gUART_FIFO_Rx_DC = gUART_FIFO_Rx_DC + 1;
        // Clear RDRF
        SCI5.SSR.BIT.RDRF = 0; // read 1 and write 0
    }
    //------------------------
    // If FIFO Rx has no Room
    //------------------------
    else
    {
        // Disable Interrupt RXI (still RDRF flag is ON)
        SCI5.SCR.BIT.RIE = 0;
    }
}

// --------------------------------------------------------------------
// UART ��M�G���[�n���h��
// --------------------------------------------------------------------
void Int_Handler_UART_Rx_ERR(void)
{
    SCI5.SSR.BIT.FER = 0;
    SCI5.SSR.BIT.ORER = 0;
    SCI5.SSR.BIT.PER = 0;
    SCI5.SSR.BIT.RDRF = 0;
}

// --------------------------------------------------------------------
// UART ���M�I���n���h��
// --------------------------------------------------------------------
void Int_Handler_UART_Tx_END(void)
{
    SCI5.SSR.BIT.TEND = 0;
}
