# Environment
   ### The environment for this document is as follows:

>NDK : 21.4.7075529<br>
>Cocos : cocos2d-x-4.0<br>
>Android Studio : Dolphin | 2021.3.1 Patch 1<br>


# Module Description
>  - ONEstoreNativeALCHelper
>     - ONEstore App License Checker Helper
>  - ONEstoreNativeIAPHelper
>     - ONEstore In-App Purchase SDK Helper 
   

# Folder Structure
>   - onestore<br>
>        - ONEstoreNativeALCHelper<br>
>            - include<br>
>                - ONEstoreAlcCallbacksListener.h<br>
>                - ONEstoreAlcEngine.h<br>
>                - ONEstoreAlcError.h<br>
>            - libs<br>
>                - arm64-v8a   / libONEstoreNativeAlcHelper.so<br>
>                - armeabi-v7a / libONEstoreNativeAlcHelper.so<br>
>                - x86         / libONEstoreNativeAlcHelper.so<br>
>                - x86_64      / libONEstoreNativeAlcHelper.so<br>
>            - ONEstoreALC.jar<br>
>            <br>
>        - ONEstoreNativeIAPHelper<br>
>            - include<br>
>                - ONEstoreIapCallbacksListener.h<br>
>                - ONEstoreIapEngine.h<br>
>                - ONEstoreIapEnums.h<br>
>                - ONEstoreIapError.h<br>
>                - ONEstoreIapObject.h<br>
>                - ONEstoreIapProductDetail.h<br>
>                - ONEstoreIapPurchaseData.h<br>
>                - ONEStoreIapResult.h<br>
>            - libs<br>
>                - arm64-v8a   / libONEstoreNativeIAPHelper.so<br>
>                - armeabi-v7a / libONEstoreNativeIAPHelper.so<br>
>                - x86         / libONEstoreNativeIAPHelper.so<br>
>                - x86_64      / libONEstoreNativeIAPHelper.so<br>
>            - ONEstoreIAP.jar <br>
>            <br>
>   - reference<br>
>       - AppDelegate.h<br>
>       - AppDelegate_ONEstore.cpp<br>
>       - CMakeLists_sample.txt


