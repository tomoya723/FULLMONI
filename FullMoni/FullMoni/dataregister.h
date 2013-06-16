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
// filename		:	dataregister.h
// brief		:	FullMoni rev.B �f�[�^�Ǘ�
// author		:	Tomoya Sato
// update		:	2013/06/16
// version		:	1.03
// --------------------------------------------------------------------

// --------------------------------------------------------------------
// ���d�C���N���[�h�h�~
// --------------------------------------------------------------------
#ifndef _DATAREGISTER_H_
#define _DATAREGISTER_H_

// --------------------------------------------------------------------
// define�錾
// --------------------------------------------------------------------
#define num_data_select_value	90
#define rev_data_select_value	4
#define afr_data_select_value	6
#define num_dp_value			3
#define num_label_value			16
#define afr_label_value			2
#define num_unit_value			4

// --------------------------------------------------------------------
// �v���g�^�C�v�錾
// --------------------------------------------------------------------
void Init_e2p_data(void);
void Init_MoTeC1_data(void);
void Init_MoTeC2_data(void);
void Init_Haltech1_data(void);
void Init_Haltech2_data(void);
void Init_Freedom2_data(void);
unsigned int rev_data_select(unsigned char rev_data_select);
unsigned int afr_data_select(unsigned char afr_data_select);
unsigned int num_data_select(unsigned char num_data_select);
void rev_data_select_draw(unsigned char rev_data_select_draw);
void afr_data_select_draw(unsigned char afr_data_select_draw);
void num_data_select_draw(unsigned char num_data_select_draw);
void num_dp_draw(unsigned char num_dp);
void num_label_draw(unsigned char num_tag);
void num_unit_draw(unsigned char num_unit);

// --------------------------------------------------------------------
// MoTeC m#00�n�f�[�^���W�X�^
// --------------------------------------------------------------------
typedef struct {
	unsigned int RPM;					/* �G���W����]��		*/
	unsigned int ThrottlePosition;		/* �X���|�W				*/
	unsigned int ManifoldPressure;		/* �z�C��				*/
	unsigned int InletAirTemp;			/* �z�C��				*/
	unsigned int EngineTemp;			/* �G���W�����x			*/
	unsigned int Lambda1;				/* �����_�l1			*/
	unsigned int Lambda2;				/* �����_�l2			*/
	unsigned int ExhaustPressure;		/* �r�C��				*/
	unsigned int MassAirFlow;			/* �G�A�t��				*/
	unsigned int FuelTemp;				/* �R��					*/
	unsigned int FuelPressure;			/* �R��					*/
	unsigned int OilTemp;				/* ����					*/
	unsigned int OilPressure;			/* ����					*/
//	unsigned int GearVoltage;			/* �M�A�d��				*/
//	unsigned int KnockVoltage;			/* �m�b�N�d��			*/
//	unsigned int GearShiftForce;		/* �M�A�V�t�g�t�H�[�X	*/
	unsigned int ExhaustTemp1;			/* �r�C��1				*/
	unsigned int ExhaustTemp2;			/* �r�C��2				*/
//	unsigned int UserChannel1;			/* ���[�U�`�����l��1	*/
//	unsigned int UserChannel2;			/* ���[�U�`�����l��2	*/
//	unsigned int UserChannel3;			/* ���[�U�`�����l��3	*/
//	unsigned int UserChannel4;			/* ���[�U�`�����l��4	*/
	unsigned int BatteryVoltage;		/* �o�b�e���[�d��		*/
	unsigned int ECUTemp;				/* ECU�������x			*/
//	unsigned int Dig1Speed;				/* Dig1���x				*/
//	unsigned int Dig2Speed;				/* Dig2���x				*/
//	unsigned int Dig3Speed;				/* Dig3���x				*/
//	unsigned int Dig4Speed;				/* Dig4���x				*/
//	unsigned int DriveSpeed;			/* �h���C�u���x			*/
	unsigned int GroundSpeed;			/* �ԑ�					*/
//	unsigned int Slip;					/* �X���b�v���x			*/
//	unsigned int AimSlip;				/* �ڕW�X���b�v���x		*/
//	unsigned int LaunchRPM;				/* ���[���`��]��		*/
//	unsigned int La1ShortTrim;			/* �����_1�Z���ԕ␳	*/
//	unsigned int La2ShortTrim;			/* �����_2�Z���ԕ␳	*/
//	unsigned int La1LongTrim;			/* �����_1�����ԕ␳	*/
//	unsigned int La2LongTrim;			/* �����_2�����ԕ␳	*/
	unsigned int AimLambda1;			/* �ڕW�����_�l1		*/
	unsigned int AimLambda2;			/* �ڕW�����_�l2		*/
//	unsigned int FuelCutLevel;			/* �R���J�b�g���x��		*/
//	unsigned int IGCutLevel;			/* �_�΃J�b�g���x��		*/
	unsigned int IgnitionAdvance;		/* �_�Ύ���				*/
//	unsigned int LoadPoint;				/* ���׎��l				*/
//	unsigned int EffPoint;				/* ���׎��l				*/
//	unsigned int FuelUsed;				/* 						*/
//	unsigned int Aux1Duty;				/* Aux1�f���[�e�B		*/
//	unsigned int Aux2Duty;				/* Aux2�f���[�e�B		*/
//	unsigned int Aux3Duty;				/* Aux3�f���[�e�B		*/
//	unsigned int Aux4Duty;				/* Aux4�f���[�e�B		*/
//	unsigned int Aux5Duty;				/* Aux5�f���[�e�B		*/
//	unsigned int Aux6Duty;				/* Aux6�f���[�e�B		*/
//	unsigned int Aux7Duty;				/* Aux7�f���[�e�B		*/
//	unsigned int Aux8Duty;				/* Aux8�f���[�e�B		*/
//	unsigned int FuelActualWidth;		/* 						*/
//	unsigned int FuelEffPulseWidth;		/* 						*/
	unsigned int InjectorDuty;			/* �J�ٗ�				*/
	unsigned int Gear;					/* �M�A�|�W�V����		*/
//	unsigned int SyncPosition;			/* 						*/
//	unsigned int FuelComp1;				/* 						*/
//	unsigned int FuelComp2;				/* 						*/
} MoTeC1_data_t;

