// Copyright Epic Games, Inc. All Rights Reserved.

#include "WL_StarLibrary.h"

#define LOCTEXT_NAMESPACE "FWL_StarLibraryModule"

void FWL_StarLibraryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FWL_StarLibraryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWL_StarLibraryModule, WL_StarLibrary)