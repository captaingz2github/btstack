# Bluetooth for All! #

The aim of this project is to support devices for which the OS either does not provide a Bluetooth Stack or the available stack is severely limited (e.g., on the iPhone - more than 2.5 million installations). In addition, BTstack is well suited for small, resource-constraint devices such as 8 or 16 bit embedded systems as it is highly configurable and comes with an ultra small memory footprint.  A minimal configuration for an SPP server on a MSP430 can run in 32 kB FLASH and only 4 kB of RAM.

On larger POSIX systems, it provides a user-space daemon that connects to the Bluetooth modules via different Bluetooth HCI transport layers (e.g., HCI H4 UART and H5 the "Tree-Wire" protocol). Multiple applications can communicate with this daemon over different inter-process communication methods.

On embedded systems, a minimal run loop implementation allows to use BTstack without a Real Time OS (RTOS). If a RTOS is already used, BTstack can be integrated and run as a single thread. The source repository provides ports for different MSP430 development boards. Other platforms can be targeted by providing the necessary UART, CPU, and CLOCK implementations, see MSP430GettingStarted  and EmbeddedSystems. Get the documentation for embedded systems: [BTstack Manual v1.1](http://bluekitchen-gmbh.com/docs/btstack-gettingstarted-1.1.pdf).

BTstack supports the Peripheral Role of Bluetooth 4.0 Low Energy specification and we currently work to complete support for LE Central as well. It can be operated both as a single mode or a dual mode stack, see [BLE](BLE.md).

For starters, look at the Wiki pages for an [Architecture](Architecture.md) overview and the little GettingStarted example for iOS.

Quite a while ago, [BTstack was presented](http://btstack.ringwald.ch/BTstack-GoogleOpenSourceJam-20090813.pdf) at the Google Open Source Jam in Zurich with a focus on the iPhone.

BTstack is available under a dual license. The code provided in this repository allows for non-commercial use. Commercial use is provided by [BlueKitchen GmbH](http://bluekitchen-gmbh.com). The Serial Port Profile (SPP) and the Bluetooth Low Energy Peripheral role (LE Peripheral) have been qualified with the Bluetooth SIG (QD ID 54558).

# News #
  * **2014-02-20:** SPP and LE Peripheral have been qualified with the Bluetooth SIG (QD ID 54558).
  * **2013-08-30:** [BTstack Manual v1.1](http://bluekitchen-gmbh.com/docs/btstack-gettingstarted-1.1.pdf) covering the SDP client.
  * **2013-02-18:** [BTstack Manual v1.0](http://bluekitchen-gmbh.com/docs/btstack-gettingstarted-1.0.pdf)
  * **2012-11-16:** Implementation of [ANT(tm)](http://www.thisisant.com) protocol for CC2567 added. Available with commercial BTstack licenses from [BlueKitchen GmbH](mailto:contact@bluekitchen-gmbh.com).
  * **2012-08-01:** We founded [BlueKitchen GmbH](http://bluekitchen-gmbh.com) to provide commercial support and licensing of BTstack.
  * **2012-02-05:** Bluetooth Low Energy GATT Profile/ATT Protocol added to BTstack code base. See [BLE](BLE.md)
  * **2011-11-05:** [Early support for Bluetooth Low Energy in BTstack running on MSP430F5438/CC2564 talking to iPhone 4S](http://www.youtube.com/watch?v=xWY5GinDCQc)
  * **2011-10-28:** [BTstack used on IOIO (PIC & USB)](http://ytai-mer.blogspot.com/2011/10/ioio-over-bluetooth-or-who-needs-cables.html)   also mentioned on [hack-a-day](http://hackaday.com/2011/10/29/bluetooth-for-android-open-accessories/)
  * **2011-09-17:** [Embedded examples for MSP-EXP430F5438+CC256x development board](http://groups.google.com/group/btstack-dev/browse_thread/thread/0e76cc6efef1e272), see [MSP430GettingStarted](MSP430GettingStarted.md)
  * **2011-07-18:** [iWallet hack](http://www.cmw.me/?q=node/50) using an Arduino with a SPP module
  * **2011-04-23:** [BTstack on TI MSP430-F5438](http://www.youtube.com/watch?v=j7mJuklrIxw) video
  * **2011-04-06:** BTstack used in Art projects:
    * [Mardi Gras Costume](http://thevillager.com/index411.html) with [technical details](http://arlduc.org/circuit/MobilePeripheralPack/MobilePeripheralPack.html)
    * [Counter during an Erik Satie - Vexations presentation](http://www.klaviervilla.org/forum/viewtopic.php?f=11&t=225)
  * **2011-03-24:** [Celeste: Bluetooth file sharing for iOS, at last.](http://getceleste.com) released
  * **2010-12-10:** [WeBe++ Bluetooth HID Mouse and Keyboard](http://www.weblooks.ch/webe-plus/) released
  * **2010-10-31:** [BTstack Keyboard on ATV2](http://www.youtube.com/watch?v=RIvaRD-Ugis)
  * **2010-08-08:** [BTstack on Stellaris Cortex-M3 ARM](http://www.youtube.com/watch?v=NlOcoKWuZhU) video
  * **2010-05-11:** [BTstack GPS](http://www.ringwald.ch/cydia/gps/) released and featured on [TUAW](http://www.tuaw.com/2010/05/11/add-gps-to-your-jailbroken-wifi-ipad-with-btstack-gps/)
  * **2010-01-24:** [BTstack for iPod Touch 1st Generation with external Bluetooth](iPodTouch1stGen.md) featured on [TUAW](http://www.tuaw.com/2010/01/24/found-footage-jailbreak-btstack-support-extended-to-1st-gen-ipo/)
  * **2010-01-08:** BTstack supports iPhone 2G
  * **2010-01-05:** iPhone-Mouse-Laser Keyboard integration featured on [TUAW](http://www.tuaw.com/2010/01/04/found-footage-iphone-mouse-integration), [engadget](http://www.engadget.com/2010/01/04/iphone-and-magic-mouse-linked-up-by-btstack-video) and [The BigMoney](http://www.thebigmoney.com/blogs/app-economy/2010/01/05/how-jailbreaking-drives-innovation-iphone)
  * **2010-01-03:** Happy New Year with [iPhone, Laser Keyboard and Magic Mouse](http://www.youtube.com/watch?v=WFWjVkzJb_s)
  * **2009-12-27:** BTstack Keyboard Tutorials in [TUAW](http://www.tuaw.com/2009/12/26/using-a-wireless-keyboard-with-an-iphone-using-btstack-keyboard/) and [iClarified](http://www.iclarified.com/entry/index.php?enid=6854)
  * **2009-12-24:** BTstack Keyboard in [TUAW](http://www.tuaw.com/2009/12/23/btstack-keyboard-jailbreak-app-provides-iphone-text-entry/), the [Wall Street Journal Blog](http://blogs.wsj.com/digits/2009/12/24/at-last-a-keyboard-for-some-iphones/), and [engadget](http://www.engadget.com/2009/12/24/want-to-connect-your-iphone-and-bluetooth-keyboard-theres-a-j/)
  * **2009-12-21:** [iPhone BTstack Keyboard v1.0](http://keyboard.ringwald.ch/Welcome.html) released in Cydia Store! [Demo version](http://apt.thebigboss.org/onepackage.php?bundleid=ch.ringwald.keyboarddemo&db=) at BigBoss
  * **2009-11-30:** [mame4iphone with WiiMote support](http://www.zodttd.com/wp/2009/11/wiimote-demonstration-video-with-mame4iphone/) by ZodTTD
  * **2009-11-28:** BTstack used for [Robot Control](http://www.youtube.com/watch?v=WKFECpQ8asI)
  * **2009-11-08:** BTstack version 0.1 released for iPhone/iPod touch, see [Status](Status.md), on [TUAW](http://www.tuaw.com/2009/11/10/found-footage-the-iphone-and-the-wiimote/)
  * **2009-11-08:** Updated [iPhone WiiMote demo ](http://www.youtube.com/watch?v=H98MZD67JRs) (Part 2)
  * **2009-08-13:** BTstack presentation at the Google Open Source Jam in Zurich [slides](http://btstack.ringwald.ch/BTstack-GoogleOpenSourceJam-20090813.pdf)
  * **2009-08-05:** YouTube [iPhone WiiMote demo ](http://www.youtube.com/watch?v=3FPHpMonoC8) video featured on:
    * [ubiq\_uitous communication, wearable and multimedia systems](http://www.ubiqkom.org/blog/?p=74)
    * [MAKE](http://blog.makezine.com/archive/2009/08/iphone_wiimote_together_at_last.html?CMP=OTC-0D6B48984890)
    * [engadget](http://www.engadget.com/2009/08/05/iphone-and-wiimote-brought-together-by-bluetooth/)
    * [gizmodo](http://gizmodo.com/5330582/the-wiimote-and-iphone-mix-like-peanut-butter-and-chocolate)
    * [Hack-a-Day](http://hackaday.com/2009/08/05/wiimote-iphone/)
    * and even in [GeekBrief.tv](http://www.mevio.com/episode/169139/GBTV+608+HD+Control+iPhone+with+a+WiiMote+New+Ustream+App+TomTom+Car)
  * **2009-02-13**: iPhone Bluetooth proof-of-concept featured on [ars technica](http://arstechnica.com/apple/news/2009/02/iphone-bluetooth-device-to-device-communications-achieved.ars)


[![](http://btstack.googlecode.com/svn/files/BTstack_architecture.png)](http://code.google.com/p/btstack/wiki/Architecture)