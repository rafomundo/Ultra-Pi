/* Program for calculating the number pi on multicore-machines.
 * This program is using the BBP-algorithm for calculation.
 * The main program creates processes depending on the numbers of cpus
 * and tells them which range they should calculate.
 * 
 * Author: Raphael Kuchta				Date: 2008-09-08
 */

#include "StdAfx.h"
#include "test.h"
#include <windows.h>
#include <tchar.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include <time.h>
#include <sys/timeb.h>




const int MAX_CPU = 64;
const int MAX_CHAR = 50;
const int BUFFER = 11;					//TRUSTED (form calc_pi.cpp) + 3
const char *PI_RESULT_FILE = "ultra_pi_result.txt";


int nCPU;
wchar_t filename[MAX_CPU][MAX_CHAR]; 



int test()
{
	int count = 5000;

	wchar_t pi_digits[MAX_CHAR] = L"";
	wchar_t my_id[MAX_CHAR] = L"";
	wchar_t num_processes[MAX_CHAR] = L"";

	double start_sec, start_mill, end_sec, end_mill, diff;
	struct _timeb start_t, end_t;

	//cpu_info();

	nCPU = 3;

	

	
	_ftime_s(&start_t);					//save start time

	STARTUPINFO si[MAX_CPU];
	PROCESS_INFORMATION pi[MAX_CPU];

	for(int i = 0; i < nCPU; i++)
	{
		ZeroMemory( &si[i], sizeof(si[i]));
		si[i].cb = sizeof(si[i]);
		si[i].dwFlags = STARTF_USESHOWWINDOW;
		si[i].wShowWindow = SW_HIDE;
		ZeroMemory( &pi[i], sizeof(pi[i]));
	}

	for(int i = 0; i < nCPU; i++)
	{
		wchar_t parameter[MAX_CHAR * 4] = L"";

		_itow_s(count, pi_digits, MAX_CHAR - 1, 10);
		_itow_s(i, my_id, MAX_CHAR - 1, 10);
		_itow_s(nCPU, num_processes, MAX_CHAR - 1, 10);

		//filename[i] = L"";

		wcscpy(filename[i], _T("ultra_pi_"));
		wcscat(filename[i], my_id);
		wcscat(filename[i], _T(".txt"));
		
		wcscat(parameter, my_id);
		wcscat(parameter, _T(" "));
		wcscat(parameter, pi_digits);	
		wcscat(parameter, _T(" "));
		wcscat(parameter, num_processes);
		wcscat(parameter, _T(" "));
		wcscat(parameter, filename[i]);

		printf("\nCalculating PI on CPU %d", i);
		if(!CreateProcess(
			_T("calc_pi.exe"),
			parameter,
			NULL,
			NULL,
			false,
			0,
			NULL,
			NULL,
			&si[i],
			&pi[i] ))
		{
			printf("\nError: Creating process failed!");
			return -1;
		}
	}

	for(int i = 0; i < nCPU; i++)
	{
		WaitForSingleObject(pi[i].hProcess, INFINITE);
		CloseHandle(pi[i].hThread);
	}

	printf("\nNow all finished!");
	_ftime_s(&end_t);						//save end time


	start_sec = (double) start_t.time;
	start_mill = (double) start_t.millitm;
	end_sec = (double) end_t.time;
	end_mill = (double) end_t.millitm;
	diff = (end_sec + (end_mill / 1000)) - (start_sec + (start_mill / 1000));

	printf("\nTime needed: %.3lf sec", diff);

	//if(union_files() == -1)
	//{
	//	printf("\nError: Cannot open result files!");
	//	return -1;
	//}
	union_files();

	getchar();
	return 0;
}

const char* szFeatures[] =
{
    "x87 FPU On Chip",
    "Virtual-8086 Mode Enhancement",
    "Debugging Extensions",
    "Page Size Extensions",
    "Time Stamp Counter",
    "RDMSR and WRMSR Support",
    "Physical Address Extensions",
    "Machine Check Exception",
    "CMPXCHG8B Instruction",
    "APIC On Chip",
    "Unknown1",
    "SYSENTER and SYSEXIT",
    "Memory Type Range Registers",
    "PTE Global Bit",
    "Machine Check Architecture",
    "Conditional Move/Compare Instruction",
    "Page Attribute Table",
    "36-bit Page Size Extension",
    "Processor Serial Number",
    "CFLUSH Extension",
    "Unknown2",
    "Debug Store",
    "Thermal Monitor and Clock Ctrl",
    "MMX Technology",
    "FXSAVE/FXRSTOR",
    "SSE Extensions",
    "SSE2 Extensions",
    "Self Snoop",
    "Multithreading Technology",
    "Thermal Monitor",
    "Unknown4",
    "Pend. Brk. EN."
};

