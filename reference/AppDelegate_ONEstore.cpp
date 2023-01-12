// for ONEstore
#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;


//----------------------------------------------------------------------------------------------
//                  ONEstore Initialze.
//----------------------------------------------------------------------------------------------
void AppDelegate::initONEstore(){
    // regist callback object
    ONESTORE_ALC::NativeAlcHelper->changeCallbacksListener( this );
    // regist callback object
    ONESTORE_IAP::NativeIapHelper->changeCallbacksListener( this );
}


//----------------------------------------------------------------------------------------------
//                  ONEstoreNativeIap CallbacksListener.
//----------------------------------------------------------------------------------------------

// callback of acknowledgeAsync()
void AppDelegate::onAcknowledgeAsync(ONESTORE_IAP::IapResult* result, ONESTORE_IAP::PurchaseData* data)
{
    // add your service scenario
}

// callback of consumeAsync()
void AppDelegate::onConsumeAsync(ONESTORE_IAP::IapResult* result, ONESTORE_IAP::PurchaseData* data)
{
    // add your service scenario
}

// callback of launchLoginFlowAsync()
void AppDelegate::onLaunchLoginFlowAsync(ONESTORE_IAP::IapResult* result)
{
    // add your service scenario
}


// callback of launchUpdateOrInstallFlow()
void AppDelegate::onLaunchUpdateOrInstallFlow(ONESTORE_IAP::IapResult* result)
{
    // add your service scenario
}

// callback of queryProductDetailsAsync()
void AppDelegate::onQueryProductDetailsAsync(ONESTORE_IAP::IapResult* result,
                                             std::list <ONESTORE_IAP::ProductDetail>* plist)
{
    // add your service scenario
}


// callback of queryPurchasesAsync()
void AppDelegate::onQueryPurchasesAsync(ONESTORE_IAP::IapResult* result,
                                        std::list <ONESTORE_IAP::PurchaseData>* plist)
{
    // add your service scenario
}


// callback of launchPurchaseFlow(), launchUpdateSubscription
void AppDelegate::onPurchasesUpdated(ONESTORE_IAP::IapResult* result, std::list <ONESTORE_IAP::PurchaseData>* plist)
{
    // add your service scenario
}


// callback of manageRecurringProductAsync()
void AppDelegate::onManageRecurringProductAsync(ONESTORE_IAP::IapResult* result,
                                                ONESTORE_IAP::PurchaseData* data ,
                                                ONESTORE_IAP::RecurringState state)
{
    // add your service scenario
}



// callback of service disconnection
void AppDelegate::onServiceDisconnected()
{
    // add your service scenario
}


// callback of startConnection()
void AppDelegate::onSetupFinished(ONESTORE_IAP::IapResult* result)
{
    // add your service scenario
}


// callback of getStoreInfoAsync()
void AppDelegate::onStoreInfoAsync(ONESTORE_IAP::IapResult* result, const char* info)
{
    // add your service scenario
}


//--------------------------------------------------------------------------------------------------
//                  ONEstoreNativeAlc CallbacksListener.
//--------------------------------------------------------------------------------------------------
void AppDelegate::onGranted(const char* license, const char* signature)
{
    // add your service scenario
}


void AppDelegate::onDenied()
{
    // add your service scenario
}


void AppDelegate::onError(int code, const char* msg)
{ 
    // add your service scenario
}
