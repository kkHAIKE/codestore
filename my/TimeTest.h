#pragma once
#define INIT_TIME_TEST  LARGE_INTEGER begin_time_test;\
						LARGE_INTEGER end_time_test;\
						LARGE_INTEGER li_time_test;\
						double RET_TIME_TEST;\
						QueryPerformanceFrequency(&li_time_test);

#define BEGIN_TIME_TEST QueryPerformanceCounter(&begin_time_test);

#define END_TIME_TEST QueryPerformanceCounter(&end_time_test);\
					  RET_TIME_TEST=(static_cast<double>(end_time_test.QuadPart-begin_time_test.QuadPart))/(static_cast<double>(li_time_test.QuadPart));//*1000000000.0;