int cpu_info()
{

	int logical_cpus = 0;

    char CPUString[0x20];
    char CPUBrandString[0x40];
    int CPUInfo[4] = {-1};
    int nSteppingID = 0;
    int nModel = 0;
    int nFamily = 0;
    int nProcessorType = 0;
    int nExtendedmodel = 0;
    int nExtendedfamily = 0;
    int nBrandIndex = 0;
    int nCLFLUSHcachelinesize = 0;
    int nLogicalProcessors = 0;
    int nAPICPhysicalID = 0;
    int nFeatureInfo = 0;
    int nCacheLineSize = 0;
    int nL2Associativity = 0;
    int nCacheSizeK = 0;
    int nPhysicalAddress = 0;
    int nVirtualAddress = 0;
    int nRet = 0;
    unsigned    nIds, nExIds, i;

    bool    bSSE3Instructions = false;
    bool    bMONITOR_MWAIT = false;
    bool    bCPLQualifiedDebugStore = false;
    bool    bVirtualMachineExtensions = false;
    bool    bEnhancedIntelSpeedStepTechnology = false;
    bool    bThermalMonitor2 = false;
    bool    bSupplementalSSE3 = false;
    bool    bL1ContextID = false;
    bool    bCMPXCHG16B = false;
    bool    bxTPRUpdateControl = false;
    bool    bPerfDebugCapabilityMSR = false;
    bool    bSSE41Extensions = false;
    bool    bSSE42Extensions = false;
    bool    bPOPCNT = false;

    bool    bMultithreading = false;

    bool    bLAHF_SAHFAvailable = false;
    bool    bCmpLegacy = false;
    bool    bSVM = false;
    bool    bExtApicSpace = false;
    bool    bAltMovCr8 = false;
    bool    bLZCNT = false;
    bool    bSSE4A = false;
    bool    bMisalignedSSE = false;
    bool    bPREFETCH = false;
    bool    bSKINITandDEV = false;
    bool    bSYSCALL_SYSRETAvailable = false;
    bool    bExecuteDisableBitAvailable = false;
    bool    bMMXExtensions = false;
    bool    bFFXSR = false;
    bool    b1GBSupport = false;
    bool    bRDTSCP = false;
    bool    b64Available = false;
    bool    b3DNowExt = false;
    bool    b3DNow = false;
    bool    bNestedPaging = false;
    bool    bLBRVisualization = false;
    bool    bFP128 = false;
    bool    bMOVOptimization = false;

    // __cpuid with an InfoType argument of 0 returns the number of
    // valid Ids in CPUInfo[0] and the CPU identification string in
    // the other three array elements. The CPU identification string is
    // not in linear order. The code below arranges the information 
    // in a human readable form.
    __cpuid(CPUInfo, 0);
    nIds = CPUInfo[0];
    memset(CPUString, 0, sizeof(CPUString));
    *((int*)CPUString) = CPUInfo[1];
    *((int*)(CPUString+4)) = CPUInfo[3];
    *((int*)(CPUString+8)) = CPUInfo[2];

    // Get the information associated with each valid Id
    for (i=0; i<=nIds; ++i)
    {
        __cpuid(CPUInfo, i);

        // Interpret CPU feature information.
        if  (i == 1)
        {
            nSteppingID = CPUInfo[0] & 0xf;
            nModel = (CPUInfo[0] >> 4) & 0xf;
            nFamily = (CPUInfo[0] >> 8) & 0xf;
            nProcessorType = (CPUInfo[0] >> 12) & 0x3;
            nExtendedmodel = (CPUInfo[0] >> 16) & 0xf;
            nExtendedfamily = (CPUInfo[0] >> 20) & 0xff;
			logical_cpus = (CPUInfo[1] >> 16) & 0xf;
            nBrandIndex = CPUInfo[1] & 0xff;
            nCLFLUSHcachelinesize = ((CPUInfo[1] >> 8) & 0xff) * 8;
            nLogicalProcessors = ((CPUInfo[1] >> 16) & 0xff);
            nAPICPhysicalID = (CPUInfo[1] >> 24) & 0xff;
            bSSE3Instructions = (CPUInfo[2] & 0x1) || false;
            bMONITOR_MWAIT = (CPUInfo[2] & 0x8) || false;
            bCPLQualifiedDebugStore = (CPUInfo[2] & 0x10) || false;
            bVirtualMachineExtensions = (CPUInfo[2] & 0x20) || false;
            bEnhancedIntelSpeedStepTechnology = (CPUInfo[2] & 0x80) || false;
            bThermalMonitor2 = (CPUInfo[2] & 0x100) || false;
            bSupplementalSSE3 = (CPUInfo[2] & 0x200) || false;
            bL1ContextID = (CPUInfo[2] & 0x300) || false;
            bCMPXCHG16B= (CPUInfo[2] & 0x2000) || false;
            bxTPRUpdateControl = (CPUInfo[2] & 0x4000) || false;
            bPerfDebugCapabilityMSR = (CPUInfo[2] & 0x8000) || false;
            bSSE41Extensions = (CPUInfo[2] & 0x80000) || false;
            bSSE42Extensions = (CPUInfo[2] & 0x100000) || false;
            bPOPCNT= (CPUInfo[2] & 0x800000) || false;
            nFeatureInfo = CPUInfo[3];
            bMultithreading = (nFeatureInfo & (1 << 28)) || false;
        }
    }

    // Calling __cpuid with 0x80000000 as the InfoType argument
    // gets the number of valid extended IDs.
    __cpuid(CPUInfo, 0x80000000);
    nExIds = CPUInfo[0];
    memset(CPUBrandString, 0, sizeof(CPUBrandString));

    // Get the information associated with each extended ID.
    for (i=0x80000000; i<=nExIds; ++i)
    {
        __cpuid(CPUInfo, i);

        if  (i == 0x80000001)
        {
            bLAHF_SAHFAvailable = (CPUInfo[2] & 0x1) || false;
            bCmpLegacy = (CPUInfo[2] & 0x2) || false;
            bSVM = (CPUInfo[2] & 0x4) || false;
            bExtApicSpace = (CPUInfo[2] & 0x8) || false;
            bAltMovCr8 = (CPUInfo[2] & 0x10) || false;
            bLZCNT = (CPUInfo[2] & 0x20) || false;
            bSSE4A = (CPUInfo[2] & 0x40) || false;
            bMisalignedSSE = (CPUInfo[2] & 0x80) || false;
            bPREFETCH = (CPUInfo[2] & 0x100) || false;
            bSKINITandDEV = (CPUInfo[2] & 0x1000) || false;
            bSYSCALL_SYSRETAvailable = (CPUInfo[3] & 0x800) || false;
            bExecuteDisableBitAvailable = (CPUInfo[3] & 0x10000) || false;
            bMMXExtensions = (CPUInfo[3] & 0x40000) || false;
            bFFXSR = (CPUInfo[3] & 0x200000) || false;
            b1GBSupport = (CPUInfo[3] & 0x400000) || false;
            bRDTSCP = (CPUInfo[3] & 0x8000000) || false;
            b64Available = (CPUInfo[3] & 0x20000000) || false;
            b3DNowExt = (CPUInfo[3] & 0x40000000) || false;
            b3DNow = (CPUInfo[3] & 0x80000000) || false;
        }

        // Interpret CPU brand string and cache information.
        if  (i == 0x80000002)
            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
        else if  (i == 0x80000003)
            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
        else if  (i == 0x80000004)
            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
        else if  (i == 0x80000006)
        {
            nCacheLineSize = CPUInfo[2] & 0xff;
            nL2Associativity = (CPUInfo[2] >> 12) & 0xf;
            nCacheSizeK = (CPUInfo[2] >> 16) & 0xffff;
        }
        else if  (i == 0x80000008)
        {
           nPhysicalAddress = CPUInfo[0] & 0xff;
           nVirtualAddress = (CPUInfo[0] >> 8) & 0xff;
        }
        else if  (i == 0x8000000A)
        {
            bNestedPaging = (CPUInfo[3] & 0x1) || false;
            bLBRVisualization = (CPUInfo[3] & 0x2) || false;
        }
        else if  (i == 0x8000001A)
        {
            bFP128 = (CPUInfo[0] & 0x1) || false;
            bMOVOptimization = (CPUInfo[0] & 0x2) || false;
        }
    }

    // Display all the information in user-friendly format.

    printf_s("\n\nCPU String: %s\n", CPUString);

    if  (nIds >= 1)
    {
        if  (nSteppingID)
            printf_s("Stepping ID = %d\n", nSteppingID);
        if  (nModel)
            printf_s("Model = %d\n", nModel);
        if  (nFamily)
            printf_s("Family = %d\n", nFamily);
        if  (nProcessorType)
            printf_s("Processor Type = %d\n", nProcessorType);
        if  (nExtendedmodel)
            printf_s("Extended model = %d\n", nExtendedmodel);
        if  (nExtendedfamily)
            printf_s("Extended family = %d\n", nExtendedfamily);
        if  (nBrandIndex)
            printf_s("Brand Index = %d\n", nBrandIndex);
        if  (nCLFLUSHcachelinesize)
            printf_s("CLFLUSH cache line size = %d\n",
                     nCLFLUSHcachelinesize);
        if (bMultithreading && (nLogicalProcessors > 0))
           printf_s("Logical Processor Count = %d\n", nLogicalProcessors);
        if  (nAPICPhysicalID)
            printf_s("APIC Physical ID = %d\n", nAPICPhysicalID);

        if  (nFeatureInfo || bSSE3Instructions ||
             bMONITOR_MWAIT || bCPLQualifiedDebugStore ||
             bVirtualMachineExtensions || bEnhancedIntelSpeedStepTechnology ||
             bThermalMonitor2 || bSupplementalSSE3 || bL1ContextID || 
             bCMPXCHG16B || bxTPRUpdateControl || bPerfDebugCapabilityMSR || 
             bSSE41Extensions || bSSE42Extensions || bPOPCNT || 
             bLAHF_SAHFAvailable || bCmpLegacy || bSVM ||
             bExtApicSpace || bAltMovCr8 ||
             bLZCNT || bSSE4A || bMisalignedSSE ||
             bPREFETCH || bSKINITandDEV || bSYSCALL_SYSRETAvailable || 
             bExecuteDisableBitAvailable || bMMXExtensions || bFFXSR || b1GBSupport ||
             bRDTSCP || b64Available || b3DNowExt || b3DNow || bNestedPaging || 
             bLBRVisualization || bFP128 || bMOVOptimization )
        {
            printf_s("\nThe following features are supported:\n");

            if  (bSSE3Instructions)
                printf_s("\tSSE3\n");
            if  (bMONITOR_MWAIT)
                printf_s("\tMONITOR/MWAIT\n");
            if  (bCPLQualifiedDebugStore)
                printf_s("\tCPL Qualified Debug Store\n");
            if  (bVirtualMachineExtensions)
                printf_s("\tVirtual Machine Extensions\n");
            if  (bEnhancedIntelSpeedStepTechnology)
                printf_s("\tEnhanced Intel SpeedStep Technology\n");
            if  (bThermalMonitor2)
                printf_s("\tThermal Monitor 2\n");
            if  (bSupplementalSSE3)
                printf_s("\tSupplemental Streaming SIMD Extensions 3\n");
            if  (bL1ContextID)
                printf_s("\tL1 Context ID\n");
            if  (bCMPXCHG16B)
                printf_s("\tCMPXCHG16B Instruction\n");
            if  (bxTPRUpdateControl)
                printf_s("\txTPR Update Control\n");
            if  (bPerfDebugCapabilityMSR)
                printf_s("\tPerf\\Debug Capability MSR\n");
            if  (bSSE41Extensions)
                printf_s("\tSSE4.1 Extensions\n");
            if  (bSSE42Extensions)
                printf_s("\tSSE4.2 Extensions\n");
            if  (bPOPCNT)
                printf_s("\tPPOPCNT Instruction\n");

            i = 0;
            nIds = 1;
            while (i < (sizeof(szFeatures)/sizeof(const char*)))
            {
                if  (nFeatureInfo & nIds)
                {
                    printf_s("\t");
                    printf_s(szFeatures[i]);
                    printf_s("\n");
                }

                nIds <<= 1;
                ++i;
            }
            if (bLAHF_SAHFAvailable)
                printf_s("\tLAHF/SAHF in 64-bit mode\n");
            if (bCmpLegacy)
                printf_s("\tCore multi-processing legacy mode\n");
            if (bSVM)
                printf_s("\tSecure Virtual Machine\n");
            if (bExtApicSpace)
                printf_s("\tExtended APIC Register Space\n");
            if (bAltMovCr8)
                printf_s("\tAltMovCr8\n");
            if (bLZCNT)
                printf_s("\tLZCNT instruction\n");
            if (bSSE4A)
                printf_s("\tSSE4A (EXTRQ, INSERTQ, MOVNTSD, MOVNTSS)\n");
            if (bMisalignedSSE)
                printf_s("\tMisaligned SSE mode\n");
            if (bPREFETCH)
                printf_s("\tPREFETCH and PREFETCHW Instructions\n");
            if (bSKINITandDEV)
                printf_s("\tSKINIT and DEV support\n");
            if (bSYSCALL_SYSRETAvailable)
                printf_s("\tSYSCALL/SYSRET in 64-bit mode\n");
            if (bExecuteDisableBitAvailable)
                printf_s("\tExecute Disable Bit\n");
            if (bMMXExtensions)
                printf_s("\tExtensions to MMX Instructions\n");
            if (bFFXSR)
                printf_s("\tFFXSR\n");
            if (b1GBSupport)
                printf_s("\t1GB page support\n");
            if (bRDTSCP)
                printf_s("\tRDTSCP instruction\n");
            if (b64Available)
                printf_s("\t64 bit Technology\n");
            if (b3DNowExt)
                printf_s("\t3Dnow Ext\n");
            if (b3DNow)
                printf_s("\t3Dnow! instructions\n");
            if (bNestedPaging)
                printf_s("\tNested Paging\n");
            if (bLBRVisualization)
                printf_s("\tLBR Visualization\n");
            if (bFP128)
                printf_s("\tFP128 optimization\n");
            if (bMOVOptimization)
                printf_s("\tMOVU Optimization\n");
        }
    }

    if  (nExIds >= 0x80000004)
        printf_s("\nCPU Brand String: %s\n", CPUBrandString);

    if  (nExIds >= 0x80000006)
    {
        printf_s("Cache Line Size = %d\n", nCacheLineSize);
        printf_s("L2 Associativity = %d\n", nL2Associativity);
        printf_s("Cache Size = %dK\n", nCacheSizeK);
    }

    if  (nExIds >= 0x80000008)
    {
        printf_s("Physical Address = %d\n", nPhysicalAddress);
        printf_s("Virtual Address = %d\n", nVirtualAddress);
    }

	printf_s("Logical CPUs = %d\n", logical_cpus);
	nCPU = logical_cpus;

    return  nRet;
}

