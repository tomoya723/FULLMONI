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
// filename		:	main.c
// brief		:	FullMoni rev.B ���C�����[�`��
// author		:	Tomoya Sato
// update		:	2013/03/20
// version		:	1.01
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// �v���g�^�C�v�錾
// --------------------------------------------------------------------
void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

// --------------------------------------------------------------------
// �V�X�e���w�b�_�t�@�C��
// --------------------------------------------------------------------
#include <machine.h>

// --------------------------------------------------------------------
// ���[�U�[�w�b�_�t�@�C��
// --------------------------------------------------------------------
#include "dataregister.h"
#include "iodefine.h"
#include "init_system.h"
#include "TFTLCD35.h"
#include "CAN2515.h"
#include "spi.h"
#include "state_control.h"

// --------------------------------------------------------------------
// �O���[�o���ϐ��錾
// --------------------------------------------------------------------
volatile char version[5] = "v1.01";

// --------------------------------------------------------------------
// �O���[�o���\���̐錾
// --------------------------------------------------------------------
volatile e2p_data_t			g_e2p_data;
volatile MoTeC1_data_t		g_MoTeC1_data;
volatile Haltech1_data_t	g_Haltech1_data;
volatile Haltech2_data_t	g_Haltech2_data;
volatile Freedom2_data_t	g_Freedom2_data;

// --------------------------------------------------------------------
// ���C�����[�`��
// --------------------------------------------------------------------
void main(void)
{
	// --------------------------------------------------------------------
	// �e��@�\������
	// --------------------------------------------------------------------
	Init_CPG();
	Init_INTC();
	Init_MSTP();
	Init_GPIO();
	Init_BSC();
	Init_EXDMAC();
	Init_DMAC();
	Init_TPU();
	Init_UART();
	Init_TFTLCD();
	Init_SPI();
//	Init_CAN();		//���f���ʑΉ��̈�state_control�Ŏ��s
	Init_ADS7843();
	Init_IIC();
	
	// --------------------------------------------------------------------
	// �f�[�^������
	// --------------------------------------------------------------------
	Init_MoTeC1_data();
	Init_Haltech1_data();
	Init_Haltech2_data();
	Init_Freedom2_data();
	
	// --------------------------------------------------------------------
	// FONT�f�[�^�W�J(Flash������RAM)
	// --------------------------------------------------------------------
	FONT_open();
	
	// --------------------------------------------------------------------
	// �����X�e�[�g��`
	// --------------------------------------------------------------------
	A001();
	
	// --------------------------------------------------------------------
	// ���C�����[�v
	// --------------------------------------------------------------------
	while(1)
	{
		state_control();		// ��ԕʏ������s
	}
}

// --------------------------------------------------------------------
// �C�����C���֐��錾
// --------------------------------------------------------------------
#pragma inline (Touch_Decision)
#pragma inline (Beep_OneShotMin_control)
#pragma inline (Beep_OneShotMax_control)
#pragma inline (Beep_TwoShotMin_control)

// --------------------------------------------------------------------
// �C�����C���֐��v���g�^�C�v�錾
// --------------------------------------------------------------------
static void Touch_Decision(void);
static void Beep_OneShotMin_control(void);
static void Beep_OneShotMax_control(void);
static void Beep_TwoShotMin_control(void);

// --------------------------------------------------------------------
// �O���[�o���ϐ��錾
// --------------------------------------------------------------------
volatile long			g_int50mscnt;
volatile unsigned int	touch_done_flg;
volatile unsigned int	touch_drag_flg;
volatile unsigned int	g_PressX, g_PressY;
volatile unsigned int	g_DragX, g_DragY;
volatile unsigned int	g_refresh_done;
volatile unsigned int	g_led_o_max_flg;
volatile unsigned int	g_led_o_min_flg;
volatile unsigned int	g_led_r_max_flg;
volatile unsigned int	g_led_r_min_flg;
static unsigned int		touch_cnt;
static unsigned int		Beep_OneShotMin_cnt;
static unsigned int		Beep_OneShotMax_cnt;
static unsigned int		Beep_TwoShotMin_cnt;
static unsigned int		master_warning_cnt;
static unsigned int		g_shift_timing_cnt;
static unsigned int		LEDonoff_cnt;