# The integration is as follows
```
1. create cocos2dx_project.

2. copy onestore/*.*  to cocos2dx_project/proj.android/app/onestore/*.*  

3. copy reference/AppDelegate_ONEstore.cpp  to cocos2dx_project/Classes/AppDelegate_ONEstore.cpp 

4. modify cocos2dx_project/Classes/AppDelegate.h( refer to reference/AppDelegate.h )
    #include "ONEstoreAlcEngine.h"
    #include "ONEstoreIapEngine.h"

    class AppDelegate : private cocos2d::Application, 
                        public ONESTORE_ALC::CallbacksListener,
                        public ONESTORE_IAP::CallbacksListener
                        
    {
        ...

        //----------------------------------------------------------------------------------------------
        // for ONEstore
        void initONEstore();

        //----------------------------------------------------------------------------------------------
        //                  ONEstoreNativeIap CallbacksListener.
        //----------------------------------------------------------------------------------------------

        // callback of acknowledgeAsync()
        virtual void onAcknowledgeAsync( ONESTORE_IAP::IapResult *, ONESTORE_IAP::PurchaseData * );

        // callback of consumeAsync()
        virtual void onConsumeAsync( ONESTORE_IAP::IapResult *, ONESTORE_IAP::PurchaseData * );

        // callback of launchLoginFlowAsync()
        virtual void onLaunchLoginFlowAsync( ONESTORE_IAP::IapResult * );

        // callback of launchUpdateOrInstallFlow()
        virtual void onLaunchUpdateOrInstallFlow( ONESTORE_IAP::IapResult * );

        // callback of queryProductDetailsAsync()
        virtual void onQueryProductDetailsAsync( ONESTORE_IAP::IapResult *, std::list<ONESTORE_IAP::ProductDetail> * );

        // callback of queryPurchasesAsync()
        virtual void onQueryPurchasesAsync( ONESTORE_IAP::IapResult *, std::list<ONESTORE_IAP::PurchaseData> * );

        // callback of launchPurchaseFlow()
        virtual void onPurchasesUpdated( ONESTORE_IAP::IapResult *, std::list<ONESTORE_IAP::PurchaseData> * );

        // callback of service disconnection
        virtual void onServiceDisconnected();

        // callback of startConnection()
        virtual void onSetupFinished( ONESTORE_IAP::IapResult * );

        // callback of getStoreInfoAsync()
        virtual void onStoreInfoAsync( ONESTORE_IAP::IapResult *, const char * );

        // callback of manageRecurringProductAsync()
        virtual void onManageRecurringProductAsync( ONESTORE_IAP::IapResult *, 
                                                    ONESTORE_IAP::PurchaseData *, 
                                                    ONESTORE_IAP::RecurringState );

        //----------------------------------------------------------------------------------------------
        //                  ONEstoreNativeAlc CallbacksListener.
        //----------------------------------------------------------------------------------------------
        virtual void onGranted( const char *license, const char *signature );
        virtual void onDenied();
        virtual void onError( int code, const char *msg );
    }

    The AppDelegate Class must inherit the 
    ONESTORE_ALC::CallbacksListener or ONESTORE_IAP::CallbackListener Class to implement a pure virtual function.
    The implemented file is  "reference/AppDelegate_ONEstore.cpp".
    "AppDelegate_ONEstore.cpp" is just a sample file. Please modify and use it to your service logic.

5. add ONEstore initialze code to cocos2dx_project/Classes/AppDelegate.cpp
    bool AppDelegate::applicationDidFinishLaunching() {
        // for ONEstore
        initONEstore();

        ....
    }

    The implementation of the initONEstore() function is located in AppDelegate_ONEstore.cpp.
    
    // for ONESTORE
    void AppDelegate::initONEstore(){
        // regist callback object if using ONEstore ALC 
        ONESTORE_ALC::NativeAlcHelper->changeCallbacksListener( this );
        // regist callback object if using ONEstore IAP
        ONESTORE_IAP::NativeIapHelper->changeCallbacksListener( this );
    }

6. add url of ONEstore Maven in project/build.gradle.
    maven{
      url "https::repo.onestore.co.kr/repository/onestore-sdk-public"
    }     

7. add prevent code obfuscation in proguard-rules.pro
   -keep class com.gaa.**{*;}
   -keep class com.onestore.**{*;}
   
8. add dependency in app/build.gradle.
    dependencies {
        ...
        // for ONEstore ALC
        implementation fileTree(dir: 'onestore/ONEstoreNativeAlcHelper', include: ['*.jar'])
        def onestore_alc_version = "2.0.0"
        implementation "com.onestorecorp.sdk:sdk-licensing:$onestore_alc_version"
        
        // for ONEstore IAP
        implementation fileTree(dir: 'onestore/ONEstoreNativeIapHelper', include: ['*.jar'])
        def onestore_iap_version = "21.00.01"
        implementation "com.onestorecorp.sdk:sdk-iap:$onestore_iap_version"

        // for ONEstore language set. default set is [kr].
        def onestore_config_version = "1.0.0"
        def onestore_config_region = "sdk-configuration-kr"
        implementation "com.onestorecorp.sdk:$onestore_config_region:$onestore_config_version"        
        ...
    }

   
9. add <queries> tag to AndroidManifest.xml
   <manifest>
       <application>
             ...
            <quries>
                <intent>
                    <action android:name="com.onestore.ipc.iap.IapService.ACTION" />
               </intent>
               <intent&gt;
                    <action android:name="android.intent.action.VIEW" />
                    <data android:scheme="onestore" />
               </intent>
          </queries>
            ... 
       </application>
   </manifest>
   
   
10. modify CMakeLists.txt in cocos2dx_project( refer to the reference/CMakeLists_sample.txt ).
    ...
    list(APPEND GAME_SOURCE
         Classes/AppDelegate.cpp
         # add for ONEstore
         Classes/AppDelegate_ONEstore.cpp
         ...
         Classes/HelloWorldScene.cpp
    )
    ...

    # ONESTORE SETTINGS
    if(ANDROID)
        set( ONESTORE_ROOT         ${CMAKE_CURRENT_SOURCE_DIR}/proj.android/app/onestore )
        set( ONESTORE_ALC_ROOT     ${ONESTORE_ROOT}/ONEstoreNativeAlcHelper )
        set( ONESTORE_IAP_ROOT     ${ONESTORE_ROOT}/ONEstoreNativeIapHelper )

        set( ONESTORE_ALC_HEADER   ${ONESTORE_ALC_ROOT}/include )
        set( ONESTORE_IAP_HEADER   ${ONESTORE_IAP_ROOT}/include )

        set( ONESTORE_ALC_LIBRARY  ${ONESTORE_ALC_ROOT}/libs/${CMAKE_ANDROID_ARCH_ABI} )
        set( ONESTORE_IAP_LIBRARY  ${ONESTORE_IAP_ROOT}/libs/${CMAKE_ANDROID_ARCH_ABI} )

        # include header
        target_include_directories( ${APP_NAME} PRIVATE ${ONESTORE_ALC_HEADER} ${ONESTORE_IAP_HEADER})

        # include library
        add_library( libONEstoreAlc SHARED IMPORTED )
        set_target_properties( libONEstoreAlc PROPERTIES IMPORTED_LOCATION
                               ${ONESTORE_ALC_LIBRARY}/libONEstoreNativeAlcHelper.so )

        add_library( libONEstoreIap SHARED IMPORTED )
        set_target_properties( libONEstoreIap PROPERTIES IMPORTED_LOCATION
                               ${ONESTORE_IAP_LIBRARY}/libONEstoreNativeIapHelper.so )

        target_link_libraries( ${APP_NAME} libONEstoreAlc libONEstoreIap )        
   endif()
```

