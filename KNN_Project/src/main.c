/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */
#include "main.h"

int main(void)
{
	HAL_Init();
	USART1_Init();
	MX_USART2_UART_Init();
	I2C1_init();

	if(LSM6DS0_Who_Am_I()==LSM6DS0_Who_am_i_val)
	{
		LSM6DS0_present = ENABLE;
		char *msg="\n\rLSM6DS0 found on the I2C bus! \r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
		LSM6DS0_Config();
	}
	else
	{
		char *msg="\n\rNOT FOUND \r\n";
		HAL_UART_Transmit(&huart2, (uint8_t*)msg, strlen(msg), 0xFFFF);
		LSM6DS0_present = DISABLE;
	}

	char buffer[100];
	char *newline = "\n\r";
	char *tab = "\t";

	int cycleNum=0;

	float acceleration_data[3]={0};
	float gyro_data[3]={0};
/*
	float trainingSetAccelerationX[nOfSamples][vectorLength]=
	{
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 }
	};
	float trainingSetAccelerationY[nOfSamples][vectorLength]=
	{
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 }
	};
	float trainingSetAccelerationZ[nOfSamples][vectorLength]=
	{
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 }
	};
	float trainingSetGyroX[nOfSamples][vectorLength]=
	{
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 }
	};
	float trainingSetGyroY[nOfSamples][vectorLength]=
	{
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 }
	};
	float trainingSetGyroZ[nOfSamples][vectorLength]=
	{
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 },
			{ 45,4,5,7,2,1,8,66,8,12 }
	};
*/
	//etichette del training set (note)
	//
	// 0: appartenenza a "classe1"
	// 1: appartenenza a "classe2"

	//INSERIRE QUI TRAINING SET
	float trainingSetFeatures[nOfSamples][nOfFeatures]=
	{
			{-0.000838, 	-0.051079,       4.972633,       -6.101900,       -3.796625,       144.377792,      0.094651,        2.382049,        6.371462,        0.094651,        2.382049,        6.371462,        1,     -0.110169,       -0.017742},
			{0.026378, 		0.541873,        -3.078591,       -3.193400,       -3.106775,       143.869583,      0.081020,        1.724061,        9.591606,        0.081020,        1.724061,        9.591606,        1,     1,              -0.156335},
			{-0.004128,      0.027023,        5.340247,        -0.806050,       -6.426700,      140.723083,      0.122172,        3.060799,        15.262811,       0.122172,        3.060799,        15.262811,       -1,    -0.112480,       0.083045},
			{0.045081,        0.659509,        -8.238513,       -2.727200,       -2.563750,       143.608826,      0.096797,        2.340041,        8.351008,        0.096797,        2.340041,        8.351008,        -1,    0.428299,        -0.026274},
			{0.020509,        -0.410694,       -1.611947,       -3.533600,       -2.020375,       144.077820,      0.119626,        2.396930,        7.064073,        0.119626,        2.396930,        7.064073,        1,    -0.388271,       -0.217081},
			{-0.005804,       0.379479,        5.184171,        -1.953700,       -0.852250,       142.156357,      0.132158,        2.453578,        15.746669,       0.132158,        2.453578,        15.746669,       -1,    -0.474023,       -0.036769},
			{-0.017800,       -0.124343,       7.693158,        -5.830475,       -2.399250,       145.155319,      0.102366,        2.817596,        9.284985,        0.102366,        2.817596,        9.284985,        1,     -0.403091,       -0.233609},
			{0.022379,        0.408308,        -1.162945,       -7.912975,       -0.581350,       144.538284,      0.077923,        2.382340,        6.063750,        0.077923,        2.382340,        6.063750,        1,     -0.819962,       -0.292859},
			{0.041018,        0.381478,        -7.313291,       -4.195625,       -1.481725,       143.483200,      0.117711,        2.354248,        9.725722,        0.117711,        2.354248,        9.725722,        1,     0.298610,        -0.125095},
			{0.015930,        0.322531,        0.060559,        -8.408926,      -0.496825,       145.322800,      0.105153,        2.264061,        7.361965,        0.105153,        2.264061,       7.361965,        -1, 	  -0.232789,       0.306719},
			{0.069975,        -0.093128,       -7.404936,       -10.791202,      0.701925,        142.983582,      0.125416,        2.409236,        10.625913,       0.125416,        2.409236,        10.625913,       1,     -0.503682,       0.131738},
			{0.059269,        -0.011738,       -7.727468,       -13.978125,      1.225525,        144.289429,      0.119412,        2.660257,        7.329367,        0.119412,        2.660257,        7.329367,        -1,    -0.884063,       -0.067035},
			{0.026571,        0.012383,        -2.790629,       -10.486873,      1.457925,        142.408356,      0.178733,        2.599277,        17.572735,       0.178733,        2.599277,        17.572735,       -1,    0.064815,        -0.051800},
			{-0.084357,       0.477638,        14.951176,       -13.525751,      0.140350,        142.898865,      0.143119,        2.632852,        12.190303,       0.143119,        2.632852,        12.190303,       1,     0.392872,        0.011951},
			{-0.015220,       0.194512,        5.649943,        -14.177975,      -0.246925,       144.629440,      0.104682,        2.328938,        9.589276,        0.104682,        2.328938,        9.589276,        -1,    -0.065496,       -0.317193},
			{-0.046435,       -0.083648,       9.845946,        -14.051101,      -1.264900,       143.649109,      0.123869,        2.365296,        10.652678,       0.123869,        2.365296,        10.652678,       -1,    -0.248861,       0.190632},
			{0.045661,        0.025023,        -2.680474,       -17.851572,      -0.185850,       140.937653,      0.137397,        2.637403,        9.929008,        0.137397,        2.637403,        9.929008,        1,     0.274046,        0.049859},
			{-0.071265,       0.180968,        11.055131,       -17.647524,      -1.235500,       142.441605,      0.131358,        1.879788,        9.739284,        0.131358,        1.879788,        9.739284,        -1,    0.701835,        0.048786},
			{-0.018445,       0.061914,        4.545042,        -16.456823,      -0.059325,       144.579071,      0.107493,        2.794995,        5.469193,        0.107493,        2.794995,        5.469193,        1,     -0.001644,       -0.377527},
			{-0.026894,       0.019412,        7.657685,        -13.573175,      -1.318275,       142.920258,      0.153030,        2.365622,        12.845691,       0.153030,        2.365622,        12.845691,       1,     -0.753021,       -0.079360},
			{-0.002322,       0.131824,        3.702759,        -14.384125,      -0.443625,       141.014832,      0.104033,        2.388915,        10.809194,       0.104033,        2.388915,        10.809194,       -1,    -0.775085,       0.054092},
			{0.048499,        -0.102480,       -4.490739,       -13.871024,      2.368100,        143.059341,      0.113330,        2.161752,        11.001549,       0.113330,        2.161752,        11.001549,       1,     0.232171,        -0.022080},
			{0.051659,        0.031150,        -4.147505,       -14.023800,      4.053874,        143.513657,      0.110978,        2.019907,        8.837499,        0.110978,        2.019907,        8.837499,        -1,    0.139400,        0.114800},
			{0.042759,        -0.076360,       -3.494961,       -13.774949,      3.323424,        140.310638,      0.092178,        3.122678,        7.076470,        0.092178,        3.122678,        7.076470,        1,    -0.370567,       -0.174257},
			{0.070169,        -0.039341,       -5.861030,       -15.902077,      3.416525,        143.858582,      0.107550,        1.627358,        8.873111,        0.107550,        1.627358,        8.873111,        1,     -0.142293,       -0.126163},
			{-0.001870,       0.093644,        2.131828,       -13.414799,       2.109800,        144.137360,      0.072652,        2.413228,        7.686354,        0.072652,        2.413228,        7.686354,        -1,    0.712684,        -0.076503},
			{0.037019,        0.441651,        -4.290100,       -11.363448,      0.487550,        143.324097,      0.128651,        2.501580,        9.511423,        0.128651,        2.501580,        9.511423,        -1,    0.224712,        -0.115024},
			{0.026313,        -0.026765,       -0.709233,       -13.899199,      1.325625,        141.896637,      0.162768,        1.710796,        11.520280,       0.162768,        1.710796,        11.520280,       -1,    1,		        -0.010141},
			{0.023024,       0.471382,        0.544582,        -18.514299,      2.639350,        143.035217,      0.095118,        2.657016,        5.624974,        0.095118,        2.657016,       5.624974,          1,     0.481641,        -0.058388},
			{0.026958,        -0.013157,       -2.284485,       -16.649326,      3.518899,        142.532074,      0.117005,        2.841595,        8.528635,        0.117005,        2.841595,        8.528635,        1,     -0.131992,       -0.134578},
			{-0.069201,       0.245010,        10.451024,       -14.295224,      1.187725,        142.654602,      0.171990,        2.848695,        12.396350,       0.171990,        2.848695,        12.396350,       1,     -1,		       0.065313},
			{0.071136,        0.075393,       -6.132676,       -17.375046,      3.071601,        142.710236,      0.158120,        2.909716,        13.880224,       0.158120,        2.909716,       13.880224,       -1,    0.773075,        0.004596},
			{0.069330,        -0.116926,       -4.666482,       -15.122624,      3.927350,        142.742065,      0.118787,        2.412264,        7.321387,        0.118787,        2.412264,        7.321387,        1,     -0.033686,       0.026628},
			{-0.006191,       0.102415,        3.190100,        -17.799599,      3.568075,        142.937546,      0.121230,        1.977814,        9.074983,        0.121230,        1.977814,        9.074983,        1,     -1,			       0.027073},
			{0.010190,        -0.060366,       -0.259779,       -17.521873,      1.997975,        143.138763,      0.067869,        2.046270,        5.801754,        0.067869,        2.046270,        5.801754,        1,     -0.478453,       -0.269947},
			{0.048886,        0.030376,        -2.506213,       -13.719477,      1.639050,        142.952408,      0.121380,        1.765830,        11.997251,       0.121380,        1.765830,        11.997251,       -1,    0.478017,        0.038168},
			{0.041792,        0.262617,        -2.812557,       -18.592176,      2.345525,        141.344879,      0.126808,        2.158458,        10.560312,       0.126808,        2.158458,        10.560312,       1,     0.019075,        -0.165985},
			{0.032311,        -0.075006,       -1.518432,       -16.218475,      2.195200,        143.401489,      0.125367,        2.369204,        7.552142,        0.125367,        2.369204,        7.552142,        1,     0.533009,        -0.093349},
			{0.009674,        0.294606,        0.985525,        -17.642973,      3.893050,        139.784561,      0.167222,        2.579537,        12.655560,       0.167222,        2.579537,        12.655560,       1,     0.328874,        0.117028},
			{-0.047596,       0.389991,        8.986056,        -17.051123,      0.034300,        141.856430,      0.171422,        2.019228,        12.909938,       0.171422,        2.019228,        12.909938,       -1,    0.194247,        0.055496},
			{-0.020122,       0.424818,        4.528918,        -17.204950,      2.719150,        143.294373,      0.130708,        2.549068,        8.440595,        0.130708,        2.549068,        8.440595,        -1,    0.896305,        -0.095768},
			{0.103705,        -0.036374,       -10.686489,      -16.667524,      3.306625,        142.846741,      0.134642,        2.422596,        9.819854,        0.134642,        2.422596,        9.819854,        -1,    0.285647,        0.271907},
			{-0.010964,       -0.404889,       1.579379,       -15.388278,      3.992100,        143.203735,      0.121896,        2.754549,       10.810369,       0.121896,        2.754549,        10.810369,         1,     -1,		       -0.243323},
			{0.059463,        -0.150721,       -4.092492,       -15.249325,      3.862425,        142.044525,      0.170081,        2.483019,        13.485336,       0.170081,        2.483019,        13.485336,       -1,    0.540260,        0.017488},
			{0.042114,        0.377157,        -1.647935,       -14.298897,      3.344949,        143.673248,      0.144397,        2.256619,        12.999559,       0.144397,        2.256619,        12.999559,       1,     -0.148766,       -0.028753},
			{-0.003031,       -0.041340,      3.333921,        -13.993877,      3.137575,        140.738510,     0.112615,        3.101369,        9.953571,        0.112615,        3.101369,        9.953571,         1,     -0.262223,       0.295021},
			{0.036568,        -0.076489,       -4.780508,       -11.740749,     0.446075,        142.870865,      0.128419,        2.499109,        9.559705,        0.128419,        2.499109,        9.559705,        1,     -0.580736,       0.009466},
			{0.045145,        0.397021,        -1.846058,       -13.962729,      2.358825,        141.952454,      0.166690,        2.424792,        11.715002,       0.166690,        2.424792,        11.715002,       1,     0.858497,        0.015255},
			{0.014447,        0.783853,        0.822936,        -15.146424,      1.229900,        143.750778,      0.125377,        2.885193,        8.668916,        0.125377,        2.885193,        8.668916,        -1,    0.274233,        -0.542300},
			{0.042630,        -0.160524,       -4.384455,       -10.203551,      1.329300,        141.785522,      0.101103,        2.270773,        11.535971,       0.101103,        2.270773,        11.535971,       -1,   -0.303391,       -0.060309},
			{0.019928,	-0.031666,	6.158215,	4.399324,	-2.455425,	141.853775,	0.404680,	5.756093,	8.077033,	0.404680,	5.756093,	8.077033,	1,		0.105733,	0.250469},
			{-0.004644,	0.374062,	7.438538,	14.042522,	-1.580600,	141.437286,	0.554212,	4.450397,	10.550186,	0.554212,	4.450397,	10.550186,	1,		-0.601523,	0.056510},
			{0.007868,	-0.398763,	-3.868957,	10.465000,	7.028350,	140.925751,	0.499164,	6.035095,	15.654121,	0.499164,	6.035095,	15.654121,	1,		0.048970,	-0.082026},
			{-0.001741,	0.243527,	0.719812,	1.064525,	0.763700,	143.406372,	0.366397,	7.734085,	14.080572,	0.366397,	7.734085,	14.080572,	-1,		0.212981,	0.190337},
			{0.041598,	0.555095,	1.380997,	2.882250,	4.089400,	144.309204,	0.514743,	5.071359,	14.596272,	0.514743,	5.071359,	14.596272,	-1,		-0.365347,	0.089831},
			{0.147625,	1.037570,	-10.826051,	-5.928999,	0.335475,	142.143753,	0.436193,	8.486063,	12.523438,	0.436193,	8.486063,	12.523438,	-1,		0.069852,	-0.008968},
			{-0.047919,	0.110284,	6.882926,	-2.337125,	-4.442375,	143.550217,	0.706699,	4.827217,	12.137708,	0.706699,	4.827217,	12.137708,	1,		-1,			-0.156514},
			{0.045984,	-0.380188,	1.564739,	-0.759499,	-1.339450,	140.221939,	0.622788,	10.490523,	11.790931,	0.622788,	10.490523,	11.790931,	1,		0.303841,	0.314635},
			{0.086486,	0.654608,	-5.252276,	1.921675,	-7.683900,	142.476578,	0.706509,	7.253930,	23.155399,	0.706509,	7.253930,	23.155399,	1,		-0.631479,	-0.093693},
			{-0.004063,	-0.236820,	-4.847129,	4.983999,	1.562050,	142.417816,	0.483101,	8.019143,	18.499580,	0.483101,	8.019143,	18.499580,	-1,   	-0.493813,	0.079927},
			{-0.030763,	0.947343,	3.836066,	8.359573,	-3.887450,	141.870575,	0.519396,	5.983553,	20.536451,	0.519396,	5.983553,	20.536451,	1,    	0.255080,	0.128187},
			{0.048499,	0.841445,	-0.436943,	-12.240024,	3.734500,	140.667786,	0.572848,	8.425054,	22.586788,	0.572848,	8.425054,	22.586788,	-1,   	-0.128913,	0.243708},
			{-0.031215,	-0.357551,	2.484800,	-11.606876,	14.493499,	141.381088,	0.334457,	7.595252,	16.751766,	0.334457,	7.595252,	16.751766,	1,    	0.270732,	0.060816},
			{0.110542,	-0.582117,	-9.645954,	-15.519701,	5.684000,	143.273224,	0.432839,	6.049396,	14.124704,	0.432839,	6.049396,	14.124704,	1,    	-1,			-0.173101},
			{-0.012254,	0.257973,	3.177718,	-3.277923,	17.957624,	140.298889,	0.648111,	7.530686,	11.535598,	0.648111,	7.530686,	11.535598,	1,     	-0.445058,	0.481925},
			{0.054561,	2.426951,	2.453006,	-11.122824,	17.596424,	139.871704,	0.800952,	10.878620,	14.861249,	0.800952,	10.878620,	14.861249,	-1,    	0.372935,	0.327660},
			{0.032892,	0.865050,	-6.879444,	-4.710475,	6.099272,	139.822723,	0.740109,	7.486643,	19.086502,	0.740109,	7.486643,	19.086502,	-1,    	-1,			-0.025739},
			{-0.049918,	0.492729,	2.925936,	-2.596650,	-3.977924,	139.218979,	0.635357,	10.364867,	13.855571,	0.635357,	10.364867,	13.855571,	-1,    	-0.757871,	0.137993},
			{0.023927,	-1.567769,	-1.728745,	11.805153,	4.272625,	139.830414,	0.663813,	10.731772,	16.626171,	0.663813,	10.731772,	16.626171,	-1,    	-0.345446,	-0.012312},
			{-0.025475,	-0.437330,	-3.983175,	1.935499,	9.216900,	143.035904,	0.336191,	7.611690,	12.845521,	0.336191,	7.611690,	12.845521,	1,     	-0.786993,	0.229568},
			{-0.019993,	0.306215,	-0.284802,	-3.974776,	-5.555377,	143.962891,	0.500584,	6.105564,	21.049934,	0.500584,	6.105564,	21.049934,	1,     	-1,			-0.013907},
			{0.069524,	0.621394,	-15.413722,	11.711349,	-13.349000,	140.662018,	0.394053,	7.685262,	14.477435,	0.394053,	7.685262,	14.477435,	-1,    	-1,			0.225916},
			{0.006127,	2.090746,	1.312054,	5.101950,	-12.109125,	139.795425,	0.580368,	10.766104,	14.054166,	0.580368,	10.766104,	14.054166,	-1,    	0.427091,	0.060957},
			{0.075973,	-1.055176,	-2.941092,	7.045149,	-0.445726,	139.149323,	0.697349,	9.074348,	16.998930,	0.697349,	9.074348,	16.998930,	1,     	-0.232802,	-0.043931},
			{0.012189,	-0.262875,	-4.730073,	2.781800,	10.999275,	140.182526,	0.831838,	9.258089,	16.615576,	0.831838,	9.258089,	16.615576,	-1,    	-0.720303,	-0.223837},
			{-0.075135,	-0.200897,	7.502256,	0.347725,	-9.366351,	141.750366,	0.713446,	8.925179,	12.290474,	0.713446,	8.925179,	12.290474,	1,     	-1,	  		0.187904},
			{0.114089,	-0.794429,	0.461644,	7.404950,	-4.250050,	140.682678,	0.666905,	8.421721,	13.674560,	0.666905,	8.421721,	13.674560,	-1,    	0.378593,	-0.066038},
			{0.102802,	1.201190,	-2.627331,	11.879002,	-6.434226,	132.045731,	0.718894,	13.352355,	18.427593,	0.718894,	13.352355,	18.427593,	1,     	0.186792,	0.196500},
			{0.058367,	-0.231145,	8.270051,	9.943325,	-19.549599,	138.210266,	0.615716,	9.300193,	21.845804,	0.615716,	9.300193,	21.845804,	-1,    	0.701938,	0.094819},
			{-0.068814,	0.241721,	6.964319,	9.292324,	-9.680648,	141.043884,	0.507346,	13.856619,	17.542908,	0.507346,	13.856619,	17.542908,	1,     	0.178443,	-0.152886},
			{0.013221,	1.116509,	-7.912694,	14.276851,	-11.707675,	140.961121,	0.400237,	13.018427,	14.711573,	0.400237,	13.018427,	14.711573,	-1,    	0.181613,	0.069595},
			{-0.009738,	-0.239593,	6.223161,	12.176675,	-7.708222,	141.117905,	0.473889,	7.537686,	9.512319,	0.473889,	7.537686,	9.512319,	1,     	-0.286815,	0.140001},
			{-0.052111,	1.059626,	-3.512890,	13.847400,	-9.427774,	137.555756,	0.365256,	9.101843,	11.252199,	0.365256,	9.101843,	11.252199,	-1,    	0.247636,	-0.273578},
			{0.735160,	4.117451,	-7.568945,	3.995600,	-9.501450,	143.784729,	0.757498,	10.609903,	16.574505,	0.757498,	10.609903,	16.574505,	1,     	-0.504852,	0.131433},
			{0.078101,	0.095773,	7.264212,	-1.076250,	-15.866899,	139.047455,	1.098819,	10.651134,	24.712576,	1.098819,	10.651134,	24.712576,	-0.180041,	-0.435427,	-0.074994},
			{1.266070,	8.818374,	-3.417118,	-6.251351,	-3.827600,	141.969955,	0.816974,	6.101861,	12.263049,	0.816974,	6.101861,	12.263049,	-1,		0.853173,	0.631695},
			{1.697466,	10.324939,	2.853767,	-13.424603,	1.432551,	139.711777,	0.370190,	1.491357,	1.720815,	0.370190,	1.491357,	1.720815,	1,		1,	1},
			{0.683307,	5.445627,	-10.134812,	-1.753850,	-0.463575,	136.341293,	0.913210,	7.227240,	19.074953,	0.913210,	7.227240,	19.074953,	1,		0.610084,	-0.123052},
			{-0.100287,	-0.646933,	8.219552,	-2.925826,	-3.365600,	142.601517,	0.454554,	13.661610,	11.887608,	0.454554,	13.661610,	11.887608,	1,		0.136112,	-0.145143},
			{0.024959,	0.263455,	-6.085917,	-0.286475,	7.147700,	139.071808,	0.583993,	7.247105,	16.721569,	0.583993,	7.247105,	16.721569,	1,		0.401290,	0.233191},
			{-0.003805,	-1.597567,	-4.417603,	-15.227623,	0.178675,	142.130630,	0.663737,	15.403244,	17.602417,	0.663737,	15.403244,	17.602417,	-1,		0.399482,	0.033111},
			{0.043727,	0.198059,	-6.892602,	-5.449500,	-1.334375,	141.096176,	0.567198,	6.576869,	21.094625,	0.567198,	6.576869,	21.094625,	1,		-1,  		0.032049},
			{0.012383,	-0.037729,	3.358364,	-11.157824,	-1.950899,	143.568970,	0.551069,	6.758516,	17.228321,	0.551069,	6.758516,	17.228321,	-1,		0.671219,	0.285380},
			{0.039857,	2.036443,	-2.774505,	-13.046251,	-5.396125,	141.007660,	0.561992,	10.639934,	12.045113,	0.561992,	10.639934,	12.045113,	1,		-0.138011,	-0.169667},
			{-0.068298,	0.497373,	-4.339501,	3.122349,	15.358701,	143.166443,	0.479117,	7.443470,	16.334061,	0.479117,	7.443470,	16.334061,	-1,		-1,	 		0.237530},
			{-0.001096,	0.338526,	2.125056,	-14.137552,	-1.792701,	138.150757,	0.778571,	12.542549,	15.872071,	0.778571,	12.542549,	15.872071,	-1,		-0.502609,	-0.194082},
			{-0.030054,	0.171036,	0.290285,	-6.485500,	-1.829450,	141.117004,	0.542197,	7.483891,	15.459855,	0.542197,	7.483891,	15.459855,	1,		-0.466101,	0.019935},
			{0.096289,	-1.472190,	-5.245311,	-5.763450,	-4.286624,	138.507782,	0.555319,	5.729400,	17.720259,	0.555319,	5.729400,	17.720259,	-1,		-0.240074,	-0.142900},
			{0.035213,	1.337012,	1.543455,	-8.400701,	-6.613599,	140.642075,	0.795691,	10.141720,	14.110466,	0.795691,	10.141720,	14.110466,	1,		0.398382,	0.170754},
			{0.057980,	-0.146722,	-8.228194,	-2.710751,	-6.700575,	140.306946,	0.617250,	7.209540,	14.426613,	0.617250,	7.209540,	14.426613,	1,		-0.887274,	-0.114009},
	};
//normalizzazione facoltativa
/*
	for(int i=0;i<nOfSamples;i++)
	{
		trainingSetFeatures[i][3]=trainingSetFeatures[i][3]/140;
		trainingSetFeatures[i][4]=trainingSetFeatures[i][3]/140;
		trainingSetFeatures[i][5]=trainingSetFeatures[i][3]/140;
	}
*/
	int trainingLabels[nOfSamples] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	/*
		indici trainingFeatures:
		0 : media accelerazione
		1 : media direzione
		2 : deviazione standard accelerazione
		3 : deviazione standard direzione
		4 : correlazione tra accelerazione e direzione
	 */

	//estrazione delle features dei vettori di training
	/*
	for (int ri = 0; ri < nOfSamples; ri++)
	{
		trainingSetFeatures[ri][0] = calculateMean(trainingSetAcceleration[ri]);
		trainingSetFeatures[ri][1] = calculateMean(trainingSetDirection[ri]);
		trainingSetFeatures[ri][2] = sqrt(calculateVar(trainingSetAcceleration[ri],trainingSetFeatures[ri][0]));
		trainingSetFeatures[ri][3] = sqrt(calculateVar(trainingSetDirection[ri], trainingSetFeatures[ri][1]));
		trainingSetFeatures[ri][4] = calculateCorr(trainingSetAcceleration[ri], trainingSetDirection[ri], trainingSetFeatures[ri][0], trainingSetFeatures[ri][1], trainingSetFeatures[ri][2], trainingSetFeatures[ri][3]);
	}
	 */
	/*
	  indici trainingFeatures:
	  0		media accelerazione x
	  1		media accelerazione y
	  2		media accelerazione z
	  3		media gyro x
	  4		media gyro y
	  5		media gyro z
	  6		dev accelerazione x
	  7		dev accelerazione y
	  8		dev accelerazione z
	  9		dev gyro x
	  10	dev gyro y
	  11	dev gyro z
	  12	corr x
	  13	corr y
	  14	corr z
	 */
/*
	for (int ri = 0; ri < nOfSamples; ri++)
	{
		trainingSetFeatures[ri][0] = calculateMean(trainingSetAccelerationX[ri]);
		trainingSetFeatures[ri][1] = calculateMean(trainingSetAccelerationY[ri]);
		trainingSetFeatures[ri][2] = calculateMean(trainingSetAccelerationZ[ri]);

		trainingSetFeatures[ri][3] = calculateMean(trainingSetGyroX[ri]);
		trainingSetFeatures[ri][4] = calculateMean(trainingSetGyroY[ri]);
		trainingSetFeatures[ri][5] = calculateMean(trainingSetGyroZ[ri]);

		trainingSetFeatures[ri][6] = sqrt(calculateVar(trainingSetAccelerationX[ri],trainingSetFeatures[ri][0]));
		trainingSetFeatures[ri][7] = sqrt(calculateVar(trainingSetAccelerationY[ri],trainingSetFeatures[ri][1]));
		trainingSetFeatures[ri][8] = sqrt(calculateVar(trainingSetAccelerationZ[ri],trainingSetFeatures[ri][2]));

		trainingSetFeatures[ri][9] = sqrt(calculateVar(trainingSetGyroX[ri],trainingSetFeatures[ri][3]));
		trainingSetFeatures[ri][10] = sqrt(calculateVar(trainingSetGyroY[ri],trainingSetFeatures[ri][4]));
		trainingSetFeatures[ri][11] = sqrt(calculateVar(trainingSetGyroZ[ri],trainingSetFeatures[ri][5]));

		trainingSetFeatures[ri][12] = calculateCorr(trainingSetAccelerationX[ri], trainingSetGyroX[ri], trainingSetFeatures[ri][0], trainingSetFeatures[ri][3], trainingSetFeatures[ri][6], trainingSetFeatures[ri][9]);
		trainingSetFeatures[ri][13] = calculateCorr(trainingSetAccelerationY[ri], trainingSetGyroY[ri], trainingSetFeatures[ri][1], trainingSetFeatures[ri][4], trainingSetFeatures[ri][7], trainingSetFeatures[ri][10]);
		trainingSetFeatures[ri][14] = calculateCorr(trainingSetAccelerationZ[ri], trainingSetGyroZ[ri], trainingSetFeatures[ri][2], trainingSetFeatures[ri][5], trainingSetFeatures[ri][8], trainingSetFeatures[ri][11]);
	}
	*/
	/*
	for(int c=0;c<nOfSamples;c++)
	{
		for(int ri = 0; ri<nOfFeatures; ri++)
		{
			snprintf(buffer, sizeof buffer, "%f", trainingSetFeatures[c][ri]);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
		}
		HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	}
	 */
	//float sampleToClassify_acceleration[vectorLength] = { 35,1,2,3,66,0,12,6,18,1 };
	//float sampleToClassify_direction[vectorLength] = { 4,21,6,6,18,10,9,61,12,11 };

	//test
	/*
	float sampleToClassify_acceleration[vectorLength] = { 106,94,105,117,92,111,98,126,98,112 };
	float sampleToClassify_direction[vectorLength] = { 45,4,5,7,2,1,8,66,8,12 };

	float sampleFeatures[nOfFeatures] = { 0 };

	sampleFeatures[0] = calculateMean(sampleToClassify_acceleration);
	sampleFeatures[1] = calculateMean(sampleToClassify_direction);
	sampleFeatures[2] = sqrt(calculateVar(sampleToClassify_acceleration, sampleFeatures[0]));
	sampleFeatures[3] = sqrt(calculateVar(sampleToClassify_direction, sampleFeatures[1]));
	sampleFeatures[4] = calculateCorr(sampleToClassify_acceleration, sampleToClassify_direction, sampleFeatures[0], sampleFeatures[1], sampleFeatures[2], sampleFeatures[3]);
	 */
	/*
	float sampleToClassify_accelerationX[vectorLength] = { 106,94,105,117,92,111,98,126,98,112 };
	float sampleToClassify_accelerationY[vectorLength] = { 106,94,105,117,92,111,98,126,98,112 };
	float sampleToClassify_accelerationZ[vectorLength] = { 106,94,105,117,92,111,98,126,98,112 };

	float sampleToClassify_gyroX[vectorLength] = { 45,4,5,7,2,1,8,66,8,12 };
	float sampleToClassify_gyroY[vectorLength] = { 45,4,5,7,2,1,8,66,8,12 };
	float sampleToClassify_gyroZ[vectorLength] = { 45,4,5,7,2,1,8,66,8,12 };

	float sampleFeatures[nOfFeatures] = { 0 };
	 */

	float sampleToClassify_accelerationX[vectorLength] = { 0 };
	float sampleToClassify_accelerationY[vectorLength] = { 0 };
	float sampleToClassify_accelerationZ[vectorLength] = { 0 };

	float sampleToClassify_gyroX[vectorLength] = { 0 };
	float sampleToClassify_gyroY[vectorLength] = { 0 };
	float sampleToClassify_gyroZ[vectorLength] = { 0 };

	float sampleFeatures[nOfFeatures] = { 0 };

	/*
	sampleFeatures[0] = calculateMean(sampleToClassify_accelerationX);
	sampleFeatures[1] = calculateMean(sampleToClassify_accelerationY);
	sampleFeatures[2] = calculateMean(sampleToClassify_accelerationZ);
	sampleFeatures[3] = calculateMean(sampleToClassify_gyroX);
	sampleFeatures[4] = calculateMean(sampleToClassify_gyroY);
	sampleFeatures[5] = calculateMean(sampleToClassify_gyroZ);

	sampleFeatures[6] = sqrt(calculateVar(sampleToClassify_accelerationX, sampleFeatures[0]));
	sampleFeatures[7] = sqrt(calculateVar(sampleToClassify_accelerationY, sampleFeatures[1]));
	sampleFeatures[8] = sqrt(calculateVar(sampleToClassify_accelerationZ, sampleFeatures[2]));
	sampleFeatures[9] = sqrt(calculateVar(sampleToClassify_accelerationX, sampleFeatures[0]));
	sampleFeatures[10] = sqrt(calculateVar(sampleToClassify_accelerationY, sampleFeatures[1]));
	sampleFeatures[11] = sqrt(calculateVar(sampleToClassify_accelerationZ, sampleFeatures[2]));

	sampleFeatures[12] = calculateCorr(sampleToClassify_accelerationX, sampleToClassify_gyroX, sampleFeatures[0], sampleFeatures[3], sampleFeatures[6], sampleFeatures[9]);
	sampleFeatures[13] = calculateCorr(sampleToClassify_accelerationY, sampleToClassify_gyroY, sampleFeatures[1], sampleFeatures[4], sampleFeatures[7], sampleFeatures[10]);
	sampleFeatures[14] = calculateCorr(sampleToClassify_accelerationZ, sampleToClassify_gyroZ, sampleFeatures[2], sampleFeatures[5], sampleFeatures[8], sampleFeatures[11]);
	 */
	int knn_index[nOfSamples] = { 0 };
	for (int i = 0; i < nOfSamples; i++)
	{
		knn_index[i] = i;
	}
	//ordina gli indici contenuti in knn_index in maniera crescente rispetto alla distanza, in maniera da mantenere un
	//riferimento al rispettivo vettore di training
	/*
	findKNN(trainingSetFeatures, knn_index, sampleFeatures);
	 */
	/*
	for(int i = 0; i<nOfSamples;i++)
	{
		snprintf(buffer, sizeof buffer, "%d", knn_index[i]);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
		HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	}

	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	for(int i = 0; i<nOfSamples;i++)
	{
		int temp=knn_index[i];
		snprintf(buffer, sizeof buffer, "%d", trainingLabels[temp]);
		HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
		HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	}
	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	 */
	//sfrutta gli indici ordinati e va a vedere il rispettivo valore di essi per capire la classe del vettore sampleToClassify
	//int sampleLabel = classificate(trainingLabels, knn_index);

	char *class="";
	/*
	if (sampleLabel == 0)
	{
		class="classe 1\t\t";
	}
	else
	{
		class="classe 2\t\t";
	}

	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)class, strlen(class), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	 */
	/*
	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	char *placeHolder = "Acc_X";
	HAL_UART_Transmit(&huart2, (uint8_t*)placeHolder, strlen(placeHolder), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	placeHolder="Acc_Y";
	HAL_UART_Transmit(&huart2, (uint8_t*)placeHolder, strlen(placeHolder), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	placeHolder="Acc_Z";
	HAL_UART_Transmit(&huart2, (uint8_t*)placeHolder, strlen(placeHolder), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	placeHolder="Gyr_X";
	HAL_UART_Transmit(&huart2, (uint8_t*)placeHolder, strlen(placeHolder), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	placeHolder="Gyr_Y";
	HAL_UART_Transmit(&huart2, (uint8_t*)placeHolder, strlen(placeHolder), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	placeHolder="Gyr_Z";
	HAL_UART_Transmit(&huart2, (uint8_t*)placeHolder, strlen(placeHolder), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	 */
	/*
	int vettnum=0;
	char *sep = "#############";
	char *vet= "SAMPLE:";
	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)vet, strlen(vet), 0xFFFF);
	snprintf(buffer, sizeof buffer, "%d", vettnum);
	HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)sep, strlen(sep), 0xFFFF);
	HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
	*/
	for(;;)
	{
		/*
		for(int i = 0; i<nOfSamples;i++)
		{
			snprintf(buffer, sizeof buffer, "%d", knn_index[i]);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
		}
		HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
		 */
		LSM6DS0_ReadAcceleration(acceleration_data);
		LSM6DS0_ReadGyro(gyro_data);

		/*
		for(int i = 0; i<3;i++)
		{
			snprintf(buffer, sizeof buffer, "%f", acceleration_data[i]);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
		}
		for(int i = 0; i<3;i++)
		{
			snprintf(buffer, sizeof buffer, "%f", gyro_data[i]);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
		}
		HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
		 */

		if(cycleNum<vectorLength)
		{
			sampleToClassify_accelerationX[cycleNum] = acceleration_data[0];
			sampleToClassify_accelerationY[cycleNum] = acceleration_data[1];
			sampleToClassify_accelerationZ[cycleNum] = acceleration_data[2];
/*
			for(int i = 0; i<3;i++)
			{
				snprintf(buffer, sizeof buffer, "%f", acceleration_data[i]);
				HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
				HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
			}
*/
			sampleToClassify_gyroX[cycleNum] = gyro_data[0];
			sampleToClassify_gyroY[cycleNum] = gyro_data[1];
			sampleToClassify_gyroZ[cycleNum] = gyro_data[2];
	/*
			for(int i = 0; i<3;i++)
			{
				snprintf(buffer, sizeof buffer, "%f", gyro_data[i]);
				HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
				HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
			}
			HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
*/
			cycleNum++;
		}
		else
		{
			cycleNum=0;
			//vettnum++;
			sampleFeatures[0] = calculateMean(sampleToClassify_accelerationX);
			sampleFeatures[1] = calculateMean(sampleToClassify_accelerationY);
			sampleFeatures[2] = calculateMean(sampleToClassify_accelerationZ);
			sampleFeatures[3] = calculateMean(sampleToClassify_gyroX);
			sampleFeatures[4] = calculateMean(sampleToClassify_gyroY);
			sampleFeatures[5] = calculateMean(sampleToClassify_gyroZ);
			//sampleFeatures[3] = calculateMean(sampleToClassify_gyroX)/140;
			//sampleFeatures[4] = calculateMean(sampleToClassify_gyroY)/140;
			//sampleFeatures[5] = calculateMean(sampleToClassify_gyroZ)/140;

			sampleFeatures[6] = sqrt(calculateVar(sampleToClassify_accelerationX, sampleFeatures[0]));
			sampleFeatures[7] = sqrt(calculateVar(sampleToClassify_accelerationY, sampleFeatures[1]));
			sampleFeatures[8] = sqrt(calculateVar(sampleToClassify_accelerationZ, sampleFeatures[2]));
			sampleFeatures[9] = sqrt(calculateVar(sampleToClassify_accelerationX, sampleFeatures[0]));
			sampleFeatures[10] = sqrt(calculateVar(sampleToClassify_accelerationY, sampleFeatures[1]));
			sampleFeatures[11] = sqrt(calculateVar(sampleToClassify_accelerationZ, sampleFeatures[2]));

			sampleFeatures[12] = calculateCorr(sampleToClassify_accelerationX, sampleToClassify_gyroX, sampleFeatures[0], sampleFeatures[3], sampleFeatures[6], sampleFeatures[9]);
			sampleFeatures[13] = calculateCorr(sampleToClassify_accelerationY, sampleToClassify_gyroY, sampleFeatures[1], sampleFeatures[4], sampleFeatures[7], sampleFeatures[10]);
			sampleFeatures[14] = calculateCorr(sampleToClassify_accelerationZ, sampleToClassify_gyroZ, sampleFeatures[2], sampleFeatures[5], sampleFeatures[8], sampleFeatures[11]);

			//sampleFeatures[3] = sampleFeatures[3]/140;
			//sampleFeatures[4] = sampleFeatures[4]/140;
			//sampleFeatures[5] = sampleFeatures[5]/140;
			for(int ri = 0; ri<nOfFeatures; ri++)
			{
				snprintf(buffer, sizeof buffer, "%f", sampleFeatures[ri]);
				HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
				HAL_UART_Transmit(&huart2, (uint8_t*)tab, strlen(tab), 0xFFFF);
			}
			HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
			/*
			HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)vet, strlen(vet), 0xFFFF);
			snprintf(buffer, sizeof buffer, "%d", vettnum);
			HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)sep, strlen(sep), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
			*/

			for (int i = 0; i < nOfSamples; i++)
			{
				knn_index[i] = i;
			}
			findKNN(trainingSetFeatures, knn_index, sampleFeatures);
			int sampleLabel = classificate(trainingLabels, knn_index);
			//sampleLabel = classificate(trainingLabels, knn_index);
			class="";
			if (sampleLabel == 0)
			{
				class="alterato\t\t";
			}
			else
			{
				class="normale\t\t";
			}

			HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)class, strlen(class), 0xFFFF);
			HAL_UART_Transmit(&huart2, (uint8_t*)newline, strlen(newline), 0xFFFF);

		}
		HAL_Delay(sampleTime);
	}
}
/*
//inizializzazione della seriale
void MX_USART2_UART_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	HAL_UART_Init(&huart2);
}
 */
//configurazione dei pin per comunicazione

/*
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	if(huart->Instance==USART2)
	{
		__GPIOA_CLK_ENABLE();
		__USART2_CLK_ENABLE();

		/**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX

		GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
		GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	}
}
 */