// --------------------------------------------------------------------
// MCP2515 CAN IRQ �O�����荞��
// --------------------------------------------------------------------
void Int_CAN2515(void)
{
	// --------------------------------------------------------------------
	// ���[�J���ϐ��錾
	// --------------------------------------------------------------------
	unsigned char CAN_rcv_INTF, can_rcv[14];
	signed short msgID;
	
	// --------------------------------------------------------------------
	// ���荞�݃t���O�N���A
	// --------------------------------------------------------------------
	INTC.ISR.BIT.IRQ3F = 0;
	
	// --------------------------------------------------------------------
	// MCP2515���荞�ݗv���ʏ���
	// --------------------------------------------------------------------
	CAN_rcv_INTF = CANReadReg(CANINTF);
	
	if((CAN_rcv_INTF & 0x02) == 0x02)
	{
		CANRxB1Read(&can_rcv[1], 8);
		
		msgID = MAKE_SID(can_rcv[1], can_rcv[2]);		// ID�쐬
		
		if(Onetime_Peakclear_cnt > 0) Onetime_Peakclear_cnt --;
		
		if		(g_e2p_data.E2P_1.model == MoTeC1)
		{
			switch(msgID)
			{
				case 0x010:
							g_MoTeC1_data.RPM					= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_MoTeC1_data.GroundSpeed			= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_MoTeC1_data.OilPressure			= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x011:
							g_MoTeC1_data.EngineTemp			= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_MoTeC1_data.FuelPressure			= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_MoTeC1_data.BatteryVoltage		= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							g_MoTeC1_data.ThrottlePosition		= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x012:
							g_MoTeC1_data.ManifoldPressure		= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_MoTeC1_data.InletAirTemp			= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							// N/A								= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							g_MoTeC1_data.Lambda				= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x013:
							g_MoTeC1_data.IgnitionAdvance		= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_MoTeC1_data.Gear					= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_MoTeC1_data.InjectorDuty			= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							default: break;
			}
		}
		else if	(g_e2p_data.E2P_1.model == Haltech1)
		{
			switch(msgID)
			{
				case 0x010:
							g_Haltech1_data.RPM					= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech1_data.GroundSpeed			= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech1_data.OilPressure			= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x011:
							g_Haltech1_data.EngineTemp			= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech1_data.FuelPressure		= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech1_data.BatteryVoltage		= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							g_Haltech1_data.ThrottlePosition	= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x012:
							g_Haltech1_data.ManifoldPressure	= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech1_data.InletAirTemp		= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							// N/A								= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							g_Haltech1_data.Lambda				= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x013:
							g_Haltech1_data.IgnitionAdvance		= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech1_data.Gear				= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech1_data.InjectorDuty		= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							default: break;
			}
		}
		else if	(g_e2p_data.E2P_1.model == Haltech2)
		{
			switch(msgID)
			{
				case 0x360:
							g_Haltech2_data.RPM					= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech2_data.ManifoldPressure	= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech2_data.ThrottlePosition	= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x361:
							g_Haltech2_data.FuelPressure		= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech2_data.OilPressure			= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							// N/A								= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x362:
							g_Haltech2_data.InjectorDuty		= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							// N/A								= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech2_data.IgnitionAdvance1	= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							g_Haltech2_data.IgnitionAdvance2	= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x368:
							g_Haltech2_data.Lambda				= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							// N/A								= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							// N/A								= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x370:
							g_Haltech2_data.GroundSpeed			= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech2_data.Gear				= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							// N/A								= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x372:
							g_Haltech2_data.InletAirTemp2		= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech2_data.BatteryVoltage		= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech2_data.BaroPressure		= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x373:
							g_Haltech2_data.EGT					= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							// N/A								= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							// N/A								= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x3E0:
							g_Haltech2_data.OilTemp				= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech2_data.EngineTemp			= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech2_data.InletAirTemp1		= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							g_Haltech2_data.FuelTemp			= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							default: break;
			}
		}
	}
	if((CAN_rcv_INTF & 0x01) == 0x01)
	{
		CANRxB0Read(&can_rcv[1], 8);
		
		if(Onetime_Peakclear_cnt > 0) Onetime_Peakclear_cnt --;
		
		msgID = MAKE_SID(can_rcv[1], can_rcv[2]);		// ID�쐬
		
		if		(g_e2p_data.E2P_1.model == MoTeC1)
		{
			switch(msgID)
			{
				case 0x010:
							g_MoTeC1_data.RPM					= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_MoTeC1_data.GroundSpeed			= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_MoTeC1_data.OilPressure			= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x011:
							g_MoTeC1_data.EngineTemp			= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_MoTeC1_data.FuelPressure			= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_MoTeC1_data.BatteryVoltage		= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							g_MoTeC1_data.ThrottlePosition		= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x012:
							g_MoTeC1_data.ManifoldPressure		= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_MoTeC1_data.InletAirTemp			= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							// N/A								= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							g_MoTeC1_data.Lambda				= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x013:
							g_MoTeC1_data.IgnitionAdvance		= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_MoTeC1_data.Gear					= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_MoTeC1_data.InjectorDuty			= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							default: break;
			}
		}
		else if	(g_e2p_data.E2P_1.model == Haltech1)
		{
			switch(msgID)
			{
				case 0x010:
							g_Haltech1_data.RPM					= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech1_data.GroundSpeed			= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech1_data.OilPressure			= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x011:
							g_Haltech1_data.EngineTemp			= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech1_data.FuelPressure		= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech1_data.BatteryVoltage		= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							g_Haltech1_data.ThrottlePosition	= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x012:
							g_Haltech1_data.ManifoldPressure	= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech1_data.InletAirTemp		= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							// N/A								= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							g_Haltech1_data.Lambda				= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x013:
							g_Haltech1_data.IgnitionAdvance		= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech1_data.Gear				= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech1_data.InjectorDuty		= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							default: break;
			}
		}
		else if	(g_e2p_data.E2P_1.model == Haltech2)
		{
			switch(msgID)
			{
				case 0x360:
							g_Haltech2_data.RPM					= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech2_data.ManifoldPressure	= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech2_data.ThrottlePosition	= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x361:
							g_Haltech2_data.FuelPressure		= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech2_data.OilPressure			= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							// N/A								= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x362:
							g_Haltech2_data.InjectorDuty		= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							// N/A								= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech2_data.IgnitionAdvance1	= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							g_Haltech2_data.IgnitionAdvance2	= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x368:
							g_Haltech2_data.Lambda				= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							// N/A								= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							// N/A								= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x370:
							g_Haltech2_data.GroundSpeed			= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech2_data.Gear				= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							// N/A								= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x372:
							g_Haltech2_data.InletAirTemp2		= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech2_data.BatteryVoltage		= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech2_data.BaroPressure		= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x373:
							g_Haltech2_data.EGT					= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							// N/A								= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							// N/A								= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							// N/A								= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							break;
				case 0x3E0:
							g_Haltech2_data.OilTemp				= ((((unsigned int) can_rcv[6] ) << 8) + can_rcv[7] );
							g_Haltech2_data.EngineTemp			= ((((unsigned int) can_rcv[8] ) << 8) + can_rcv[9] );
							g_Haltech2_data.InletAirTemp1		= ((((unsigned int) can_rcv[10]) << 8) + can_rcv[11]);
							g_Haltech2_data.FuelTemp			= ((((unsigned int) can_rcv[12]) << 8) + can_rcv[13]);
							default: break;
			}
		}
	}
	
	CANWriteReg(CANINTF, 0x00);
}