// --------------------------------------------------------------------
// Haltech E8/E11�f�[�^���W�X�^
// --------------------------------------------------------------------
typedef struct {
	unsigned int RPM;					/* �G���W����]��		*/
	unsigned int GroundSpeed;			/* �ԑ�					*/
	unsigned int OilPressure;			/* ����					*/
	unsigned int EngineTemp;			/* �G���W�����x			*/
	unsigned int FuelPressure;			/* �R��					*/
	unsigned int BatteryVoltage;		/* �o�b�e���[�d��		*/
	unsigned int ThrottlePosition;		/* �X���|�W				*/
	unsigned int ManifoldPressure;		/* �z�C��				*/
	unsigned int InletAirTemp;			/* �z�C��				*/
	unsigned int Lambda;				/* �����_�l				*/
	unsigned int IgnitionAdvance;		/* �_�Ύ���				*/
	unsigned int Gear;					/* �M�A�|�W�V����		*/
	unsigned int InjectorDuty;			/* �J�ٗ�				*/
} Haltech1_data_t;

// --------------------------------------------------------------------
// Haltech SPORT�n�f�[�^���W�X�^
// --------------------------------------------------------------------
typedef struct {
	unsigned int RPM;					/* �G���W����]��		*/
	unsigned int ManifoldPressure;		/* �z�C��				*/
	unsigned int ThrottlePosition;		/* �X���|�W				*/
	unsigned int FuelPressure;			/* �R��					*/
	unsigned int OilPressure;			/* ����					*/
	unsigned int InjectorDuty;			/* �J�ٗ�				*/
	unsigned int IgnitionAdvance1;		/* �_�Ύ���1			*/
	unsigned int IgnitionAdvance2;		/* �_�Ύ���2			*/
	unsigned int Lambda;				/* �����_�l				*/
	unsigned int GroundSpeed;			/* �ԑ�					*/
	unsigned int Gear;					/* �M�A�|�W�V����		*/
	unsigned int BatteryVoltage;		/* �o�b�e���[�d��		*/
	unsigned int InletAirTemp2;			/* �z�C��2				*/
	unsigned int BaroPressure;			/* ��C��				*/
	unsigned int EGT;					/* �r�C��				*/
	unsigned int EngineTemp;			/* �G���W�����x			*/
	unsigned int InletAirTemp1;			/* �z�C��1				*/
	unsigned int FuelTemp;				/* �R��					*/
	unsigned int OilTemp;				/* ����					*/
} Haltech2_data_t;

