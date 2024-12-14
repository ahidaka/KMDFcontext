#include "driver.h"
#include "driver.tmh"

#ifdef ALLOC_PRAGMA
#pragma alloc_text (INIT, DriverEntry)
#pragma alloc_text (PAGE, KMDFcontextEvtDeviceAdd)
#pragma alloc_text (PAGE, KMDFcontextEvtDriverContextCleanup)
#endif

NTSTATUS
    DriverEntry(
        _In_ PDRIVER_OBJECT  DriverObject,
        _In_ PUNICODE_STRING RegistryPath
    )
{
    NTSTATUS status;
    WDF_DRIVER_CONFIG config;
    WDF_OBJECT_ATTRIBUTES attributes;
    PDRIVER_CONTEXT driverContext;

    //
    // Initialize WPP Tracing
    //
    WPP_INIT_TRACING(DriverObject, RegistryPath);

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Entry");

    WDF_DRIVER_CONFIG_INIT(&config, KMDFcontextEvtDeviceAdd);

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(&attributes, DRIVER_CONTEXT);

    status = WdfDriverCreate(DriverObject, RegistryPath, &attributes, &config, WDF_NO_HANDLE);
    if (!NT_SUCCESS(status)) {
        return status;
    }

    driverContext = WdfObjectGetTypedContext(WdfGetDriver(), DRIVER_CONTEXT);
    driverContext->SharedData = 0; // ������

    return status;
}

NTSTATUS
KMDFcontextEvtDeviceAdd(
    _In_    WDFDRIVER Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
)
{
    NTSTATUS status;
    WDFDEVICE device;
    WDF_OBJECT_ATTRIBUTES attributes;
    PDRIVER_CONTEXT driverContext;

    UNREFERENCED_PARAMETER(Driver);

    WDF_OBJECT_ATTRIBUTES_INIT(&attributes);

    status = WdfDeviceCreate(&DeviceInit, &attributes, &device);
    if (!NT_SUCCESS(status)) {
        return status;
    }

    // �h���C�o�[�R���e�L�X�g�̎擾
    driverContext = WdfObjectGetTypedContext(WdfGetDriver(), DRIVER_CONTEXT);
    // �K�v�ȏ������������ōs��
    driverContext->SharedData = 123; // ��Ƃ��ăf�[�^�ݒ�

    return status;
}


VOID
KMDFcontextEvtDriverContextCleanup(
    _In_ WDFOBJECT DriverObject
    )
{
    UNREFERENCED_PARAMETER(DriverObject);

    PAGED_CODE();

    TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DRIVER, "%!FUNC! Entry");

    //
    // Stop WPP Tracing
    //
    WPP_CLEANUP(WdfDriverWdmGetDriverObject((WDFDRIVER)DriverObject));
}

