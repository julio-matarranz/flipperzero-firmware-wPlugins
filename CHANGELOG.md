## New changes
* LFRFID: **Electra intercom protocol support** (Romania) (by @Leptopt1los | PR #750)
* NFC: Temp fix for `iso14443_4_layer_decode_block` crash
* NFC: CharlieCard parser (by @zacharyweiss)
* SubGHz: FAAC RC XT - add 0xB button code on arrow buttons for programming mode
* SubGHz: Add Manually - Sommer FM fixes
* SubGHz: Enabled tx-rx state on unused gpio pin by default (**external amp option was removed and is enabled by default now**)
* SubGHz: **Status output !TX/RX on the GDO2 CC1101 pin** (by @quen0n | PR #742)
* SubGHz: Reworked saved settings (by @xMasterX and @Willy-JL)
* Desktop: Fixes for animation unload (by @Willy-JL)
* iButton: Updated DS1420 for latest ibutton changes
* Misc: Allow no prefix usage of name_generator_make_detailed_datetime
* Misc: Allow setting view dispatcher callbacks to NULL
* Misc: Added `void` due to `-Wstrict-prototypes`
* Misc: Some code cleanup and proper log levels in nfc parsers
* Infrared: Allow external apps to use infrared settings (by @Willy-JL)
* JS & HAL: Various fixes and FURI_HAL_RANDOM_MAX define added (by @Willy-JL)
* JS: **BadUSB layout support** (by @Willy-JL)
* JS: New Modules `widget`, `vgm` and path globals (by @jamisonderek)
* Apps: Enhance Random Interval and Movement Functionality in HID Mouse Jiggler for Improved Stealth and Human-Like Behavior (by @gushmazuko | PR #746)
* Apps: NFC Magic - **Gen2 writing support, Gen4 NTAG password and PACK fixes** (by @Astrrra)
* Apps: MFKey - **fixed crashes**, add more free ram (by @noproto & @Willy-JL) 
* Apps: **Check out Apps updates by following** [this link](https://github.com/xMasterX/all-the-plugins/commits/dev)
* OFW PR 3616: NFC: Mf Desfire fix reading big files (by gornekich)
* OFW: iButton: fix crash when deleting some keys
* OFW: Desktop: cleanup error popups
* OFW: Troika parser visual fixes 
* OFW: Fix the retry/exit confirmation prompts in iButton
* OFW: nfc app: add legacy keys for plantain cards
* OFW: GUI: Fix array out of bounds in menu exit 
* OFW: add support for S(WTX) request in iso14443_4a_poller
* OFW: Mosgortrans parser output fixes
* OFW: BLE: Add GapPairingNone support 
* OFW: iButton new UI 
* OFW: FuriHal: add ADC API
* OFW: Mf Desfire multiple file rights support
* OFW: **Felica poller** (NFC-F)
* OFW: Desktop/Loader: Unload animations before loading FAPs
* OFW: JS Documentation
* OFW: **Update radio stack to v1.19.0**
* OFW: **Move crypto1 to helpers, add it to the public API**
* OFW: Explain RNG differences, add FURI_HAL_RANDOM_MAX
* OFW: Furi: Add "out of memory" and "malloc(0)" crash messages
* OFW: IR: Fix crash on duty_cycle=1
* OFW: **Desktop: ensure that animation is unloaded before app start (fixes some out of memory crashes)**
* OFW: Hide unlock with reader for MFU-C 
* OFW: fbt: fixed missing FBT_FAP_DEBUG_ELF_ROOT to dist env
* OFW: fbt: added -Wstrict-prototypes for main firmware
* OFW: Mifare Ultralight naming fix 
* OFW: IR: Remember OTG state
* OFW: Bad USB: fix crash when selecting a keyboard layout
* OFW: L1_Mods animation update : adding VGM visual 
* OFW: RFID Improvements 
* OFW: Fixed plugins and UI 
* OFW: **NFC: Fix mf desfire detect**
* OFW: infrared_transmit.h was missing `#pragma once`
* OFW: Show the wrong PIN Attempt count on the login screen
* OFW: SavedStruct: Introduce saved_struct_get_metadata
* OFW: JS CLI command
* OFW: Add ChromeOS Bad USB demo
* OFW: **Configurable Infrared TX output** (previous UL version is replaced with OFW version, new features added "AutoDetect" and saving settings)
* OFW: BadUSB: BLE, media keys, Fn/Globe key commands
* OFW: NFC: Slix privacy password reveal ->(was included in previous UL release) and **Desfire detect fix**
* OFW: github: additional pre-upload checks for doxygen workflow
* OFW: NFC UI fixes
* OFW: Gui: unicode support, new canvas API
* OFW: **Api Symbols: replace asserts with checks**
<br><br>
#### Known NFC post-refactor regressions list: 
- Mifare Mini clones reading is broken (original mini working fine) (OFW)
- NFC CLI was removed with refactoring (OFW) (will be back soon)
- Mifare Nested not ported to latest API yet, `unlshd-065` is the latest version on old NFC API that works with "nested app"

### Thanks to the UNLEASHED sponsors for supporting UNLEASHED changes!

### THANKS TO ALL RM SPONSORS FOR BEING AWESOME!

# MOST OF ALL, THANK YOU TO THE FLIPPER ZERO COMMUNITY THAT KEEPS GROWING OUR PROJECT!