// --------------------------------------------------------------------
// Freedom Ver3.XX �f�[�^���W�X�^
// --------------------------------------------------------------------
typedef struct {
	unsigned int RPM;					/* �G���W����]��		*/
	unsigned int ManifoldPressure;		/* �z�C��				*/
	unsigned int EngineTemp;			/* �G���W�����x			*/
	unsigned int InletAirTemp;			/* �z�C��				*/
	unsigned int BarometricPressure;	/* �O�C��				*/
	unsigned int ThrottlePosition;		/* �X���b�g���|�W�V����	*/
	unsigned int BatteryVoltage;		/* �o�b�e���[�d��		*/
	unsigned int ValidFuelTime;			/* �L�����ˎ���			*/
	unsigned int InvalidFuelTime;		/* �������ˎ���			*/
	unsigned int IgnitionAdvance;		/* �_�Ύ���				*/
	unsigned int Status;				/* �X�e�[�^�X			*/
	unsigned int GroundSpeed;			/* �f�[�^				*/
	unsigned int AFR;					/* AFR�l				*/
	unsigned int AimAFR;				/* �ڕWAFR�l			*/
	unsigned int IATCorrection;			/* �z�C���␳			*/
	unsigned int ETCorrection;			/* �����␳				*/
	unsigned int EStartCorrection;		/* �n���㑝�ʕ␳		*/
	unsigned int AccelCorrection;		/* �������␳			*/
	unsigned int PowerCorrection;		/* �o�͑��ʕ␳			*/
	unsigned int FeedbackCorrection;	/* �t�B�[�h�o�b�N�␳	*/
	unsigned int IdolCorrection;		/* �A�C�h�����艻�␳	*/
	unsigned int DecelCutCorrection;	/* ���˕��A�␳			*/
	unsigned int BaroCorrection;		/* �O�C���␳			*/
	unsigned int IdolIGCorrection;		/* �A�C�h�����艻�_�Ε␳			*/
	unsigned int RetardCorrection;		/* ���˕��A�_�Ε␳���m�b�N�x�p�␳	*/
} Freedom2_data_t;

// --------------------------------------------------------------------
// MegaSquirt(MS2/Extra) �f�[�^���W�X�^
// --------------------------------------------------------------------
typedef struct {						/* 						*/
	unsigned int rpm;					/* 						*/
	unsigned int advance;				/* 						*/
	unsigned int afrtgt1;				/* 						*/
	unsigned int afrtgt2;				/* 						*/
	unsigned int barometer;				/* 						*/
	unsigned int map;					/* 						*/
	unsigned int mat;					/* 						*/
	unsigned int coolant;				/* 						*/
	unsigned int tps;					/* 						*/
	unsigned int batteryVoltage;		/* 						*/
	unsigned int afr1;					/* 						*/
	unsigned int afr2;					/* 						*/
} Megasquirt1_data_t;