// --------------------------------------------------------------------
// ������荞�݃��[�`�� 50mSec��
// --------------------------------------------------------------------
void Int_50msFunc(void)
{
	// --------------------------------------------------------------------
	// ���[�J���ϐ��錾
	// --------------------------------------------------------------------
	unsigned long i;
	
	// --------------------------------------------------------------------
	// ���荞�݃t���O�N���A
	// --------------------------------------------------------------------
	TPU0.TSR.BIT.TGFA = 0;
	
	// --------------------------------------------------------------------
	// TFT LCD ���t���b�V������
	// --------------------------------------------------------------------
	Display_Home();
	g_refresh_done = 1;
	
	// --------------------------------------------------------------------
	// 50msec�J�E���^�C���N�������g
	// --------------------------------------------------------------------
	g_int50mscnt ++;
	
	// --------------------------------------------------------------------
	// �}�X�^�[���[�j���O����
	// --------------------------------------------------------------------
	if ((g_e2p_data.E2P_1.control.BIT.ms_on == 0)
	&& ((g_master_warning_flg1 == 1)
	||  (g_master_warning_flg2 == 1)
	||  (g_master_warning_flg3 == 1)
	||  (g_master_warning_flg4 == 1)
	||  (g_master_warning_flg5 == 1)
	||  (g_master_warning_flg6 == 1)))
	{
		master_warning_cnt ++;
		if(master_warning_cnt == 1)
		{
			Beep_OneShotMax();
		}
		else if(master_warning_cnt >= 10)
		{
			master_warning_cnt = 0;
		}
	}
	// --------------------------------------------------------------------
	// �V�t�g�^�C�~���O�����v����
	// --------------------------------------------------------------------
	else if(g_shift_timing_flg == 3)
	{
		g_shift_timing_cnt ++;
		
		if(g_shift_timing_cnt == 1)
		{
			Led_R_Min_ON();
			Led_O_Min_ON();
		}
		else if(g_shift_timing_cnt == 2)
		{
			Led_R_Min_OFF();
			Led_O_Min_OFF();
			g_shift_timing_cnt = 0;
		}
	}
	else if(g_shift_timing_flg == 2)
	{
		Led_R_Min_ON();
		Led_O_Min_ON();
	}
	else if(g_shift_timing_flg == 1)
	{
		Led_R_Min_OFF();
		Led_O_Min_ON();
	}
	else
	{
		master_warning_cnt = 0;
		Led_R_Min_OFF();
		Led_O_Min_OFF();
	}
	
	// --------------------------------------------------------------------
	// �^�b�`�p�l�����͏���
	// --------------------------------------------------------------------
	Touch_Read();
	
	// --------------------------------------------------------------------
	// �^�b�`�p�l���������f
	// --------------------------------------------------------------------
	Touch_Decision();
	
	// --------------------------------------------------------------------
	// �u�U�[����
	// --------------------------------------------------------------------
	if(g_e2p_data.E2P_1.control.BIT.beep_on == 0)	// �u�U�[ on/off �ݒ�ɂ��L���̎�
	{
		Beep_OneShotMin_control();					// ���u�U�[ 1�V���b�g ����
		Beep_OneShotMax_control();					// ��u�U�[ 1�V���b�g ����
		Beep_TwoShotMin_control();					// ���u�U�[ 2�V���b�g ����
	}
	else											// �u�U�[ on/off �ݒ�ɂ�薳���̎�
	{
		TPU3.TGRD = 0x0000;
		g_beep_oneshotmin_flg = 0;
		Beep_OneShotMin_cnt = 0;
		g_beep_oneshotmax_flg = 0;
		Beep_OneShotMax_cnt = 0;
		g_beep_twoshotmin_flg = 0;
		Beep_TwoShotMin_cnt = 0;
	}
	// --------------------------------------------------------------------
	// FPS�v���J�E���^�C���N�������g
	// --------------------------------------------------------------------
	g_fps_cnt ++;
	if(g_fps_cnt == 20)
	{
		g_fps_max = g_fps;
		g_fps = 0;
		g_fps_cnt = 0;
	}
	else
	{
		//
	}
	
//	// --------------------------------------------------------------------
//	// LED�I��/�I�t����
//	// --------------------------------------------------------------------
//	if((backlight_dimmer_flg == 0) && ((g_led_o_max_flg) || (g_led_o_min_flg))) { PM.DR.BIT.B0 = 1; } else { PM.DR.BIT.B0 = 0; }
//	if((backlight_dimmer_flg == 0) && ((g_led_r_max_flg) || (g_led_r_min_flg))) { PB.DR.BIT.B3 = 1; } else { PB.DR.BIT.B3 = 0; }
	
	// --------------------------------------------------------------------
	// EXDMA�]�����ԑҋ@
	// --------------------------------------------------------------------
	for(i = 0; i <= 60000; i++);
	
//	// --------------------------------------------------------------------
//	// LED��������
//	// --------------------------------------------------------------------
//	if(backlight_dimmer_flg)
//	{
//		if(g_led_o_min_flg) PM.DR.BIT.B0 = 0;
//		if(g_led_r_min_flg) PB.DR.BIT.B3 = 0;
//	}
}


