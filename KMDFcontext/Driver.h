/*++

Module Name:

    driver.h

Abstract:

    This file contains the driver definitions.

Environment:

    Kernel-mode Driver Framework

--*/

#include <ntddk.h>
#include <wdf.h>
#include <initguid.h>

#include "device.h"
#include "queue.h"
#include "trace.h"

EXTERN_C_START

//

typedef struct _DRIVER_CONTEXT {
    ULONG SharedData; // 共有データ
    // 他の共有データを追加可能
} DRIVER_CONTEXT, * PDRIVER_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DRIVER_CONTEXT, DriverGetContext)

//
// WDFDRIVER Events
//

DRIVER_INITIALIZE DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD KMDFcontextEvtDeviceAdd;
EVT_WDF_OBJECT_CONTEXT_CLEANUP KMDFcontextEvtDriverContextCleanup;

EXTERN_C_END
