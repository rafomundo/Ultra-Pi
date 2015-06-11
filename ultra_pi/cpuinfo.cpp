// cpuinfo.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "ultra_pi.h"
#include "cpuinfo.h"
#include <intrin.h>

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
// Ccpuinfo-Dialogfeld

IMPLEMENT_DYNAMIC(Ccpuinfo, CDialog)

Ccpuinfo::Ccpuinfo(CWnd* pParent /*=NULL*/)
	: CDialog(Ccpuinfo::IDD, pParent)
	, m_text(_T(""))
{
	m_text = Ccpuinfo::ShowInfo();
}

Ccpuinfo::~Ccpuinfo()
{
}

void Ccpuinfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_text);
}


BEGIN_MESSAGE_MAP(Ccpuinfo, CDialog)
	ON_BN_CLICKED(IDOK, &Ccpuinfo::OnBnClickedOk)
END_MESSAGE_MAP()


// Ccpuinfo-Meldungshandler

CString Ccpuinfo::ShowInfo()
{
	CString text, temp;
	text = _T("");
	temp = _T("");


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

    //printf_s("\n\nCPU String: %s\n", CPUString);
	if  (nExIds >= 0x80000004)
	{
        //printf_s("\nCPU Brand String: %s\n", CPUBrandString);
		CString temp2(CPUBrandString);
		temp.Format(_T("%s\r\n\r\n"), temp2);
		text += temp;
	}

    if  (nIds >= 1)
    {
		if (bMultithreading && (nLogicalProcessors > 0))
		{
			//printf_s("Logical Processor Count = %d\n", nLogicalProcessors);
			temp.Format(_T("Logical Processor Count = %d\r\n\r\n"), nLogicalProcessors);
			text += temp;
		}
        if  (nSteppingID)
		{
            //printf_s("Stepping ID = %d\n", nSteppingID);
			temp.Format(_T("Stepping ID = %d\r\n"), nSteppingID);
			text += temp;
		}
        if  (nModel)
		{
			//printf_s("Model = %d\n", nModel);
			temp.Format(_T("Model = %d\r\n"), nModel);
			text += temp;
		}
        if  (nFamily)
		{
            //printf_s("Family = %d\n", nFamily);
			temp.Format(_T("Family = %d\r\n"), nFamily);
			text += temp;
		}
        if  (nProcessorType)
		{
            //printf_s("Processor Type = %d\n", nProcessorType);
			temp.Format(_T("Processor Type = %d\r\n"), nProcessorType);
			text += temp;
		}
        if  (nExtendedmodel)
		{
            //printf_s("Extended model = %d\n", nExtendedmodel);
			temp.Format(_T("Extended model = %d\r\n"), nExtendedmodel);
			text += temp;
		}
        if  (nExtendedfamily)
		{
            printf_s("Extended family = %d\n", nExtendedfamily);
			temp.Format(_T("Extended family = %d\r\n"), nExtendedfamily);
			text += temp;
		}
        if  (nBrandIndex)
		{
            //printf_s("Brand Index = %d\n", nBrandIndex);
			temp.Format(_T("Brand Index = %d\r\n"), nBrandIndex);
			text += temp;

		}
        if  (nAPICPhysicalID)
		{
            //printf_s("APIC Physical ID = %d\n", nAPICPhysicalID);
			temp.Format(_T("APIC Physical ID = %d\r\n"), nAPICPhysicalID);
			text += temp;
		}
		if  (nCLFLUSHcachelinesize)
		{
            //printf_s("CLFLUSH cache line size = %d\n", nCLFLUSHcachelinesize);
			temp.Format(_T("\r\nCLFLUSH cache line size = %d\r\n"), nCLFLUSHcachelinesize);
			text += temp;
		}
	}

	if  (nExIds >= 0x80000006)
    {
        //printf_s("Cache Line Size = %d\n", nCacheLineSize);
        //printf_s("L2 Associativity = %d\n", nL2Associativity);
        //printf_s("Cache Size = %dK\n", nCacheSizeK);
		temp.Format(_T("Cache Line Size = %d\r\n"), nCacheLineSize);
		text += temp;
		temp.Format(_T("Cache Size = %dK\r\n"), nCacheSizeK);
		text += temp;
		temp.Format(_T("L2 Associativity = %d\r\n"), nL2Associativity);
		text += temp;
    }

    if  (nExIds >= 0x80000008)
    {
        //printf_s("Physical Address = %d\n", nPhysicalAddress);
        //printf_s("Virtual Address = %d\n", nVirtualAddress);
		temp.Format(_T("\r\nPhysical Address = %d\r\n"), nPhysicalAddress);
		text += temp;
		temp.Format(_T("Virtual Address = %d\r\n"), nVirtualAddress);
		text += temp;
    }

	if  (nIds >= 1)
    {

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
            //printf_s("\nThe following features are supported:\n");
			temp.Format(_T("\r\nThe following features are supported by your CPU:\r\n\r\n"));
			text += temp;

            if  (bSSE3Instructions)
			{
                //printf_s("\tSSE3\n");
				temp.Format(_T("\tSSE3\r\n"));
				text += temp;
			}
            if  (bMONITOR_MWAIT)
			{
                //printf_s("\tMONITOR/MWAIT\n");
				temp.Format(_T("\tMONITOR/MWAIT\r\n"));
				text += temp;
			}
            if  (bCPLQualifiedDebugStore)
			{
                //printf_s("\tCPL Qualified Debug Store\n");
				temp.Format(_T("\tCPL Qualified Debug Store\r\n"));
				text += temp;
			}
            if  (bVirtualMachineExtensions)
			{
                //printf_s("\tVirtual Machine Extensions\n");
				temp.Format(_T("\tVirtual Machine Extensions\r\n"));
				text += temp;
			}
            if  (bEnhancedIntelSpeedStepTechnology)
			{
				//printf_s("\tEnhanced Intel SpeedStep Technology\n");
				temp.Format(_T("\tEnhanced Intel SpeedStep Technology\r\n"));
				text += temp;
			}
            if  (bThermalMonitor2)
			{
				//printf_s("\tThermal Monitor 2\n");
				temp.Format(_T("\tThermal Monitor 2\r\n"));
				text += temp;
			}
            if  (bSupplementalSSE3)
			{
				//printf_s("\tSupplemental Streaming SIMD Extensions 3\n");
				temp.Format(_T("\tSupplemental Streaming SIMD Extensions 3\r\n"));
				text += temp;
			}
            if  (bL1ContextID)
			{
                //printf_s("\tL1 Context ID\n");
				temp.Format(_T("\tL1 Context ID\r\n"));
				text += temp;
			}
            if  (bCMPXCHG16B)
			{
				//printf_s("\tCMPXCHG16B Instruction\n");
				temp.Format(_T("\tCMPXCHG16B Instruction\r\n"));
				text += temp;
			}
            if  (bxTPRUpdateControl)
			{
                //printf_s("\txTPR Update Control\n");
				temp.Format(_T("\txTPR Update Control\r\n"));
				text += temp;
			}
            if  (bPerfDebugCapabilityMSR)
			{
				//printf_s("\tPerf\\Debug Capability MSR\n");
				temp.Format(_T("\tPerf\\Debug Capability MSR\r\n"));
				text += temp;
			}
            if  (bSSE41Extensions)
			{
				//printf_s("\tSSE4.1 Extensions\n");
				temp.Format(_T("\tSSE4.1 Extensions\r\n"));
				text += temp;
			}
            if  (bSSE42Extensions)
			{
                //printf_s("\tSSE4.2 Extensions\n");
				temp.Format(_T("\tSSE4.2 Extensions\r\n"));
				text += temp;
			}
            if  (bPOPCNT)
			{
                //printf_s("\tPPOPCNT Instruction\n");
				temp.Format(_T("\tPPOPCNT Instruction\r\n"));
				text += temp;
			}

            i = 0;
            nIds = 1;
            while (i < (sizeof(szFeatures)/sizeof(const char*)))
            {
                if  (nFeatureInfo & nIds)
                {
                    //printf_s("\t");
                    //printf_s(szFeatures[i]);
                    //printf_s("\n");
					//temp.Format(_T("\t%s\r\n"), szFeatures[i]);
					CString temp2(szFeatures[i]);
					temp.Format(_T("\t%s\r\n"), temp2);
					text += temp;
                }
                nIds <<= 1;
                ++i;
            }
            if (bLAHF_SAHFAvailable)
			{
				//printf_s("\tLAHF/SAHF in 64-bit mode\n");
				temp.Format(_T("\tLAHF/SAHF in 64-bit mode\r\n"));
				text += temp;
			}
            if (bCmpLegacy)
			{
                //printf_s("\tCore multi-processing legacy mode\n");
				temp.Format(_T("\tCore multi-processing legacy mode\r\n"));
				text += temp;
			}
            if (bSVM)
			{
                //printf_s("\tSecure Virtual Machine\n");
				temp.Format(_T("\tSecure Virtual Machine\r\n"));
				text += temp;
			}
            if (bExtApicSpace)
			{
                //printf_s("\tExtended APIC Register Space\n");
				temp.Format(_T("\tExtended APIC Register Space\r\n"));
				text += temp;
			}
            if (bAltMovCr8)
			{
                //printf_s("\tAltMovCr8\n");
				temp.Format(_T("\tAltMovCr8\r\n"));
				text += temp;
			}
            if (bLZCNT)
			{
                //printf_s("\tLZCNT instruction\n");
				temp.Format(_T("\tLZCNT instruction\r\n"));
				text += temp;
			}
            if (bSSE4A)
			{
                //printf_s("\tSSE4A (EXTRQ, INSERTQ, MOVNTSD, MOVNTSS)\n");
				temp.Format(_T("\tSSE4A (EXTRQ, INSERTQ, MOVNTSD, MOVNTSS)\r\n"));
				text += temp;
			}
            if (bMisalignedSSE)
			{
				//printf_s("\tMisaligned SSE mode\n");
				temp.Format(_T("\tMisaligned SSE mode\r\n"));
				text += temp;
			}
            if (bPREFETCH)
			{
				//printf_s("\tPREFETCH and PREFETCHW Instructions\n");
				temp.Format(_T("\tPREFETCH and PREFETCHW Instructions\r\n"));
				text += temp;
			}
            if (bSKINITandDEV)
			{
				//printf_s("\tSKINIT and DEV support\n");
				temp.Format(_T("\tSKINIT and DEV support\r\n"));
				text += temp;
			}
            if (bSYSCALL_SYSRETAvailable)
			{
				//printf_s("\tSYSCALL/SYSRET in 64-bit mode\n");
				temp.Format(_T("\tSYSCALL/SYSRET in 64-bit mode\r\n"));
				text += temp;
			}
            if (bExecuteDisableBitAvailable)
			{
				//printf_s("\tExecute Disable Bit\n");
				temp.Format(_T("\tExecute Disable Bit\r\n"));
				text += temp;
			}
            if (bMMXExtensions)
			{
				//printf_s("\tExtensions to MMX Instructions\n");
				temp.Format(_T("\tExtensions to MMX Instructions\r\n"));
				text += temp;
			}
            if (bFFXSR)
			{
				//printf_s("\tFFXSR\n");
				temp.Format(_T("\tFFXSR\r\n"));
				text += temp;
			}
            if (b1GBSupport)
			{
                //printf_s("\t1GB page support\n");
				temp.Format(_T("\t1GB page support\r\n"));
				text += temp;
			}
            if (bRDTSCP)
			{
				//printf_s("\tRDTSCP instruction\n");
				temp.Format(_T("\tRDTSCP instruction\r\n"));
				text += temp;
			}
            if (b64Available)
			{
				//printf_s("\t64 bit Technology\n");
				temp.Format(_T("\t64 bit Technology\r\n"));
				text += temp;
			}
            if (b3DNowExt)
			{
				//printf_s("\t3Dnow Ext\n");
				temp.Format(_T("\t3Dnow Ext\r\n"));
				text += temp;
			}
            if (b3DNow)
			{
				//printf_s("\t3Dnow! instructions\n");
				temp.Format(_T("\t3Dnow! instructions\r\n"));
				text += temp;
			}
            if (bNestedPaging)
			{
				//printf_s("\tNested Paging\n");
				temp.Format(_T("\tNested Paging\r\n"));
				text += temp;
			}
            if (bLBRVisualization)
			{
                //printf_s("\tLBR Visualization\n");
				temp.Format(_T("\tLBR Visualization\r\n"));
				text += temp;
			}
            if (bFP128)
			{
                //printf_s("\tFP128 optimization\n");
				temp.Format(_T("\tFP128 optimization\r\n"));
				text += temp;
			}
            if (bMOVOptimization)
			{
				//printf_s("\tMOVU Optimization\n");
				temp.Format(_T("\tMOVU Optimization\r\n"));
				text += temp;
			}
        }
    }

	return text;
}

int Ccpuinfo::get_num_cpu()
{
	int logical_cpus = 0;

    char CPUString[0x20];
    int CPUInfo[4] = {-1};
   
    unsigned    nIds, i;

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
			logical_cpus = (CPUInfo[1] >> 16) & 0xff;

        }
    }
	
	return logical_cpus;
}

void Ccpuinfo::OnBnClickedOk()
{
	// TODO: Fügen Sie hier Ihren Kontrollbehandlungscode für die Benachrichtigung ein.
	OnOK();
}