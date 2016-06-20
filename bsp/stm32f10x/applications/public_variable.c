#include "includes.h"
#include "api_type.h"

uchar ProUart0Rec;
uchar KBDRecWrongFlag;
volatile uchar Rec_keyboard_data_buffer[20];
volatile uchar Current_Protocol;      
uchar domeNo=0xff, Protocol_No;
uchar Baud_rate=0;
uchar Rec_byte_com = 0, Rocket_fir_data, Rocket_sec_data, Rocket_thr_data, Rocket_fou_data,Rocket_six_data, Rocket_fiv_data, command_byte = 0;

uchar KBDRecWrongFlag;
uchar PanTiltStopFlag;
uchar PanTiltStopFlag1;
uchar Uart0RecResetFlag;

uchar ReturnStep_Zoomdata_Flag;
uchar com_buffer[6];   //main to motor command buffer
uchar com_buffer_tilt[6];   //main to motor command buffer

uchar txd1_buffer[200], txd1_buff_cFlag = 1, rxd1_buffer[200], rxd1_buff_cFlag = 0,  counter_receive = 0;
uchar cam_counter_send = 1; //byte of command counter
u8 cam_cmd_lenth = 0;

uchar Call_presetpoint_flag = 0;


Union_system_para system_para;


const double focus_pos_table[2045]=
{
	
	/*0.0071,
	0.0064,
	0.0057,
	0.0050,
	0.0043,
	0.0036,
	0.0029,
	0.0022,
	0.0015,
	0.0007, */
	0.0000,
	-0.0007,
	-0.0014,
	-0.0021,
	-0.0028,
	-0.0035,
	-0.0042,
	-0.0049,
	-0.0056,
	-0.0063,
	-0.0070,
	-0.0077,
	-0.0084,
	-0.0091,
	-0.0098,
	-0.0105,
	-0.0112,
	-0.0119,
	-0.0126,
	-0.0133,
	-0.0140,
	-0.0147,
	-0.0154,
	-0.0161,
	-0.0168,
	-0.0175,
	-0.0182,
	-0.0189,
	-0.0196,
	-0.0203,
	-0.0210,
	-0.0217,
	-0.0224,
	-0.0231,
	-0.0238,
	-0.0245,
	-0.0252,
	-0.0259,
	-0.0266,
	-0.0272,
	-0.0279,
	-0.0286,
	-0.0293,
	-0.0300,
	-0.0307,
	-0.0314,
	-0.0321,
	-0.0328,
	-0.0335,
	-0.0342,
	-0.0349,
	-0.0356,
	-0.0363,
	-0.0370,
	-0.0376,
	-0.0383,
	-0.0390,
	-0.0397,
	-0.0404,
	-0.0411,
	-0.0418,
	-0.0425,
	-0.0432,
	-0.0439,
	-0.0445,
	-0.0452,
	-0.0459,
	-0.0466,
	-0.0473,
	-0.0480,
	-0.0487,
	-0.0494,
	-0.0501,
	-0.0507,
	-0.0514,
	-0.0521,
	-0.0528,
	-0.0535,
	-0.0542,
	-0.0549,
	-0.0555,
	-0.0562,
	-0.0569,
	-0.0576,
	-0.0583,
	-0.0590,
	-0.0597,
	-0.0603,
	-0.0610,
	-0.0617,
	-0.0624,
	-0.0631,
	-0.0638,
	-0.0644,
	-0.0651,
	-0.0658,
	-0.0665,
	-0.0672,
	-0.0679,
	-0.0685,
	-0.0692,
	-0.0699,
	-0.0706,
	-0.0713,
	-0.0719,
	-0.0726,
	-0.0733,
	-0.0740,
	-0.0747,
	-0.0753,
	-0.0760,
	-0.0767,
	-0.0774,
	-0.0780,
	-0.0787,
	-0.0794,
	-0.0801,
	-0.0808,
	-0.0814,
	-0.0821,
	-0.0828,
	-0.0835,
	-0.0841,
	-0.0848,
	-0.0855,
	-0.0862,
	-0.0868,
	-0.0875,
	-0.0882,
	-0.0888,
	-0.0895,
	-0.0902,
	-0.0909,
	-0.0915,
	-0.0922,
	-0.0929,
	-0.0936,
	-0.0942,
	-0.0949,
	-0.0956,
	-0.0962,
	-0.0969,
	-0.0976,
	-0.0982,
	-0.0989,
	-0.0996,
	-0.1003,
	-0.1009,
	-0.1016,
	-0.1023,
	-0.1029,
	-0.1036,
	-0.1043,
	-0.1049,
	-0.1056,
	-0.1063,
	-0.1069,
	-0.1076,
	-0.1083,
	-0.1089,
	-0.1096,
	-0.1103,
	-0.1109,
	-0.1116,
	-0.1122,
	-0.1129,
	-0.1136,
	-0.1142,
	-0.1149,
	-0.1156,
	-0.1162,
	-0.1169,
	-0.1175,
	-0.1182,
	-0.1189,
	-0.1195,
	-0.1202,
	-0.1208,
	-0.1215,
	-0.1222,
	-0.1228,
	-0.1235,
	-0.1241,
	-0.1248,
	-0.1255,
	-0.1261,
	-0.1268,
	-0.1274,
	-0.1281,
	-0.1287,
	-0.1294,
	-0.1301,
	-0.1307,
	-0.1314,
	-0.1320,
	-0.1327,
	-0.1333,
	-0.1340,
	-0.1346,
	-0.1353,
	-0.1359,
	-0.1366,
	-0.1372,
	-0.1379,
	-0.1385,
	-0.1392,
	-0.1398,
	-0.1404,
	-0.1411,
	-0.1417,
	-0.1424,
	-0.1430,
	-0.1437,
	-0.1443,
	-0.1450,
	-0.1456,
	-0.1463,
	-0.1469,
	-0.1476,
	-0.1482,
	-0.1488,
	-0.1495,
	-0.1501,
	-0.1508,
	-0.1514,
	-0.1521,
	-0.1528,
	-0.1534,
	-0.1541,
	-0.1547,
	-0.1553,
	-0.1559,
	-0.1566,
	-0.1572,
	-0.1579,
	-0.1585,
	-0.1591,
	-0.1598,
	-0.1604,
	-0.1611,
	-0.1617,
	-0.1623,
	-0.1630,
	-0.1636,
	-0.1642,
	-0.1649,
	-0.1655,
	-0.1662,
	-0.1668,
	-0.1674,
	-0.1681,
	-0.1687,
	-0.1693,
	-0.1700,
	-0.1706,
	-0.1712,
	-0.1719,
	-0.1725,
	-0.1731,
	-0.1738,
	-0.1744,
	-0.1750,
	-0.1757,
	-0.1763,
	-0.1769,
	-0.1776,
	-0.1782,
	-0.1789,
	-0.1795,
	-0.1801,
	-0.1808,
	-0.1814,
	-0.1820,
	-0.1827,
	-0.1833,
	-0.1839,
	-0.1845,
	-0.1852,
	-0.1858,
	-0.1864,
	-0.1870,
	-0.1877,
	-0.1883,
	-0.1889,
	-0.1895,
	-0.1901,
	-0.1908,
	-0.1914,
	-0.1920,
	-0.1926,
	-0.1933,
	-0.1939,
	-0.1945,
	-0.1951,
	-0.1957,
	-0.1964,
	-0.1970,
	-0.1976,
	-0.1982,
	-0.1988,
	-0.1994,
	-0.2001,
	-0.2007,
	-0.2013,
	-0.2019,
	-0.2025,
	-0.2031,
	-0.2037,
	-0.2044,
	-0.2050,
	-0.2056,
	-0.2062,
	-0.2068,
	-0.2074,
	-0.2080,
	-0.2086,
	-0.2092,
	-0.2099,
	-0.2105,
	-0.2111,
	-0.2117,
	-0.2123,
	-0.2129,
	-0.2135,
	-0.2141,
	-0.2147,
	-0.2153,
	-0.2159,
	-0.2165,
	-0.2171,
	-0.2177,
	-0.2183,
	-0.2189,
	-0.2195,
	-0.2201,
	-0.2207,
	-0.2213,
	-0.2219,
	-0.2225,
	-0.2231,
	-0.2237,
	-0.2243,
	-0.2249,
	-0.2255,
	-0.2261,
	-0.2267,
	-0.2273,
	-0.2279,
	-0.2285,
	-0.2291,
	-0.2297,
	-0.2303,
	-0.2309,
	-0.2315,
	-0.2321,
	-0.2327,
	-0.2333,
	-0.2339,
	-0.2345,
	-0.2350,
	-0.2356,
	-0.2362,
	-0.2368,
	-0.2374,
	-0.2380,
	-0.2386,
	-0.2392,
	-0.2398,
	-0.2403,
	-0.2409,
	-0.2415,
	-0.2421,
	-0.2427,
	-0.2433,
	-0.2439,
	-0.2444,
	-0.2450,
	-0.2456,
	-0.2462,
	-0.2468,
	-0.2473,
	-0.2479,
	-0.2485,
	-0.2491,
	-0.2497,
	-0.2502,
	-0.2508,
	-0.2514,
	-0.2520,
	-0.2526,
	-0.2531,
	-0.2537,
	-0.2543,
	-0.2549,
	-0.2554,
	-0.2560,
	-0.2566,
	-0.2571,
	-0.2577,
	-0.2583,
	-0.2589,
	-0.2594,
	-0.2600,
	-0.2606,
	-0.2611,
	-0.2617,
	-0.2623,
	-0.2628,
	-0.2634,
	-0.2640,
	-0.2645,
	-0.2651,
	-0.2657,
	-0.2662,
	-0.2668,
	-0.2674,
	-0.2679,
	-0.2685,
	-0.2690,
	-0.2696,
	-0.2702,
	-0.2707,
	-0.2713,
	-0.2718,
	-0.2724,
	-0.2730,
	-0.2735,
	-0.2741,
	-0.2746,
	-0.2752,
	-0.2757,
	-0.2763,
	-0.2768,
	-0.2774,
	-0.2780,
	-0.2785,
	-0.2791,
	-0.2796,
	-0.2802,
	-0.2807,
	-0.2813,
	-0.2818,
	-0.2824,
	-0.2829,
	-0.2835,
	-0.2840,
	-0.2845,
	-0.2851,
	-0.2856,
	-0.2862,
	-0.2867,
	-0.2873,
	-0.2878,
	-0.2884,
	-0.2889,
	-0.2894,
	-0.2900,
	-0.2905,
	-0.2911,
	-0.2916,
	-0.2921,
	-0.2927,
	-0.2932,
	-0.2937,
	-0.2943,
	-0.2948,
	-0.2954,
	-0.2959,
	-0.2964,
	-0.2970,
	-0.2975,
	-0.2980,
	-0.2986,
	-0.2991,
	-0.2996,
	-0.3001,
	-0.3007,
	-0.3012,
	-0.3017,
	-0.3023,
	-0.3028,
	-0.3033,
	-0.3038,
	-0.3044,
	-0.3049,
	-0.3054,
	-0.3059,
	-0.3065,
	-0.3070,
	-0.3075,
	-0.3080,
	-0.3085,
	-0.3091,
	-0.3096,
	-0.3101,
	-0.3106,
	-0.3111,
	-0.3116,
	-0.3122,
	-0.3127,
	-0.3132,
	-0.3137,
	-0.3142,
	-0.3147,
	-0.3152,
	-0.3158,
	-0.3163,
	-0.3168,
	-0.3173,
	-0.3178,
	-0.3183,
	-0.3188,
	-0.3193,
	-0.3198,
	-0.3203,
	-0.3208,
	-0.3213,
	-0.3218,
	-0.3223,
	-0.3228,
	-0.3233,
	-0.3238,
	-0.3243,
	-0.3248,
	-0.3253,
	-0.3258,
	-0.3263,
	-0.3268,
	-0.3273,
	-0.3278,
	-0.3283,
	-0.3288,
	-0.3293,
	-0.3298,
	-0.3303,
	-0.3308,
	-0.3313,
	-0.3318,
	-0.3323,
	-0.3327,
	-0.3332,
	-0.3337,
	-0.3342,
	-0.3347,
	-0.3352,
	-0.3357,
	-0.3361,
	-0.3366,
	-0.3371,
	-0.3376,
	-0.3381,
	-0.3386,
	-0.3390,
	-0.3395,
	-0.3400,
	-0.3405,
	-0.3410,
	-0.3414,
	-0.3419,
	-0.3424,
	-0.3429,
	-0.3433,
	-0.3438,
	-0.3443,
	-0.3447,
	-0.3452,
	-0.3457,
	-0.3462,
	-0.3466,
	-0.3471,
	-0.3476,
	-0.3480,
	-0.3485,
	-0.3490,
	-0.3494,
	-0.3499,
	-0.3503,
	-0.3508,
	-0.3513,
	-0.3517,
	-0.3522,
	-0.3527,
	-0.3531,
	-0.3536,
	-0.3540,
	-0.3545,
	-0.3549,
	-0.3554,
	-0.3558,
	-0.3563,
	-0.3567,
	-0.3572,
	-0.3577,
	-0.3581,
	-0.3586,
	-0.3590,
	-0.3594,
	-0.3599,
	-0.3603,
	-0.3608,
	-0.3612,
	-0.3617,
	-0.3621,
	-0.3626,
	-0.3630,
	-0.3634,
	-0.3639,
	-0.3643,
	-0.3648,
	-0.3652,
	-0.3656,
	-0.3661,
	-0.3665,
	-0.3669,
	-0.3674,
	-0.3678,
	-0.3682,
	-0.3687,
	-0.3691,
	-0.3695,
	-0.3700,
	-0.3704,
	-0.3708,
	-0.3712,
	-0.3717,
	-0.3721,
	-0.3725,
	-0.3729,
	-0.3734,
	-0.3738,
	-0.3742,
	-0.3746,
	-0.3751,
	-0.3755,
	-0.3759,
	-0.3763,
	-0.3767,
	-0.3771,
	-0.3776,
	-0.3780,
	-0.3784,
	-0.3788,
	-0.3792,
	-0.3796,
	-0.3800,
	-0.3804,
	-0.3808,
	-0.3813,
	-0.3817,
	-0.3821,
	-0.3825,
	-0.3829,
	-0.3833,
	-0.3837,
	-0.3841,
	-0.3845,
	-0.3849,
	-0.3853,
	-0.3857,
	-0.3861,
	-0.3865,
	-0.3869,
	-0.3873,
	-0.3877,
	-0.3880,
	-0.3884,
	-0.3888,
	-0.3892,
	-0.3896,
	-0.3900,
	-0.3904,
	-0.3908,
	-0.3912,
	-0.3915,
	-0.3919,
	-0.3923,
	-0.3927,
	-0.3931,
	-0.3935,
	-0.3938,
	-0.3942,
	-0.3946,
	-0.3950,
	-0.3953,
	-0.3957,
	-0.3961,
	-0.3965,
	-0.3968,
	-0.3972,
	-0.3976,
	-0.3979,
	-0.3983,
	-0.3987,
	-0.3991,
	-0.3994,
	-0.3998,
	-0.4001,
	-0.4005,
	-0.4009,
	-0.4012,
	-0.4016,
	-0.4020,
	-0.4023,
	-0.4027,
	-0.4030,
	-0.4034,
	-0.4037,
	-0.4041,
	-0.4044,
	-0.4048,
	-0.4051,
	-0.4055,
	-0.4058,
	-0.4062,
	-0.4065,
	-0.4069,
	-0.4072,
	-0.4076,
	-0.4079,
	-0.4083,
	-0.4086,
	-0.4089,
	-0.4093,
	-0.4096,
	-0.4100,
	-0.4103,
	-0.4106,
	-0.4110,
	-0.4113,
	-0.4116,
	-0.4120,
	-0.4123,
	-0.4126,
	-0.4130,
	-0.4133,
	-0.4136,
	-0.4139,
	-0.4143,
	-0.4146,
	-0.4149,
	-0.4152,
	-0.4156,
	-0.4159,
	-0.4162,
	-0.4165,
	-0.4168,
	-0.4171,
	-0.4175,
	-0.4178,
	-0.4181,
	-0.4184,
	-0.4187,
	-0.4190,
	-0.4193,
	-0.4196,
	-0.4199,
	-0.4202,
	-0.4206,
	-0.4209,
	-0.4212,
	-0.4215,
	-0.4218,
	-0.4221,
	-0.4224,
	-0.4227,
	-0.4230,
	-0.4232,
	-0.4235,
	-0.4238,
	-0.4241,
	-0.4244,
	-0.4247,
	-0.4250,
	-0.4253,
	-0.4256,
	-0.4259,
	-0.4261,
	-0.4264,
	-0.4267,
	-0.4270,
	-0.4273,
	-0.4276,
	-0.4278,
	-0.4281,
	-0.4284,
	-0.4287,
	-0.4289,
	-0.4292,
	-0.4295,
	-0.4297,
	-0.4300,
	-0.4303,
	-0.4306,
	-0.4308,
	-0.4311,
	-0.4313,
	-0.4316,
	-0.4319,
	-0.4321,
	-0.4324,
	-0.4327,
	-0.4329,
	-0.4332,
	-0.4334,
	-0.4337,
	-0.4339,
	-0.4342,
	-0.4344,
	-0.4346,
	-0.4349,
	-0.4351,
	-0.4354,
	-0.4356,
	-0.4359,
	-0.4361,
	-0.4364,
	-0.4366,
	-0.4369,
	-0.4371,
	-0.4373,
	-0.4376,
	-0.4378,
	-0.4380,
	-0.4383,
	-0.4385,
	-0.4387,
	-0.4390,
	-0.4392,
	-0.4394,
	-0.4396,
	-0.4399,
	-0.4401,
	-0.4403,
	-0.4405,
	-0.4407,
	-0.4410,
	-0.4412,
	-0.4414,
	-0.4416,
	-0.4418,
	-0.4420,
	-0.4422,
	-0.4425,
	-0.4427,
	-0.4429,
	-0.4431,
	-0.4433,
	-0.4435,
	-0.4437,
	-0.4439,
	-0.4441,
	-0.4443,
	-0.4445,
	-0.4447,
	-0.4449,
	-0.4451,
	-0.4453,
	-0.4455,
	-0.4456,
	-0.4458,
	-0.4460,
	-0.4462,
	-0.4464,
	-0.4466,
	-0.4468,
	-0.4469,
	-0.4471,
	-0.4473,
	-0.4475,
	-0.4477,
	-0.4478,
	-0.4480,
	-0.4482,
	-0.4483,
	-0.4485,
	-0.4487,
	-0.4488,
	-0.4490,
	-0.4492,
	-0.4493,
	-0.4495,
	-0.4497,
	-0.4498,
	-0.4500,
	-0.4501,
	-0.4503,
	-0.4505,
	-0.4506,
	-0.4508,
	-0.4509,
	-0.4511,
	-0.4512,
	-0.4514,
	-0.4515,
	-0.4516,
	-0.4518,
	-0.4519,
	-0.4521,
	-0.4522,
	-0.4523,
	-0.4525,
	-0.4526,
	-0.4527,
	-0.4529,
	-0.4530,
	-0.4531,
	-0.4533,
	-0.4534,
	-0.4535,
	-0.4536,
	-0.4538,
	-0.4539,
	-0.4540,
	-0.4541,
	-0.4542,
	-0.4543,
	-0.4545,
	-0.4546,
	-0.4547,
	-0.4548,
	-0.4549,
	-0.4550,
	-0.4551,
	-0.4552,
	-0.4553,
	-0.4554,
	-0.4555,
	-0.4556,
	-0.4557,
	-0.4558,
	-0.4559,
	-0.4560,
	-0.4561,
	-0.4562,
	-0.4563,
	-0.4564,
	-0.4565,
	-0.4565,
	-0.4566,
	-0.4567,
	-0.4568,
	-0.4569,
	-0.4569,
	-0.4570,
	-0.4571,
	-0.4572,
	-0.4572,
	-0.4573,
	-0.4574,
	-0.4574,
	-0.4575,
	-0.4576,
	-0.4576,
	-0.4577,
	-0.4578,
	-0.4578,
	-0.4579,
	-0.4579,
	-0.4580,
	-0.4580,
	-0.4581,
	-0.4581,
	-0.4582,
	-0.4582,
	-0.4583,
	-0.4583,
	-0.4584,
	-0.4584,
	-0.4584,
	-0.4585,
	-0.4585,
	-0.4585,
	-0.4586,
	-0.4586,
	-0.4586,
	-0.4587,
	-0.4587,
	-0.4587,
	-0.4587,
	-0.4588,
	-0.4588,
	-0.4588,
	-0.4588,
	-0.4588,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4589,
	-0.4588,
	-0.4588,
	-0.4588,
	-0.4588,
	-0.4588,
	-0.4588,
	-0.4587,
	-0.4587,
	-0.4587,
	-0.4587,
	-0.4586,
	-0.4586,
	-0.4586,
	-0.4585,
	-0.4585,
	-0.4584,
	-0.4584,
	-0.4584,
	-0.4583,
	-0.4583,
	-0.4582,
	-0.4582,
	-0.4581,
	-0.4581,
	-0.4580,
	-0.4580,
	-0.4579,
	-0.4579,
	-0.4578,
	-0.4577,
	-0.4577,
	-0.4576,
	-0.4575,
	-0.4575,
	-0.4574,
	-0.4573,
	-0.4573,
	-0.4572,
	-0.4571,
	-0.4570,
	-0.4570,
	-0.4569,
	-0.4568,
	-0.4567,
	-0.4566,
	-0.4565,
	-0.4564,
	-0.4563,
	-0.4562,
	-0.4562,
	-0.4561,
	-0.4560,
	-0.4559,
	-0.4558,
	-0.4556,
	-0.4555,
	-0.4554,
	-0.4553,
	-0.4552,
	-0.4551,
	-0.4550,
	-0.4549,
	-0.4547,
	-0.4546,
	-0.4545,
	-0.4544,
	-0.4543,
	-0.4541,
	-0.4540,
	-0.4539,
	-0.4537,
	-0.4536,
	-0.4535,
	-0.4533,
	-0.4532,
	-0.4530,
	-0.4529,
	-0.4528,
	-0.4526,
	-0.4525,
	-0.4523,
	-0.4522,
	-0.4520,
	-0.4518,
	-0.4517,
	-0.4515,
	-0.4514,
	-0.4512,
	-0.4510,
	-0.4509,
	-0.4507,
	-0.4505,
	-0.4503,
	-0.4502,
	-0.4500,
	-0.4498,
	-0.4496,
	-0.4495,
	-0.4493,
	-0.4491,
	-0.4489,
	-0.4487,
	-0.4485,
	-0.4483,
	-0.4481,
	-0.4479,
	-0.4477,
	-0.4475,
	-0.4473,
	-0.4471,
	-0.4469,
	-0.4467,
	-0.4465,
	-0.4463,
	-0.4461,
	-0.4458,
	-0.4456,
	-0.4454,
	-0.4452,
	-0.4449,
	-0.4447,
	-0.4445,
	-0.4443,
	-0.4440,
	-0.4438,
	-0.4436,
	-0.4433,
	-0.4431,
	-0.4428,
	-0.4426,
	-0.4423,
	-0.4421,
	-0.4418,
	-0.4416,
	-0.4413,
	-0.4411,
	-0.4408,
	-0.4406,
	-0.4403,
	-0.4400,
	-0.4398,
	-0.4395,
	-0.4392,
	-0.4390,
	-0.4387,
	-0.4384,
	-0.4381,
	-0.4378,
	-0.4376,
	-0.4373,
	-0.4370,
	-0.4367,
	-0.4364,
	-0.4361,
	-0.4358,
	-0.4355,
	-0.4352,
	-0.4349,
	-0.4346,
	-0.4343,
	-0.4340,
	-0.4337,
	-0.4334,
	-0.4331,
	-0.4327,
	-0.4324,
	-0.4321,
	-0.4318,
	-0.4315,
	-0.4311,
	-0.4308,
	-0.4305,
	-0.4301,
	-0.4298,
	-0.4295,
	-0.4291,
	-0.4288,
	-0.4284,
	-0.4281,
	-0.4277,
	-0.4274,
	-0.4270,
	-0.4267,
	-0.4263,
	-0.4260,
	-0.4256,
	-0.4252,
	-0.4249,
	-0.4245,
	-0.4241,
	-0.4238,
	-0.4234,
	-0.4230,
	-0.4226,
	-0.4222,
	-0.4219,
	-0.4215,
	-0.4211,
	-0.4207,
	-0.4203,
	-0.4199,
	-0.4195,
	-0.4191,
	-0.4187,
	-0.4183,
	-0.4179,
	-0.4175,
	-0.4171,
	-0.4167,
	-0.4162,
	-0.4158,
	-0.4154,
	-0.4150,
	-0.4146,
	-0.4141,
	-0.4137,
	-0.4133,
	-0.4128,
	-0.4124,
	-0.4120,
	-0.4115,
	-0.4111,
	-0.4106,
	-0.4102,
	-0.4097,
	-0.4093,
	-0.4088,
	-0.4084,
	-0.4079,
	-0.4075,
	-0.4070,
	-0.4065,
	-0.4061,
	-0.4056,
	-0.4051,
	-0.4046,
	-0.4042,
	-0.4037,
	-0.4032,
	-0.4027,
	-0.4022,
	-0.4017,
	-0.4012,
	-0.4007,
	-0.4002,
	-0.3997,
	-0.3992,
	-0.3987,
	-0.3982,
	-0.3977,
	-0.3972,
	-0.3967,
	-0.3962,
	-0.3957,
	-0.3951,
	-0.3946,
	-0.3941,
	-0.3936,
	-0.3930,
	-0.3925,
	-0.3920,
	-0.3914,
	-0.3909,
	-0.3903,
	-0.3898,
	-0.3892,
	-0.3887,
	-0.3881,
	-0.3876,
	-0.3870,
	-0.3865,
	-0.3859,
	-0.3853,
	-0.3848,
	-0.3842,
	-0.3836,
	-0.3830,
	-0.3825,
	-0.3819,
	-0.3813,
	-0.3807,
	-0.3801,
	-0.3795,
	-0.3789,
	-0.3783,
	-0.3777,
	-0.3771,
	-0.3765,
	-0.3759,
	-0.3753,
	-0.3747,
	-0.3741,
	-0.3735,
	-0.3729,
	-0.3722,
	-0.3716,
	-0.3710,
	-0.3703,
	-0.3697,
	-0.3691,
	-0.3684,
	-0.3678,
	-0.3672,
	-0.3665,
	-0.3659,
	-0.3652,
	-0.3646,
	-0.3639,
	-0.3632,
	-0.3626,
	-0.3619,
	-0.3612,
	-0.3606,
	-0.3599,
	-0.3592,
	-0.3585,
	-0.3579,
	-0.3572,
	-0.3565,
	-0.3558,
	-0.3551,
	-0.3544,
	-0.3537,
	-0.3530,
	-0.3523,
	-0.3516,
	-0.3509,
	-0.3502,
	-0.3495,
	-0.3488,
	-0.3480,
	-0.3473,
	-0.3466,
	-0.3459,
	-0.3451,
	-0.3444,
	-0.3437,
	-0.3429,
	-0.3422,
	-0.3414,
	-0.3407,
	-0.3399,
	-0.3392,
	-0.3384,
	-0.3377,
	-0.3369,
	-0.3361,
	-0.3354,
	-0.3346,
	-0.3338,
	-0.3331,
	-0.3323,
	-0.3315,
	-0.3307,
	-0.3299,
	-0.3291,
	-0.3283,
	-0.3276,
	-0.3268,
	-0.3260,
	-0.3251,
	-0.3243,
	-0.3235,
	-0.3227,
	-0.3219,
	-0.3211,
	-0.3203,
	-0.3194,
	-0.3186,
	-0.3178,
	-0.3169,
	-0.3161,
	-0.3153,
	-0.3144,
	-0.3136,
	-0.3127,
	-0.3119,
	-0.3110,
	-0.3102,
	-0.3093,
	-0.3084,
	-0.3076,
	-0.3067,
	-0.3058,
	-0.3050,
	-0.3041,
	-0.3032,
	-0.3023,
	-0.3014,
	-0.3005,
	-0.2997,
	-0.2988,
	-0.2979,
	-0.2970,
	-0.2960,
	-0.2951,
	-0.2942,
	-0.2933,
	-0.2924,
	-0.2915,
	-0.2906,
	-0.2896,
	-0.2887,
	-0.2878,
	-0.2868,
	-0.2859,
	-0.2849,
	-0.2840,
	-0.2830,
	-0.2821,
	-0.2811,
	-0.2802,
	-0.2792,
	-0.2783,
	-0.2773,
	-0.2763,
	-0.2753,
	-0.2744,
	-0.2734,
	-0.2724,
	-0.2714,
	-0.2704,
	-0.2694,
	-0.2684,
	-0.2674,
	-0.2664,
	-0.2654,
	-0.2644,
	-0.2634,
	-0.2624,
	-0.2614,
	-0.2603,
	-0.2593,
	-0.2583,
	-0.2573,
	-0.2562,
	-0.2552,
	-0.2541,
	-0.2531,
	-0.2521,
	-0.2510,
	-0.2499,
	-0.2489,
	-0.2478,
	-0.2468,
	-0.2457,
	-0.2446,
	-0.2436,
	-0.2425,
	-0.2414,
	-0.2403,
	-0.2392,
	-0.2381,
	-0.2370,
	-0.2359,
	-0.2348,
	-0.2337,
	-0.2326,
	-0.2315,
	-0.2304,
	-0.2293,
	-0.2282,
	-0.2270,
	-0.2259,
	-0.2248,
	-0.2236,
	-0.2225,
	-0.2214,
	-0.2202,
	-0.2191,
	-0.2179,
	-0.2168,
	-0.2156,
	-0.2144,
	-0.2133,
	-0.2121,
	-0.2109,
	-0.2098,
	-0.2086,
	-0.2074,
	-0.2062,
	-0.2050,
	-0.2038,
	-0.2026,
	-0.2014,
	-0.2002,
	-0.1990,
	-0.1978,
	-0.1966,
	-0.1954,
	-0.1942,
	-0.1929,
	-0.1917,
	-0.1905,
	-0.1892,
	-0.1880,
	-0.1867,
	-0.1855,
	-0.1843,
	-0.1830,
	-0.1817,
	-0.1805,
	-0.1792,
	-0.1780,
	-0.1767,
	-0.1754,
	-0.1741,
	-0.1728,
	-0.1716,
	-0.1703,
	-0.1690,
	-0.1677,
	-0.1664,
	-0.1651,
	-0.1638,
	-0.1625,
	-0.1611,
	-0.1598,
	-0.1585,
	-0.1572,
	-0.1558,
	-0.1545,
	-0.1532,
	-0.1518,
	-0.1505,
	-0.1491,
	-0.1478,
	-0.1464,
	-0.1451,
	-0.1437,
	-0.1423,
	-0.1410,
	-0.1396,
	-0.1382,
	-0.1368,
	-0.1354,
	-0.1340,
	-0.1327,
	-0.1313,
	-0.1299,
	-0.1284,
	-0.1270,
	-0.1256,
	-0.1242,
	-0.1228,
	-0.1214,
	-0.1199,
	-0.1185,
	-0.1171,
	-0.1156,
	-0.1142,
	-0.1127,
	-0.1113,
	-0.1098,
	-0.1084,
	-0.1069,
	-0.1054,
	-0.1040,
	-0.1025,
	-0.1010,
	-0.0995,
	-0.0980,
	-0.0966,
	-0.0951,
	-0.0936,
	-0.0921,
	-0.0906,
	-0.0890,
	-0.0875,
	-0.0860,
	-0.0845,
	-0.0830,
	-0.0814,
	-0.0799,
	-0.0784,
	-0.0768,
	-0.0753,
	-0.0737,
	-0.0722,
	-0.0706,
	-0.0690,
	-0.0675,
	-0.0659,
	-0.0643,
	-0.0627,
	-0.0612,
	-0.0596,
	-0.0580,
	-0.0564,
	-0.0548,
	-0.0532,
	-0.0516,
	-0.0500,
	-0.0483,
	-0.0467,
	-0.0451,
	-0.0435,
	-0.0419,
	-0.0402,
	-0.0386,
	-0.0369,
	-0.0353,
	-0.0336,
	-0.0320,
	-0.0303,
	-0.0286,
	-0.0270,
	-0.0253,
	-0.0236,
	-0.0219,
	-0.0202,
	-0.0186,
	-0.0169,
	-0.0152,
	-0.0135,
	-0.0117,
	-0.0100,
	-0.0083,
	-0.0066,
	-0.0049,
	-0.0031,
	-0.0014,
	0.0003,
	0.0021,
	0.0038,
	0.0056,
	0.0073,
	0.0091,
	0.0109,
	0.0126,
	0.0144,
	0.0162,
	0.0180,
	0.0197,
	0.0215,
	0.0233,
	0.0251,
	0.0269,
	0.0287,
	0.0305,
	0.0324,
	0.0342,
	0.0360,
	0.0378,
	0.0397,
	0.0415,
	0.0434,
	0.0452,
	0.0471,
	0.0489,
	0.0508,
	0.0526,
	0.0545,
	0.0564,
	0.0583,
	0.0601,
	0.0620,
	0.0639,
	0.0658,
	0.0677,
	0.0696,
	0.0715,
	0.0735,
	0.0754,
	0.0773,
	0.0792,
	0.0812,
	0.0831,
	0.0851,
	0.0870,
	0.0890,
	0.0909,
	0.0929,
	0.0948,
	0.0968,
	0.0988,
	0.1008,
	0.1028,
	0.1047,
	0.1067,
	0.1087,
	0.1107,
	0.1127,
	0.1148,
	0.1168,
	0.1188,
	0.1208,
	0.1229,
	0.1249,
	0.1269,
	0.1290,
	0.1310,
	0.1331,
	0.1352,
	0.1372,
	0.1393,
	0.1414,
	0.1434,
	0.1455,
	0.1476,
	0.1497,
	0.1518,
	0.1539,
	0.1560,
	0.1581,
	0.1603,
	0.1624,
	0.1645,
	0.1666,
	0.1688,
	0.1709,
	0.1731,
	0.1752,
	0.1774,
	0.1795,
	0.1817,
	0.1839,
	0.1861,
	0.1882,
	0.1904,
	0.1926,
	0.1948,
	0.1970,
	0.1992,
	0.2014,
	0.2037,
	0.2059,
	0.2081,
	0.2103,
	0.2126,
	0.2148,
	0.2171,
	0.2193,
	0.2216,
	0.2238,
	0.2261,
	0.2284,
	0.2307,
	0.2330,
	0.2352,
	0.2375,
	0.2398,
	0.2421,
	0.2444,
	0.2468,
	0.2491,
	0.2514,
	0.2537,
	0.2561,
	0.2584,
	0.2608,
	0.2631,
	0.2655,
	0.2678,
	0.2702,
	0.2726,
	0.2749,
	0.2773,
	0.2797,
	0.2821,
	0.2845,
	0.2869,
	0.2893,
	0.2917,
	0.2942,
	0.2966,
	0.2990,
	0.3014,
	0.3039,
	0.3063,
	0.3088,
	0.3112,
	0.3137,
	0.3162,
	0.3186,
	0.3211,
	0.3236,
	0.3261,
	0.3286,
	0.3311,
	0.3336,
	0.3361,
	0.3386,
	0.3411,
	0.3437,
	0.3462,
	0.3487,
	0.3513,
	0.3538,
	0.3564,
	0.3589,
	0.3615,
	0.3641,
	0.3667,
	0.3692,
	0.3718,
	0.3744,
	0.3770,
	0.3796,
	0.3822,
	0.3848,
	0.3875,
	0.3901,
	0.3927,
	0.3954,
	0.3980,
	0.4007,
	0.4033,
	0.4060,
	0.4086,
	0.4113,
	0.4140,
	0.4167,
	0.4194,
	0.4221,
	0.4248,
	0.4275,
	0.4302,
	0.4329,
	0.4356,
	0.4383,
	0.4411,
	0.4438,
	0.4466,
	0.4493,
	0.4521,
	0.4548,
	0.4576,
	0.4604,
	0.4632,
	0.4660,
	0.4687,
	0.4715,
	0.4743,
	0.4772,
	0.4800,
	0.4828,
	0.4856,
	0.4885,
	0.4913,
	0.4941,
	0.4970,
	0.4999,
	0.5027,
	0.5056,
	0.5085,
	0.5113,
	0.5142,
	0.5171,
	0.5200,
	0.5229,
	0.5258,
	0.5288,
	0.5317,
	0.5346,
	0.5375,
	0.5405,
	0.5434,
	0.5464,
	0.5494,
	0.5523,
	0.5553,
	0.5583,
	0.5613,
	0.5642,
	0.5672,
	0.5702,
	0.5733,
	0.5763,
	0.5793,
	0.5823,
	0.5854,
	0.5884,
	0.5914,
	0.5945,
	0.5976,
	0.6006,
	0.6037,
	0.6068,
	0.6099,
	0.6129,
	0.6160,
	0.6191,
	0.6223,
	0.6254,
	0.6285,
	0.6316,
	0.6348,
	0.6379,
	0.6410,
	0.6442,
	0.6474,
	0.6505,
	0.6537,
	0.6569,
	0.6601,
	0.6633,
	0.6665,
	0.6697,
	0.6729,
	0.6761,
	0.6793,
	0.6825,
	0.6858,
	0.6890,
	0.6923,
	0.6955,
	0.6988,
	0.7021,
	0.7053,
	0.7086,
	0.7119,
	0.7152,
	0.7185,
	0.7218,
	0.7251,
	0.7285,
	0.7318,
	0.7351,
	0.7385,
	0.7418,
	0.7452,
	0.7485,
	0.7519,
	0.7553,
	0.7587,
	0.7621,
	0.7655,
	0.7689,
	0.7723,
	0.7757,
	0.7791,
	0.7825,
	0.7860,
	0.7894,
	0.7929,
	0.7963,
	0.7998,
	0.8033,
	0.8067,
	0.8102,
	0.8137,
	0.8172,
	0.8207,
	0.8242,
	0.8278,
	0.8313,
	0.8348,
	0.8384,
	0.8419,
	0.8455,
	0.8490,
	0.8526,
	0.8562,
	0.8597,
	0.8633,
	0.8669,
	0.8705,
	0.8741,
	0.8778,
	0.8814,
	0.8850,
	0.8886,
	0.8923,
	0.8959,
	0.8996,
	0.9033,
	0.9069,
	0.9106,
	0.9143,
	0.9180,
	0.9217,
	0.9254,
	0.9291,
	0.9329,
	0.9366,
	0.9403,
	0.9441,
	0.9478,
	0.9516,
	0.9554,
	0.9591,
	0.9629,
	0.9667,
	0.9705,
	0.9743,
	0.9781,
	0.9819,
	0.9857,
	0.9896,
	0.9934,
	0.9973,
	1.0011,
	1.0050,
	1.0089,
	1.0127,
	1.0166,
	1.0205,
	1.0244,
	1.0283,
	1.0322,
	1.0362,
	1.0401,
	1.0440,
	1.0480,
	1.0519,
	1.0559,
	1.0599,
	1.0638,
	1.0678,
	1.0718,
	1.0758,
	1.0798,
	1.0838,
	1.0879,
	1.0919,
	1.0959,
	1.1000,
	1.1040,
	1.1081,
	1.1121,
	1.1162,
	1.1203,
	1.1244,
	1.1285,
	1.1326,
	1.1367,
	1.1409,
	1.1450,
	1.1491,
	1.1533,
	1.1574,
	1.1616,
	1.1658,
	1.1699,
	1.1741,
	1.1783,
	1.1825,
	1.1867,
	1.1909,
	1.1952,
	1.1994,
	1.2037,


};
























