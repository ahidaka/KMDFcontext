/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that apps can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_KMDFcontext,
    0xd5cbc502,0x21c0,0x4dba,0x8a,0x93,0xb9,0x36,0xbb,0x47,0x26,0xc5);
// {d5cbc502-21c0-4dba-8a93-b936bb4726c5}
