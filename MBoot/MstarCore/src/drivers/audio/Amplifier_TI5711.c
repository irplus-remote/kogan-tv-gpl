//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
 //wjq20100112>>>
#include <common.h>
#include <audio/Amplifier_TI5711.h>
#include <linux/types.h>
#include <apiSWI2C.h>


#define TAS5711_ADDR     0x36
#define TAS5711_BUSID     (((MS_U16) E_I2C_BUS_SYS << 8) | TAS5711_ADDR)


MAPI_U8  g_ucTas5711RegAddr;

MAPI_U8 AmpInitTbl[]=
{
    //DataLength        Address     DataN       DataN+1...
    // I2C Configuration file for TAS5700x
    1,0x1B,0x00,
    1,0x06,0x00,
    1,0x0A,0xFF,
    1,0x09,0x30,
    1,0x09,0x30,
    1,0x08,0x30,
    1,0x14,0x54,
    1,0x13,0xAC,
    1,0x12,0x54,
    1,0x11,0xAC,
    1,0x0E,0xD1,
    1,0x1A,0x95,
    4,0x20,0x00,0x01,0x77,0x72,
    4,0x21,0x00,0x00,0x42,0x03,
    1,0x10,0x02,
    1,0x0B,0x00,
    1,0x10,0x02,
    1,0x1C,0x02,
    1,0x19,0x30,
    4,0x25,0x01,0x01,0x32,0x45,
    // Biquads
    4,0x50,0x00,0x00,0x00,0x00,
    20,0x29,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x30,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x2A,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x2B,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x2C,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x2D,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x2E,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x2F,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x58,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x59,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x31,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x32,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x33,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x34,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x35,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x36,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x5C,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x5D,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x5E,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x5F,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    20,0x5A,0x00,0x00,0x05,0x83,0x00,0x00,0x0B,0x06,0x00,0x00,0x05,0x83,0x00,0xFB,0x42,0xC1,0x0F,0x84,0xA7,0x33,
    20,0x5B,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    // DRCs
    8,0x3A,0x00,0x7F,0xFF,0xB4,0x00,0x00,0x00,0x4B,
    8,0x3B,0x00,0x7F,0xFF,0xB4,0x00,0x00,0x00,0x4B,
    8,0x3C,0x00,0x7F,0xFF,0xB4,0x00,0x00,0x00,0x4B,
    4,0x40,0xFC,0x83,0x10,0xD4,
    4,0x41,0x0F,0x83,0x33,0x34,
    4,0x42,0x00,0x08,0x42,0x10,
    4,0x46,0x00,0x00,0x00,0x00,
    8,0x39,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    8,0x3D,0x00,0x7F,0xFF,0xB4,0x00,0x00,0x00,0x08,
    8,0x3E,0x00,0x7F,0xFF,0xB4,0x00,0x00,0x00,0x08,
    8,0x3F,0x00,0x7F,0xFF,0xB4,0x00,0x00,0x00,0x08,
    4,0x43,0xFC,0x83,0x10,0xD4,
    4,0x44,0x0F,0x83,0x33,0x34,
    4,0x45,0x00,0x08,0x42,0x10,
    4,0x46,0x00,0x00,0x00,0x00,
    12,0x52,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    8,0x60,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,
    4,0x56,0x00,0x80,0x00,0x00,
    4,0x57,0x00,0x02,0x00,0x00,
    16,0x53,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,
    16,0x54,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,
    12,0x55,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    12,0x51,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    1,0x07,0xF0,
    1,0x05,0x84,
    0x00,
};

MAPI_BOOL Amplifier_TI5711_Init(void)
{
        MAPI_U8 * Pstr=NULL;
        MAPI_U8 DataLength = 0;
//        printf("********Amplifier_Init\n");

		Amplifier_TI5711_Reset(1);
		MsOS_DelayTask(2);
		Amplifier_TI5711_StandBy(FALSE);

    	MsOS_DelayTask(10);
		Amplifier_TI5711_Reset(0);

    	MsOS_DelayTask(50);

        Pstr = AmpInitTbl;

        do
        {
            DataLength = *Pstr;
            if(DataLength>20)
            {
                printf("5711 set command error!!\n");
                break;
            }
            g_ucTas5711RegAddr = *(++Pstr);
            Pstr++;

            if (MApi_SWI2C_WriteBytes(TAS5711_BUSID,1,&g_ucTas5711RegAddr,DataLength, Pstr) == FALSE)
		        printf("5711write fail = %d\n",g_ucTas5711RegAddr);

            if (g_ucTas5711RegAddr==0x1B)
            {
                MsOS_DelayTask(50);
            }
            else
            {
                MsOS_DelayTask(1);
            }

            Pstr = Pstr + DataLength;
        }while(*Pstr != 0);

	return MAPI_TRUE;
}


MAPI_U8 AmpmasterSWMute[]=
{
    1,0x06,0x07,
    0x00,
};
MAPI_U8 AmpmasterSWUnMute[]=
{
    1,0x06,0x00,
    0x00,
};