#pragma pack 1
// --------------------------------------------------------------------
// EEPROM�f�[�^���W�X�^
// --------------------------------------------------------------------
typedef struct {						/*										*/
	struct {							/*										*/
		union {							/*										*/
			unsigned char BYTE;			/*	0x0000	EEPROM�Ǘ�					*/
			struct {					/*										*/
				unsigned WROK		:1;	/*		b0	�������ݐ���/�ُ�t���O		*/
				unsigned 			:1;	/*		b1								*/
				unsigned 			:1;	/*		b2								*/
				unsigned 			:1;	/*		b3								*/
				unsigned 			:1;	/*		b4								*/
				unsigned 			:1;	/*		b5								*/
				unsigned 			:1;	/*		b6								*/
				unsigned 			:1;	/*		b7								*/
			} BIT;						/*										*/
		} E2Pmanage;					/*										*/
		unsigned char model;			/*	0x0001	�Ή����f���I��ԍ�			*/
		union {							/*										*/
			unsigned char BYTE;			/*	0x0002	�t�����j�Ǘ�				*/
			struct {					/*										*/
				unsigned beep_on	:1;	/*		b0	�u�U�[ on/off				*/
				unsigned ms_on		:1;	/*		b1	�}�X�^�[���[�j���O on/off	*/
				unsigned FC_mode	:1;	/*		b2	�t���[�_�����[�h FAST/ALL	*/
				unsigned defi_on	:1;	/*		b3	Defi��M on/off				*/
				unsigned 			:1;	/*		b4								*/
				unsigned 			:1;	/*		b5								*/
				unsigned 			:1;	/*		b6								*/
				unsigned 			:1;	/*		b7								*/
			} BIT;						/*										*/
		} control;						/*										*/
		unsigned char tp_Xmin;			/*	0x0003	�^�b�`�p�l��X�������Z���l	*/
		unsigned char tp_Xmax;			/*	0x0004	�^�b�`�p�l��X������Z���l	*/
		unsigned char tp_Ymin;			/*	0x0005	�^�b�`�p�l��Y�������Z���l	*/
		unsigned char tp_Ymax;			/*	0x0006	�^�b�`�p�l��Y������Z���l	*/
		unsigned char dimmer1;			/*	0x0007	�o�b�N���C�g�f�B�}�[����1	*/
		unsigned char dimmer2;			/*	0x0008	�o�b�N���C�g�f�B�}�[����2	*/
		unsigned char dummy1;			/*	0x0009								*/
		unsigned char dummy2;			/*	0x000A								*/
		unsigned char dummy3;			/*	0x000B								*/
		unsigned char dummy4;			/*	0x000C								*/
		unsigned char dummy5;			/*	0x000D								*/
		unsigned char dummy6;			/*	0x000E								*/
		unsigned char dummy7;			/*	0x000F								*/
	} E2P_1;							/* 										*/
	struct {							/*										*/
		int           rev_timing_rmp1;	/*	0x0010	�V�t�g�����v ��쓮��]��	*/
										/*	0x0011								*/
		int           rev_timing_rmp2;	/*	0x0012	�V�t�g�����v �ԍ쓮��]��	*/
										/*	0x0013								*/
		int           rev_timing_rmp3;	/*	0x0014	�V�t�g�����v ��+�ԍ쓮��]��*/
										/*	0x0015								*/
		unsigned char dummy1;			/*	0x0016								*/
		unsigned char dummy2;			/*	0x0017								*/
		unsigned char dummy3;			/*	0x0018								*/
		unsigned char dummy4;			/*	0x0019								*/
		unsigned char dummy5;			/*	0x001A								*/
		unsigned char dummy6;			/*	0x001B								*/
		unsigned char dummy7;			/*	0x001C								*/
		unsigned char dummy8;			/*	0x001D								*/
		unsigned char dummy9;			/*	0x001E								*/
		unsigned char dummyA;			/*	0x001F								*/
	} E2P_2;							/* 										*/
	struct {							/*										*/
		unsigned char rev_data_select;	/*	0x0020	��]�� �f�[�^�I��			*/
		int           rev_gain;			/*	0x0021	��]�� �Q�C��H				*/
										/*	0x0022	��]�� �Q�C��L				*/
		int           rev_bias;			/*	0x0023	��]�� �o�C�A�XH			*/
										/*	0x0024	��]�� �o�C�A�XL			*/
		unsigned char dummy1;			/*	0x0025								*/
		unsigned char dummy2;			/*	0x0026								*/
		unsigned char dummy3;			/*	0x0027								*/
		unsigned char afr_data_select;	/*	0x0028	��R�� �f�[�^�I��			*/
		int           afr_gain;			/*	0x0029	��R�� �Q�C��H				*/
										/*	0x002A	��R�� �Q�C��L				*/
		int           afr_bias;			/*	0x002B	��R�� �o�C�A�XH			*/
										/*	0x002C	��R�� �o�C�A�XL			*/
		unsigned char afr_dp;			/*	0x002D	��R�� �����_�ʒu			*/
		unsigned char afr_label;		/*	0x002E	��R�� ���x���I��			*/
		unsigned char dummy4;			/*	0x002F								*/
	} E2P_3;							/* 										*/
	struct {							/*										*/
		unsigned char num1_data_select;	/*	0x0030	���l�\��1 �f�[�^�I��		*/
		int           num1_gain;		/*	0x0031	���l�\��1 �Q�C��H			*/
										/*	0x0032	���l�\��1 �Q�C��L			*/
		int           num1_bias;		/*	0x0033	���l�\��1 �o�C�A�XH			*/
										/*	0x0034	���l�\��1 �o�C�A�XL			*/
		unsigned char num1_dp;			/*	0x0035	���l�\��1 �����_�ʒu		*/
		unsigned char num1_label;		/*	0x0036	���l�\��1 ���x���I��		*/
		unsigned char num1_unit;		/*	0x0037	���l�\��1 �P�ʑI��			*/
		unsigned char num2_data_select;	/*	0x0038	���l�\��2 �f�[�^�I��		*/
		int           num2_gain;		/*	0x0039	���l�\��2 �Q�C��H			*/
										/*	0x003A	���l�\��2 �Q�C��L			*/
		int           num2_bias;		/*	0x003B	���l�\��2 �o�C�A�XH			*/
										/*	0x003C	���l�\��2 �o�C�A�XL			*/
		unsigned char num2_dp;			/*	0x003D	���l�\��2 �����_�ʒu		*/
		unsigned char num2_label;		/*	0x003E	���l�\��2 �^�O�I��			*/
		unsigned char num2_unit;		/*	0x003F	���l�\��2 �P�ʑI��			*/
	} E2P_4;							/* 										*/
	struct {							/*										*/
		unsigned char num3_data_select;	/*	0x0040	���l�\��3 �f�[�^�I��		*/
		int           num3_gain;		/*	0x0041	���l�\��3 �Q�C��H			*/
										/*	0x0042	���l�\��3 �Q�C��L			*/
		int           num3_bias;		/*	0x0043	���l�\��3 �o�C�A�XH			*/
										/*	0x0044	���l�\��3 �o�C�A�XL			*/
		unsigned char num3_dp;			/*	0x0045	���l�\��3 �����_�ʒu		*/
		unsigned char num3_label;		/*	0x0046	���l�\��3 ���x���I��		*/
		unsigned char num3_unit;		/*	0x0047	���l�\��3 �P�ʑI��			*/
		unsigned char num4_data_select;	/*	0x0048	���l�\��4 �f�[�^�I��		*/
		int           num4_gain;		/*	0x0049	���l�\��4 �Q�C��H			*/
										/*	0x004A	���l�\��4 �Q�C��L			*/
		int           num4_bias;		/*	0x004B	���l�\��4 �o�C�A�XH			*/
										/*	0x003C	���l�\��4 �o�C�A�XL			*/
		unsigned char num4_dp;			/*	0x004D	���l�\��4 �����_�ʒu		*/
		unsigned char num4_label;		/*	0x004E	���l�\��4 ���x���I��		*/
		unsigned char num4_unit;		/*	0x004F	���l�\��4 �P�ʑI��			*/
	} E2P_5;							/* 										*/
	struct {							/*										*/
		unsigned char num5_data_select;	/*	0x0050	���l�\��5 �f�[�^�I��		*/
		int           num5_gain;		/*	0x0051	���l�\��5 �Q�C��H			*/
										/*	0x0052	���l�\��5 �Q�C��L			*/
		int           num5_bias;		/*	0x0053	���l�\��5 �o�C�A�XH			*/
										/*	0x0054	���l�\��5 �o�C�A�XL			*/
		unsigned char num5_dp;			/*	0x0055	���l�\��5 �����_�ʒu		*/
		unsigned char num5_label;		/*	0x0056	���l�\��5 ���x���I��		*/
		unsigned char num5_unit;		/*	0x0057	���l�\��5 �P�ʑI��			*/
		unsigned char num6_data_select;	/*	0x0058	���l�\��6 �f�[�^�I��		*/
		int           num6_gain;		/*	0x0059	���l�\��6 �Q�C��H			*/
										/*	0x005A	���l�\��6 �Q�C��L			*/
		int           num6_bias;		/*	0x005B	���l�\��6 �o�C�A�XH			*/
										/*	0x005C	���l�\��6 �o�C�A�XL			*/
		unsigned char num6_dp;			/*	0x005D	���l�\��6 �����_�ʒu		*/
		unsigned char num6_label;		/*	0x005E	���l�\��6 ���x���I��		*/
		unsigned char num6_unit;		/*	0x005F	���l�\��6 �P�ʑI��			*/
	} E2P_6;							/* 										*/
	struct {							/*										*/
		int           num1_warning;		/*	0x0060	���l1����l					*/
										/*	0x0061								*/
		int           num2_warning;		/*	0x0062	���l2����l					*/
										/*	0x0063								*/
		int           num3_warning;		/*	0x0064	���l3����l					*/
										/*	0x0065								*/
		int           num4_warning;		/*	0x0066	���l4����l					*/
										/*	0x0067								*/
		int           num5_warning;		/*	0x0068	���l5����l					*/
										/*	0x0069								*/
		int           num6_warning;		/*	0x006A	���l6����l					*/
										/*	0x006B								*/
		unsigned char dummy1;			/*	0x006C								*/
		unsigned char dummy2;			/*	0x006D								*/
		unsigned char dummy3;			/*	0x006E								*/
		unsigned char dummy4;			/*	0x006F								*/
	} E2P_7;							/* 										*/
	struct {							/*										*/
		unsigned char dummy0;			/*	0x0070								*/
		unsigned char dummy1;			/*	0x0071								*/
		unsigned char dummy2;			/*	0x0072								*/
		unsigned char dummy3;			/*	0x0073								*/
		unsigned char dummy4;			/*	0x0074								*/
		unsigned char dummy5;			/*	0x0075								*/
		unsigned char dummy6;			/*	0x0076								*/
		unsigned char dummy7;			/*	0x0077								*/
		unsigned char dummy8;			/*	0x0078								*/
		unsigned char dummy9;			/*	0x0079								*/
		unsigned char dummyA;			/*	0x007A								*/
		unsigned char dummyB;			/*	0x007B								*/
		unsigned char dummyC;			/*	0x007C								*/
		unsigned char dummyD;			/*	0x007D								*/
		unsigned char dummyE;			/*	0x007E								*/
		unsigned char dummyF;			/*	0x007F								*/
	} E2P_8;							/* 										*/
} e2p_data_t;
#pragma unpack

// --------------------------------------------------------------------
// extern�錾
// --------------------------------------------------------------------
extern volatile e2p_data_t			g_e2p_data;
extern volatile MoTeC1_data_t		g_MoTeC1_data;
extern volatile Haltech1_data_t		g_Haltech1_data;
extern volatile Haltech2_data_t		g_Haltech2_data;
extern volatile Freedom2_data_t		g_Freedom2_data;
extern volatile Megasquirt1_data_t	g_Megasquirt1_data;

// --------------------------------------------------------------------
// ���d�C���N���[�h�h�~
// --------------------------------------------------------------------
#endif /* _DATAREGISTER_H_ */