// --------------------------------------------------------------------
// �^�b�`�p�l���������f
// --------------------------------------------------------------------
static void Touch_Decision(void)
{
	if((g_TouchX != 0) || (g_TouchY != 0))				// �^�b�`�����ł͖����ꍇ
	{
		if((g_TouchX != 999) || (g_TouchY != 999))		// ����������ł͖����ꍇ
		{
			touch_cnt ++;		// �������J�E���g�A�b�v
			if(touch_cnt > 10)
			touch_cnt = 10;		// ���~�b�g
		}
		else
		{
			touch_cnt = 0;		// �����[�X�N���A
		}
	}
	else
	{
		touch_cnt = 0;			// �����[�X�N���A
	}
	
	if(touch_cnt == 1)			// ����1��ɂ�
	{
 		// �}�X�^�[���[�j���O����
 		if(g_master_warning_flg1 == 1)g_master_warning_flg1 = 2;
 		if(g_master_warning_flg2 == 1)g_master_warning_flg2 = 2;
 		if(g_master_warning_flg3 == 1)g_master_warning_flg3 = 2;
 		if(g_master_warning_flg4 == 1)g_master_warning_flg4 = 2;
 		if(g_master_warning_flg5 == 1)g_master_warning_flg5 = 2;
 		if(g_master_warning_flg6 == 1)g_master_warning_flg6 = 2;
		Beep_OneShotMin();		// �u�U�[��
		touch_done_flg = 1;		// �^�b�`�������蔭�s
		g_PressX = g_TouchX;	// ����X���W
		g_PressY = g_TouchY;
	}
	else
	{
		//
	}
	if(touch_cnt >= 2)			// �A�������̎�
	{
	//	Beep_OneShotMin();		// �u�U�[��
		touch_drag_flg = 1;		// �h���b�O���蔭�s
		g_DragX = g_TouchX;		// ����X���W
		g_DragY = g_TouchY;
	}
	else
	{
		//
	}
}