MAPI_U8 AmpmasterMuteVolume[]=
{
    1,0x07,0xFF,
    0x00,
};
MAPI_U8 AmpmasterVolume_ATV[]=
{
    1,0x07,0xF0,
    1,0x07,0x7C,
    1,0x07,0x37,
    0x00,
};
MAPI_U8 AmpmasterVolume_OTHER[]=
{
    1,0x07,0xF0,
    1,0x07,0x7C,
    1,0x07,0x37,
    1,0x07,0x06,
    0x00,
};

MAPI_BOOL Amplifier_TI5711_SWMute(MAPI_BOOL bMute)
{
    MAPI_U8 * Pstr;
    MAPI_U8 DataLength = 0;

    printf("******Amplifier_TI5711_SWMute(%d)\n",bMute);
    if(bMute)
    {
	Pstr=AmpmasterMuteVolume;
        do
        {
            DataLength = *Pstr;
            if(DataLength>20)
            {
                printf("5711 set command error!!\n");
                break;
            }
            g_ucTas5711RegAddr = *(++Pstr);
            Pstr++;

            if (MApi_SWI2C_WriteBytes(TAS5711_BUSID,1, &g_ucTas5711RegAddr, DataLength, Pstr) == FALSE)
		        printf("5711write fail = %d\n",g_ucTas5711RegAddr);

            MsOS_DelayTask(2);
            Pstr = Pstr + DataLength;
        }while(*Pstr != 0);

	Pstr=AmpmasterSWMute;
        do
        {
            DataLength = *Pstr;
            if(DataLength>20)
            {
                printf("5711 set command error!!\n");
                break;
            }
            g_ucTas5711RegAddr = *(++Pstr);
            Pstr++;
            #if 0
            if(iptr->WriteBytes(1, &g_ucTas5711RegAddr, DataLength, Pstr) == MAPI_FALSE)
                printf("5711write fail = %d\n",g_ucTas5711RegAddr);
            #else
            if (MApi_SWI2C_WriteBytes(TAS5711_BUSID,1, &g_ucTas5711RegAddr, DataLength, Pstr) == FALSE)
		        printf("5711write fail = %d\n",g_ucTas5711RegAddr);
            #endif
            MsOS_DelayTask(2);
            Pstr = Pstr + DataLength;
        }while(*Pstr != 0);
    }
    else
    {
	Pstr=AmpmasterVolume_OTHER;
        do
        {
            DataLength = *Pstr;
            if(DataLength>20)
            {
                printf("5711 set command error!!\n");
                break;
            }
            g_ucTas5711RegAddr = *(++Pstr);
            Pstr++;
            #if 0
            if(iptr->WriteBytes(1, &g_ucTas5711RegAddr, DataLength, Pstr) == MAPI_FALSE)
                printf("5711write fail = %d\n",g_ucTas5711RegAddr);
            #else
            if (MApi_SWI2C_WriteBytes(TAS5711_BUSID,1, &g_ucTas5711RegAddr, DataLength, Pstr) == FALSE)
		        printf("5711write fail = %d\n",g_ucTas5711RegAddr);
            #endif
            MsOS_DelayTask(2);

            Pstr = Pstr + DataLength;
        }while(*Pstr != 0);

	Pstr=AmpmasterSWUnMute;
        do
        {
            DataLength = *Pstr;
            if(DataLength>20)
            {
                printf("5711 set command error!!\n");
                break;
            }
            g_ucTas5711RegAddr = *(++Pstr);
            Pstr++;
            #if 0
            if(iptr->WriteBytes(1, &g_ucTas5711RegAddr, DataLength, Pstr) == MAPI_FALSE)
                printf("5711write fail = %d\n",g_ucTas5711RegAddr);
            #else
            if (MApi_SWI2C_WriteBytes(TAS5711_BUSID,1, &g_ucTas5711RegAddr, DataLength, Pstr) == FALSE)
		        printf("5711write fail = %d\n",g_ucTas5711RegAddr);
            #endif
            MsOS_DelayTask(2);

            Pstr = Pstr + DataLength;
        }while(*Pstr != 0);
    }
    return TRUE;
}
//#endif
 //wjq20100112<<<

MAPI_BOOL Amplifier_TI5711_Mute(MAPI_BOOL bMute)
{
    // TODO: HW no use
    return TRUE;
}

MAPI_BOOL Amplifier_TI5711_StandBy(MAPI_U8 u8Para)
{
    if(u8Para == FALSE)
    {
        Audio_Amplifier_ON();
    }
    else
    {
        Audio_Amplifier_OFF();
    }
    return TRUE;
}

MAPI_BOOL Amplifier_TI5711_Reset(MAPI_U8 u8Para)
{
    if(u8Para == FALSE)
    {
        Audio_Amplifier_RST_OFF();
    }
    else
    {
        Audio_Amplifier_RST_ON();
    }
    return TRUE;
}