int union_files()
{
	char cfilename[MAX_CPU][MAX_CHAR];
	//for(int a = 0; a < nCPU; a++)
	//	for(int x = 0; x < sizeof(filename[a]); x++)
	//		wctomb(cfilename[a][x], filename[a][x]);
	//printf("\n_cFilename: %s", cfilename[0]);

	strcpy(cfilename[0],"ultra_pi_0.txt");
	strcpy(cfilename[1],"ultra_pi_1.txt");
	strcpy(cfilename[2],"ultra_pi_2.txt");
	strcpy(cfilename[3],"ultra_pi_3.txt");

	int i = 0;
	FILE * stream;
	FILE * file_streams[MAX_CPU];
	char line[BUFFER];
	if(!fopen_s(&stream, PI_RESULT_FILE, "w"))
	{
		for(i = 0; i < nCPU; i++)
		{
			//if(!_wfopen_s(&file_streams[i], filename[i], _T("r")))
			if(!fopen_s(&file_streams[i], cfilename[i], "r"))
			{
				printf("\nsorry cannot open file %i", i);
				wprintf(L"\nFilename: %s!", filename[i]);
				getchar();
				//_fcloseall();
				//return -1;
			}
		}
		return -1;

		i = 0;
		while((feof(file_streams[i]) == 0) && (i < nCPU))
		{
			fgets(line, BUFFER - 1, file_streams[i]);

			if(i%5 == 0)
				fprintf(stream, "%.8s\n", line);
			fprintf(stream, "%.8s ", line);
			i++;
		}
		
		for(i = 0; i < nCPU; i++)
			fclose(file_streams[i]);

		fclose(stream);
		return 0;
	}
	return -1;
}