// --------------------------------------------------------------------
// ���u�U�[ 1�V���b�g ����
// --------------------------------------------------------------------
static void Beep_OneShotMin_control(void)
{
	if(g_beep_oneshotmin_flg == 1)
	{
		g_beep_oneshotmin_flg = 2;
		Beep_OneShotMin_cnt = 0;
	}
	else
	{
		//
	}
	
	if(g_beep_oneshotmin_flg == 2)
	{
		TPU3.TGRD = 0x0100;
		Beep_OneShotMin_cnt ++;
	
		if(Beep_OneShotMin_cnt >= 2)	// 0.1sec�o��
		{
			TPU3.TGRD = 0x0000;
			g_beep_oneshotmin_flg = 0;
			Beep_OneShotMin_cnt = 0;
		}
		else
		{
			//
		}
	}
}

// --------------------------------------------------------------------
// ��u�U�[ 1�V���b�g ����
// --------------------------------------------------------------------
static void Beep_OneShotMax_control(void)
{
	if(g_beep_oneshotmax_flg == 1)
	{
		g_beep_oneshotmax_flg = 2;
		Beep_OneShotMax_cnt = 0;
	}
	else
	{
		//
	}
	
	if(g_beep_oneshotmax_flg == 2)
	{
		TPU3.TGRD = 0x0BB8;
		Led_R_Min_ON();
		Led_O_Min_OFF();
		Beep_OneShotMax_cnt ++;
	
		if(Beep_OneShotMax_cnt >= 5)	// 0.25sec�o��
		{
			TPU3.TGRD = 0x0000;
			Led_R_Min_OFF();
			Led_O_Min_OFF();
			g_beep_oneshotmax_flg = 0;
			Beep_OneShotMax_cnt = 0;
		}
		else
		{
			//
		}
	}
}

