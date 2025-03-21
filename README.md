# Monero Wallet for ESP32C3

WIP :P

https://emn178.github.io/online-tools/keccak_256.html
https://www.getmonero.org/library/MoneroAddressesCheatsheet20201206.pdf
https://gitlab.demlabs.net/cellframe/cellframe-sdk/-/blob/c83fbc812966aaf675c3f499c19c21dd888ea94d/3rdparty/monero_crypto/crypto_ops_builder/crypto-ops-old.c
https://github.com/rohanrhu/MoneroSharp/blob/master/MoneroSharp/MoneroSharp/MoneroAccount.cs
https://xmr.llcoins.net/addresstests.html
https://appdevtools.com/base58-encoder-decoder
https://github.com/monero-ecosystem/monero-python/tree/master/monero

7E8FB15A382D9977E08822DA8CCC652ED8D6353E39A1A6A49C246A9C996E71B3

## warning, this locks esp32c3 forever!
espefuse.py --chip esp32c3 --port /dev/ttyACM28 burn_efuse DIS_DOWNLOAD_MODE
espefuse.py --chip esp32c3 --port /dev/ttyACM28 burn_efuse DIS_USB_SERIAL_JTAG
espefuse.py --chip esp32c3 --port /dev/ttyACM28 burn_efuse ABS_DONE_0
espefuse.py --chip esp32c3 --port /dev/ttyACM28 burn_efuse ABS_DONE_1
espefuse.py --chip esp32c3 --port /dev/ttyACM28 burn_efuse BLOCK_WR_DIS
