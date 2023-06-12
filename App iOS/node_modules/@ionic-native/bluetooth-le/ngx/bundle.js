'use strict';

Object.defineProperty(exports, '__esModule', { value: true });

var tslib = require('tslib');
var core$1 = require('@angular/core');
var core = require('@ionic-native/core');
require('rxjs');

exports.AndroidGattTransportMode = void 0;
(function (AndroidGattTransportMode) {
    /**
     * No preference of physical transport for GATT connections to remote dual-mode devices
     */
    AndroidGattTransportMode[AndroidGattTransportMode["TRANSPORT_AUTO"] = 0] = "TRANSPORT_AUTO";
    /**
     * Prefer BR/EDR transport for GATT connections to remote dual-mode devices
     */
    AndroidGattTransportMode[AndroidGattTransportMode["TRANSPORT_BREDR"] = 1] = "TRANSPORT_BREDR";
    /**
     * Prefer LE transport for GATT connections to remote dual-mode devices
     */
    AndroidGattTransportMode[AndroidGattTransportMode["TRANSPORT_LE"] = 2] = "TRANSPORT_LE";
})(exports.AndroidGattTransportMode || (exports.AndroidGattTransportMode = {}));
exports.BluetoothScanMode = void 0;
(function (BluetoothScanMode) {
    BluetoothScanMode[BluetoothScanMode["SCAN_MODE_OPPORTUNISTIC"] = -1] = "SCAN_MODE_OPPORTUNISTIC";
    BluetoothScanMode[BluetoothScanMode["SCAN_MODE_LOW_POWER"] = 0] = "SCAN_MODE_LOW_POWER";
    BluetoothScanMode[BluetoothScanMode["SCAN_MODE_BALANCED"] = 1] = "SCAN_MODE_BALANCED";
    BluetoothScanMode[BluetoothScanMode["SCAN_MODE_LOW_LATENCY"] = 2] = "SCAN_MODE_LOW_LATENCY";
})(exports.BluetoothScanMode || (exports.BluetoothScanMode = {}));
exports.BluetoothMatchMode = void 0;
(function (BluetoothMatchMode) {
    BluetoothMatchMode[BluetoothMatchMode["MATCH_MODE_AGRESSIVE"] = 1] = "MATCH_MODE_AGRESSIVE";
    BluetoothMatchMode[BluetoothMatchMode["MATCH_MODE_STICKY"] = 2] = "MATCH_MODE_STICKY";
})(exports.BluetoothMatchMode || (exports.BluetoothMatchMode = {}));
exports.BluetoothMatchNum = void 0;
(function (BluetoothMatchNum) {
    BluetoothMatchNum[BluetoothMatchNum["MATCH_NUM_ONE_ADVERTISEMENT"] = 1] = "MATCH_NUM_ONE_ADVERTISEMENT";
    BluetoothMatchNum[BluetoothMatchNum["MATCH_NUM_FEW_ADVERTISEMENT"] = 2] = "MATCH_NUM_FEW_ADVERTISEMENT";
    BluetoothMatchNum[BluetoothMatchNum["MATCH_NUM_MAX_ADVERTISEMENT"] = 3] = "MATCH_NUM_MAX_ADVERTISEMENT";
})(exports.BluetoothMatchNum || (exports.BluetoothMatchNum = {}));
exports.BluetoothCallbackType = void 0;
(function (BluetoothCallbackType) {
    BluetoothCallbackType[BluetoothCallbackType["CALLBACK_TYPE_ALL_MATCHES"] = 1] = "CALLBACK_TYPE_ALL_MATCHES";
    BluetoothCallbackType[BluetoothCallbackType["CALLBACK_TYPE_FIRST_MATCH"] = 2] = "CALLBACK_TYPE_FIRST_MATCH";
    BluetoothCallbackType[BluetoothCallbackType["CALLBACK_TYPE_MATCH_LOST"] = 4] = "CALLBACK_TYPE_MATCH_LOST";
})(exports.BluetoothCallbackType || (exports.BluetoothCallbackType = {}));
var BluetoothLE = /** @class */ (function (_super) {
    tslib.__extends(BluetoothLE, _super);
    function BluetoothLE() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    BluetoothLE.prototype.initialize = function (params) { return core.cordova(this, "initialize", { "successIndex": 0, "errorIndex": 2, "observable": true }, arguments); };
    BluetoothLE.prototype.enable = function () { return core.cordova(this, "enable", { "callbackOrder": "reverse", "sync": true }, arguments); };
    BluetoothLE.prototype.disable = function () { return core.cordova(this, "disable", { "callbackOrder": "reverse", "sync": true }, arguments); };
    BluetoothLE.prototype.getAdapterInfo = function () { return core.cordova(this, "getAdapterInfo", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.startScan = function (params) { return core.cordova(this, "startScan", { "callbackOrder": "reverse", "observable": true }, arguments); };
    BluetoothLE.prototype.stopScan = function () { return core.cordova(this, "stopScan", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.retrieveConnected = function (params) { return core.cordova(this, "retrieveConnected", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.bond = function (params) { return core.cordova(this, "bond", { "callbackOrder": "reverse", "observable": true }, arguments); };
    BluetoothLE.prototype.unbond = function (params) { return core.cordova(this, "unbond", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.connect = function (params) { return core.cordova(this, "connect", { "callbackOrder": "reverse", "observable": true }, arguments); };
    BluetoothLE.prototype.reconnect = function (params) { return core.cordova(this, "reconnect", { "callbackOrder": "reverse", "observable": true }, arguments); };
    BluetoothLE.prototype.disconnect = function (params) { return core.cordova(this, "disconnect", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.close = function (params) { return core.cordova(this, "close", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.discover = function (params) { return core.cordova(this, "discover", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.services = function (params) { return core.cordova(this, "services", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.characteristics = function (params) { return core.cordova(this, "characteristics", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.descriptors = function (params) { return core.cordova(this, "descriptors", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.read = function (params) { return core.cordova(this, "read", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.subscribe = function (params) { return core.cordova(this, "subscribe", { "callbackOrder": "reverse", "observable": true }, arguments); };
    BluetoothLE.prototype.unsubscribe = function (params) { return core.cordova(this, "unsubscribe", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.write = function (params) { return core.cordova(this, "write", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.writeQ = function (params) { return core.cordova(this, "writeQ", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.readDescriptor = function (params) { return core.cordova(this, "readDescriptor", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.writeDescriptor = function (params) { return core.cordova(this, "writeDescriptor", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.rssi = function (params) { return core.cordova(this, "rssi", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.mtu = function (params) { return core.cordova(this, "mtu", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.requestConnectionPriority = function (params) { return core.cordova(this, "requestConnectionPriority", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.isInitialized = function () { return core.cordova(this, "isInitialized", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.isEnabled = function () { return core.cordova(this, "isEnabled", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.isScanning = function () { return core.cordova(this, "isScanning", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.isBonded = function (params) { return core.cordova(this, "isBonded", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.wasConnected = function (params) { return core.cordova(this, "wasConnected", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.isConnected = function (params) { return core.cordova(this, "isConnected", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.isDiscovered = function (params) { return core.cordova(this, "isDiscovered", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.hasPermission = function () { return core.cordova(this, "hasPermission", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.requestPermission = function () { return core.cordova(this, "requestPermission", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.isLocationEnabled = function () { return core.cordova(this, "isLocationEnabled", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.requestLocation = function () { return core.cordova(this, "requestLocation", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.initializePeripheral = function (params) { return core.cordova(this, "initializePeripheral", { "callbackOrder": "reverse", "observable": true }, arguments); };
    BluetoothLE.prototype.addService = function (params) { return core.cordova(this, "addService", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.removeService = function (params) { return core.cordova(this, "removeService", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.removeAllServices = function () { return core.cordova(this, "removeAllServices", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.startAdvertising = function (params) { return core.cordova(this, "startAdvertising", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.stopAdvertising = function () { return core.cordova(this, "stopAdvertising", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.isAdvertising = function () { return core.cordova(this, "isAdvertising", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.respond = function (params) { return core.cordova(this, "respond", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.notify = function (params) { return core.cordova(this, "notify", { "callbackOrder": "reverse" }, arguments); };
    BluetoothLE.prototype.encodedStringToBytes = function (value) { return core.cordova(this, "encodedStringToBytes", { "sync": true }, arguments); };
    BluetoothLE.prototype.bytesToEncodedString = function (value) { return core.cordova(this, "bytesToEncodedString", { "sync": true }, arguments); };
    BluetoothLE.prototype.stringToBytes = function (value) { return core.cordova(this, "stringToBytes", { "sync": true }, arguments); };
    BluetoothLE.prototype.bytesToString = function (value) { return core.cordova(this, "bytesToString", { "sync": true }, arguments); };
    Object.defineProperty(BluetoothLE.prototype, "SCAN_MODE_OPPORTUNISTIC", {
        get: function () { return core.cordovaPropertyGet(this, "SCAN_MODE_OPPORTUNISTIC"); },
        set: function (value) { core.cordovaPropertySet(this, "SCAN_MODE_OPPORTUNISTIC", value); },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(BluetoothLE.prototype, "SCAN_MODE_LOW_POWER", {
        get: function () { return core.cordovaPropertyGet(this, "SCAN_MODE_LOW_POWER"); },
        set: function (value) { core.cordovaPropertySet(this, "SCAN_MODE_LOW_POWER", value); },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(BluetoothLE.prototype, "SCAN_MODE_BALANCED", {
        get: function () { return core.cordovaPropertyGet(this, "SCAN_MODE_BALANCED"); },
        set: function (value) { core.cordovaPropertySet(this, "SCAN_MODE_BALANCED", value); },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(BluetoothLE.prototype, "SCAN_MODE_LOW_LATENCY", {
        get: function () { return core.cordovaPropertyGet(this, "SCAN_MODE_LOW_LATENCY"); },
        set: function (value) { core.cordovaPropertySet(this, "SCAN_MODE_LOW_LATENCY", value); },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(BluetoothLE.prototype, "MATCH_MODE_AGGRESSIVE", {
        get: function () { return core.cordovaPropertyGet(this, "MATCH_MODE_AGGRESSIVE"); },
        set: function (value) { core.cordovaPropertySet(this, "MATCH_MODE_AGGRESSIVE", value); },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(BluetoothLE.prototype, "MATCH_MODE_STICKY", {
        get: function () { return core.cordovaPropertyGet(this, "MATCH_MODE_STICKY"); },
        set: function (value) { core.cordovaPropertySet(this, "MATCH_MODE_STICKY", value); },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(BluetoothLE.prototype, "MATCH_NUM_ONE_ADVERTISEMENT", {
        get: function () { return core.cordovaPropertyGet(this, "MATCH_NUM_ONE_ADVERTISEMENT"); },
        set: function (value) { core.cordovaPropertySet(this, "MATCH_NUM_ONE_ADVERTISEMENT", value); },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(BluetoothLE.prototype, "MATCH_NUM_FEW_ADVERTISEMENT", {
        get: function () { return core.cordovaPropertyGet(this, "MATCH_NUM_FEW_ADVERTISEMENT"); },
        set: function (value) { core.cordovaPropertySet(this, "MATCH_NUM_FEW_ADVERTISEMENT", value); },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(BluetoothLE.prototype, "MATCH_NUM_MAX_ADVERTISEMENT", {
        get: function () { return core.cordovaPropertyGet(this, "MATCH_NUM_MAX_ADVERTISEMENT"); },
        set: function (value) { core.cordovaPropertySet(this, "MATCH_NUM_MAX_ADVERTISEMENT", value); },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(BluetoothLE.prototype, "CALLBACK_TYPE_ALL_MATCHES", {
        get: function () { return core.cordovaPropertyGet(this, "CALLBACK_TYPE_ALL_MATCHES"); },
        set: function (value) { core.cordovaPropertySet(this, "CALLBACK_TYPE_ALL_MATCHES", value); },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(BluetoothLE.prototype, "CALLBACK_TYPE_FIRST_MATCH", {
        get: function () { return core.cordovaPropertyGet(this, "CALLBACK_TYPE_FIRST_MATCH"); },
        set: function (value) { core.cordovaPropertySet(this, "CALLBACK_TYPE_FIRST_MATCH", value); },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(BluetoothLE.prototype, "CALLBACK_TYPE_MATCH_LOST", {
        get: function () { return core.cordovaPropertyGet(this, "CALLBACK_TYPE_MATCH_LOST"); },
        set: function (value) { core.cordovaPropertySet(this, "CALLBACK_TYPE_MATCH_LOST", value); },
        enumerable: false,
        configurable: true
    });
    BluetoothLE.pluginName = "BluetoothLE";
    BluetoothLE.plugin = "cordova-plugin-bluetoothle";
    BluetoothLE.pluginRef = "bluetoothle";
    BluetoothLE.repo = "https://github.com/randdusing/cordova-plugin-bluetoothle";
    BluetoothLE.install = "ionic cordova plugin add cordova-plugin-bluetoothle";
    BluetoothLE.installVariables = [];
    BluetoothLE.platforms = ["Android", "iOS"];
    BluetoothLE.decorators = [
        { type: core$1.Injectable }
    ];
    return BluetoothLE;
}(core.IonicNativePlugin));

exports.BluetoothLE = BluetoothLE;