// --------------------------------------------------------------------
// ���u�U�[ 2�V���b�g ����
// --------------------------------------------------------------------
static void Beep_TwoShotMin_control(void)
{
	if(g_beep_twoshotmin_flg == 1)
	{
		g_beep_twoshotmin_flg = 2;
		Beep_TwoShotMin_cnt = 0;
	}
	else
	{
		//
	}
	
	if(g_beep_twoshotmin_flg == 2)
	{
		Beep_TwoShotMin_cnt ++;
	
		if     (Beep_TwoShotMin_cnt == 1)	// 0.00sec�o��
		{
			TPU3.TGRD = 0x0100;
		}
		else if(Beep_TwoShotMin_cnt == 2)	// 0.05sec�o��
		{
			TPU3.TGRD = 0x0000;
		}
		else if(Beep_TwoShotMin_cnt == 3)	// 0.10sec�o��
		{
			TPU3.TGRD = 0x0100;
		}
		else if(Beep_TwoShotMin_cnt >= 4)	// 0.20sec�o��
		{
			TPU3.TGRD = 0x0000;
			g_beep_twoshotmin_flg = 0;
			Beep_TwoShotMin_cnt = 0;
		}
		else
		{
			//
		}
	}
}

// --------------------------------------------------------------------
// LED�I��/�I�t����
// --------------------------------------------------------------------
void Int_LEDonoff(void)
{
	// --------------------------------------------------------------------
	// ���荞�݃t���O�N���A
	// --------------------------------------------------------------------
	TPU6.TSR.BIT.TGFA = 0;
	
	if		(LEDonoff_cnt == 0)
	{
		if((g_led_o_max_flg) || (g_led_o_min_flg)) { PM.DR.BIT.B0 = 1;} else { PM.DR.BIT.B0 = 0; }
		if((g_led_r_max_flg) || (g_led_r_min_flg)) { PB.DR.BIT.B3 = 1;} else { PB.DR.BIT.B3 = 0; }
	}
	else if((LEDonoff_cnt >= 1) && (LEDonoff_cnt <= 19))
	{
		if((backlight_dimmer_flg == 1) && ((g_led_o_max_flg) || (g_led_o_min_flg))) PM.DR.BIT.B0 = 0;
		if((backlight_dimmer_flg == 1) && ((g_led_r_max_flg) || (g_led_r_min_flg))) PB.DR.BIT.B3 = 0;
	}
	
	LEDonoff_cnt ++;
	if(LEDonoff_cnt > 19) LEDonoff_cnt = 0;
}

#ifdef __cplusplus
void abort(void)
{

}
#endif