##### Please refer to the ONEstore announcement for the following if your TargetSDK version is 30 or 31
   >   - <a href="https://dev.onestore.co.kr/devpoc/support/news/noticeView.omp?pageNo=4&noticeId=32968">Target SDK version set to 30(OS 11) or later.</a><br>
   >   - <a href="https://dev.onestore.co.kr/devpoc/support/news/noticeView.omp?pageNo=1&noticeId=33072">Target SDK version set to 31(OS 12) or later.</a><br>

<br>

# How To Using
```c++

using namespace ONESTORE_IAP;
using namespace ONESTORE_ALC;

void class::your_function() {
   ...
   // verify apk license.
   NativeAlcHelper->queryLicense( onestore_public_key );

   // query product list
   std::list<std::string> itemlist;
   itemlist.push_back( "product_inapp_1000" );        // product id
   itemlist.push_back( "product_auto_2000" );         // product id
   itemlist.push_back( "product_subs_5000" );         // product id
   NativeIapHelper->queryProductDetailsAsync( ProductType::ALL, &itemlist );

   // query purchase list
   NativeIapHelper->queryPurchasesAsync( ProductType::INAPP ); 
   NativeIapHelper->queryPurchasesAsync( ProductType::AUTO );
   NativeIapHelper->queryPurchasesAsync( ProductType::SUBS );
   
   // purchase product
   NativeIapHelper->launchPurchaseFlow( product_id,   // product id
                                        product_type, // product type
                                        nullptr,      // developer_payload. optional
                                        nullptr,      // product_name. optional
                                        nullptr,      // game_user_id. optional
                                        1,            // quantity
                                        false );      // promotion applicable
   ...
   
}
   
```
<br>

# Now
> You can use NativeIapHelper and NativeAlcHelper in native C++ file very simply.<br>
> For more information, refer to ONEstoreAlcEngine.h or ONEstoreIapEngine.h or visit the ONEstore Developer Site( https://dev.onestore.co.kr )
>
>
>

<br><br>
Thanks for reading.


# License
```
Copyright 2023 One store Co., Ltd.

Licensed under the Apache License, Version 2.0 (the "License"); 
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, 
software distributed under the License is distributed on an "AS IS" BASIS, 
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
See the License for the specific language governing permissions and
limitations under the License.
```
